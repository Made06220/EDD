#include "appedd.h"
#include "ccapteurtem_SI7021_A20.h"
#include "ui_appedd.h"
#include <iostream>
#include <stdio.h>

using namespace std ;

AppEdd::AppEdd(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AppEdd)
{
  ui->setupUi(this);
  hum = new CCapteurHum_SI7021_A20(this, mNum);
  dist = new CCapteurDist_VL53L0X(this, mNum);
  temp = new CCapteurTem_SI7021_A20(this, mNum);
  gps = new CCapteurGps(this, mNum);
//  save = new CSave(this, nbCapteur);
  capteurs.append(new CCapteurHum_SI7021_A20(this, data[1].numCap));
  capteurs.append(new CCapteurDist_VL53L0X(this, data[2].numCap));
  capteurs.append(new CCapteurTem_SI7021_A20(this, data[3].numCap));
  capteurs.append(new CCapteurGps(this, data[4].numCap));
//  capteurs.append(CSave(this, data[5].numCap));

// Initialisation de la zone de mémoire partagée
  mshm = new QSharedMemory(KEY, this);
    mshm->attach();
    if (!mshm->isAttached())
    {
      int res = mshm->create(NBMAXCAP*sizeof(T_Memo));
      if(res == false)
        qDebug(mshm->errorString().toStdString().c_str());
    }

}

AppEdd::~AppEdd()
{
  delete ui;
}

int AppEdd::threadOn()
{
  hum->start();
  dist->start();
  temp->start();
  gps->start();
//  save->start();
}

int AppEdd::threadOff()
{
  hum->stop();
  dist->stop();
  temp->stop();
  gps->stop();
//  save->stop();
}
