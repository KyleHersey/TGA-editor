#include <QApplication>
#include "imageGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imageGUI w;

    //show gui
    w.show();

    return a.exec();
}
