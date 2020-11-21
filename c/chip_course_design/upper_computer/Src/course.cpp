#include "course.h"
#include "debug.h"
#include "usart_data.h"
#include "ui_course.h"
#include<QRegExp>
#include<QValidator>
#include<QColorDialog>

#include<QDebug>

Course::Course(QWidget *parent, const QStringList a_parity) : QDialog(nullptr)
  , ui(new Ui::Course)
{
    mParent = qobject_cast<UsartData *>(parent);
    mParent->hide();
    connect(mParent, SIGNAL(Read(QString)), this, SLOT(mParent_Read(QString)));

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);

    int count = a_parity.count();
    if(count > 0) ui->MyFormerParity->setText(a_parity[0]);
    if(count > 1) ui->MyLastParity->setText(a_parity[1]);

    ui->MyExitBtn->setFixedSize(24, 24);
    ui->MyExitBtn->setStyleSheet(
                "QPushButton{border-image: url(image/noun_False_normal.ico);border-width:0px;border-radius:12px;}"
                "QPushButton:pressed{ border-image: url(image/noun_False_press.ico);}"
                "QPushButton:hover{border-image: url(image/noun_False_hover.ico);}");
    connect(ui->MyExitBtn, &QPushButton::clicked, this, &QWidget::close);

    ui->MyLCD_H->display("0000");
    ui->MyLCD_L->display("0000");

    connect(ui->MyGetFileNameBtn, SIGNAL(clicked()), this, SLOT(MyGetFileNameBtn_clicked()));

    //setting
    connect(ui->MySaveSetting, SIGNAL(clicked()), this, SLOT(MySaveSetting_clicked()));
    connect(ui->MyLoadSetting, SIGNAL(clicked()), this, SLOT(MyLoadSetting_clicked()));

    //Colorful lights
    QRegExp regExp("([1‐9]?\\d|1\\d{2}|2[0‐4]\\d|25[0‐5])");
    QValidator *validator = new QRegExpValidator(regExp, this);
    ui->MyRedEdit->setValidator(validator);
    ui->MyRedEdit->setValidator(validator);
    ui->MyRedEdit->setValidator(validator);

    connect(ui->MyRedSlider, SIGNAL(valueChanged(int)), this, SLOT(MyRedSlider_valueChanged(int)));
    connect(ui->MyGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(MyGreenSlider_valueChanged(int)));
    connect(ui->MyBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(MyBlueSlider_valueChanged(int)));
    connect(ui->MyRedEdit, SIGNAL(returnPressed()), this, SLOT(MyRedEdit_returnPressed()));
    connect(ui->MyGreenEdit, SIGNAL(returnPressed()), this, SLOT(MyGreenEdit_returnPressed()));
    connect(ui->MyBlueEdit, SIGNAL(returnPressed()), this, SLOT(MyBlueEdit_returnPressed()));
    connect(ui->MyColorBtn, SIGNAL(clicked()), this, SLOT(MyColorBtn_clicked()));

    //LED
    connect(ui->MyLED_0, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));
    connect(ui->MyLED_1, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));
    connect(ui->MyLED_2, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));
    connect(ui->MyLED_3, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));
    connect(ui->MyLED_4, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));
    connect(ui->MyLED_5, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));
    connect(ui->MyLED_6, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));
    connect(ui->MyLED_7, SIGNAL(clicked(bool)), this, SLOT(MyLED_clicked(bool)));

    //KEY
    connect(ui->MyKEY_0, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));
    connect(ui->MyKEY_1, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));
    connect(ui->MyKEY_2, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));
    connect(ui->MyKEY_3, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));
    connect(ui->MyKEY_4, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));
    connect(ui->MyKEY_5, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));
    connect(ui->MyKEY_6, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));
    connect(ui->MyKEY_7, SIGNAL(clicked(bool)), this, SLOT(MyKEY_clicked(bool)));

    //motor
    connect(ui->MyMotorBtn, SIGNAL(clicked(bool)), this, SLOT(MyMotorBtn_clicked(bool)));
    connect(ui->MySpeedSpin, SIGNAL(valueChanged(int)), this, SLOT(MySpeedSpin_valueChanged(int)));
    connect(ui->MyReverseMotor, SIGNAL(clicked()), this, SLOT(MyReverseMotor_clicked()));

    //beep
    connect(ui->MyBeepBtn, SIGNAL(clicked(bool)), this, SLOT(MyBeepBtn_clicked(bool)));
    connect(ui->MyBeepFreq, SIGNAL(returnPressed()), this, SLOT(MyBeepFreq_returnPressed()));

    connect(ui->MySaveParity, SIGNAL(clicked()), this, SLOT(MySaveParity_clicked()));
    connect(ui->MyLoadParity, SIGNAL(clicked()), this, SLOT(MyLoadParity_clicked()));

    this->show();
}

