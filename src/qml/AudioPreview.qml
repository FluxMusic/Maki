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
}