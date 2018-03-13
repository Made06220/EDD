#ifndef CSHAREDMEMORY_H
#define CSHAREDMEMORY_H

#include <QSharedMemory>
#include <QDebug>
#include "global.h"
#include "ccapteurdist_vl53l0x.h"
#include "ccapteurgps.h"
#include "ccapteurhum_.SI7021_A20.h"
#include "ccapteurtem_SI7021_A20.h"

// définition de la mémoire partagée
typedef struct {
    float temp_TC72;
    float temp_SHT20;
    float hum_SHT20;
} T_SHM_DATA;

class CSharedMemory : public QSharedMemory, public QThread
{

  Q_OBJECT

public:
  explicit CSharedMemory(QObject *parent = 0, int size = 10);
  ~CSharedMemory();
  int AttacherouCreer();
  int AttacherSeulement();
  int ecrire(int no, float mesure);
  float lire(int no);

private:
  int m_taille;
  float *m_adrBase;
  QObject *m_parent;

signals:
  void sigErreur(QString mess);
};

#endif // CSHAREDMEMORY_H