void Course::Write(QString a_str)
{
    mParent->Write(ui->MyFormerParity->text()+
                   a_str+
                   ui->MyLastParity->text());
}

void Course::setColor()
{
    ui->MyColorBtn->setStyleSheet(tr("color:%1;background-color:%2")
                                  .arg(QColor(255-mColor.red()
                                              , 255-mColor.green()
                                              , 255-mColor.blue()).name())
                                  .arg(mColor.name()));
}

QString Course::Complement(QString a_str, int max)
{
    int length = a_str.length();
    for(int i = 0; i < max-length; ++i) {
        a_str.insert(0, '0');
    }
    return a_str;
}

#include<QFileDialog>
#include<QMessageBox>
void Course::MyGetFileNameBtn_clicked()
{
    QString str = QFileDialog::getOpenFileName();
    if(str.isEmpty()) {
        QMessageBox::information(this, tr("配置"), tr("文件获取失败！"));
    } else {
        ui->MyFileName->setText(str);
    }
}

#include<QMessageBox>
void Course::MySaveSetting_clicked()
{
    QFile file(ui->MyFileName->text());
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << tr("Color:%1").arg(mColor.name()) << endl
            << tr("LED:%1").arg(ui->MyLED_Status->toolTip()) << endl
            << tr("KEY:%1").arg(ui->MyKEY_Status->toolTip()) << endl
            << tr("Motor:%1").arg(ui->MyMotorBtn->isChecked()) << endl
            << tr("Motor-Speed:%1").arg(ui->MySpeedSpin->value()) << endl
            << tr("LCDNumber-H:%1").arg(Complement(mLCD_H, 4)) << endl
            << tr("LCDNumber-L:%1").arg(Complement(mLCD_L, 4)) << endl
            << tr("Beep:%1").arg(ui->MyBeepBtn->isChecked()) << endl
            << tr("Beep-Freq:%1").arg(ui->MyBeepFreq->text());
        QMessageBox::information(this, tr("配置"), tr("保存成功！"));
    } else {
        QMessageBox::information(this, tr("配置"), tr("保存失败！"));
    }
}

void Course::MyLoadSetting_clicked()
{
    QFile file(ui->MyFileName->text());
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString temp = in.readAll();
        mParent_Read(CHIP+temp);
        Write(temp);
        file.close();
        QMessageBox::information(this, tr("配置"), tr("配置成功！"));
    } else {
        QMessageBox::information(this, tr("配置"), tr("配置失败！"));
    }
}

void Course::MyRedSlider_valueChanged(int a_value)
{
    if(ui->MyRedEdit->text().toInt() != a_value)
    {
        disconnect(ui->MyRedEdit, SIGNAL(returnPressed()), this, SLOT(MyRedEdit_returnPressed()));
        ui->MyRedEdit->setText(QString::number(a_value));
        connect(ui->MyRedEdit, SIGNAL(returnPressed()), this, SLOT(MyRedEdit_returnPressed()));
    }

    mColor.setRed(a_value);
    setColor();
    Write(tr("Color:%1").arg(mColor.name()));
}

void Course::MyGreenSlider_valueChanged(int a_value)
{
    if(ui->MyGreenEdit->text().toInt() != a_value)
    {
        disconnect(ui->MyGreenEdit, SIGNAL(returnPressed()), this, SLOT(MyGreenEdit_returnPressed()));
        ui->MyGreenEdit->setText(QString::number(a_value));
        connect(ui->MyGreenEdit, SIGNAL(returnPressed()), this, SLOT(MyGreenEdit_returnPressed()));
    }

    mColor.setGreen(a_value);
    setColor();
    Write(tr("Color:%1").arg(mColor.name()));
}

