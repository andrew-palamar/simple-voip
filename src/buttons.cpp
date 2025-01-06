#include "backend.hpp"
#include <QSound>

void BackEnd::on_b1_clicked()
{
	setNumberStr(m_numberStr + "1");
	QSound::play(":/sounds/Dtmf-1.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("1");
}

void BackEnd::on_b2_clicked()
{
	setNumberStr(m_numberStr + "2");
	QSound::play(":/sounds/Dtmf-2.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("2");
}

void BackEnd::on_b3_clicked()
{
	setNumberStr(m_numberStr + "3");
	QSound::play(":/sounds/Dtmf-3.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("3");
}

void BackEnd::on_b4_clicked()
{
	setNumberStr(m_numberStr + "4");
	QSound::play(":/sounds/Dtmf-4.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("4");
}

void BackEnd::on_b5_clicked()
{
	setNumberStr(m_numberStr + "5");
	QSound::play(":/sounds/Dtmf-5.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("5");
}

void BackEnd::on_b6_clicked()
{
	setNumberStr(m_numberStr + "6");
	QSound::play(":/sounds/Dtmf-6.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("6");
}

void BackEnd::on_b7_clicked()
{
	setNumberStr(m_numberStr + "7");
	QSound::play(":/sounds/Dtmf-7.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("7");
}

void BackEnd::on_b8_clicked()
{
	setNumberStr(m_numberStr + "8");
	QSound::play(":/sounds/Dtmf-8.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("8");
}

void BackEnd::on_b9_clicked()
{
	setNumberStr(m_numberStr + "9");
	QSound::play(":/sounds/Dtmf-9.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("9");
}

void BackEnd::on_b0_clicked()
{
	setNumberStr(m_numberStr + "0");
	QSound::play(":/sounds/Dtmf-0.wav");
	if (sipState == "calling")
		metaVoIP->sendDtmf("0");
}

void BackEnd::on_bPound_clicked()
{
	setNumberStr(m_numberStr + "#");
	QSound::play(":/sounds/Dtmf-pound.wav");
	// Is this legit?
	if (sipState == "calling")
		metaVoIP->sendDtmf("#");
}

void BackEnd::on_bStar_clicked()
{
	setNumberStr(m_numberStr + "*");
	QSound::play(":/sounds/Dtmf-star.wav");
	// Is this legit?
	if (sipState == "calling")
		metaVoIP->sendDtmf("*");
}

void BackEnd::on_hangButton_clicked()
{
	setNumberStr("");
	metaVoIP->hangupCall(callId);
	sipState = "";
	setStatusStr("");
}

void BackEnd::on_phoneButton_clicked()
{
	if (sipState == "calling")
	{
		metaVoIP->holdCall(callId);
		sipState = "calling";
	}
	else if (sipState == "localRing")
	{
		metaVoIP->acceptCall(callId);
		sipState = "calling";
		ringtone.stop();
	}
	else if (sipState != "localRing" && m_numberStr != "")
	{
		metaVoIP->makeCall("sip:" + m_numberStr + "@" + sipServer);
		setStatusStr("Calling " + m_numberStr + "...");
		setNumberStr("");
	}
}
