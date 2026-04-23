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
    
    Q_PROPERTY(bool pause READ getPause WRITE setPause NOTIFY pauseChanged)
    bool getPause() const;
    void setPause(bool pause);
    Q_SIGNAL void pauseChanged();

    Q_PROPERTY(bool mute READ getMute WRITE setMute NOTIFY muteChanged)
    bool getMute() const;
    void setMute(bool mute);
    Q_SIGNAL void muteChanged();

    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    int getVolume() const;
    void setVolume(int volume);
    Q_SIGNAL void volumeChanged();
    
    Q_PROPERTY(double position READ getPosition WRITE setPosition NOTIFY positionChanged)
    double getPosition() const;
    void setPosition(double position);
    Q_SIGNAL void positionChanged();
    
    Q_PROPERTY(double duration READ getDuration NOTIFY durationChanged)
    double getDuration() const;
    Q_SIGNAL void durationChanged();

private:

    void onPropertyChanged(const QString& property, const QVariant& value);

private:

    int m_VideoWidth  { 1920 };
    int m_VideoHeight { 1080 };

    bool m_Pause { true };
    bool m_Mute  { false };

    int m_Volume { 100 };

    double m_Position { 0.0 };
    double m_Duration { 0.0 };
};