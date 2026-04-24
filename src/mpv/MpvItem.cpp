#include "MpvItem.h"

#include <MpvController>

MpvItem::MpvItem(QQuickItem* parent)
    : MpvAbstractItem(parent)
{
    Q_EMIT observeProperty(QStringLiteral("width"), MPV_FORMAT_NODE);
    Q_EMIT observeProperty(QStringLiteral("height"), MPV_FORMAT_NODE);
    Q_EMIT observeProperty(QStringLiteral("time-pos"), MPV_FORMAT_DOUBLE);
    Q_EMIT observeProperty(QStringLiteral("duration"), MPV_FORMAT_DOUBLE);
    Q_EMIT observeProperty(QStringLiteral("time-start"), MPV_FORMAT_DOUBLE);

    connect(mpvController(), &MpvController::propertyChanged,
            this,            &MpvItem::onPropertyChanged, 
            Qt::QueuedConnection);

    connect(mpvController(), &MpvController::videoReconfig,
            this,            &MpvItem::videoReconfig, 
            Qt::QueuedConnection);

    Q_EMIT setProperty(QStringLiteral("vo"), QStringLiteral("libmpv"));
    Q_EMIT setProperty(QStringLiteral("hwdec"), QStringLiteral("auto-safe"));
}

void MpvItem::loadFile(const QUrl& url)
{
    // Q_EMIT setProperty(QStringLiteral("keep-open"), QStringLiteral("always"));

    // setPropertyBlocking(QStringLiteral("start"), QString::number(0));

    setPropertyBlocking(QStringLiteral("mute"), true);
    
    Q_EMIT command(QStringList() << QStringLiteral("loadfile") << url.toLocalFile());
    Q_EMIT setProperty(QStringLiteral("pause"), m_Pause);

    setPropertyBlocking(QStringLiteral("volume"), m_Volume);
    setPropertyBlocking(QStringLiteral("mute"), m_Mute);
}

int MpvItem::getVideoWidth() const
{
    return m_VideoWidth;
}

int MpvItem::getVideoHeight() const
{
    return m_VideoHeight;
}

bool MpvItem::getPause() const
{
    return m_Pause;
}

void MpvItem::setPause(bool pause)
{
    if (pause == m_Pause)
    {
        return;
    }

    m_Pause = pause;
    Q_EMIT setProperty(QStringLiteral("pause"), pause);
    Q_EMIT pauseChanged();
}

bool MpvItem::getMute() const
{
    return m_Mute;
}

void MpvItem::setMute(bool mute)
{
    if (mute == m_Mute)
    {
        return;
    }

    m_Mute = mute;
    Q_EMIT setProperty(QStringLiteral("mute"), mute);
    Q_EMIT muteChanged();
}

int MpvItem::getVolume() const
{
    return m_Volume;
}

void MpvItem::setVolume(int volume)
{
    if (volume == m_Volume)
    {
        return;
    }
    
    m_Volume = volume;
    Q_EMIT setProperty(QStringLiteral("volume"), volume);
    Q_EMIT volumeChanged();
}

double MpvItem::getPosition() const
{
    return m_Position;
}

void MpvItem::setPosition(double position)
{
    if (m_Position == position)
    {
        return;
    }
    
    m_Position = position;
    Q_EMIT setProperty(QStringLiteral("time-pos"), position);
    Q_EMIT positionChanged();
}

double MpvItem::getDuration() const
{
    return m_Duration;
}

QString MpvItem::getCurrentTimecode() const
{
    return m_CurrentTimecode;
}

QString MpvItem::getEndTimecode() const
{
    return m_EndTimecode;
}

void MpvItem::onPropertyChanged(const QString& property, const QVariant& value)
{
    if (property == QStringLiteral("width"))
    {
        m_VideoWidth = value.toInt();
        Q_EMIT videoWidthChanged();
    }
    else if (property == QStringLiteral("height"))
    {
        m_VideoHeight = value.toInt();
        Q_EMIT videoHeightChanged();
    }
    else if (property == QStringLiteral("time-pos"))
    {
        m_Position = value.toDouble();
        m_CurrentTimecode = secondsToTimecode(value.toDouble());
        Q_EMIT currentTimecodeChanged();
        Q_EMIT positionChanged();
    }
    else if (property == QStringLiteral("duration"))
    {
        m_Duration = value.toDouble();
        m_EndTimecode = secondsToTimecode(m_Duration);
        Q_EMIT durationChanged();
        Q_EMIT endTimecodeChanged();
    }
}

QString MpvItem::secondsToTimecode(double seconds)
{
    int secondCount = std::floor(std::fmod(seconds, 60));
    int minuteCount = std::floor(std::fmod(seconds/60, 60));
    int hourCount   = std::floor(seconds / 3600);

    int hourDigits  = std::max(2, static_cast<int>(QString::number(hourCount).length()));

    return QString(QStringLiteral("%1:%2:%3"))
        .arg(hourCount,   hourDigits, 10, QLatin1Char('0'))
        .arg(minuteCount,          2, 10, QLatin1Char('0'))
        .arg(secondCount,          2, 10, QLatin1Char('0'));
}
