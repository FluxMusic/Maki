// SPDX-FileCopyrightText: 2026 Alex Huber <alex.huber743@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls

Item {
    anchors.fill: parent

    ScrollView {
        anchors.fill: parent

        TextArea {
            id: textArea

            readOnly: true
            text: WindowManager.fileText
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