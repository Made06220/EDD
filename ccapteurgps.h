#ifndef CCAPTEURGPS_H
#define CCAPTEURGPS_H

#include <QThread>
#include <QDebug>
#include <QByteArray>
#include <stdio.h>
#include "global.h"
#include "cserialport.h"


class CCapteurGps : public QThread
{
    Q_OBJECT

private:
    int mNum; // numéro de la mesure
    QSharedMemory *mShm;  // mémoire partagée
    T_Mes *mData;   // pointeur du segment de mémoire partagé
    CSerialPort *mPs;  // gestion du port série
    bool mArret;
    bool mStopped;
    int lireMesure(QByteArray &latitude, QByteArray &longitude);
public:
    explicit CCapteurGps(QObject *parent = 0, const char *nomvs = "/dev/ttyAMA0", int no = 0, int vit = 9600, char par = 'N', int nbc = 8);
    ~CCapteurGps();
    void run();  // méthode virtuelle à implémenter, contenu du thread

signals:

public slots:
    void stop();
};

#endif // CCAPTEURGPS_H
