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
    Q_INVOKABLE uint32_t getCaptureDev() const;
    Q_INVOKABLE void setCaptureDev(QString device);
    Q_INVOKABLE uint32_t getPlaybackDev() const;
    Q_INVOKABLE void setPlaybackDev(QString device);
    Q_INVOKABLE uint32_t getInputVolume() const;
    Q_INVOKABLE uint32_t getOutputVolume() const;
    Q_INVOKABLE void setInputVolume(uint32_t volume, bool keep = true);
    Q_INVOKABLE void setOutputVolume(uint32_t volume, bool keep = true);
    Q_INVOKABLE void initializeDevices();

private:
    AudDevManager &m_audDevManager;

    QStringList m_inputDevices;
    QStringList m_outputDevices;
};

#endif // AUDIOMANAGER_HPP
