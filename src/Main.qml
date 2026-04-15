import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow
{
    id: root

    width: WindowManager.WindowSize.width
    height: WindowManager.WindowSize.height

    title: i18nc("@title:window", "Hello World")

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