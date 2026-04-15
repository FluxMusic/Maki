#include "WindowManager.h"

#include <QMimeDatabase>
#include <QMimeType>

#include <QImageReader>

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

        qWarning() << "width: " << imageSize.width();
        qWarning() << "height: " << imageSize.height();
        
        //TODO: Currently hardcoded, fix later
        while (imageSize.width() >= 1920 || imageSize.height() >= 1080)
        {
            imageSize /= 2;
        }
        
        qWarning() << "width: " << imageSize.width();
        qWarning() << "height: " << imageSize.height();

        setWindowSize(imageSize);
        
        setFileType(QStringLiteral("image"));
    }
    else
    {
        QIcon icon = QIcon::fromTheme(mime.iconName());

        if (m_pImageProvider)
        {
            //TODO: Should this be in a config?
            m_pImageProvider->setPixmap(icon.pixmap(512,512));

            setWindowSize(QSize(512, 512));

            m_URL = QUrl(QStringLiteral("image://Maki/preview"));
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
