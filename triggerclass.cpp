#include "triggerclass.h"
#include "apireader.h"
#include <chrono>
#include <thread>

TriggerClass::TriggerClass(QObject *parent)
{

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
