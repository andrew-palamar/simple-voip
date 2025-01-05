#ifndef MYACCOUNT_H
#define MYACCOUNT_H

#include <pjsua2.hpp>
#include "MetaVoIP.h"

#include <QString>
#include <QObject>

using namespace pj;

class MetaVoIP;

// Subclass to extend the Account and get notifications etc.
class MyAccount : public Account
{

public:

    MyAccount(MetaVoIP *parent);
    ~MyAccount();

    virtual void onRegState(OnRegStateParam &prm);

    virtual void onRegStarted(OnRegStartedParam &prm);

    virtual void onIncomingCall(OnIncomingCallParam &iprm);

private:
    MetaVoIP *parent;
};

#endif // MYACCOUNT_H
