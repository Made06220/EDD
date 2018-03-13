#ifndef CCAPTEURTEM_SI7021_A20_H
#define CCAPTEURTEM_SI7021_A20_H

#include "global.h"
#include "cmsg.h"

class CCapteurTem_SI7021_A20 : public QThread
{
  Q_OBJECT

public:
  CCapteurTem_SI7021_A20();
  ~CCapteurTem_SI7021_A20();
  void virtualrun();
  float lireMesure();

private:
  int mNum;
  T_Mes *mData;
  unsigned char *mAddr;
  CCapteurTem_SI7021_A20 *mesure;

public slots:
  void stop();
};

#endif // CCAPTEURTEM_H
