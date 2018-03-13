#include "cserialport.h"

CSerialPort::CSerialPort(QObject *parent, const QString &portname)
{
    mParent = parent;
    mPs = new QSerialPort(parent);
    connect(mPs, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(mPs, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onErreur(QSerialPort::SerialPortError)));
    qDebug() << "L'objet CRs232c est créé par " << mParent->thread();
    mPs->setPortName(portname);
    qDebug() << portname;
}

CSerialPort::~CSerialPort()
{
    mPs->close();
    delete mPs;
    qDebug() << "L'objet CRs232c est détruit par " << mParent->thread();
}

int CSerialPort::initialiser(QSerialPort::BaudRate vitesse, QSerialPort::DataBits data,
                             QSerialPort::Parity parity, QSerialPort::StopBits nbStop,
                             QSerialPort::FlowControl flow)
{
    mPs->setBaudRate(vitesse);
    mPs->setDataBits(data);
    mPs->setParity(parity);
    mPs->setStopBits(nbStop);
    mPs->setFlowControl(flow);
    return 0;
}

//QStringList CSerialPort::getAvailablePorts()
//{
//    QStringList portsDescription;
//    QList<QSerialPortInfo> portInfo;

//    portInfo = QSerialPortInfo::availablePorts();
//    qDebug() << portInfo.size();

//    foreach(const QSerialPortInfo &info, portInfo)
//    {
//        qDebug() << "Name: " << info.portName() << endl;
//        qDebug() << "Description: " << info.description() << endl;
//        qDebug() << "Manufacturer: " << info.manufacturer() << endl;

//        portsDescription.append(info.portName() + " - " + info.description());
//        qDebug() << info.portName() << " - " << info.description() << endl;
//    }

//    return portsDescription;
//}

int CSerialPort::open(QString portname)
{
    bool res = false;
    res = mPs->open(QIODevice::ReadWrite);
    if (!res)
    {
        emit sigErreur(mPs->error());
        mPs->close();
    } // if res
    return res;
}

void CSerialPort::onReadyRead()
{
    QByteArray ba;
    ba = mPs->readAll();
    emit(sigData(ba));
}

int CSerialPort::lireLigne(QByteArray &ligne)
{
    ligne = mFile->readLine();
    return 1;
}
