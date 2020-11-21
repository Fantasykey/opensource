#include <QApplication>

#include <QDebug>
#include "clogwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CLogWidget logWidget;
    logWidget.setTabPosition(QTabWidget::South);

    logWidget.createWindow("Debug");
    logWidget("Debug") << __DATE__;
    QString tmp;
    logWidget("Debug") >> tmp;
    qDebug() <<  tmp;

    logWidget.createWindow("Error");
    logWidget("Error") << __TIME__;
    logWidget("Error") >> tmp;
    qDebug() <<  tmp;


    logWidget.show();

    return a.exec();
}
