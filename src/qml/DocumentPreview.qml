import QtQuick
import QtQuick.Controls

Item
{
    anchors.fill: parent

    ScrollView
    {
        anchors.fill: parent
        
        ListView
        {
            anchors.fill: parent
            model: WindowManager.PageNum
            spacing: 8

            delegate: Image
            {
                width: parent.width
                fillMode: Image.PreserveAspectFit
                source: "image://Maki/" + (index + 1)
                mipmap: true
            }

            Component.onCompleted:
            {

                //TODO: Put this into a config
                const maxScale = Qt.size(1920, 1080);

                const pageSize = Qt.size(WindowManager.WindowSize.width, WindowManager.WindowSize.height);

                const rw = maxScale.height * (pageSize.width / pageSize.height);

                const useHeight = rw <= maxScale.width;

                if (useHeight)
                {
                    root.width = rw;
                    root.height = maxScale.height;
                }
                else
                {
                    root.width = maxScale.width;
                    root.height = maxScale.width * (pageSize.height / pageSize.width);
                }
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