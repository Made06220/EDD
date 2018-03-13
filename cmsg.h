#ifndef CMSG_H
#define CMSG_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include "global.h"

#define TYPE_MESS_MESURE 1
#define TYPE_MESS_INCRUSTER 2
#define TYPE_MESS_TIMERINC 21
#define TYPE_MESS_ORDRE_CAMERA 5
#define TYPE_MESS_ACK_ORDRE 11
#define TYPE_MESS_STOP_THREAD

using namespace std;

// type de message pour une mesure

typedef union umess {
    double valDouble;
    int valInt;
    char valCh[AFFMAX];
} U_Mess;

typedef struct {
    long type;
    int noMesure;
    U_Mess corps;
} T_MessMess;

// type de message pour autoriser les mesures à incruster
// -1 si pas d'incrustation de la mesure

typedef struct {
    long type;
    int c[9];  // nO du capteur à incruster
} T_MessInc;

// type pour un ordre

typedef struct {
    long type;
    char ordre[255];
} T_MessOrdre;

// type pour changer l'interval d'un timer

typedef struct {
    long type;
    int interval;
    bool enable; // pour start ou stop timer
} T_MessIntTimer;

class CMsg : public QObject
{
public:
    explicit CMsg(QObject *parent);
    ~CMsg();
    int sendMessage(long type, const void *mess, size_t lg);
    int getMessage(long type, void *mess, size_t lg);
    int initialiser(const char *nomfic, int val);
    int detruire();

private:
    T_Mes message;
    int mId;
    int mInited;
    char mNomFic[255];
    int mMsgId;
    key_t mClef;
    T_MessMess mMess;

signals:
    void sigMailReady(long type);

};
#endif
