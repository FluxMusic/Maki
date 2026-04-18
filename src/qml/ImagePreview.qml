import QtQuick
import QtQuick.Controls

Item
{
    anchors.fill: parent
    
    Image
    {
        anchors.fill: parent
        source: WindowManager.URL
        fillMode: Image.PreserveAspectFit
        mipmap: true

        Component.onCompleted:
        {
            //TODO: Into a config
            const maxScale = Qt.size(1920, 1080);

            const imageSize = sourceSize;

            const rw = maxScale.height * (imageSize.width / imageSize.height);

            const useHeight = rw <= maxScale.width;

            if (useHeight)
            {
                root.width = rw;
                root.height = maxScale.height;
            }
            else
            {
                root.width = maxScale.width;
                root.height = maxScale.width * (imageSize.height / imageSize.width);
            }
        }
    }
}