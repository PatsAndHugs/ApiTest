import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.example.api 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ApiReader{
        id:_apiReader
    }

    ColumnLayout{
        anchors.fill: parent
        Text {
            //text://_apiReader.dataFromApi
            Layout.preferredHeight: 100
            Layout.preferredWidth: 200
        }

        Button{
            text: "Fetch Data"
            onClicked: _apiReader.showData()
        }

    }
}
