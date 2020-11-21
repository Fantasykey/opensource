#include "usart_data.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    QFile file("style.css");
//    if( file.open(QFile::ReadOnly))
//    {
//        QString styleSheet = QLatin1String(file.readAll());

//        a.setStyleSheet(styleSheet);
//        file.close();
//    } else {
//        QMessageBox::warning(nullptr, "warning", "Open failed", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }

    UsartData window;
    window.show();

    return app.exec();
}