void Course::MyBlueSlider_valueChanged(int a_value)
{
    if(ui->MyBlueEdit->text().toInt() != a_value)
    {
        disconnect(ui->MyBlueEdit, SIGNAL(returnPressed()), this, SLOT(MyBlueEdit_returnPressed()));
        ui->MyBlueEdit->setText(QString::number(a_value));
        connect(ui->MyBlueEdit, SIGNAL(returnPressed()), this, SLOT(MyBlueEdit_returnPressed()));
    }

    mColor.setBlue(a_value);
    setColor();
    Write(tr("Color:%1").arg(mColor.name()));
}

void Course::MyRedEdit_returnPressed()
{
    int value = ui->MyRedEdit->text().toInt();
    if(ui->MyRedSlider->value() != value)
    {
        disconnect(ui->MyRedSlider, SIGNAL(valueChanged(int)), this, SLOT(MyRedSlider_valueChanged(int)));
        ui->MyRedSlider->setValue(value);
        connect(ui->MyRedSlider, SIGNAL(valueChanged(int)), this, SLOT(MyRedSlider_valueChanged(int)));
    }

    mColor.setRed(value);
    setColor();
    Write(tr("Color:%1").arg(mColor.name()));
}

void Course::MyGreenEdit_returnPressed()
{
    int value = ui->MyGreenEdit->text().toInt();
    if(ui->MyGreenSlider->value() != value)
    {
        disconnect(ui->MyGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(MyGreenSlider_valueChanged(int)));
        ui->MyGreenSlider->setValue(value);
        connect(ui->MyGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(MyGreenSlider_valueChanged(int)));
    }

    mColor.setGreen(value);
    setColor();
    Write(tr("Color:%1").arg(mColor.name()));
}

void Course::MyBlueEdit_returnPressed()
{
    int value = ui->MyBlueEdit->text().toInt();
    if(ui->MyBlueSlider->value() != value)
    {
        disconnect(ui->MyBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(MyBlueSlider_valueChanged(int)));
        ui->MyBlueSlider->setValue(value);
        connect(ui->MyBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(MyBlueSlider_valueChanged(int)));
    }

    mColor.setBlue(value);
    setColor();
    Write(tr("Color:%1").arg(mColor.name()));
}

#include<QColorDialog>
void Course::MyColorBtn_clicked()
{
    mColor = QColorDialog::getColor(mColor, this, tr("取色器"));
    disconnect(ui->MyRedSlider, SIGNAL(valueChanged(int)), this, SLOT(MyRedSlider_valueChanged(int)));
    disconnect(ui->MyGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(MyGreenSlider_valueChanged(int)));
    disconnect(ui->MyBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(MyBlueSlider_valueChanged(int)));
    disconnect(ui->MyRedEdit, SIGNAL(returnPressed()), this, SLOT(MyRedEdit_returnPressed()));
    disconnect(ui->MyGreenEdit, SIGNAL(returnPressed()), this, SLOT(MyGreenEdit_returnPressed()));
    disconnect(ui->MyBlueEdit, SIGNAL(returnPressed()), this, SLOT(MyBlueEdit_returnPressed()));

    ui->MyRedSlider->setValue(mColor.red());
    ui->MyGreenSlider->setValue(mColor.green());
    ui->MyBlueSlider->setValue(mColor.blue());
    ui->MyRedEdit->setText(QString::number(mColor.red()));
    ui->MyGreenEdit->setText(QString::number(mColor.green()));
    ui->MyBlueEdit->setText(QString::number(mColor.blue()));

    connect(ui->MyRedSlider, SIGNAL(valueChanged(int)), this, SLOT(MyRedSlider_valueChanged(int)));
    connect(ui->MyGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(MyGreenSlider_valueChanged(int)));
    connect(ui->MyBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(MyBlueSlider_valueChanged(int)));
    connect(ui->MyRedEdit, SIGNAL(returnPressed()), this, SLOT(MyRedEdit_returnPressed()));
    connect(ui->MyGreenEdit, SIGNAL(returnPressed()), this, SLOT(MyGreenEdit_returnPressed()));
    connect(ui->MyBlueEdit, SIGNAL(returnPressed()), this, SLOT(MyBlueEdit_returnPressed()));

    setColor();
    Write(tr("Color:%1").arg(mColor.name()));
}

