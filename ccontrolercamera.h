#ifndef CCONTROLERCAMERA_H
#define CCONTROLERCAMERA_H

#include <QObject>
#include <QString>
#include <QDebug>


class CControlerCamera
{
public:
  CControlerCamera(QObject *parent = 0, CMsg *msg = 0);
  ~CControlerCamera();

private:
  CMsg *mMsg; //
//  QHostAddress mAdrIP;     // adr IP de la caméra
  int mPort;
  QString mMdp;            // Mot de passe WIFI
//  QTcpSocket *mSock;

signals:

private slots:
  void onMessReady(long type);
  void onReadyRead();
  void onConnected();
  void onDisconnected();

public slots:

};

#endif // CCONTROLERCAMERA_H
