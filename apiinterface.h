#ifndef APIINTERFACE_H
#define APIINTERFACE_H

class ApiInterface
{

public:
    ApiInterface();

    virtual void triggerSignal() = 0;
};

#endif // APIINTERFACE_H
