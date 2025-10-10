#ifndef TRIGGERCLASS_H
#define TRIGGERCLASS_H

#include <QObject>

class TriggerClass : public QObject
{
    Q_OBJECT
public:
    explicit TriggerClass(QObject *parent = nullptr);

public slots:
    void testTrigger();
signals:
    void triggerSignal();

};

#endif // TRIGGERCLASS_H
