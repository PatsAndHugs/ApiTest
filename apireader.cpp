#include "apireader.h"

ApiReader::ApiReader(QObject *parent) : QObject(parent)
{

}

void ApiReader::setDataFromApi(QString newval)
{
    m_dataFromApi = newval;
}

void ApiReader::setUsername(QString usernameVal)
{
    m_username = usernameVal;
}

void ApiReader::setPassword(QString passwordVal)
{
    m_password = passwordVal;
}

void ApiReader::showData()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/")));

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            // Process the responseData (e.g., parse JSON)
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull()) {
                if (jsonDoc.isObject()) {
                    QJsonObject rootObject = jsonDoc.object();
                    // Access data from rootObject
                    m_jsonObject = rootObject;
                } else if (jsonDoc.isArray()) {
                    QJsonArray rootArray = jsonDoc.array();
                    // Access data from rootArray
                    m_jsonArray = rootArray;
                }
            }
            qDebug() <<"Success";
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });

    qDebug()<<"jsonarray is empty"<<m_jsonArray.isEmpty();
    qDebug()<<"jsonObject is empty"<<m_jsonObject.isEmpty();


    for (QJsonObject::iterator it = m_jsonObject.begin(); it != m_jsonObject.end(); ++it) {
        qDebug() << "Key:" << it.key() << "Value:" << it.value();
    }

    // // Modify a value
    // QJsonObject::iterator it = m_jsonObject.find("age");
    // if (it != m_jsonObject.end()) {
    //     it.value() = 31; // Modify the value
    // }

    // // Verify modification
    // qDebug() << "Updated age:" << m_jsonObject["age"].toInt();
}

void ApiReader::logIn()
{
    QJsonObject loginData;
    loginData["username"] = m_username;
    loginData["password"] = m_password;

    QJsonDocument doc(loginData);
    QByteArray jsonData = doc.toJson();

    QUrl serviceUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/testresource"); // Replace with your actual login endpoint
    QNetworkRequest request(serviceUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this); // 'this' refers to the parent object, e.g., a QWidget or QObject
    QNetworkReply *reply = networkManager->post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            // Parse the response if needed (e.g., using QJsonDocument::fromJson)
            QVariant statusCodeVariant = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            if(statusCodeVariant.isValid())
            {
                int statusCode = statusCodeVariant.toInt();
                qDebug()<<"statuscode: "<<statusCode;
                if (statusCode >= 200 && statusCode < 300)
                {
                    // Process the data from reply->readAll();
                    qDebug() << "Server Response:" << responseData;
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
                    if (!jsonDoc.isNull()) {
                        if (jsonDoc.isObject()) {
                            QJsonObject rootObject = jsonDoc.object();
                            // Access data from rootObject
                            for (QJsonObject::iterator it = rootObject.begin(); it != rootObject.end(); ++it) {
                                //qDebug() << "Key:" << it.key() << "Value:" << it.value();
                                if(it.key() == "statusCode" && (it.value().toInt() >= 200 && it.value().toInt() <300))
                                    qDebug() << "Login successful!";
                            }
                        }
                    }

                }
                else if (statusCode >= 300 && statusCode < 400)
                {
                    qDebug() << "Redirect or other informational status.";
                }
                else if (statusCode >= 400 && statusCode < 500)
                {
                    qDebug() << "Client error (e.g., 404 Not Found, 403 Forbidden).";
                }
                else if (statusCode >= 500 && statusCode < 600)
                {
                    qDebug() << "Server error.";
                }
            }
        }

        else
        {
            qDebug() << "Network Error:" << reply->errorString();
        }
        reply->deleteLater(); // Clean up the reply object
    });
}





