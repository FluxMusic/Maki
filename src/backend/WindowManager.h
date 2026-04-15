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
public:
    explicit WindowManager(QObject* parent = nullptr);

public:

    void setURL(const QUrl& URL);

    QString getFileType() const;
    void setFileType(const QString& FileType);
    Q_SIGNAL void FileTypeChanged();

private:
    QUrl m_URL;

    QString m_FileType = QStringLiteral("Placeholder");
};
