#include "appedd.h"
#include <QApplication>
#include "ccapteurtem_SI7021_A20.h"

using namespace std ;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AppEdd w;
  w.show();

  return a.exec();
}

