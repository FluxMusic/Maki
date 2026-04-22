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
        
        if (id == QStringLiteral("audioCover"))
        {
            return m_AudioCover;
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

    void setAudioCover(const QPixmap& Pixmap)
    {
        m_AudioCover = Pixmap;
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

    QPixmap m_AudioCover;

    std::vector<QPixmap> m_DocumentImages;
};
