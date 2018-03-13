#ifndef CSERIALPORT_H
#define CSERIALPORT_H

#include <QtSerialPort/QSerialPort>
#include <QByteArray>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <stdio.h>
#include <QtSerialPort/QSerialPortInfo>
#include <QStringList>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <QTimer>
#include <QThread>

#ifndef ERREUR
#define ERREUR (char)-1
#endif

#define OK (char)0
#define TO 3000  // 3s timeout réception

using namespace std;

class CSerialPort : public QObject
{
    Q_OBJECT

public:
    explicit CSerialPort(QObject *parent = 0, const QString &portname = "/dev/");
    ~CSerialPort();
    int lireLigne(QByteArray &ligne);
    int open(QString portname);
    QStringList getAvailablePorts();
    int initialiser(QSerialPort::BaudRate vitesse, QSerialPort::DataBits data,
                    QSerialPort::Parity parity, QSerialPort::StopBits nbStop,
                    QSerialPort::FlowControl flow);
    char ecrire(const char *trame, int nbOctets);


private:
    //int mVit;
    //char mPar;
    //int mNbc;
    //char mNomVs[200];
    QSerialPort *mPs;
    QFile *mFile;
    QObject *mParent;

private slots:
    void onReadyRead();
    //void onErreur(QSerialPort::SerialPortError err);

signals:
    void sigData(QByteArray ba);
    void sigErreur(QSerialPort::SerialPortError err);
};

#endif // CSERIALPORT_H
