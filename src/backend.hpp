#ifndef BACKEND_H
#define BACKEND_H

#include <QGuiApplication>
#include <QObject>
#include <QString>
#include <QDebug>
#include "MetaVoIP.hpp"
#include <QSoundEffect>

class BackEnd : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString statusStr READ getStr WRITE setStatusStr NOTIFY statusStrChanged)
	Q_PROPERTY(QString numberStr READ getNumber WRITE setNumberStr NOTIFY numberStrChanged)
	Q_PROPERTY(QString sipServerStr READ getSipServerStr WRITE setSipServerStr NOTIFY sipServerStrChanged)
	Q_PROPERTY(QString sipUserStr READ getSipUserStr WRITE setSipUserStr NOTIFY sipUserStrChanged)
	Q_PROPERTY(QString sipPassStr READ getSipPassStr WRITE setSipPassStr NOTIFY sipPassStrChanged)
	Q_PROPERTY(QString sipPortStr READ getSipPortStr WRITE setSipPortStr NOTIFY sipPortStrChanged)
	Q_PROPERTY(bool buttonPhoneEnabled READ getButtonPhone WRITE setButtonPhone NOTIFY buttonPhoneChanged)
	Q_PROPERTY(bool buttonHangupEnabled READ getButtonHangup WRITE setButtonHangup NOTIFY buttonHangupChanged)
	Q_PROPERTY(int currentProtocolIndex READ getProtocolIndex WRITE setSipProtocol NOTIFY protocolIndexChanged)
	Q_PROPERTY(QString errorMessage READ errorMessage WRITE handleError NOTIFY errorMessageChanged)

	Q_PROPERTY(QStringList inputDevicesList READ getInputDevices WRITE on_InputListChanged NOTIFY audioInputsChanged)
	Q_PROPERTY(QStringList outputDevicesList READ getOutputDevices WRITE on_OutputListChanged NOTIFY audioOutputsChanged)

	Q_PROPERTY(int audioInputIndex READ getAudioInputIndex WRITE setAudioInputIndex NOTIFY audioInputIndexChanged)
	Q_PROPERTY(int audioOutputIndex READ getAudioOutputIndex WRITE setAudioOutputIndex NOTIFY audioOutputIndexChanged)

public:
	explicit BackEnd(QObject *parent = nullptr);
	~BackEnd() override;

	// Getters
	const QString getStr();
	const QString getNumber();
	bool getButtonPhone();
	bool getButtonHangup();
	QString errorMessage();
	Q_INVOKABLE QStringList getInputDevices() const;
	Q_INVOKABLE QStringList getOutputDevices() const;
	Q_INVOKABLE const QString getInputDeviceStr();
	Q_INVOKABLE const QString getOutputDeviceStr();

public slots:

	void exit();

	void on_CallStateChanged(int role, int callId, int state, int status, QString remoteUri);
	void on_RegStateStarted(bool status);
	void on_RegStateChanged(bool status);
	void on_InputListChanged(QStringList list);
	void on_OutputListChanged(QStringList list);
	void setStatusStr(const QString str);
	void setNumberStr(const QString str);
	void setSipServerStr(const QString str);
	void setSipUserStr(const QString str);
	void setSipPassStr(const QString str);
	void setSipPortStr(const QString str);
	void setButtonPhone(const bool &enabled);
	void setButtonHangup(const bool &enabled);
	void setProtocolIndex(const int &currentIndex);
	void setSipProtocol(const int &index);
	void setAudioInputIndex(const int &currentIndex);
	void setAudioOutputIndex(const int &currentIndex);
	void setInputDevice(const QString &str);
	void setOutputDevice(const QString &str);
	void on_phoneButton_clicked();
	void on_saveButton_clicked();
	void on_b0_clicked();
	void on_b1_clicked();
	void on_b2_clicked();
	void on_b3_clicked();
	void on_b4_clicked();
	void on_b5_clicked();
	void on_b6_clicked();
	void on_b7_clicked();
	void on_b8_clicked();
	void on_b9_clicked();
	void on_bPound_clicked();
	void on_bStar_clicked();
	void on_hangButton_clicked();
	void handleError(const QString &message);

signals:
	void wantToQuit();
	void statusStrChanged();
	void numberStrChanged();
	void buttonPhoneChanged();
	void buttonHangupChanged();
	void sipServerStrChanged();
	void sipUserStrChanged();
	void sipPassStrChanged();
	void sipPortStrChanged();
	void sipProtocolStrChanged();
	void protocolIndexChanged();
	void errorMessageChanged();
	void audioInputsChanged();
	void audioOutputsChanged();
	void audioInputChanged();
	void audioOutputChanged();
	void audioInputIndexChanged();
	void audioOutputIndexChanged();

private:
	const QString SETTINGS_FILE_PATH = "settings.dat";
	QSoundEffect ringtone, outgoingRing;
	MetaVoIP *metaVoIP;
	QString m_statusStr = "";
	QString m_numberStr = "";
	bool m_buttonPhoneEnabled = false;
	bool m_buttonHangupEnabled = false;
	int callId;
	int m_currentProtocolIndex = 0;
	QString sipState, sipUser, sipServer, sipPass, sipProto, sipPortText;
	// QStringList m_inputsList = {"default", "lavrate", "samplerate", "speexrate", "pulse", "speex", "upmix", "vdownmix", "hw:CARD=sofessx8336,DEV=0", "hw:CARD=sofessx8336,DEV=1", "hw:CARD=sofessx8336,DEV=2", "plughw:CARD=sofessx8336,DEV=0", "plughw:CARD=sofessx8336,DEV=1", "plughw:CARD=sofessx8336,DEV=2", "sysdefault:CARD=sofessx8336", "dsnoop:CARD=sofessx8336,DEV=0", "dsnoop:CARD=sofessx8336,DEV=1", "dsnoop:CARD=sofessx8336,DEV=2"};
	QStringList m_inputsList;
	QStringList m_outputsList;
	void getSettings();
	void registerSip();
	int getProtocolIndex();
	int getAudioInputIndex();
	int getAudioOutputIndex();
	const QString getSipServerStr();
	const QString getSipPassStr();
	const QString getSipUserStr();
	const QString getSipPortStr();

	bool isRegistering = false;
	QString m_errorMessage;
	QString m_currentInputDevice, m_currentOutputDevice = "";
	// ComboBox indexes
	int m_currentInputDeviceIndex, m_currentOutputDeviceIndex = -1;
};

#endif // BACKEND_H
