#include "AudioDeviceManager.hpp"
#include <QDebug>

AudioDeviceManager::AudioDeviceManager(QObject *parent) : QObject(parent), m_audDevManager(pj::Endpoint::instance().audDevManager())
{
}

void AudioDeviceManager::initializeDevices()
{
    unsigned count = m_audDevManager.getDevCount();
    qDebug() << "Available Audio Devices: " << count;

    auto media_devices = m_audDevManager.enumDev2();

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
}

QStringList AudioDeviceManager::getInputDevices() const
{
    return m_inputDevices;
}

QStringList AudioDeviceManager::getOutputDevices() const
{
    return m_outputDevices;
}

uint32_t AudioDeviceManager::getCaptureDev() const
{
    return m_audDevManager.getCaptureDev();
}

void AudioDeviceManager::setCaptureDev(QString device)
{
    // Lookup device ID by its name. Name could be found running 'aplay -L' and 'arecord -L'
    auto devId = m_audDevManager.lookupDev("ALSA", device.toStdString());
    if (devId >= 0) // Check if device ID is valid
    {
        m_audDevManager.setCaptureDev(devId);
    }
    else
    {
        qDebug() << "Failed to set capture device: Device not found.";
    }
}

// Get current output device
uint32_t AudioDeviceManager::getPlaybackDev() const
{
    return m_audDevManager.getPlaybackDev();
}

void AudioDeviceManager::setPlaybackDev(QString device)
{
    auto devId = m_audDevManager.lookupDev("ALSA", device.toStdString());
    if (devId >= 0) // Check if device ID is valid
    {
        m_audDevManager.setPlaybackDev(devId);
    }
    else
    {
        qDebug() << "Failed to set playback device: Device not found.";
    }
}

// Get current input volume, percent
uint32_t AudioDeviceManager::getInputVolume() const
{
    uint32_t device;
    m_audDevManager.getCaptureDev() >= 0 ? device = m_audDevManager.getInputVolume() : device = -1;
    return device;
}

// Get current output volume, percent
uint32_t AudioDeviceManager::getOutputVolume() const
{
    uint32_t device;
    m_audDevManager.getPlaybackDev() >= 0 ? device = m_audDevManager.getOutputVolume() : device = -1;
    return device;
}

void AudioDeviceManager::setInputVolume(uint32_t volume, bool keep)
{
    m_audDevManager.setInputVolume(volume, keep);
}

void AudioDeviceManager::setOutputVolume(uint32_t volume, bool keep)
{
    m_audDevManager.setOutputVolume(volume, keep);
}
