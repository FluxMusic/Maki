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

WindowManager::WindowManager(QObject *parent)
    : QObject(parent)
{
}

void WindowManager::initApp(QApplication *app)
{
    m_app = app;
}

void WindowManager::setImageProvider(MakiImageProvider *provider)
{
    m_imageProvider = provider;
}

QSize WindowManager::getWindowSize() const
{
    return m_windowSize;
}

QUrl WindowManager::getURL() const
{
    return m_url;
}

void WindowManager::setURL(const QUrl &url)
{
    m_url = url;

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForUrl(url);

    if (mime.name().startsWith(QStringLiteral("image/"))) {
        setFileType(QStringLiteral("image"));
    } else if (mime.name().startsWith(QStringLiteral("text/"))) {
        QFile file(url.toLocalFile());

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            m_fileText = QString::fromUtf8(file.readAll());
            Q_EMIT fileTextChanged();
        }

        setFileType(QStringLiteral("text"));
    } else if (mime.name().startsWith(QStringLiteral("audio/"))) {
        TagLib::MPEG::File file(url.toLocalFile().toUtf8().constData());

        if (file.isValid()) {
            // Extract all other metadata here

            // Extract the cover art
            bool imageFound = false;
            if (file.ID3v2Tag()) {
                auto frames = file.ID3v2Tag()->frameListMap()["APIC"];
                if (!frames.isEmpty()) {
                    auto *frame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());
                    if (frame) {
                        QImage cover;
                        cover.loadFromData(reinterpret_cast<const uchar *>(frame->picture().data()), frame->picture().size());
                        if (!cover.isNull()) {
                            if (m_imageProvider)
                                m_imageProvider->setAudioCover(QPixmap::fromImage(cover));
                            m_audioCoverURL = QUrl(QStringLiteral("image://Maki/audioCover?") + QString::number(QDateTime::currentMSecsSinceEpoch()));
                            Q_EMIT audioCoverURLChanged();

                            imageFound = true;
                        }
                    }
                }
            }

            if (!imageFound) {
                QIcon icon = QIcon::fromTheme(mime.iconName());

                if (m_imageProvider)
                    m_imageProvider->setAudioCover(icon.pixmap(512, 512));
                m_audioCoverURL = QUrl(QStringLiteral("image://Maki/audioCover?") + QString::number(QDateTime::currentMSecsSinceEpoch()));
                Q_EMIT audioCoverURLChanged();
                qWarning() << "fall back to generic";
            }
        }

        setFileType(QStringLiteral("audio"));
    } else if (mime.name().startsWith(QStringLiteral("video/"))) {
        setFileType(QStringLiteral("video"));
    } else if (mime.name() == QStringLiteral("application/pdf")) {
        std::unique_ptr<Poppler::Document> doc = Poppler::Document::load(url.toLocalFile());

        if (!doc) {
            return;
        }

        doc->setRenderHint(Poppler::Document::RenderHint::Antialiasing, true);
        doc->setRenderHint(Poppler::Document::RenderHint::TextAntialiasing, true);
        doc->setRenderHint(Poppler::Document::RenderHint::ThinLineSolid, true);

        int numPages = doc->numPages();
        m_pageNum = numPages;

        std::vector<QImage> pageImages;

        pageImages.reserve(numPages);

        for (int i = 0; i < numPages; i++) {
            std::unique_ptr<Poppler::Page> page = doc->page(i);

            if (page) {
                // TODO: DPI as config?
                pageImages.push_back(page->renderToImage(72, 72));
            }
        }

        // TODO: Currently sets the window size to the first page's size
        //       But if there is ever a bigger page in the document
        //       It will clip. Maybe set the size to the dimensions
        //       of the biggest pages? So the width will be the max
        //       width of all the pages and the height as well
        m_windowSize = pageImages[0].size();
        Q_EMIT windowSizeChanged();

        if (m_imageProvider) {
            m_imageProvider->setDocumentImages(pageImages);
        }

        Q_EMIT pageNumChanged();

        setFileType(QStringLiteral("pdf"));
    }
    else
    {
        QIcon icon = QIcon::fromTheme(mime.iconName());

        if (m_imageProvider) {
            // TODO: Should this be in a config?
            m_imageProvider->setPixmap(icon.pixmap(512, 512));

            m_fallbackURL = QUrl(QStringLiteral("image://Maki/fallback"));
            Q_EMIT fallbackURLChanged();
        }

        setFileType(QStringLiteral("None"));
    }

    Q_EMIT urlChanged();
    Q_EMIT fileNameChanged();
}

QUrl WindowManager::getFallbackURL() const 
{
    return m_fallbackURL;
}

QUrl WindowManager::getAudioCoverURL() const
{
    return m_audioCoverURL;
}

QString WindowManager::getFileName() const
{
    return m_url.fileName();
}

QString WindowManager::getFileType() const
{
    return m_fileType;
}

void WindowManager::setFileType(const QString &fileType)
{
    m_fileType = fileType;
    Q_EMIT fileTypeChanged();
}

QString WindowManager::getFileText() const
{
    return m_fileText;
}

int WindowManager::getPageNum() const
{
    return m_pageNum;
}

void WindowManager::openInDefaultApp()
{
    auto *job = new KIO::OpenUrlJob(m_url);
    job->setUiDelegate(KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, nullptr));

    connect(job, &KJob::result, this, [this](KJob *job) {
        if (job->error() == 0)
        {
            m_app->quit();
        }
    });

    job->start();
}
