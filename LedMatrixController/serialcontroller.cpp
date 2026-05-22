#include "serialcontroller.h"
#include <QDebug>
#include <QThread>

SerialController::SerialController(QObject *parent)
    : QObject(parent)
    , m_serial(new QSerialPort(this))
{
    connect(m_serial, &QSerialPort::readyRead, this, &SerialController::onReadyRead);
    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialController::onErrorOccurred);

    refreshPorts();
    setStatusMessage("Nessuna porta connessa");
}

SerialController::~SerialController()
{
    if (m_serial->isOpen())
        m_serial->close();
}

bool SerialController::isConnected() const
{
    return m_serial->isOpen();
}

QString SerialController::statusMessage() const
{
    return m_statusMessage;
}

QStringList SerialController::availablePorts() const
{
    return m_availablePorts;
}

void SerialController::refreshPorts()
{
    m_availablePorts.clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        m_availablePorts << info.portName();
    }
    emit availablePortsChanged();
}

void SerialController::connectToPort(const QString &portName)
{
    if (m_serial->isOpen()) {
        m_serial->close();
        emit connectedChanged();
    }

    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        setStatusMessage("Connesso a " + portName);
        emit connectedChanged();
        qDebug() << "Connesso a" << portName;
    } else {
        setStatusMessage("Errore: impossibile aprire " + portName);
        qDebug() << "Errore connessione:" << m_serial->errorString();
    }
}

void SerialController::disconnectPort()
{
    if (m_serial->isOpen()) {
        m_serial->close();
        setStatusMessage("Disconnesso");
        emit connectedChanged();
    }
}

void SerialController::sendMatrix(const QStringList &matrix)
{
    if (!m_serial->isOpen()) {
        setStatusMessage("Errore: nessuna porta connessa!");
        return;
    }

    if (matrix.size() != 8) {
        setStatusMessage("Errore: la matrice deve avere 8 righe");
        return;
    }

    for (int i = 0; i < 8; i++) {
        QString row = matrix[i];
        if (row.length() != 8) {
            setStatusMessage(QString("Errore: riga %1 non ha 8 bit").arg(i));
            return;
        }
        QByteArray data = (row + "\n").toUtf8();
        m_serial->write(data);
        m_serial->flush();
        QThread::msleep(20);
    }

    setStatusMessage("Matrice inviata!");
    qDebug() << "Matrice inviata all'Arduino";
}

void SerialController::onReadyRead()
{
    m_receiveBuffer += QString::fromUtf8(m_serial->readAll());

    // Processa le righe complete
    while (m_receiveBuffer.contains('\n')) {
        int idx = m_receiveBuffer.indexOf('\n');
        QString line = m_receiveBuffer.left(idx).trimmed();
        m_receiveBuffer = m_receiveBuffer.mid(idx + 1);

        if (!line.isEmpty()) {
            qDebug() << "Arduino:" << line;
            emit serialDataReceived(line);

            // Aggiorna lo status con i messaggi dell'Arduino
            if (line.contains("salvata") || line.contains("ricevuta") || line.contains("Pronto")) {
                setStatusMessage("Arduino: " + line);
            }
        }
    }
}

void SerialController::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        setStatusMessage("Errore seriale: " + m_serial->errorString());
        qDebug() << "Errore seriale:" << error << m_serial->errorString();
        if (m_serial->isOpen()) {
            m_serial->close();
            emit connectedChanged();
        }
    }
}

void SerialController::setStatusMessage(const QString &msg)
{
    if (m_statusMessage != msg) {
        m_statusMessage = msg;
        emit statusMessageChanged();
    }
}
