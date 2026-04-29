// SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QApplication>
#include <QObject>
#include <qqmlintegration.h>
#include <QQuickTextDocument>
#include <QSize>

#include <QUrl>
#include "ImageProvider.h"

class WindowManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString fileType READ getFileType WRITE setFileType NOTIFY fileTypeChanged)
    Q_PROPERTY(QUrl url READ getURL WRITE setURL NOTIFY urlChanged)
    Q_PROPERTY(QUrl fallbackURL READ getFallbackURL NOTIFY fallbackURLChanged)
    Q_PROPERTY(QUrl audioCoverURL READ getAudioCoverURL NOTIFY audioCoverURLChanged)
    Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QSize windowSize READ getWindowSize NOTIFY windowSizeChanged)
    Q_PROPERTY(QString fileText READ getFileText NOTIFY fileTextChanged)
    Q_PROPERTY(int pageNum READ getPageNum NOTIFY pageNumChanged)

public:
    explicit WindowManager(QObject *parent = nullptr);

    void initApp(QApplication *app);

    void setImageProvider(MakiImageProvider *provider);

public:
    QSize getWindowSize() const;
    Q_SIGNAL void windowSizeChanged();

    QUrl getURL() const;
    void setURL(const QUrl &url);
    Q_SIGNAL void urlChanged();

    QUrl getFallbackURL() const;
    Q_SIGNAL void fallbackURLChanged();

    QUrl getAudioCoverURL() const;
    Q_SIGNAL void audioCoverURLChanged();

    QString getFileName() const;
    Q_SIGNAL void fileNameChanged();

    QString getFileType() const;
    void setFileType(const QString &fileType);
    Q_SIGNAL void fileTypeChanged();

    QString getFileText() const;
    Q_SIGNAL void fileTextChanged();

    int getPageNum() const;
    Q_SIGNAL void pageNumChanged();

    Q_INVOKABLE void openInDefaultApp();

private:
    QApplication *m_app{nullptr};

    QSize m_windowSize;

    QUrl m_url;
    QUrl m_fallbackURL;
    QUrl m_audioCoverURL;

    QString m_fileType{QStringLiteral("Placeholder")};

    QString m_fileText{QStringLiteral("Placeholder")};

    MakiImageProvider *m_imageProvider{nullptr};

    int m_pageNum{0};
};
