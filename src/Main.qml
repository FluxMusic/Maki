import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow
{
    id: root

    width: WindowManager.WindowSize.width
    height: WindowManager.WindowSize.height

    title: i18nc("@title:window", "Maki Preview")

    Loader
    {
        width: parent.width
        height: parent.width       

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