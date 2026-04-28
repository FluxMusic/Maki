// SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QQuickImageProvider>
#include <QPixmap>

class MakiImageProvider : public QQuickImageProvider
{
public:
    MakiImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        Q_UNUSED(size)
        Q_UNUSED(requestedSize)

        if (id == QStringLiteral("fallback")) {
            return m_pixmap;
        }

        if (id.contains(QStringLiteral("audioCover"))) {
            return m_audioCover;
        }

        int page = id.toInt();

        if (page == 0 || page >= static_cast<int>(m_documentImages.size() + 1)) {
            return QPixmap();
        } else {
            return m_documentImages[page - 1];
        }
    }

    void setPixmap(const QPixmap &pixmap)
    {
        m_pixmap = pixmap;
    }

    void setAudioCover(const QPixmap &pixmap)
    {
        m_audioCover = pixmap;
    }

    void setDocumentImages(const std::vector<QImage> documentImages)
    {
        m_documentImages.clear();

        for (QImage image : documentImages) {
            m_documentImages.push_back(QPixmap::fromImage(image));
        }
    }

private:
    QPixmap m_pixmap;

    QPixmap m_audioCover;

    std::vector<QPixmap> m_documentImages;
};
