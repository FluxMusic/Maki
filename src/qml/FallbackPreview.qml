import QtQuick
import QtQuick.Controls

Item
{
    anchors.fill: parent
    
    Image
    {
        anchors.fill: parent
        source: WindowManager.URL
        visible: WindowManager.URL !== ""
        fillMode: Image.PreserveAspectFit

        Component.onCompleted:
        {
            //TODO: Move this to a config
            root.width = 512;
            root.height = 512;
        }
    }
    Label
    {
        anchors.centerIn: parent
        text: "No Preview available"
        visible: WindowManager.URL === ""
    }
}