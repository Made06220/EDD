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
  capteurs.append(new CCapteurHum_SI7021_A20(this, data[i].numCap));
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