void Course::MyLED_clicked(bool a_bool)
{
    static uint8_t LED_status = 0;

    QRadioButton *temp = qobject_cast<QRadioButton *>(sender());
    if(temp == ui->MyLED_0) {
        a_bool ? (LED_status |= 0x01) : (LED_status &= ~0x01);
    } else if(temp == ui->MyLED_1) {
        a_bool ? (LED_status |= 0x02) : (LED_status &= ~0x02);
    } else if(temp == ui->MyLED_2) {
        a_bool ? (LED_status |= 0x04) : (LED_status &= ~0x04);
    } else if(temp == ui->MyLED_3) {
        a_bool ? (LED_status |= 0x08) : (LED_status &= ~0x08);
    } else if(temp == ui->MyLED_4) {
        a_bool ? (LED_status |= 0x10) : (LED_status &= ~0x10);
    } else if(temp == ui->MyLED_5) {
        a_bool ? (LED_status |= 0x20) : (LED_status &= ~0x20);
    } else if(temp == ui->MyLED_6) {
        a_bool ? (LED_status |= 0x40) : (LED_status &= ~0x40);
    } else if(temp == ui->MyLED_7) {
        a_bool ? (LED_status |= 0x80) : (LED_status &= ~0x80);
    }
    uint8_t H = LED_status/16;
    uint8_t L = LED_status%16;
    QString str = tr("0X%1%2").
            arg(char((H>9) ? (H-10+'A') : (H+'0'))).
            arg(char((L>9) ? (L-10+'A') : (L+'0')));
    ui->MyLED_Status->setToolTip(str);

    Write(tr("LED:%1").arg(str));
}

void Course::MyKEY_clicked(bool a_bool)
{
    static uint8_t KEY_status = 0;

    QRadioButton *temp = qobject_cast<QRadioButton *>(sender());
    if(temp == ui->MyKEY_0) {
        a_bool ? (KEY_status |= 0x01) : (KEY_status &= ~0x01);
    } else if(temp == ui->MyKEY_1) {
        a_bool ? (KEY_status |= 0x02) : (KEY_status &= ~0x02);
    } else if(temp == ui->MyKEY_2) {
        a_bool ? (KEY_status |= 0x04) : (KEY_status &= ~0x04);
    } else if(temp == ui->MyKEY_3) {
        a_bool ? (KEY_status |= 0x08) : (KEY_status &= ~0x08);
    } else if(temp == ui->MyKEY_4) {
        a_bool ? (KEY_status |= 0x10) : (KEY_status &= ~0x10);
    } else if(temp == ui->MyKEY_5) {
        a_bool ? (KEY_status |= 0x20) : (KEY_status &= ~0x20);
    } else if(temp == ui->MyKEY_6) {
        a_bool ? (KEY_status |= 0x40) : (KEY_status &= ~0x40);
    } else if(temp == ui->MyKEY_7) {
        a_bool ? (KEY_status |= 0x80) : (KEY_status &= ~0x80);
    }
    uint8_t H = KEY_status/16;
    uint8_t L = KEY_status%16;
    QString str = tr("0X%1%2").
            arg(char((H>9) ? (H-10+'A') : (H+'0'))).
            arg(char((L>9) ? (L-10+'A') : (L+'0')));
    ui->MyKEY_Status->setToolTip(str);

    Write(tr("KEY:%1").arg(str));
}

void Course::MyMotorBtn_clicked(bool a_bool)
{
    Write(tr("Motor:%1").arg(a_bool));
}

void Course::MySpeedSpin_valueChanged(int a_value)
{
    Write(tr("Motor-Speed:%1").arg(a_value));

}

void Course::MyReverseMotor_clicked()
{
    ui->MySpeedSpin->setValue(-ui->MySpeedSpin->value());
}

void Course::MyBeepBtn_clicked(bool a_bool)
{
    Write(tr("Beep:%1").arg(a_bool));
}

void Course::MyBeepFreq_returnPressed()
{
    Write(tr("Beep-Freq:%1").arg(ui->MyBeepFreq->text()));
}

