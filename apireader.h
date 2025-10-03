#ifndef APIREADER_H
#define APIREADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ApiReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString dataFromApi READ dataFromApi WRITE setDataFromApi NOTIFY dataFromApiChanged)

public:

    explicit ApiReader(QObject *parent = nullptr);

    QString dataFromApi() { return m_dataFromApi; }
    void setDataFromApi(QString newval);
public slots:
    void showData();
signals:
    void dataFromApiChanged();

private:
    QString m_dataFromApi;
    QJsonArray m_jsonArray;
    QJsonObject m_jsonObject;
};

#endif // APIREADER_H
