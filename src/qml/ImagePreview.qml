import QtQuick
import QtQuick.Controls

Item
{
    anchors.fill: parent
    
    Image
    {
        anchors.fill: parent
        source: WindowManager.URL
        fillMode: Image.PreserveAspectFit
    }
}