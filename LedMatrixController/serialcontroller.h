#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>

class SerialController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)
    Q_PROPERTY(QStringList availablePorts READ availablePorts NOTIFY availablePortsChanged)

public:
    explicit SerialController(QObject *parent = nullptr);
    ~SerialController();

    bool isConnected() const;
    QString statusMessage() const;
    QStringList availablePorts() const;

public slots:
    // Connette alla porta seriale selezionata
    void connectToPort(const QString &portName);
    // Disconnette dalla porta seriale
    void disconnectPort();
    // Invia la matrice 8x8 come stringhe binarie all'Arduino
    // matrix è una lista di 8 stringhe, ognuna da 8 caratteri '0'/'1'
    void sendMatrix(const QStringList &matrix);
    // Aggiorna la lista delle porte disponibili
    void refreshPorts();

signals:
    void connectedChanged();
    void statusMessageChanged();
    void availablePortsChanged();
    void serialDataReceived(const QString &data);

private slots:
    void onReadyRead();
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serial;
    QString m_statusMessage;
    QStringList m_availablePorts;
    QString m_receiveBuffer;

    void setStatusMessage(const QString &msg);
};

#endif // SERIALCONTROLLER_H
