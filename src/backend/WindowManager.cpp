#include "WindowManager.h"

#include <KIO/OpenUrlJob>
#include <KIO/JobUiDelegateFactory>

#include <poppler-qt6.h>

#include <QFile>

#include <QIcon>

#include <QImageReader>

#include <QMimeDatabase>
#include <QMimeType>

#include <QTimer>

#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

WindowManager::WindowManager(QObject* parent)
: QObject(parent)
{}

void WindowManager::initApp(QApplication* App)
{
    m_pApp = App;
}

void WindowManager::setImageProvider(MakiImageProvider* Provider)
{
    m_pImageProvider = Provider;
}

QSize WindowManager::getWindowSize() const
{
    return m_WindowSize;
}

QUrl WindowManager::getURL() const
{
    return m_URL;
}

void WindowManager::setURL(const QUrl& URL)
{
    m_URL = URL;

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForUrl(URL);

    if (mime.name().startsWith(QStringLiteral("image/")))
    {
        setFileType(QStringLiteral("image"));
    }
    else if (mime.name().startsWith(QStringLiteral("text/")))
    {

        QFile file(URL.toLocalFile());

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            m_FileText = QString::fromUtf8(file.readAll());
            Q_EMIT FileTextChanged();
        }

        setFileType(QStringLiteral("text"));
    }
    else if (mime.name().startsWith(QStringLiteral("audio/")))
    {
        TagLib::MPEG::File file(URL.toLocalFile().toUtf8().constData());

        if (file.isValid())
        {
            //Extract all other metadata here

            //Extract the cover art
            bool imageFound = false;
            if (file.ID3v2Tag())
            {
                auto frames = file.ID3v2Tag()->frameListMap()["APIC"];
                if (!frames.isEmpty())
                {
                    auto* frame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(frames.front());
                    if (frame)
                    {
                        QImage cover;
                        cover.loadFromData(reinterpret_cast<const uchar*>(frame->picture().data()), frame->picture().size());
                        if (!cover.isNull())
                        {
                            if (m_pImageProvider) m_pImageProvider->setAudioCover(QPixmap::fromImage(cover));
                            m_AudioCoverURL = QUrl(QStringLiteral("image://Maki/audioCover"));
                            Q_EMIT AudioCoverURLChanged();

                            imageFound = true;
                        }
                    }
                }
            }

            if (!imageFound)
            {
                QIcon icon = QIcon::fromTheme(mime.iconName());
        
                if (m_pImageProvider) m_pImageProvider->setAudioCover(icon.pixmap(512,512));
                m_AudioCoverURL = QUrl(QStringLiteral("image://Maki/audioCover"));
                Q_EMIT AudioCoverURLChanged();
                qWarning() << "fall back to generic";
            }
            
            
        }
        

        setFileType(QStringLiteral("audio"));
    }
    else if (mime.name().startsWith(QStringLiteral("video/")))
    {
        setFileType(QStringLiteral("video"));
    }
    else if (mime.name() == QStringLiteral("application/pdf"))
    {
        std::unique_ptr<Poppler::Document> doc = Poppler::Document::load(URL.toLocalFile());

        if (!doc) return;

        int numPages = doc->numPages();
        m_PageNum = numPages;

        std::vector<QImage> pageImages;

        pageImages.reserve(numPages);

        for (int i = 0; i < numPages; i++)
        {
            std::unique_ptr<Poppler::Page> page = doc->page(i);

            if (page) 
            {
                //TODO: DPI as config?
                pageImages.push_back(page->renderToImage(720, 720));
            }
        }

        //TODO: Currently sets the window size to the first page's size
        //      But if there is ever a bigger page in the document
        //      It will clip. Maybe set the size to the dimensions 
        //      of the biggest pages? So the width will be the max
        //      width of all the pages and the height as well
        m_WindowSize = pageImages[0].size();
        Q_EMIT WindowSizeChanged();

        if (m_pImageProvider)
        {
            m_pImageProvider->setDocumentImages(pageImages);
        }
        
        Q_EMIT PageNumChanged();

        setFileType(QStringLiteral("pdf"));
    }
    else
    {
        QIcon icon = QIcon::fromTheme(mime.iconName());

        if (m_pImageProvider)
        {
            //TODO: Should this be in a config?
            m_pImageProvider->setPixmap(icon.pixmap(512,512));

            m_FallbackURL = QUrl(QStringLiteral("image://Maki/fallback"));
            Q_EMIT FallbackURLChanged();
        }

        setFileType(QStringLiteral("None"));
    }
    
    Q_EMIT URLChanged();
    Q_EMIT FileNameChanged();
}

QUrl WindowManager::getFallbackURL() const
{
    return m_FallbackURL;
}

QUrl WindowManager::getAudioCoverURL() const
{
    return m_AudioCoverURL;
}

QString WindowManager::getFileName() const
{
    return m_URL.fileName();
}

QString WindowManager::getFileType() const
{
    return m_FileType;
}

void WindowManager::setFileType(const QString& FileType)
{
    m_FileType = FileType;
    Q_EMIT FileTypeChanged();
}

QString WindowManager::getFileText() const
{
    return m_FileText;
}

int WindowManager::getPageNum() const
{
    return m_PageNum;
}

void WindowManager::openInDefaultApp()
{
    auto* job = new KIO::OpenUrlJob(m_URL);
    job->setUiDelegate(KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, nullptr));

    connect(job, &KJob::result, this, [this](KJob* job)
    {
        if (job->error() == 0)
        {
            m_pApp->quit();
        }
        
    });

    job->start();
}
