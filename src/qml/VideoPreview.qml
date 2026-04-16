import QtQuick
import QtQuick.Controls
import QtMultimedia

Item
{
    anchors.fill: parent
    
    MediaPlayer
    {
        id: videoPlayer

        source: WindowManager.URL
        autoPlay: true
        audioOutput: AudioOutput
        {
            volume: 1.0
        }
        videoOutput: VideoOutput
        {
            anchors.fill: parent
        }

        onErrorOccurred: console.log(videoPlayer.errorString)
    }
}