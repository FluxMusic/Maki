import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow
{
    id: root

    width: 400
    height: 300

    title: i18nc("@title:window", "Hello World")

    pageStack.initialPage: Kirigami.Page
    {
        Loader
        {
            anchors.fill: parent
            source:
            {
                switch(WindowManager.FileType)
                {
                    case "image": return "ImagePreview.qml"
                    default: return "FallbackPreview.qml"
                }
            }
        }
    }
}