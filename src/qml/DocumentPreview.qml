import QtQuick
import QtQuick.Controls

ScrollView
{
    anchors.fill: parent
    
    ListView
    {
        anchors.fill: parent
        model: WindowManager.PageNum
        spacing: 8

        delegate: Image
        {
            width: ListView.view.width
            fillMode: Image.PreserveAspectFit
            source: "image://Maki/" + (index + 1)
        }
    }
}