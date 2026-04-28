// SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls

Item {
    anchors.fill: parent
    
    Image {
        anchors.fill: parent
        source: WindowManager.url
        fillMode: Image.PreserveAspectFit
        mipmap: true

        property url currentURL: WindowManager.url

        onCurrentURLChanged: {
            //TODO: Into a config
            const maxScale = Qt.size(1280, 720);

            const imageSize = sourceSize;

            const rw = maxScale.height * (imageSize.width / imageSize.height);

            const useHeight = rw <= maxScale.width;

            if (useHeight) {
                root.width = rw;
                root.height = maxScale.height;
            } else {
                root.width = maxScale.width;
                root.height = maxScale.width * (imageSize.height / imageSize.width);
            }
        }

        Component.onCompleted: {
            //TODO: Into a config
            const maxScale = Qt.size(1280, 720);

            const imageSize = sourceSize;

            const rw = maxScale.height * (imageSize.width / imageSize.height);

            const useHeight = rw <= maxScale.width;

            if (useHeight) {
                root.width = rw;
                root.height = maxScale.height;
            } else {
                root.width = maxScale.width;
                root.height = maxScale.width * (imageSize.height / imageSize.width);
            }
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
            console.log("clicked");
            WindowManager.openInDefaultApp();
        }

        HoverHandler {
            id: buttonHover

            margin: 64
        }
    }
}