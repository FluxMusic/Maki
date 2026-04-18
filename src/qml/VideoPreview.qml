import QtQuick
import QtQuick.Controls

MpvItem
{
    id: videoPlayer

    width: parent.width
    height: parent.height

    onReady:
    {
        console.log("Videofile URL ", WindowManager.URL)

        loadFile(WindowManager.URL)
    }
}