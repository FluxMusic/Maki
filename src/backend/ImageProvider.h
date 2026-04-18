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
        Q_UNUSED(size)
        Q_UNUSED(requestedSize)

        if (id == QStringLiteral("fallback"))
        {
            return m_Pixmap;
        }
        
        int page = id.toInt();

        if (page == 0 || page >= static_cast<int>(m_DocumentImages.size() + 1)) return QPixmap();
        else
        {
            return m_DocumentImages[page - 1];
        }
    }

    void setPixmap(const QPixmap& Pixmap)
    {
        m_Pixmap = Pixmap;
    }

    void setDocumentImages(const std::vector<QImage> documentImages)
    {
        m_DocumentImages.clear();

        for (QImage image : documentImages)
        {
            m_DocumentImages.push_back(QPixmap::fromImage(image));
        }
    }

private:

    QPixmap m_Pixmap;

    std::vector<QPixmap> m_DocumentImages;
};
