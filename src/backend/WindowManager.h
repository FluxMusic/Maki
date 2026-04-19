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

    //TODO: Do I really need Writing access?
    Q_PROPERTY(QString FileType READ getFileType WRITE setFileType NOTIFY FileTypeChanged)
    Q_PROPERTY(QUrl URL READ getURL WRITE setURL NOTIFY URLChanged)
    Q_PROPERTY(QUrl FallbackURL READ getFallbackURL NOTIFY FallbackURLChanged)
    Q_PROPERTY(QSize WindowSize READ getWindowSize NOTIFY WindowSizeChanged)
    Q_PROPERTY(QString FileText READ getFileText NOTIFY FileTextChanged)
    Q_PROPERTY(int PageNum READ getPageNum NOTIFY PageNumChanged)
    
public:
    explicit WindowManager(QObject* parent = nullptr);

    void initApp(QApplication* App);

    void setImageProvider(MakiImageProvider* Provider);

public:
    QSize getWindowSize() const;
    Q_SIGNAL void WindowSizeChanged();

    QUrl getURL() const;
    void setURL(const QUrl& URL);
    Q_SIGNAL void URLChanged();

    QUrl getFallbackURL() const;
    Q_SIGNAL void FallbackURLChanged();

    QString getFileType() const;
    void setFileType(const QString& FileType);
    Q_SIGNAL void FileTypeChanged();

    QString getFileText() const;
    Q_SIGNAL void FileTextChanged();

    int getPageNum() const;
    Q_SIGNAL void PageNumChanged();

    Q_INVOKABLE void openInDefaultApp();
private:
    QApplication* m_pApp { nullptr };

    QSize m_WindowSize;

    QUrl m_URL;
    QUrl m_FallbackURL;

    QString m_FileType = QStringLiteral("Placeholder");

    QString m_FileText = QStringLiteral("Placeholder");

    MakiImageProvider* m_pImageProvider { nullptr };

    int m_PageNum { 0 };
};
