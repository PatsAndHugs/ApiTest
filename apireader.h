#ifndef APIREADER_H
#define APIREADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "triggerclass.h"

class ApiReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString dataFromApi READ dataFromApi WRITE setDataFromApi NOTIFY dataFromApiChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:

    explicit ApiReader(QObject *parent = nullptr);

    QString dataFromApi() { return m_dataFromApi; }
    void setDataFromApi(QString newval);

    QString username(){ return m_username;}
    void setUsername(QString usernameVal);

    QString password(){return m_password;}
    void setPassword(QString passwordVal);


public slots:
    void showData();
    void logIn();
    void testJson();
    void testTriggered();
    void testLogin();
    bool getLoginResult(){return m_loginResult;}

signals:
    void dataFromApiChanged();
    void usernameChanged();
    void passwordChanged();
    void signalTriggered();
    void userLoginResultReceived();

private:
    QString m_dataFromApi;
    QJsonArray m_jsonArray;
    QJsonObject m_jsonObject;

    QString m_username;
    QString m_password;
    //TriggerClass *triggerClass;
    bool m_loginResult;

};

#endif // APIREADER_H
