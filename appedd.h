#ifndef APPEDD_H
#define APPEDD_H

#include <QMainWindow>
#include <QList>
#include <QSharedMemory>
#include "ccapteurhum_.SI7021_A20.h"
#include "ccapteurdist_vl53l0x.h"
#include "ccapteurgps.h"
#include "ccapteurtem_SI7021_A20.h"
#include "ccontrolercamera.h"
#include "csharedmemory.h"

namespace Ui {
  class AppEdd;
}

class AppEdd : public QMainWindow
{
  Q_OBJECT

public:
  explicit AppEdd(QWidget *parent = 0);
  ~AppEdd();
  int threadOn();
  int threadOff();

private:
  Ui::AppEdd *ui;
  CCapteurHum_SI7021_A20 *hum;
  CCapteurDist_VL53L0X *dist;
  CCapteurTem_SI7021_A20 *temp;
  CCapteurGps *gps;
//  CSave *save;
  QList<QThread *> capteurs;
  QSharedMemory *mshm;

};

#endif // APPEDD_H
