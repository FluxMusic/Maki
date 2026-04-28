// SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia

Item {
    anchors.fill: parent
    
    MediaPlayer {
        id: audioPlayer

        source: WindowManager.url
        autoPlay: true
        audioOutput: AudioOutput {
            volume: 1.0
        }

        Component.onCompleted: {
            //TODO: put this in config
            root.width = 500;
            root.height = 280;
        }
    }

    Button {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 8

        text: i18n("open")

        opacity: buttonHover.hovered ? 1.0 : 0.0

        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }

        onClicked: {
            WindowManager.openInDefaultApp();
        }

        HoverHandler {
            id: buttonHover

            margin: 64
        }
    }

    Item {
        id: display

        anchors.bottom: controls.top
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left

        anchors.leftMargin: root.width / 8
        anchors.rightMargin: root.width / 8
        anchors.topMargin: root.height / 12

        RowLayout {
            anchors.fill: parent
            spacing: 16
            
            Image {
                source: WindowManager.audioCoverURL

                fillMode: Image.PreserveAspectFit

                Layout.fillWidth: true
                Layout.preferredWidth: parent.width * (2/5)
                Layout.preferredHeight: parent.height
            }

            Label {
                text: WindowManager.FileName

                verticalAlignment: Text.AlignVCenter

                Layout.fillWidth: true
                Layout.preferredWidth: parent.width * (3/5)
                Layout.preferredHeight: parent.height
            }
        }
    }

    Item {
        id: controls

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.leftMargin: root.width / 8
        anchors.rightMargin: root.width / 8
        anchors.bottomMargin: root.height / 6


        RowLayout {
            anchors.fill: parent
            spacing: 8

            Button {
                id: playButton

                display: AbstractButton.IconOnly

                icon.name: audioPlayer.playing ? "media-playback-pause" : "media-playback-start"

                onClicked: {
                    if (audioPlayer.playing) {
                        audioPlayer.pause();
                    } else {
                        audioPlayer.play();
                    }
                }
            }

            Slider {
                id: playbackSlider

                Layout.fillWidth: true

                orientation: Qt.Horizontal

                from: 0
                to: audioPlayer.duration
                value: audioPlayer.position

                onMoved: audioPlayer.setPosition(value);
            }

            Button {
                id: muteButton

                display: AbstractButton.IconOnly

                icon.name: audioPlayer.audioOutput.muted ? "player-volume-muted" : "player-volume"

                onClicked: audioPlayer.audioOutput.muted = !audioPlayer.audioOutput.muted;

                HoverHandler {
                    id: muteButtonHover
                }
            }
        }

        Slider {
            id: volumeSlider

            anchors.bottom: controls.top
            anchors.right: controls.right

            anchors.bottomMargin: 8

            width: muteButton.width
            height: 100

            orientation: Qt.Vertical

            from: 0
            to: 1.0
            value: audioPlayer.audioOutput.volume
            onMoved: audioPlayer.audioOutput.volume = value

            enabled: muteButtonHover.hovered || volumeSliderHover.hovered
            opacity: muteButtonHover.hovered || volumeSliderHover.hovered 
                    ? 1.0 
                    : 0.0

            Behavior on opacity {
                NumberAnimation{ duration: 150 }
            }
            
            HoverHandler {
                id: volumeSliderHover
                enabled: muteButtonHover.hovered || hovered
                margin: 16
            }
        }
    }
}