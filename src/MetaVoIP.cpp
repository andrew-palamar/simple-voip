#include "MetaVoIP.hpp"
#include <QDebug>
// #include <QMessageBox>
#include <QThread>

MetaVoIP::MetaVoIP(QString protocol, int port, QObject *parent) : QObject(parent)
{
    try
    {
        loaded = false;
        connectDuration = 0;

        ep.libCreate();
        ep.libInit(epCfg);
        tCfg.port = port;
        call = Q_NULLPTR;

        if (protocol == "TCP")
            ep.transportCreate(PJSIP_TRANSPORT_TCP, tCfg);
        else
            ep.transportCreate(PJSIP_TRANSPORT_UDP, tCfg);

        // Start the library (worker threads etc)
        ep.libStart();

        loaded = true;

        qDebug() << "*** PJSUA2 STARTED ***";
    }
    catch (Error &err)
    {
        loaded = false;
        qDebug() << "MetaVoIP: Lib starting failed" << err.info().c_str();
    }
}

MetaVoIP::~MetaVoIP()
{
    try
    {
        // Delete the account. This will unregister from server
        delete account;
    }
    catch (Error &err)
    {
        qDebug() << "MetaVoIP: Lib deleting failed" << err.info().c_str();
    }
}

void MetaVoIP::createAccount(QString idUri, QString registrarUri, QString user, QString password)
{
    try
    {
        // Configure an AccountConfig
        aCfg.idUri = idUri.toStdString();
        aCfg.regConfig.registrarUri = registrarUri.toStdString();
        AuthCredInfo cred("digest", "*", user.toStdString(), 0, password.toStdString());
        aCfg.sipConfig.authCreds.push_back(cred);
        aCfg.callConfig.timerMinSESec = 90;
        aCfg.callConfig.timerSessExpiresSec = 1800;

        account = new MyAccount(this);
        account->create(aCfg);

        qDebug() << "MetaVoIP: Account creation successful";
    }
    catch (Error &err)
    {
        qDebug() << "MetaVoIP: Account creation failed" << err.info().c_str();
    }
}

void MetaVoIP::registerAccount()
{
    if (account)
    {
        try
        {
            account->setRegistration(true);

            qDebug() << "MetaVoIP: Register account successfull";
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: Register failed" << err.info().c_str();
        }
    }
}

void MetaVoIP::unregisterAccount()
{
    if (account)
    {
        try
        {
            account->setRegistration(false);
            qDebug() << "MetaVoIP: Unregister account successfull";
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: Unregister error: " << err.info().c_str() << Qt::endl;
        }
    }
}

void MetaVoIP::makeCall(QString number)
{
    if (account)
    {
        qDebug() << "MetaVoIP: Attempting to create call";

        call = new MyCall(this, *account);
        CallOpParam prm(true); // Use default call settings

        try
        {
            qDebug() << "MetaVoIP: Calling API with account" << account->getId() << account->getInfo().regIsActive << account->isValid();

            call->makeCall(number.toStdString(), prm);

            qDebug() << "MetaVoIP: makeCall was called with" << number;
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: Call could not be made" << err.info().c_str();
        }
    }
}

void MetaVoIP::ring(int callId)
{
    if (account != Q_NULLPTR)
    {
        try
        {
            qDebug() << "MetaVoIP: Set state to ringing for callId" << callId;

            call = new MyCall(this, *account, callId);
            CallOpParam prm;
            prm.statusCode = PJSIP_SC_RINGING;
            call->answer(prm);
        }
        catch (Error &err)
        {
            qDebug() << "Ringing failed" << err.info().c_str();
        }
    }
}

void MetaVoIP::acceptCall(int callId)
{
    if (account && call != Q_NULLPTR)
    {
        qDebug() << "MetaVoIP: Accepting call with callId" << callId;

        try
        {
            call = new MyCall(this, *account, callId);
            CallOpParam prm;
            prm.statusCode = PJSIP_SC_OK;
            call->answer(prm);
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: Accepting failed" << err.info().c_str();
        }
    }
}

bool MetaVoIP::hangupCall(int callId)
{
    if (account && call != Q_NULLPTR)
    {
        qDebug() << "MetaVoIP: Hang up on callId" << callId;

        try
        {
            CallInfo ci = call->getInfo();

            CallOpParam prm;

            if (ci.lastStatusCode == PJSIP_SC_RINGING)
            {
                prm.statusCode = PJSIP_SC_BUSY_HERE;
            }
            else
            {
                prm.statusCode = PJSIP_SC_OK;
            }

            if (callId >= 0 && callId < (int)epCfg.uaConfig.maxCalls)
                call->hangup(prm);
            else
                qDebug() << "MetaVoIP: Max calls bug";

            call = Q_NULLPTR;

            return 1;
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: HangupCall failed" << err.info().c_str();
        }
    }

    return 0;
}

bool MetaVoIP::holdCall(int callId)
{
    if (account && call != Q_NULLPTR)
    {
        try
        {
            qDebug() << "MetaVoIP: Hold call with callId" << callId;

            CallOpParam prm(true);

            if (!call->isOnHold())
            {
                qDebug() << "MetaVoIP: Call will be hold";

                call->setHoldTo(true);

                prm.statusCode = PJSIP_SC_QUEUED;
                call->setHold(prm);
            }
            else
            {
                qDebug() << "MetaVoIP: Call will be re-invited";

                call->setHoldTo(false);

                prm.opt.flag = PJSUA_CALL_UNHOLD;
                call->reinvite(prm);
            }

            return 1;
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: Accepting failed" << err.info().c_str();
        }
    }

    return 0;
}

bool MetaVoIP::transferCall(QString destination)
{
    if (account && call != Q_NULLPTR)
    {
        try
        {
            qDebug() << "MetaVoIP: Transfer call to" << destination;

            CallOpParam prm;
            prm.statusCode = PJSIP_SC_CALL_BEING_FORWARDED;
            call->xfer(destination.toStdString(), prm);

            return 1;
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: Accepting failed" << err.info().c_str();
        }
    }

    return 0;
}

void MetaVoIP::emitRegStateStarted(bool status)
{
    qDebug() << "MetaVoIP: Regstate started: " << status;
    emit regStateStarted(status);
}

void MetaVoIP::emitRegStateChanged(bool status)
{
    qDebug() << "MetaVoIP: Regstate changed: " << status;
    emit regStateChanged(status);
}

void MetaVoIP::emitCallStateChanged(int role, int callId, int state, int status, QString id)
{
    qDebug() << "MetaVoIP: Emitting data to slot " << callId;
    emit callStateChanged(role, callId, state, status, id);
}

void MetaVoIP::sendDtmf(QString num)
{
    if (call != Q_NULLPTR)
    {
        try
        {
            call->dialDtmf(num.toStdString());
            qDebug() << "MetaVoIP: Dtmf" << num << " sent";
        }
        catch (Error &err)
        {
            qDebug() << "MetaVoIP: Dtmf failed" << err.info().c_str();
        }
    }
}
