#include "link_description.h"

using namespace db;

QString LinkDescription::name() const
{
    return m_name;
}

void LinkDescription::setName(const QString& name)
{
    m_name = name;
}

LinkDescription::Type LinkDescription::type() const
{
    return m_type;
}

void LinkDescription::setType(LinkDescription::Type type)
{
    m_type = type;
}

int LinkDescription::port() const
{
    return m_port;
}

void LinkDescription::setPort(int port)
{
    m_port = port;
}

QString LinkDescription::device() const
{
    return m_device;
}

void LinkDescription::setDevice(const QString& device)
{
    m_device = device;
}

int LinkDescription::baudRate() const
{
    return m_baudRate;
}

void LinkDescription::setBaudRate(int baudRate)
{
    m_baudRate = baudRate;
}

bool LinkDescription::isAutoConnect() const
{
    return m_autoConnect;
}

void LinkDescription::setAutoConnect(bool autoConnect)
{
    m_autoConnect = autoConnect;
}

bool LinkDescription::isConnected() const
{
    return m_connected;
}

void LinkDescription::setConnected(bool connected)
{
    m_connected = connected;
}

int LinkDescription::bytesSentSec() const
{
    return m_bytesSentSec;
}

void LinkDescription::setBytesSentSec(int bytesSentSec)
{
    m_bytesSentSec = bytesSentSec;
}

int LinkDescription::bytesRecvSec() const
{
    return m_bytesRecvSec;
}

void LinkDescription::setBytesRecvSec(int bytesRecvSec)
{
    m_bytesRecvSec = bytesRecvSec;
}