#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <QObject>
#include <QStringList>
#include <pjsua2.hpp> // Include PJSUA2 library header

using namespace pj;

class AudioDeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit AudioDeviceManager(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getInputDevices() const;
    Q_INVOKABLE QStringList getOutputDevices() const;

private:
    void initializeDevices();

    QStringList m_inputDevices;
    QStringList m_outputDevices;
    AudDevManager &m_audDevManager;
};

#endif // AUDIOMANAGER_HPP
