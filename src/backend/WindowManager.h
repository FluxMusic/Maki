#pragma once

#include <QObject>
#include <qqmlintegration.h>

#include <QSize>

#include <QUrl>
#include "ImageProvider.h"


class WindowManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    //TODO: Do I really need Writing access?
    Q_PROPERTY(QString FileType READ getFileType WRITE setFileType NOTIFY FileTypeChanged)
    Q_PROPERTY(QUrl URL READ getURL WRITE setURL NOTIFY URLChanged)
    Q_PROPERTY(QSize WindowSize READ getWindowSize WRITE setWindowSize NOTIFY WindowSizeChanged)
public:
    explicit WindowManager(QObject* parent = nullptr);

    void setImageProvider(MakiImageProvider* Provider);

public:
    QSize getWindowSize() const;
    void setWindowSize(const QSize& WindowSize);
    Q_SIGNAL void WindowSizeChanged();

    QUrl getURL() const;
    void setURL(const QUrl& URL);
    Q_SIGNAL void URLChanged();

    QString getFileType() const;
    void setFileType(const QString& FileType);
    Q_SIGNAL void FileTypeChanged();

private:
    QSize m_WindowSize;

    QUrl m_URL;

    QString m_FileType = QStringLiteral("Placeholder");

    MakiImageProvider* m_pImageProvider { nullptr };
};
