#pragma once

#include <MpvAbstractItem>

class MpvItem : public MpvAbstractItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit MpvItem(QQuickItem *parent = nullptr);

    Q_INVOKABLE void loadFile(const QUrl &url);
};