#include<QFile>
#include<QDataStream>
#include<QFileDialog>
void Course::MySaveParity_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "保存校验文件", "./parity.bin", "*.bin");
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << ui->MyFormerParity->text() << ui->MyLastParity->text();
        file.close();
    }
}

void Course::MyLoadParity_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "打开校验文件", "./", "*.bin");
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        QString temp;
        in >> temp;
        ui->MyFormerParity->setText(temp);
        in >> temp;
        ui->MyLastParity->setText(temp);
        file.close();
    }
}

//Color:#6e0000
void Course::mResolveColor(QString &a_str)
{
    a_str.remove(0, 6);
    qDebug() << tr("解析---------------Color:%1").arg(a_str.mid(0, 7));
    Debug::instance()->append(tr("解析---------------Color:%1").arg(a_str.mid(0, 7)), Write_debug);

    mColor.setNamedColor(a_str.mid(0, 7));

    disconnect(ui->MyRedSlider, SIGNAL(valueChanged(int)), this, SLOT(MyRedSlider_valueChanged(int)));
    disconnect(ui->MyGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(MyGreenSlider_valueChanged(int)));
    disconnect(ui->MyBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(MyBlueSlider_valueChanged(int)));
    disconnect(ui->MyRedEdit, SIGNAL(returnPressed()), this, SLOT(MyRedEdit_returnPressed()));
    disconnect(ui->MyGreenEdit, SIGNAL(returnPressed()), this, SLOT(MyGreenEdit_returnPressed()));
    disconnect(ui->MyBlueEdit, SIGNAL(returnPressed()), this, SLOT(MyBlueEdit_returnPressed()));
    disconnect(ui->MyColorBtn, SIGNAL(clicked()), this, SLOT(MyColorBtn_clicked()));

    ui->MyRedSlider->setValue(mColor.red());
    ui->MyGreenSlider->setValue(mColor.green());
    ui->MyBlueSlider->setValue(mColor.blue());
    ui->MyRedEdit->setText(QString::number(mColor.red()));
    ui->MyGreenEdit->setText(QString::number(mColor.green()));
    ui->MyBlueEdit->setText(QString::number(mColor.blue()));
    setColor();

    connect(ui->MyRedSlider, SIGNAL(valueChanged(int)), this, SLOT(MyRedSlider_valueChanged(int)));
    connect(ui->MyGreenSlider, SIGNAL(valueChanged(int)), this, SLOT(MyGreenSlider_valueChanged(int)));
    connect(ui->MyBlueSlider, SIGNAL(valueChanged(int)), this, SLOT(MyBlueSlider_valueChanged(int)));
    connect(ui->MyRedEdit, SIGNAL(returnPressed()), this, SLOT(MyRedEdit_returnPressed()));
    connect(ui->MyGreenEdit, SIGNAL(returnPressed()), this, SLOT(MyGreenEdit_returnPressed()));
    connect(ui->MyBlueEdit, SIGNAL(returnPressed()), this, SLOT(MyBlueEdit_returnPressed()));
    connect(ui->MyColorBtn, SIGNAL(clicked()), this, SLOT(MyColorBtn_clicked()));
    a_str.remove(0, 7);
}

//LED:0X10
void Course::mResolveLED(QString &a_str)
{
    a_str.remove(0, 4);
    qDebug() << tr("解析---------------LED:%1").arg(a_str.mid(0, 4));
    Debug::instance()->append(tr("解析---------------LED:%1").arg(a_str.mid(0, 4)), Write_debug);

    char ch1 = a_str.at(2).toLatin1();
    char ch2 = a_str.at(3).toLatin1();
    uint8_t temp = (((ch1>='A')?(ch1+10-'A'):(ch1-'0'))<<4) + ((ch2>='A')?(ch2+10-'A'):(ch2-'0'));
    ui->MyLED_0->setChecked(temp & 0x01);
    ui->MyLED_1->setChecked(temp & 0x02);
    ui->MyLED_2->setChecked(temp & 0x04);
    ui->MyLED_3->setChecked(temp & 0x08);
    ui->MyLED_4->setChecked(temp & 0x10);
    ui->MyLED_5->setChecked(temp & 0x20);
    ui->MyLED_6->setChecked(temp & 0x40);
    ui->MyLED_7->setChecked(temp & 0x80);

    ui->MyLED_Status->setToolTip(a_str.mid(0, 4));
    a_str.remove(0, 4);
}

