import QtQuick
import QtQuick.Controls

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