import QtQuick
import QtQuick.Controls

ScrollView
{
    TextArea
    {
        id: textArea

        readOnly: true
        text: WindowManager.FileText
    }
}