//KEY:0X20
void Course::mResolveKEY(QString &a_str)
{
    a_str.remove(0, 4);
    qDebug() << tr("解析---------------KEY:%1").arg(a_str.mid(0, 4));
    Debug::instance()->append(tr("解析---------------KEY:%1").arg(a_str.mid(0, 4)), Write_debug);

    char ch1 = a_str.at(2).toLatin1();
    char ch2 = a_str.at(3).toLatin1();
    uint8_t temp = (((ch1>='A')?(ch1+10-'A'):(ch1-'0'))<<4) + ((ch2>='A')?(ch2+10-'A'):(ch2-'0'));
    ui->MyKEY_0->setChecked(temp & 0x01);
    ui->MyKEY_1->setChecked(temp & 0x02);
    ui->MyKEY_2->setChecked(temp & 0x04);
    ui->MyKEY_3->setChecked(temp & 0x08);
    ui->MyKEY_4->setChecked(temp & 0x10);
    ui->MyKEY_5->setChecked(temp & 0x20);
    ui->MyKEY_6->setChecked(temp & 0x40);
    ui->MyKEY_7->setChecked(temp & 0x80);

    ui->MyKEY_Status->setToolTip(a_str.mid(0, 4));
    a_str.remove(0, 4);
}

//Motor-Speed:-72
//Motor:1
void Course::mResolveMotor(QString &a_str)
{
    if(a_str.at(5) == ':') {
        a_str.remove(0, 6);
        ui->MyMotorBtn->setChecked(a_str.at(0)=='1');
        qDebug() << tr("解析---------------Motor:%1").arg(a_str.mid(0, 1));
        Debug::instance()->append(tr("解析---------------Motor:%1").arg(a_str.mid(0, 1)), Write_debug);
        a_str.remove(0, 1);
    } else {
        a_str.remove(0, 12);
        int cnt = 0;
        while(cnt < a_str.length()
              && ((a_str.at(cnt) >= '0' && a_str.at(cnt) <= '9') || a_str.at(cnt) == '-'))
            cnt++;
        ui->MySpeedSpin->setValue(a_str.mid(0, cnt).toInt());
        qDebug() << tr("解析---------------Motor-Speed:%1").arg(a_str.mid(0, cnt));
        Debug::instance()->append(tr("解析---------------Motor-Speed:%1").arg(a_str.mid(0, cnt)), Write_debug);
        a_str.remove(0, cnt);
    }
}

//LCDNumber-H:AAAA
//LCDNumber-L:BBBB
void Course::mResolveLCDNumber(QString &a_str)
{
    int cnt = 0;
    while(12+cnt < a_str.length()
          && ((a_str.at(12+cnt) >= '0' && a_str.at(12+cnt) <= '9')
              ||(a_str.at(12+cnt) >= 'a' && a_str.at(12+cnt) <= 'f')
              ||(a_str.at(12+cnt) >= 'A' && a_str.at(12+cnt) <= 'F')))
        ++cnt;
    QString temp = Complement(a_str.mid(12, cnt), 4);
    if(a_str.at(10) == 'H') {
        mLCD_H = temp;
        ui->MyLCD_H->display(temp);
        qDebug() << tr("解析---------------LCDNumber-H:%1").arg(mLCD_H);
        Debug::instance()->append(tr("解析---------------LCDNumber-H:%1").arg(mLCD_H), Write_debug);
    } else {
        mLCD_L = temp;
        ui->MyLCD_L->display(temp);
        qDebug() << tr("解析---------------LCDNumber-L:%1").arg(mLCD_L);
        Debug::instance()->append(tr("解析---------------LCDNumber-L:%1").arg(mLCD_L), Write_debug);
    }
    a_str.remove(0, 12+cnt);
}

