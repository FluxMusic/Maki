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
    }
    Label
    {
        anchors.centerIn: parent
        text: "No Preview available"
        visible: WindowManager.URL === ""
    }
}