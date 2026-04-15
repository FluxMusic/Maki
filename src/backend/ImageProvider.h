#pragma once

#include <QQuickImageProvider>
#include <QPixmap>

class MakiImageProvider : public QQuickImageProvider
{
public:
    MakiImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {}

    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override
    {
        Q_UNUSED(id)
        Q_UNUSED(size)
        Q_UNUSED(requestedSize)
        
        return m_Pixmap;
    }

    void setPixmap(const QPixmap& Pixmap)
    {
        m_Pixmap = Pixmap;
    }

private:

    QPixmap m_Pixmap;
};