//Beep:1
//Beep-Freq:1000
void Course::mResolveBeep(QString &a_str)
{
    if(a_str.at(4) == ':') {
        ui->MyBeepBtn->setChecked(a_str.at(5) == '1');
        qDebug() << tr("解析---------------Beep:%1").arg(a_str.at(5));
        Debug::instance()->append(tr("解析---------------Beep:%1").arg(a_str.at(5)), Write_debug);
        a_str.remove(0, 5);
    } else {
        a_str.remove(0, 10);
        int cnt = 0;
        while(cnt < a_str.length()
              && (a_str.at(cnt) >= '0' && a_str.at(cnt) <= '9'))
            cnt++;
        ui->MyBeepFreq->setText(a_str.mid(0, cnt));
        qDebug() << tr("解析---------------Beep-Freq:%1").arg(a_str.mid(0, cnt));
        Debug::instance()->append(tr("解析---------------Beep-Freq:%1").arg(a_str.mid(0, cnt)), Write_debug);
        a_str.remove(0, cnt);
    }
}

void Course::mParent_Read(QString a_str)
{
    qDebug() << tr("接收到的数据：%1").arg(a_str);

    if(a_str.startsWith(CHIP)) { //一级校验
        a_str.remove(0, sizeof(CHIP)-1);

        QString former = ui->MyFormerParity->text();
        QString last = ui->MyLastParity->text();
        if(a_str.startsWith(former) && a_str.endsWith(last)) { //二级校验
            a_str.remove(0, former.length());
            a_str.remove(a_str.length()-last.length(), last.length());

            while(true) { //解析
                bool flag = false;

                if(a_str.startsWith("Color:")) { //七彩灯
                    flag = true;
                    mResolveColor(a_str);
                } else if(a_str.startsWith("KEY:")) { //KEY
                    flag = true;
                    mResolveKEY(a_str);
                } else if(a_str.startsWith("LED:")) { //LED
                    flag = true;
                    mResolveLED(a_str);
                } else if(a_str.startsWith("Motor")) {
                    flag = true;
                    mResolveMotor(a_str);
                } else if(a_str.startsWith("LCDNumber-")) {
                    flag = true;
                    mResolveLCDNumber(a_str);
                } else if(a_str.startsWith("Beep")) {
                    flag = true;
                    mResolveBeep(a_str);
                }

                static int cnt = 0;
                if(flag == false) {
                    if(a_str.isEmpty()) {
                        cnt = 0;
                        return;
                    } else {
                        a_str.remove(0, 1);
                    }
                } else {
                    cnt++;
                    qDebug() << tr("这是解析成功的第%1次.").arg(cnt);
                    Debug::instance()->append(tr("这是解析成功的第%1次.").arg(cnt), Write_debug);
                }
            }
        } else {
            return;
        }
    }
}

/* QPoint QMouseEvent::pos() const
    Returns the position of the mouse cursor, relative to the widget that received the event.
    If you move the widget as a result of the mouse event, use the global position returned by globalPos() to avoid a shaking motion.
 */
#include<QMouseEvent>
//拖拽操作
void Course::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = true;
        //获得鼠标的初始位置
        mouseStartPoint = event->globalPos();
        //mouseStartPoint = event->pos();
        //获得窗口的初始位置
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void Course::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        //获得鼠标移动的距离
        QPoint distance = event->globalPos() - mouseStartPoint;
        //QPoint distance = event->pos() - mouseStartPoint;
        //改变窗口的位置
        this->move(windowTopLeftPoint + distance);
    }
}

void Course::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}

#include<QKeyEvent>
void Course::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        this->close();
    }
}

#include<QPaintEvent>
#include<QPainter>
void Course::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QPen pen = painter.pen();
    pen.setWidth(2);
    pen.setColor(QColor(70, 70, 70));
    painter.setPen(pen);
    painter.drawRect(5, 5, this->width()-10, this->height()-10);
    pen.setColor(QColor(65, 65, 65));
    painter.setPen(pen);
    painter.drawRect(4, 4, this->width()-8, this->height()-8);
    pen.setColor(QColor(60, 60, 60));
    painter.setPen(pen);
    painter.drawRect(3, 3, this->width()-6, this->height()-6);
    pen.setColor(QColor(55, 55, 55));
    painter.setPen(pen);
    painter.drawRect(2, 2, this->width()-4, this->height()-4);
    pen.setColor(QColor(50, 50, 50));
    painter.setPen(pen);
    painter.drawRect(1, 1, this->width()-2, this->height()-2);
}

#include<QCloseEvent>
#include "usart_data.h"
void Course::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    mParent->show();
}
