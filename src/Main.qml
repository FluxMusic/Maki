import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow
{
    id: root

    width: 640
    height: 360

    title: i18nc("@title:window", "Maki Preview")

    Loader
    {
        anchors.fill: parent     

        source:
        {
            switch(WindowManager.FileType)
            {
                case "image": return "ImagePreview.qml"
                case "text" : return "TextPreview.qml"
                case "audio": return "AudioPreview.qml"
                case "video": return "VideoPreview.qml"
                case "pdf"  : return "DocumentPreview.qml"
                default: return "FallbackPreview.qml"
            }
        }
    }
}