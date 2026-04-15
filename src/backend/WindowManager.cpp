#include "WindowManager.h"

#include <QMimeDatabase>
#include <QMimeType>

WindowManager::WindowManager(QObject* parent)
: QObject(parent)
{}

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
    else
    {
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
