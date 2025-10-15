#include "triggerclass.h"
#include "apireader.h"
#include <chrono>
#include <thread>

TriggerClass::TriggerClass(QObject *parent)
{
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, &QNetworkAccessManager::finished, this, &TriggerClass::onReplyFinished);

}

void TriggerClass::loginUser(QString usernameVal, QString passwordVal)
{
    QJsonObject userCredObj;
    userCredObj["username"] = usernameVal;
    userCredObj["password"] = encryptString(passwordVal);
    QJsonDocument userDoc(userCredObj);
    QByteArray userCredData = userDoc.toJson();
    //API
    QUrl checkUserUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/login");
    QNetworkRequest request(checkUserUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginReply = loginManager->post(request, userCredData);
    QObject::connect(loginReply, &QNetworkReply::finished, this, &TriggerClass::testLog);

    qDebug()<<"usercreddata"<<userCredData;

    //QObject::connect(loginReply, &QNetworkReply::finished, loginManager, &QNetworkAccessManager::clearAccessCache);
    //QObject::connect(loginReply, &QNetworkReply::finished, this, &TriggerClass::loginResultReceived);

}

void TriggerClass::testTrigger()
{
    ApiReader apiReader;

    qDebug()<<"testTrigger signal Triggered";
    QObject::connect(this,&TriggerClass::triggerSignal,&apiReader,&ApiReader::testTriggered);
    //apiReader->testTriggered();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    emit triggerSignal();
}

void TriggerClass::onReplyFinished(QNetworkReply *reply)
{
    QUrl url = reply->request().url();
    m_pendingRequests.remove(url); // Remove from pending after completion
    qDebug() << "Request for" << url.toString() << "finished.";

    if (reply->error() == QNetworkReply::NoError) {
        // Process reply data
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}

QString TriggerClass::encryptString(QString stringVal)
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(stringVal.toUtf8());
    QByteArray resultHash = hash.result();
    return resultHash.toHex();
}

void TriggerClass::testLog()
{
    if (loginReply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = loginReply->readAll();
        loginReply->deleteLater();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            rootObject = jsonDoc.object();
            qDebug()<<"Root obj"<<rootObject.value("statusCode").toInt();
            if(rootObject.value("statusCode") == 200)
            {
                qDebug() << "Login successful:";
                m_loginResult = true;

                //emit loginResultReceived();
            }
            else if(rootObject.value("statusCode") == 401)
            {
                qDebug() << "Login Failed: Invalid Username or Password";
                m_loginResult = false;
                //loginReply->abort();
                //emit loginResultReceived();

            }
            else
            {
                qDebug() << "Login Failed " << loginReply->errorString();
                m_loginResult = false;
                // emit loginResultReceived();

            }

            // QString newString = rootObject.value("body").toString();
            // newString.remove("\"");
            // m_userId = newString;

        }
        //emit loginResultReceived();
        //reply->abort();
    }
    else{
        qDebug() << "Login failed: " << loginReply->errorString();
        m_loginResult = false;
        //reply->abort();
        //emit loginResultReceived();

    }
    emit loginResultReceived();
    loginReply->deleteLater();
}
