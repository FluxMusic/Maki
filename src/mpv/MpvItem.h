#pragma once

#include <MpvAbstractItem>

class MpvItem : public MpvAbstractItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit MpvItem(QQuickItem* parent = nullptr);

    Q_INVOKABLE void loadFile(const QUrl& url);

    Q_PROPERTY(int videoWidth READ getVideoWidth NOTIFY videoWidthChanged)
    int getVideoWidth() const;
    Q_SIGNAL void videoWidthChanged();

    Q_PROPERTY(int videoHeight READ getVideoHeight NOTIFY videoHeightChanged)
    int getVideoHeight() const;
    Q_SIGNAL void videoHeightChanged();

    Q_SIGNAL void videoReconfig();

private:

    void onPropertyChanged(const QString& property, const QVariant& value);

private:

    int m_VideoWidth { 1920 };
    int m_VideoHeight { 1080 };
};