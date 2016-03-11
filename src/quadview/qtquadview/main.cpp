#include "quadview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuadView w;
    w.show();

    return a.exec();
}
