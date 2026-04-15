#include "WindowManager.h"

#include <QMimeDatabase>
#include <QMimeType>

WindowManager::WindowManager(QObject* parent)
: QObject(parent)
{}

void WindowManager::setURL(const QUrl& URL)
{
    m_URL = URL;

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForUrl(URL);

    setFileType(mime.name());
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