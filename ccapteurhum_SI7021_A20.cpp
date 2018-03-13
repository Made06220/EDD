#include "ccapteurhum_.SI7021_A20.h"


float CCapteurHum::lireMesureHum()
{
  unsigned char lecture[2];
  unsigned char ecriture=0xE3;
  char aff[50];
  int res;

  mI2c->ecrire(mAddr, &ecriture, 1);
  usleep(100000);
  res=mI2c->lire(mAddr, lecture, 2);
  if (res != 2)
      qDebug() << "CCapteurHum:lireMesureHum res=" << res;
  unsigned char MSB = lecture[0];
  unsigned char LSB = lecture[1];
  sprintf(aff,"CCapteurHum res=%d msb=%02X lsb=%02X",res, MSB, LSB);
//    qDebug() << aff;
  return res;
}

CCapteurHum::CCapteurHum(QObject *parent, int no, unsigned char addr):
  QThread(parent)
{
  int res;

  mNum = no;
  mAddr = addr;

  unsigned char init[] = {0xE6, 0x03};

  mI2c = CI2c::getInstance(this, '1');
  if(mI2c == NULL)
    qDebug("CCapteurHum: Pb init I2C");

  res = mI2c->ecrire(mAddr, init, 2);

  if (res != 2) qDebug("CCapteurHum: pb ecriture");
  usleep(250000);

  mShm = new QSharedMemory(KEY, this);
  if (!mShm->attach())
      qDebug(mShm->errorString().toStdString().c_str());
  mData = (T_Mes *)mShm->data();
  qDebug("Démarrage du thread CCapteurHum !");
}

CCapteurHum::~CCapteurHum()
{
  stop();
  mI2c->freeInstance();
  mShm->detach();
  delete mShm;
}

void CCapteurHum::stop()
{
  mArret=true;
  while (!mStopped);
}

void CCapteurHum::run()
{
  float mesureHum;

  mArret=false;
  mStopped=false;
  while(!mArret) {
      // écriture de la mesure dans le segment de mémoire partagé
      mesureHum = lireMesureHum();
      char chMes[30];
      sprintf(chMes,"Hum:%3.1f ",mesureHum);
      mShm->lock(); // on prend la mémoire partagée
      strcpy(mData[mNum].valMes,chMes);  // écriture dans la mémoire partagée
      mShm->unlock(); // on libère la mémmoire partagée
      sleep(1); // lecture toutes les s
  } // while
  mStopped=true;
}
