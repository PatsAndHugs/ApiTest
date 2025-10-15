#ifndef TRIGGERCLASS_H
#define TRIGGERCLASS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class TriggerClass : public QObject
{
    Q_OBJECT

public:
    explicit TriggerClass(QObject *parent = nullptr);

    void loginUser(QString usernameVal, QString passwordVal);
    bool getLoginResult(){return m_loginResult;}

public slots:
    void testTrigger();

private slots:
    void onReplyFinished(QNetworkReply *reply);


signals:
    void triggerSignal();
    void loginResultReceived();

private:
    bool m_loginResult;
    QString m_username;
    QString m_password;
    QString encryptString(QString stringVal);
    QJsonObject rootObject;
    QNetworkAccessManager *loginManager;
    QNetworkReply *loginReply;

    void testLog();
    QSet<QUrl> m_pendingRequests;
};

#endif // TRIGGERCLASS_H
