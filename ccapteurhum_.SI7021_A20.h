#ifndef CCAPTEURHUM_SI7021_A20_H
#define CCAPTEURHUM_SI7021_A20_H

#include <QThread>
#include <QDebug>
#include <stdio.h>
#include "global.h"
#include "ci2c.h"

class CCapteurHum_SI7021_A20 : public QThread
{
    Q_OBJECT

private:
    int mNum;
    QSharedMemory *mShm;
    T_Mes *mData;   // pointeur du segment de mémoire partagé
    CI2c *mI2c;
    unsigned char *mAddr;
    bool mArret;
    bool mStopped;
    float lireMesureHum();

public:
    explicit CCapteurHum_SI7021_A20(QObject *parent=0, int no=0, unsigned char addr=0x40);
    ~CCapteurHum_SI7021_A20();
    void run();  // méthode virtuelle à implémenter, contenu du thread0

signals:

public slots:
    void stop();

};

#endif // CCAPTEURHUM_SI7021-A20_H
