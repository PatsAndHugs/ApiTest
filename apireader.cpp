#include "apireader.h"

ApiReader::ApiReader(QObject *parent) : QObject(parent)
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


}

void ApiReader::setDataFromApi(QString newval)
{
    m_dataFromApi = newval;
}

void ApiReader::showData()
{
    qDebug()<<"jsonarray is empty"<<m_jsonArray.isEmpty();
    qDebug()<<"jsonObject is empty"<<m_jsonObject.isEmpty();
}





