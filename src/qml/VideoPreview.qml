import QtQuick
import QtQuick.Controls

Item
{
    anchors.fill: parent

    MpvItem
    {
        id: videoPlayer

        anchors.fill: parent

        onReady:
        {
            loadFile(WindowManager.URL);
        }

        onVideoReconfig:
        {
            //TODO: Into a config
            const maxScale = Qt.size(1920, 1080);

            const videoSize = Qt.size(videoWidth, videoHeight);

            const rw = maxScale.height * (videoSize.width / videoSize.height);

            const useHeight = rw <= maxScale.width;

            if (useHeight)
            {
                root.width = rw;
                root.height = maxScale.height;
            }
            else
            {
                root.width = maxScale.width;
                root.height = maxScale.width * (videoSize.height / videoSize.width);
            }
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