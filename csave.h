#ifndef CSAVE_H
#define CSAVE_H

#include <QThread>
#include <QObject>
#include "global.h"

class CSave : public QThread
{
    Q_OBJECT
public:
    CSave();
};

#endif // CSAVE_H
