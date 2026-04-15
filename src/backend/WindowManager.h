#pragma once

#include <QObject>
#include <qqmlintegration.h>


class WindowManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString URL READ getURL WRITE setURL NOTIFY URLChanged)
public:
    explicit WindowManager(QObject* parent = nullptr);

public:
    QString getURL() const;
    void setURL(const QString& URL);
    Q_SIGNAL void URLChanged();

private:
    QString m_URL = QStringLiteral("Placeholder");
};
