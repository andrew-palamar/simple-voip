#include "AudioDeviceManager.hpp"
#include <QDebug>

AudioDeviceManager::AudioDeviceManager(QObject *parent) : QObject(parent), m_audDevManager(pj::Endpoint::instance().audDevManager())
{
    initializeDevices();
}

void AudioDeviceManager::initializeDevices()
{
    AudDevManager &audDevManager = Endpoint::instance().audDevManager();
    unsigned count = audDevManager.getDevCount();
    qDebug() << "Available Audio Devices: " << count;

    auto media_devices = audDevManager.enumDev2();

    for (const auto &info : media_devices)
    {
        QString deviceName = QString::fromStdString(info.name);

        // Device inputs
        if (info.inputCount > 0)
        {
            m_inputDevices.append(deviceName);
        }

        // Device outputs
        if (info.outputCount > 0)
        {
            m_outputDevices.append(deviceName);
        }

        // qDebug() << "Device " << info.id << ": " << deviceName << " - Inputs:" << info.inputCount << " Outputs:" << info.outputCount;
    }
    // Lookup device ID by its name. Name could be found running 'aplay -L' and 'arecord -L'
    // qDebug() << "lookupDev(): " << audDevManager.lookupDev("ALSA", "pulse");

    // qDebug() << "Current input device: " << audDevManager.getCaptureDev();
    // qDebug() << "Current output device: " << audDevManager.getPlaybackDev();
    // Should not be called for device numbers < 0
    // qDebug() << "Current input volume: " << audDevManager.getInputVolume();
    // qDebug() << "Current output volume: " << audDevManager.getOutputVolume();
}

QStringList AudioDeviceManager::getInputDevices() const
{
    return m_inputDevices;
}

QStringList AudioDeviceManager::getOutputDevices() const
{
    return m_outputDevices;
}
