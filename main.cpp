#include <QApplication>
#include <iostream>
#include "model/allusers.h"
#include "model/warehouse.h"
#include "controller/maincontroller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainController* start=new MainController();
    start->exe();

    return a.exec();
}
