import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

import io.github.FluxMusic.Maki

Kirigami.ApplicationWindow
{
    id: root

    width: 400
    height: 300

    title: i18nc("@title:window", "Hello World")

    pageStack.initialPage: Kirigami.Page
    {
        Controls.Label
        {
            anchors.centerIn: parent
            text: WindowManager.URL
        }
    }
}