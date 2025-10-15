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

    TriggerClass{
        id:_triggerClass
    }

    ColumnLayout{
        //anchors.fill: parent
        anchors.centerIn: parent
        Text {
            //text://_apiReader.dataFromApi
            Layout.preferredHeight: 100
            Layout.preferredWidth: 200
        }

        TextField{
            id:_usernameTxt
            placeholderText: "Username"
            Layout.preferredHeight: 50
            Layout.preferredWidth: 200
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
        }

        TextField{
            id:_passwordTxt
            placeholderText: "Password"
            Layout.preferredHeight: 50
            Layout.preferredWidth: 200
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
        }

        Button{
            Layout.preferredHeight: 50
            Layout.preferredWidth: 200
            text: "LogIn"
            onClicked: {

                _apiReader.username = _usernameTxt.text
                _apiReader.password = _passwordTxt.text
                //_apiReader.logIn()
                _apiReader.testLogin()
            }
            Connections{
                target: _apiReader
                function onUserLoginResultReceived(){
                    if(_apiReader.getLoginResult() === true)
                    {
                        console.log("Login Success")
                    }
                    else
                        console.log("Login Failed")
                }
            }
        }

        Button{
            text: "Fetch Data"
            onClicked:{ _triggerClass.triggerSignal()
                        _triggerClass.testTrigger()


                        }//_apiReader.showData()//_apiReader.testJson()//_apiReader.showData()
            Connections{
                target: _triggerClass
                function onTriggerSignal(){
                    console.log("received signal from c++");
                }
            }
        }


    }
}
