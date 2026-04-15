#include "WindowManager.h"

WindowManager::WindowManager(QObject* parent)
: QObject(parent)
{}

QString WindowManager::getURL() const
{
    return m_URL;
}

void WindowManager::setURL(const QString& URL)
{
    m_URL = URL;
    Q_EMIT URLChanged();
}
