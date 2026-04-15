#pragma once

#include <QObject>
#include <qqmlintegration.h>

#include <QUrl>


class WindowManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString FileType READ getFileType WRITE setFileType NOTIFY FileTypeChanged)
    Q_PROPERTY(QUrl URL READ getURL WRITE setURL NOTIFY URLChanged)
public:
    explicit WindowManager(QObject* parent = nullptr);

public:
    QUrl getURL() const;
    void setURL(const QUrl& URL);
    Q_SIGNAL void URLChanged();

    QString getFileType() const;
    void setFileType(const QString& FileType);
    Q_SIGNAL void FileTypeChanged();

private:
    QUrl m_URL;

    QString m_FileType = QStringLiteral("Placeholder");
};
