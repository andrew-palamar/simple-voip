#include "backend.hpp"
#include <QByteArray>
#include <QCursor>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QRandomGenerator>
#include <QTextStream>
#include <QThread>
#include "MetaVoIP.hpp"
#include <QDebug>

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
	getSettings();

	if (getSipUserStr() != "" && getSipPassStr() != "" && getSipServerStr() != "" && getSipPortStr() != "")
		registerSip();
}

BackEnd::~BackEnd()
{
}

void BackEnd::registerSip()
{
	// Check if already registering
	if (isRegistering)
	{
		if (metaVoIP)
		{
			delete metaVoIP;	// Clean up the existing MetaVoIP instance
			metaVoIP = nullptr; // Reset pointer
		}
	}
	// Backend QML current protocol; CUrrent procol text
	metaVoIP = new MetaVoIP(sipProto, sipPortText.toInt());
	sipUser = sipUser.simplified();
	sipServer = sipServer.simplified();
	sipPass = sipPass.simplified();
	sipState = "init";

	connect(metaVoIP, SIGNAL(callStateChanged(int, int, int, int, QString)), this,
			SLOT(on_CallStateChanged(int, int, int, int, QString)));
	connect(metaVoIP, SIGNAL(regStateStarted(bool)), this, SLOT(on_RegStateStarted(bool)));
	connect(metaVoIP, SIGNAL(regStateChanged(bool)), this, SLOT(on_RegStateChanged(bool)));

	if (metaVoIP != Q_NULLPTR && metaVoIP->isLoaded())
	{
		// Set the flag to indicate we are starting registration
		isRegistering = true;
		metaVoIP->createAccount("sip:" + sipUser + "@" + sipServer, "sip:" + sipServer, sipUser, sipPass);
	}
	else
	{
		handleError("Loading SIP library failed!");
		isRegistering = false; // Reset the flag since registration failed
	}
}

void BackEnd::on_CallStateChanged(int role, int callId, int state, int status, QString remoteUri)
{
	this->callId = callId;

	if (state == PJSIP_INV_STATE_EARLY && status == 180)
	{
		if (role == 1)
		{
			int j = 0;
			QList<int> namePos;
			QList<int> numPos;

			while ((j = remoteUri.indexOf("\"", j)) != -1)
			{
				namePos.append(j);
				++j;
			}

			numPos.append(remoteUri.indexOf("sip:"));
			numPos.append(remoteUri.indexOf("@"));

			QString name = remoteUri.mid(namePos[0] + 1, namePos[1] - 1);
			QString num = remoteUri.mid(numPos[0] + 4, numPos[1] - (numPos[0] + 4));
			QString caller = name;

			if (name.size() <= 1)
				caller = num;

			setStatusStr(caller + " is calling...");
			sipState = "localRing";
			ringtone.play();
		}
		else
		{
			sipState = "remoteRing";
			outgoingRing.play();
		}
	}
	else if (state == PJSIP_INV_STATE_CONFIRMED && status == 200)
	{
		sipState = "calling";
		ringtone.stop();
		outgoingRing.stop();
	}
	else if (state == PJSIP_INV_STATE_DISCONNECTED)
	{
		setStatusStr("");
		sipState = "";
		ringtone.stop();
		outgoingRing.stop();
	}
}

void BackEnd::setButtonPhone(const bool &enabled)
{
	if (enabled != m_buttonPhoneEnabled)
	{
		m_buttonPhoneEnabled = enabled;
		emit buttonPhoneChanged();
	}
}

bool BackEnd::getButtonPhone()
{
	return m_buttonPhoneEnabled;
}

void BackEnd::setButtonHangup(const bool &enabled)
{
	if (enabled != m_buttonHangupEnabled)
	{
		m_buttonHangupEnabled = enabled;
		emit buttonHangupChanged();
	}
}

bool BackEnd::getButtonHangup()
{
	return m_buttonHangupEnabled;
}

void BackEnd::on_RegStateStarted(bool status)
{
	setStatusStr("MetaVoIP: Regstate started: " + QVariant(status).toString());
	if (status)
	{
		setButtonPhone(true);
		setButtonHangup(true);
	}
	else
	{
		setButtonPhone(false);
		setButtonHangup(false);
	}
}

