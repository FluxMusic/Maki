#include "MpvItem.h"

MpvItem::MpvItem(QQuickItem *parent)
    : MpvAbstractItem(parent)
{
    Q_EMIT setProperty(QStringLiteral("vo"), QStringLiteral("libmpv"));
    Q_EMIT setProperty(QStringLiteral("hwdec"), QStringLiteral("auto-safe"));
}

void MpvItem::loadFile(const QUrl &url)
{
    // Q_EMIT setProperty(QStringLiteral("keep-open"), QStringLiteral("always"));

    // setPropertyBlocking(QStringLiteral("start"), QString::number(0));

    setPropertyBlocking(QStringLiteral("mute"), true);
    
    Q_EMIT command(QStringList() << QStringLiteral("loadfile") << url.toLocalFile());

    setPropertyBlocking(QStringLiteral("mute"), false);
}