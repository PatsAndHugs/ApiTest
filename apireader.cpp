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

void ApiReader::testJson()
{
    //[[1, \"KI-1\", \"一\", \"ひとー\", \"イチ、イツ\", \"one\"], [2, \"KI-2\", \"二\", \"ふた、ふたたび、ふたー\", \"ニ、ジ\", \"two\"], [3, \"KI-3\", \"三\", \"み、みー\", \"サン、ゾウ\", \"three\"], [4, \"KI-4\", \"四\", \"よ、よー、よん\", \"シ\", \"four\"], [5, \"KI-5\", \"五\", \"いつ、いつー\", \"ゴ\", \"five\"], [6, \"KI-6\", \"六\", \"む、むー、むい\", \"ロク、リク\", \"six\"], [7, \"KI-7\", \"七\", \"なな、ななー、なの\", \"シチ\", \"seven\"], [8, \"KI-8\", \"八\", \"や、やー、よう\", \"ハチ、ハツ\", \"eight\"], [9, \"KI-9\", \"九\", \"ここの、ここのー\", \"キュウ、ク\", \"nine\"], [10, \"KI-10\", \"十\", \"とお、と、そ\", \"ジュウ、ジュ\", \"ten\"]]
    //QString jsonText = "[[1, \"KI-1\", \"一\", \"ひとー\", \"イチ、イツ\", \"one\"], [2, \"KI-2\", \"二\", \"ふた、ふたたび、ふたー\", \"ニ、ジ\", \"two\"], [3, \"KI-3\", \"三\", \"み、みー\", \"サン、ゾウ\", \"three\"], [4, \"KI-4\", \"四\", \"よ、よー、よん\", \"シ\", \"four\"], [5, \"KI-5\", \"五\", \"いつ、いつー\", \"ゴ\", \"five\"], [6, \"KI-6\", \"六\", \"む、むー、むい\", \"ロク、リク\", \"six\"], [7, \"KI-7\", \"七\", \"なな、ななー、なの\", \"シチ\", \"seven\"], [8, \"KI-8\", \"八\", \"や、やー、よう\", \"ハチ、ハツ\", \"eight\"], [9, \"KI-9\", \"九\", \"ここの、ここのー\", \"キュウ、ク\", \"nine\"], [10, \"KI-10\", \"十\", \"とお、と、そ\", \"ジュウ、ジュ\", \"ten\"]]";
    //QString jsonText = "[{\"name\": \"Alice\", \"age\": 30}, {\"name\": \"Bob\", \"age\": 25}]";
    QString jsonText = "[{\"KanjiId\": \"KI-1\", \"Kanji\": \"一\", \"Kunyomi\": \"ひとー\", \"Onyomi\": \"イチ、イツ\", \"KanjiMeaning\": \"one\"}, {\"KanjiId\": \"KI-2\", \"Kanji\": \"二\", \"Kunyomi\": \"ふた、ふたたび、ふたー\", \"Onyomi\": \"ニ、ジ\", \"KanjiMeaning\": \"two\"}, {\"KanjiId\": \"KI-3\", \"Kanji\": \"三\", \"Kunyomi\": \"み、みー\", \"Onyomi\": \"サン、ゾウ\", \"KanjiMeaning\": \"three\"}, {\"KanjiId\": \"KI-4\", \"Kanji\": \"四\", \"Kunyomi\": \"よ、よー、よん\", \"Onyomi\": \"シ\", \"KanjiMeaning\": \"four\"}, {\"KanjiId\": \"KI-5\", \"Kanji\": \"五\", \"Kunyomi\": \"いつ、いつー\", \"Onyomi\": \"ゴ\", \"KanjiMeaning\": \"five\"}, {\"KanjiId\": \"KI-6\", \"Kanji\": \"六\", \"Kunyomi\": \"む、むー、むい\", \"Onyomi\": \"ロク、リク\", \"KanjiMeaning\": \"six\"}, {\"KanjiId\": \"KI-7\", \"Kanji\": \"七\", \"Kunyomi\": \"なな、ななー、なの\", \"Onyomi\": \"シチ\", \"KanjiMeaning\": \"seven\"}, {\"KanjiId\": \"KI-8\", \"Kanji\": \"八\", \"Kunyomi\": \"や、やー、よう\", \"Onyomi\": \"ハチ、ハツ\", \"KanjiMeaning\": \"eight\"}, {\"KanjiId\": \"KI-9\", \"Kanji\": \"九\", \"Kunyomi\": \"ここの、ここのー\", \"Onyomi\": \"キュウ、ク\", \"KanjiMeaning\": \"nine\"}, {\"KanjiId\": \"KI-10\", \"Kanji\": \"十\", \"Kunyomi\": \"とお、と、そ\", \"Onyomi\": \"ジュウ、ジュ\", \"KanjiMeaning\": \"ten\"}]";
    QByteArray jsonData = jsonText.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (!doc.isNull() && doc.isArray()) {
        QJsonArray jsonArray = doc.array();
        // Now you can work with jsonArray
        //qDebug() << "Successfully converted to QJsonArray:" << jsonArray;
        // if(doc.isObject())
        // {
        //     QJsonObject jsonObj = doc.object();
        //     qDebug()<<"is jsonobject";
        //     for (QJsonObject::iterator it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        //         qDebug() << "Key:" << it.key() << "Value:" << it.value();
        //         if(it.value().isArray())
        //             qDebug()<< "isarray";
        //         else
        //             qDebug()<< "not array";
        //     }
        // }

        for (const QJsonValue &value : std::as_const(jsonArray)) {
            qDebug()<<value["Kanji"];
        }

        //qDebug()<<jsonArray[0][0].toString();
        // for (const QJsonValue &value : std::as_const(jsonArray)) {
        //     qDebug() << value[0];
        // }
    } else {
        qDebug() << "Failed to parse JSON or the JSON is not an array.";
    }
}

void ApiReader::showData()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://7eqjfwz2n3.execute-api.ap-southeast-2.amazonaws.com/dev/")));

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            // Process the responseData (e.g., parse JSON)
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull())
            {
                if (jsonDoc.isObject())
                {
                    QJsonObject rootObject = jsonDoc.object();
                    // Access data from rootObject
                    //m_jsonObject = rootObject;
                    QString jsonText;
                    for (QJsonObject::iterator it = rootObject.begin(); it != rootObject.end(); ++it) {
                        //qDebug() << "Key:" << it.key() << "Value:" << it.value();
                        if(it.key() == "body")
                        {
                            jsonText = it.value().toString();
                        }
                    }

                    QByteArray jsonData = jsonText.toUtf8();
                    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

                    if (!doc.isNull() && doc.isArray())
                    {
                        QJsonArray jsonArray = doc.array();
                        for (const QJsonValue &value : std::as_const(jsonArray)) {
                            qDebug()<<"Kanji: "<<value["Kanji"].toString()<<"KanjiMeaning"<<value["KanjiMeaning"].toString();
                        }
                    }

                }
                else if (jsonDoc.isArray())
                {
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





