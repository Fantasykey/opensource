#include <QApplication>

#include "cboxwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGridBoxWidget w;
    CHBoxWidget hBox(nullptr);
    hBox.addWidget(new QLabel("Address:"));
    hBox.addWidget(new QLineEdit);
    hBox.addWidget(new QLabel("Write:"));
    hBox.addWidget(new QLineEdit);
    hBox.addWidget(new QLabel("Check:"));
    hBox.addWidget(new QLineEdit);
    hBox.show();

    CVBoxWidget vBox(nullptr);
    vBox.addWidget(new QLabel("Address:"));
    vBox.addWidget(new QLineEdit);
    vBox.addWidget(new QLabel("Write:"));
    vBox.addWidget(new QLineEdit);
    vBox.addWidget(new QLabel("Check:"));
    vBox.addWidget(new QLineEdit);
    vBox.show();

    CGridBoxWidget gridBox(nullptr);
    gridBox.addWidget(new QLabel("Address:"), 0, 0);
    gridBox.addWidget(new QLineEdit, 0, 1);
    gridBox.addWidget(new QLabel("Write:"), 0, 2);
    gridBox.addWidget(new QLineEdit, 0, 3);
    gridBox.addWidget(new QLabel("Check:"), 1, 0);
    gridBox.addWidget(new QLineEdit, 1, 1);
    gridBox.show();

    w.addWidget(&hBox, 0, 0, Qt::AlignTop);
    w.addWidget(&vBox, 0, 1, 2, 1);
    w.addWidget(&gridBox, 1,0);
    w.show();

    return a.exec();
}
