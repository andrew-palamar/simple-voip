#include "MyAccount.hpp"
#include "MyCall.hpp"

#include <QString>
#include <QDebug>


MyAccount::MyAccount(MetaVoIP *parent)
{
    this->parent = parent;
}

MyAccount::~MyAccount()
{
}

void MyAccount::onRegState(OnRegStateParam &prm) {
    AccountInfo ai = getInfo();
    qDebug() << (ai.regIsActive? "*** Register:" : "*** Unregister:")
             << " code=" << prm.code;

    parent->emitRegStateStarted(ai.regIsActive);
}

void MyAccount::onRegStarted(OnRegStartedParam &prm)
{
     AccountInfo ai = getInfo();
     qDebug() << (ai.regIsActive? "*** Register:" : "*** Unregister:")
              << " code=" << prm.renew;

     parent->emitRegStateChanged(ai.regIsActive);
}

void MyAccount::onIncomingCall(OnIncomingCallParam &iprm)
{
    qDebug() << "MetaVoIP: Incoming call with callId" << iprm.callId;

    parent->ring(iprm.callId);
}

