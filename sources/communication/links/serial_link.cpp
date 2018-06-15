#include "serial_link.h"

// Qt
#include <QSerialPort>
#include <QDebug>

using namespace comm;

SerialLink::SerialLink(const QString& portName, qint32 baudRate,
                       QObject* parent):
    AbstractLink(parent),
    m_port(new QSerialPort(portName, this))
{
    m_port->setBaudRate(baudRate);

    connect(m_port, &QSerialPort::readyRead, this, &SerialLink::readSerialData);
    connect(m_port, static_cast<void(QSerialPort::*)
            (QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialLink::onError);
}

bool SerialLink::isConnected() const
{
    return m_port->isOpen();
}

QString SerialLink::device() const
{
    return m_port->portName();
}

qint32 SerialLink::baudRate() const
{
    return m_port->baudRate();
}

void SerialLink::connectLink()
{
    if (this->isConnected()) return;

    if (!m_port->open(QIODevice::ReadWrite))
    {
        qWarning("Serial port connection error: '%s'!",
                 qPrintable(m_port->errorString()));

        m_port->close();
    }
    else
    {
        emit connectedChanged(true);
    }
}

void SerialLink::disconnectLink()
{
    if (!this->isConnected()) return;

    m_port->close();
    emit connectedChanged(false);
}

void SerialLink::setDevice(QString device)
{
    if (m_port->portName() == device) return;

    m_port->setPortName(device);
    emit deviceChanged(m_port->portName());
}

void SerialLink::setBaudRate(qint32 baudRate)
{
    if (m_port->baudRate() == baudRate) return;

    m_port->setBaudRate(baudRate);
    emit baudRateChanged(m_port->baudRate());
}

bool SerialLink::sendDataImpl(const QByteArray& data)
{
    return m_port->write(data.data(), data.size()) > 0;
}


void SerialLink::readSerialData()
{
    this->receiveData(m_port->readAll());
}

void SerialLink::onError()
{
    if (m_port->error() == QSerialPort::ResourceError && this->isConnected()) this->disconnectLink();
}
