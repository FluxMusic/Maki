import QtQuick
import QtQuick.Controls

Item
{
    anchors.fill: parent
    
    Image
    {
        anchors.fill: parent
        source: WindowManager.FallbackURL
        visible: WindowManager.FallbackURL !== ""
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
        visible: WindowManager.FallbackURL === ""
    }

    Button
    {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 8

        text: i18n("open")

        opacity: buttonHover.hovered ? 1.0 : 0.0

        Behavior on opacity
        {
            NumberAnimation { duration: 150 }
        }

        onClicked:
        {
            console.log("clicked");
            WindowManager.openInDefaultApp();
        }

        HoverHandler
        {
            id: buttonHover

            margin: 64
        }
    }
}