void BackEnd::on_RegStateChanged(bool status)
{
	if (status)
	{
		setButtonPhone(true);
		setButtonHangup(true);
	}
	else
	{
		setButtonPhone(false);
		setButtonHangup(false);
	}
}

const QString BackEnd::getStr()
{
	return m_statusStr;
}

// Set status line value
void BackEnd::setStatusStr(const QString str)
{
	if (str != m_statusStr)
	{
		m_statusStr = str;
		emit statusStrChanged();
	}
}

const QString BackEnd::getNumber()
{
	return m_numberStr;
}

// Set status line value
void BackEnd::setNumberStr(const QString str)
{
	if (str != m_numberStr)
	{
		m_numberStr = str;
		emit numberStrChanged();
	}
}

const QString BackEnd::getSipServerStr()
{
	return sipServer;
}

// Set status line value
void BackEnd::setSipServerStr(const QString str)
{
	if (str != sipServer)
	{
		sipServer = str;
		emit sipServerStrChanged();
	}
}

const QString BackEnd::getSipPassStr()
{
	return sipPass;
}

// Set status line value
void BackEnd::setSipPassStr(const QString str)
{
	if (str != sipPass)
	{
		sipPass = str;
		emit numberStrChanged();
	}
}

const QString BackEnd::getSipUserStr()
{
	return sipUser;
}

// Set status line value
void BackEnd::setSipUserStr(const QString str)
{
	if (str != sipUser)
	{
		sipUser = str;
		emit numberStrChanged();
	}
}

const QString BackEnd::getSipPortStr()
{
	return sipPortText;
}

// Set status line value
void BackEnd::setSipPortStr(const QString str)
{
	if (str != sipPortText)
	{
		sipPortText = str;
		emit numberStrChanged();
	}
}

void BackEnd::exit()
{
	emit wantToQuit();
}

void BackEnd::getSettings()
{
	QFile settings(SETTINGS_FILE_PATH);
	if (settings.exists())
	{
		if (settings.open(QIODevice::ReadOnly))
		{
			setSipServerStr(settings.readLine().simplified());
			setSipUserStr(settings.readLine().simplified());
			setSipPassStr(settings.readLine().simplified());
			setProtocolIndex(settings.readLine().simplified().toInt());
			setSipPortStr(settings.readLine().simplified());
			settings.close();
		}
		else
			handleError("No read permission available");
	}

	outgoingRing.setSource(QUrl::fromLocalFile(":/sounds/outgoing.wav"));
	outgoingRing.setLoopCount(QSoundEffect::Infinite);
	ringtone.setSource(QUrl::fromLocalFile(":/sounds/incoming.wav"));
	ringtone.setLoopCount(QSoundEffect::Infinite);
}

void BackEnd::on_saveButton_clicked()
{
	if (getSipUserStr() != "" && getSipPassStr() != "" && getSipServerStr() != "" && getSipPortStr() != "")
	{
		QFile settings(SETTINGS_FILE_PATH);
		settings.remove();
		if (settings.open(QIODevice::WriteOnly))
		{
			QTextStream out(&settings);
			out << getSipServerStr().simplified();
			out << "\n";
			out << getSipUserStr().simplified();
			out << "\n";
			out << getSipPassStr().simplified();
			out << "\n";
			out << QString::number(getProtocolIndex());
			out << "\n";
			out << getSipPortStr().simplified();
			settings.close();

			registerSip();
		}
		else
			handleError("No write permission available");
	}
	else
		handleError("Please insert necessary values");
}

int BackEnd::getProtocolIndex()
{
	return m_currentProtocolIndex;
}

void BackEnd::setProtocolIndex(const int &currentIndex)
{
	if (m_currentProtocolIndex != currentIndex)
	{
		m_currentProtocolIndex = currentIndex;
		emit protocolIndexChanged();
	}
}

void BackEnd::setSipProtocol(const int &currentIndex)
{
	if (m_currentProtocolIndex != currentIndex)
	{
		m_currentProtocolIndex = currentIndex;
		emit protocolIndexChanged();
	}
}

QString BackEnd::errorMessage()
{
	return m_errorMessage;
}

void BackEnd::handleError(const QString &message)
{
	if (m_errorMessage != message)
	{
		m_errorMessage = message;
		emit errorMessageChanged();
	}
}