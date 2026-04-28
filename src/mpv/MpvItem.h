// SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <MpvAbstractItem>

class MpvItem : public MpvAbstractItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit MpvItem(QQuickItem *parent = nullptr);

    Q_INVOKABLE void loadFile(const QUrl &url);

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

    Q_PROPERTY(QString currentTimecode READ getCurrentTimecode NOTIFY currentTimecodeChanged)
    QString getCurrentTimecode() const;
    Q_SIGNAL void currentTimecodeChanged();

    Q_PROPERTY(QString endTimecode READ getEndTimecode NOTIFY endTimecodeChanged)
    QString getEndTimecode() const;
    Q_SIGNAL void endTimecodeChanged();

private:
    void onPropertyChanged(const QString &property, const QVariant &value);

    QString secondsToTimecode(double seconds);

private:
    int m_videoWidth{1920};
    int m_videoHeight{1080};

    bool m_pause{true};
    bool m_mute{false};

    int m_volume{100};

    double m_position{0.0};
    double m_duration{0.0};

    QString m_currentTimecode{QStringLiteral("00:00")};
    QString m_endTimecode{QStringLiteral("00:00")};
};