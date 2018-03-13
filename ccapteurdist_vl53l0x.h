#ifndef CCAPTEURDIST_VL53L0X_H
#define CCAPTEURDIST_VL53L0X_H

#include "cgpio.h"
#include "csharedmemory.h"

class CCapteurDist_VL53L0X : public QThread
{
    Q_OBJECT

private:
    int mNum;
    CSharedMemory *mShm;
    T_Mes *mData;   // pointeur du segment de mémoire partagé
    CGpio *mGpio;
    unsigned char mNoI2C;
    bool mArret;
    bool mStopped;
    float lireMesure();
    int getDistance();

public:
    explicit CCapteurDist_VL53L0X(QObject *parent = 0, int no = 0, unsigned char noI2C = 0x29);
    ~CCapteurDist_VL53L0X();
    void run();  // méthode virtuelle à implémenter, contenu du thread

signals:

public slots:
    void stop();

};

#endif // CCAPTEURDIST_VL53L0X_H
