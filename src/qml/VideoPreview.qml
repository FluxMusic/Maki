import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

//to use colors
import org.kde.kirigami as Kirigami

Item
{
    anchors.fill: parent

    property bool videoControlsVisible: false

    MpvItem
    {
        id: videoPlayer

        anchors.fill: parent

        property url currentURL: WindowManager.URL

        onCurrentURLChanged:
        {
            loadFile(WindowManager.URL);
        }

        onReady:
        {
            loadFile(WindowManager.URL);
        }

        onVideoReconfig:
        {
            //TODO: Into a config
            const maxScale = Qt.size(1280, 720);

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

        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: (videoControlsVisible || videoControlsHover.hovered || volumeSliderHover.hovered) ? Qt.ArrowCursor : Qt.BlankCursor

            onPositionChanged: 
            {
                videoControlsVisible = true
                videoControlsHideTimer.restart()
            }

            onPressed: function(mouse)
            {
                //Only Left click is assigned for now, but check regardless
                if (mouse.button === Qt.LeftButton)
                {
                    videoPlayer.pause = !videoPlayer.pause;
                }
            }
        }

        Timer
        {
            id: videoControlsHideTimer

            interval: 1000
            onTriggered: videoControlsVisible = false
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

    Rectangle
    {
        id: videoControls

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.leftMargin: parent.width / 30
        anchors.rightMargin: parent.width / 30
        anchors.bottomMargin: parent.height / 20

        height: videoControlsLayout.implicitHeight + 16 //2 * padding of 8

        radius: 10

        topRightRadius: (muteButton.hovered || volumeSliderHover.hovered) ? 0 : 10

        Behavior on topRightRadius
        {
            NumberAnimation { duration: 150 }
        }

        color: Qt.rgba(root.color.r, root.color.g, root.color.b, 0.5)
        border.width: 1
        border.color: Kirigami.Theme.alternateBackgroundColor

        opacity: (videoControlsVisible || videoControlsHover.hovered || volumeSliderHover.hovered) ? 1.0 : 0.0

        Behavior on opacity
        {
            NumberAnimation { duration: 150 }
        }

        HoverHandler
        {
            id: videoControlsHover
        }

        RowLayout
        {
            id: videoControlsLayout

            anchors.fill: parent

            anchors.leftMargin: 8
            anchors.rightMargin: 8

            spacing: 8

            Button
            {
                id: playButton

                display: AbstractButton.IconOnly

                icon.name: videoPlayer.pause ? "media-playback-start" : "media-playback-pause"

                onClicked:
                {
                    videoPlayer.pause = !videoPlayer.pause;
                }
            }

            Label
            {
                text: videoPlayer.currentTimecode
            }

            Slider
            {
                id: playbackSlider

                Layout.fillWidth: true

                orientation: Qt.Horizontal

                from: 0
                to: videoPlayer.duration
                value: videoPlayer.position

                onMoved: videoPlayer.position = value;

                onPressedChanged:
                {
                    if (pressed)
                    {
                        videoPlayer.pause = true;
                    }
                    else
                    {
                        videoPlayer.pause = false;
                    }
                }
            }

            Label
            {
                text: videoPlayer.endTimecode
            }

            Button
            {
                id: muteButton

                display: AbstractButton.IconOnly

                icon.name: videoPlayer.mute ? "player-volume-muted" : "player-volume"

                onClicked: videoPlayer.mute = !videoPlayer.mute;
            }
        }

        Rectangle
        {
            id: videoVolumeSliderContainer

            anchors.bottom: videoControls.top
            anchors.right: videoControls.right

            height: videoVolumeSlider.height + 16 //2 margins of 8
            width: muteButton.width + videoControlsLayout.spacing + videoControlsLayout.anchors.rightMargin

            radius: 10
            bottomRightRadius: 0
            bottomLeftRadius: 0
            color: Qt.rgba(root.color.r, root.color.g, root.color.b, 0.5)
            border.width: 1
            border.color: Kirigami.Theme.alternateBackgroundColor

            opacity: muteButton.hovered || volumeSliderHover.hovered 
                     ? 1.0 
                     : 0.0

            Behavior on opacity
            {
                NumberAnimation{ duration: 150 }
            }
            
            HoverHandler
            {
                id: volumeSliderHover
                enabled: muteButton.hovered || hovered
                margin: 16
            }

            Slider
            {
                id: videoVolumeSlider

                anchors.fill: parent
                anchors.topMargin: 8
                anchors.bottomMargin: 8

                width: muteButton.width
                height: 100

                orientation: Qt.Vertical

                from: 0
                to: 100
                value: videoPlayer.volume
                onMoved: videoPlayer.volume = value
            }
        }
    }
}