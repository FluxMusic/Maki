#include "MpvItem.h"

#include <MpvController>

MpvItem::MpvItem(QQuickItem* parent)
    : MpvAbstractItem(parent)
{
    Q_EMIT observeProperty(QStringLiteral("width"), MPV_FORMAT_NODE);
    Q_EMIT observeProperty(QStringLiteral("height"), MPV_FORMAT_NODE);

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

    setPropertyBlocking(QStringLiteral("mute"), false);
}

int MpvItem::getVideoWidth() const
{
    return m_VideoWidth;
}

int MpvItem::getVideoHeight() const
{
    return m_VideoHeight;
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
}
