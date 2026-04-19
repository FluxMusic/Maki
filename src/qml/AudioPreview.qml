import QtQuick
import QtQuick.Controls
import QtMultimedia

Item
{
    anchors.fill: parent
    
    MediaPlayer
    {
        id: audioPlayer

        source: WindowManager.URL
        autoPlay: true
        audioOutput: AudioOutput
        {
            volume: 1.0
        }

        Component.onCompleted:
        {
            //TODO: put this in config
            root.width = 500;
            root.height = 280;
        }
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