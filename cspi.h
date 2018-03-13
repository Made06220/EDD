#ifndef CSPI_H
#define CSPI_H

#include <QObject>
#include <QDebug>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

class CSpi : public QObject
{
  Q_OBJECT
public:
  explicit CSpi(QObject *parent = 0, char noCs = '0', int speed=7000000, bool csHigh = false, int mode = SPI_MODE_0);
  int lireNOctets(quint8 *buffer, int n);
  int ecrireNOctets(quint8 *buffer, int n);
  int lireEcrire(quint8 *em, int nbTotal);

private:
  int init();
  int m_addr;
  char m_noCe;
  int m_speed;
  int m_fileSpi;
  bool m_csHigh;
  int m_mode;

signals:
  void sigErreur(QString msg);
};

#endif // CSPI_H
