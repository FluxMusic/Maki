#include "WindowManager.h"

#include <poppler-qt6.h>

#include <QMimeDatabase>
#include <QMimeType>

#include <QImageReader>

#include <QFile>

#include <QIcon>

WindowManager::WindowManager(QObject* parent)
: QObject(parent)
{}

void WindowManager::setImageProvider(MakiImageProvider* Provider)
{
    m_pImageProvider = Provider;
}

QSize WindowManager::getWindowSize() const
{
    return m_WindowSize;
}

void WindowManager::setWindowSize(const QSize& WindowSize)
{
    m_WindowSize = WindowSize;
    Q_EMIT WindowSizeChanged();
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
        QImageReader reader(URL.toLocalFile());
        QSize imageSize = reader.size();
        
        //TODO: Currently hardcoded, fix later
        while (imageSize.width() >= 1920 || imageSize.height() >= 1080)
        {
            imageSize /= 2;
        }

        setWindowSize(imageSize);
        
        setFileType(QStringLiteral("image"));
    }
    else if (mime.name().startsWith(QStringLiteral("text/")))
    {
        setWindowSize(QSize(300, 400));

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
                //TODO: PPI as config?
                pageImages.push_back(page->renderToImage(300, 300));
            }
        }

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

            setWindowSize(QSize(512, 512));

            m_URL = QUrl(QStringLiteral("image://Maki/fallback"));
        }

        setFileType(QStringLiteral("None"));
    }
    
    Q_EMIT URLChanged();
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
