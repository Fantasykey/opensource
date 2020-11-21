#include "usart_data.h"
#include "ui_usart_data.h"

#include "debug.h"
#include "course.h"

#include <windows.h>
#include <dbt.h>
#include <devguid.h>
#include <setupapi.h>
#include <initguid.h>

#include <QTime>

#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

UsartData::UsartData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);

    ui->MyDebug->setStyleSheet("QPushButton{  \
                                    min-width:80px;  \
                                    min-height:32px;  \
                                    }  \
                                    QPushButton{  \
                                    color:rgb(233, 236, 243);  \
                                        min-height:20;  \
                                        border-style:solid;  \
                                        border-top-left-radius:2px;  \
                                        border-top-right-radius:2px;  \
                                    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241),   \
                                                                stop: 0.3 rgb(33,184,150),  \
                                                                stop: 1 rgb(29,170,140));  \
                                    border:1px;  \
                                        border-radius:5px;padding:2px 4px;/*border-radius控制圆角大小*/  \
                                    }  \
                                    QPushButton:hover{  /*鼠标放上后*/  \
                                    color:rgb(233, 236, 243);  \
                                        min-height:20;  \
                                        border-style:solid;  \
                                        border-top-left-radius:2px;  \
                                        border-top-right-radius:2px;  \
                                    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241),   \
                                                                stop: 0.3 rgb(37,189,252),  \
                                                                stop: 1 rgb(32,170,240));  \
                                    border:1px;  \
                                        border-radius:5px;padding:2px 4px;  \
                                    }  \
                                    QPushButton:pressed{ /*按下按钮后*/  \
                                    color:rgb(233, 236, 243);  \
                                        min-height:20;  \
                                        border-style:solid;  \
                                        border-top-left-radius:2px;  \
                                        border-top-right-radius:2px;  \
                                    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241),  \
                                                                stop: 0.3 rgb(38,190,255),  \
                                                                stop: 1 rgb(33,184,240));  \
                                    border:1px;  \
                                        border-radius:5px;padding:2px 4px;  \
                                    };");

    ui->MyGotoCourse->setStyleSheet("QPushButton{  \
                                    min-width:80px;  \
                                    min-height:32px;  \
                                    }  \
                                    QPushButton{  \
                                    color:rgb(233, 236, 243);  \
                                        min-height:20;  \
                                        border-style:solid;  \
                                        border-top-left-radius:2px;  \
                                        border-top-right-radius:2px;  \
                                    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241),   \
                                                                stop: 0.3 rgb(33,184,150),  \
                                                                stop: 1 rgb(29,170,140));  \
                                    border:1px;  \
                                        border-radius:5px;padding:2px 4px;/*border-radius控制圆角大小*/  \
                                    }  \
                                    QPushButton:hover{  /*鼠标放上后*/  \
                                    color:rgb(233, 236, 243);  \
                                        min-height:20;  \
                                        border-style:solid;  \
                                        border-top-left-radius:2px;  \
                                        border-top-right-radius:2px;  \
                                    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241),   \
                                                                stop: 0.3 rgb(37,189,252),  \
                                                                stop: 1 rgb(32,170,240));  \
                                    border:1px;  \
                                        border-radius:5px;padding:2px 4px;  \
                                    }  \
                                    QPushButton:pressed{ /*按下按钮后*/  \
                                    color:rgb(233, 236, 243);  \
                                        min-height:20;  \
                                        border-style:solid;  \
                                        border-top-left-radius:2px;  \
                                        border-top-right-radius:2px;  \
                                    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 rgb(226,236,241),  \
                                                                stop: 0.3 rgb(38,190,255),  \
                                                                stop: 1 rgb(33,184,240));  \
                                    border:1px;  \
                                        border-radius:5px;padding:2px 4px;  \
                                    };");

    ui->MyExitBtn->setFixedSize(24, 24);
    ui->MyExitBtn->setStyleSheet(
            "QPushButton{border-image: url(image/noun_False_normal.ico);border-width:0px;border-radius:12px;}"
            "QPushButton:pressed{ border-image: url(image/noun_False_press.ico);}"
            "QPushButton:hover{border-image: url(image/noun_False_hover.ico);}");
    connect(ui->MyExitBtn, &QPushButton::clicked, this, &QWidget::close);

    mEncode = utf8;
    connect(&mSerialPort, SIGNAL(readyRead()), this, SLOT(mSerialPort_readyRead()));
    connect(&mSendTimer, SIGNAL(timeout()), this, SLOT(mSendTimer_timeout()));

    SerialPortUpdate();

    connect(ui->MySerialPort, SIGNAL(currentIndexChanged(const QString&)),\
            this, SLOT(MySerialPort_currentIndexChanged(const QString&)));
    connect(ui->MyBaud, SIGNAL(currentIndexChanged(const QString&)),\
            this, SLOT(MyBaud_currentIndexChanged(const QString&)));
    connect(ui->MyStops, SIGNAL(currentIndexChanged(const QString&)),\
            this, SLOT(MyStops_currentIndexChanged(const QString&)));
    connect(ui->MyDatas, SIGNAL(currentIndexChanged(const QString&)),\
            this, SLOT(MyDatas_currentIndexChanged(const QString&)));
    connect(ui->MyOddEven, SIGNAL(currentIndexChanged(const QString&)),\
            this, SLOT(MyOddEven_currentIndexChanged(const QString&)));
    connect(ui->MyControl, SIGNAL(clicked()), this, SLOT(MyControl_clicked()));

    connect(ui->MySaveRec, SIGNAL(clicked()), this, SLOT(MySaveRec_clicked()));
    connect(ui->MyClearRec, SIGNAL(clicked()),ui->MyReceWin, SLOT(clear()));//清除接收窗
    connect(ui->MyEncode, SIGNAL(currentIndexChanged(const QString&)),
            this, SLOT(MyEncode_currentIndexChanged(const QString&)));
    connect(ui->MyIsHex, SIGNAL(clicked(bool)), this, SLOT(MyIsHex_clicked(bool)));
    ui->MyInsertTime->setToolTip(tr("以换行回车断帧"));

    connect(ui->MyReceWin, SIGNAL(textChanged()), this, SLOT(MyReceWin_textChanged()));//自动滚行

    ui->MySend->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Return));
    connect(ui->MySend, SIGNAL(clicked()), this, SLOT(MySend_clicked()));
    connect(ui->MyClearSen, SIGNAL(clicked()),ui->MySendWin, SLOT(clear()));//清除发送窗
    connect(ui->MyOpenFile, SIGNAL(clicked()), this, SLOT(MyOpenFile_clicked()));
    connect(ui->MyCirculSend, SIGNAL(clicked(bool)), this, SLOT(MyCirculSend_clicked(bool)));

    mCirculPeriod = 100;
    QRegExp regx("[1-9]+[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx,ui->MyCirculPeriod);
    ui->MyCirculPeriod->setValidator(validator);
    connect(ui->MyCirculPeriod, SIGNAL(textChanged(const QString &)), this, SLOT(MyCirculPeriod_textChanged(const QString &)));

    connect(ui->MySaveParity, SIGNAL(clicked()), this, SLOT(MySaveParity_clicked()));
    connect(ui->MyLoadParity, SIGNAL(clicked()), this, SLOT(MyLoadParity_clicked()));

    USB_Init();


    connect(ui->MyDebug, SIGNAL(clicked()), this, SLOT(MyDebug_clicked()));
    connect(ui->MyGotoCourse, SIGNAL(clicked()), this, SLOT(MyGotoCourse_clicked()));
}

UsartData::~UsartData()
{
    delete ui;
}

void UsartData::Write(QString a_str)
{
    if(mSerialPort.isReadable())
    {
        ui->MyProgress->setValue(0);
        if(ui->MyAppendEnter->isChecked())
        {
            a_str.append("\r\n");
        }
        QString encode = ui->MyEncode->currentText();
        QByteArray buffer;
        if(encode == "UTF8")
        {
            buffer = a_str.toUtf8();
        }
        else if(encode == "GBK")
        {
            buffer = a_str.toLocal8Bit();
        }

        mSerialPort.write(buffer);
        qDebug()<< "Send:" << buffer;
        Debug::instance()->append(buffer, Write_send);
        ui->MyProgress->setValue(100);
    } else {
        QMessageBox::warning(this, tr("警告："), tr("串口未打开！"));
    }
}

void UsartData::USB_Init()
{
#if 1
    const GUID GUID_DEVINTERFACE_LIST[] =
    {
        // GUID_DEVINTERFACE_USB_DEVICE
        { 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
        //    // GUID_DEVINTERFACE_DISK
        //    { 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
        //    // GUID_DEVINTERFACE_HID,
        //    { 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
        //    // GUID_NDIS_LAN_CLASS
        //    { 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } },
        //    // GUID_DEVINTERFACE_COMPORT
        //    { 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
        //    // GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
        //    { 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },
        //    // GUID_DEVINTERFACE_PARALLEL
        //    { 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },
        //    // GUID_DEVINTERFACE_PARCLASS
        //    { 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } },
    };

    //注册插拔事件
    HDEVNOTIFY hDevNotify;
    DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
    ZeroMemory(&NotifacationFiler,sizeof(DEV_BROADCAST_DEVICEINTERFACE));
    NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    for(int i=0;i<int(sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID));i++)
    {
        NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];//GetCurrentUSBGUID();//m_usb->GetDriverGUID();

        hDevNotify = RegisterDeviceNotification(HANDLE(this->winId()),&NotifacationFiler,DEVICE_NOTIFY_WINDOW_HANDLE);
        if(!hDevNotify)
        {
            GetLastError();
            qDebug() << "注册失败" <<endl;
            Debug::instance()->append("注册失败", Write_debug);
        }
    }
#endif
}

void UsartData::SerialPortUpdate()
{
    if(mSerialPort.isOpen())
        mSerialPort.close();
    ui->MySerialPort->clear();//清除已扫到的串口

    /* 查找可用串口 */
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        mSerialPort.setPort(info);
        /* 判断端口是否能打开 */
        if(mSerialPort.open(QIODevice::ReadWrite))
        {
            ui->MySerialPort->addItem(mSerialPort.portName());
            mSerialPort.close();
        }
    }

    if(ui->MySerialPort->count() != 0)//如果有可用串口就打开第一个
    {
        /* 串口已经关闭，现在来打开串口 */
        MySerialPort_currentIndexChanged(ui->MySerialPort->currentText());
        MyBaud_currentIndexChanged(ui->MyBaud->currentText());
        MyStops_currentIndexChanged(ui->MyStops->currentText());
        MyDatas_currentIndexChanged(ui->MyDatas->currentText());
        MyOddEven_currentIndexChanged(ui->MyOddEven->currentText());
        /* 打开串口 */
        if(mSerialPort.open(QIODevice::ReadWrite))
        {
            ui->MyControl->setChecked(true);
            qDebug()<<"Opened:" + ui->MySerialPort->currentText();
            Debug::instance()->append("Opened:" + ui->MySerialPort->currentText(), Write_debug);
        }
        /* 设置串口缓冲区大小，这里必须设置为这么大 */
        mSerialPort.setReadBufferSize(MyBufferSize);
    }
}

void UsartData::MySerialPort_currentIndexChanged(const QString &aPort)
{
    qDebug() << "setPortName";
    Debug::instance()->append("setPortName", Write_debug);
    mSerialPort.setPortName(aPort);
}

void UsartData::MyBaud_currentIndexChanged(const QString &aBaud)
{
    qDebug() << "setBaudRate";
    Debug::instance()->append("setBaudRate", Write_debug);
    mSerialPort.setBaudRate(aBaud.toInt());
}

void UsartData::MyStops_currentIndexChanged(const QString &aStop)
{
    qDebug() << "setStopBits";
    Debug::instance()->append("setStopBits", Write_debug);
    if(aStop == "1")
    {
        mSerialPort.setStopBits(QSerialPort::StopBits::OneStop);
    }
    else if(aStop == "1.5")
    {
        mSerialPort.setStopBits(QSerialPort::StopBits::OneAndHalfStop);
    }
    else if(aStop == "2")
    {
        mSerialPort.setStopBits(QSerialPort::StopBits::TwoStop);
    }
}

void UsartData::MyDatas_currentIndexChanged(const QString &aData)
{
    qDebug() << "setBaudRate";
    Debug::instance()->append("setBaudRate", Write_debug);
    mSerialPort.setDataBits(QSerialPort::DataBits(aData.toInt()));
}

void UsartData::MyOddEven_currentIndexChanged(const QString &aOE)
{
    qDebug() << "setParity";
    Debug::instance()->append("setParity", Write_debug);
    if(aOE == "No")
    {
        mSerialPort.setParity(QSerialPort::Parity::NoParity);
    }
    else if(aOE == "Odd")
    {
        mSerialPort.setParity(QSerialPort::Parity::OddParity);
    }
    else if(aOE == "Even")
    {
        mSerialPort.setParity(QSerialPort::Parity::EvenParity);
    }
    else if(aOE == "Space")
    {
        mSerialPort.setParity(QSerialPort::Parity::SpaceParity);
    }
    else if(aOE == "Mark")
    {
        mSerialPort.setParity(QSerialPort::Parity::MarkParity);
    }
}

void UsartData::MyControl_clicked()
{
    if(ui->MyControl->isChecked())
    {
        mSerialPort.open(QIODevice::ReadWrite);
    } else {
        mSerialPort.close();
    }
}

void UsartData::MySaveRec_clicked()
{
    QFile file(QFileDialog::getSaveFileName(nullptr,"标题","...","*.txt;;*.c;*.cpp;;*.h"));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << ui->MyReceWin->toPlainText();
        return;
    }
    QMessageBox::warning(this, tr("文件"), tr("保存失败！"));
}

void UsartData::MyEncode_currentIndexChanged(const QString &encode)
{
    if(encode == "UTF8")
    {
        mEncode = utf8;
        if(ui->MyIsHex->isChecked())
        {
            mGBKFromHex();
            mUTF8ToHex();
        }
    }
    else if(encode == "GBK")
    {
        mEncode = gbk;
        if(ui->MyIsHex->isChecked())
        {
            mUTF8FromHex();
            mGBKToHex();
        }
    }
}

void UsartData::MyReceWin_textChanged()
{
    ui->MyReceWin->moveCursor(QTextCursor::End);
}

void UsartData::MySend_clicked()
{
    if(mSerialPort.isReadable())
    {
        ui->MyProgress->setValue(0);
        QString str = ui->MySendWin->toPlainText();
        QString former = ui->MyFormerParity->text();
        QString last = ui->MyLastParity->text();
        if(!former.isEmpty())
        {
            str.insert(0, former);
        }
        if(!last.isEmpty())
        {
            str.append(last);
        }
        if(ui->MyAppendEnter->isChecked())
        {
            str.append("\r\n");
        }
        QString encode = ui->MyEncode->currentText();
        QByteArray buffer;
        if(encode == "UTF8")
        {
            buffer = str.toUtf8();
        }
        else if(encode == "GBK")
        {
            buffer = str.toLocal8Bit();
        }

        mSerialPort.write(buffer);
        qDebug()<< "Send:" << buffer;
        Debug::instance()->append(buffer, Write_send);
        ui->MyProgress->setValue(100);
    } else {
        QMessageBox::warning(this, tr("警告："), tr("串口未打开！"));
    }
}

void UsartData::MyOpenFile_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(nullptr,"标题","...","*.txt;*.c;*.cpp;*.h");
    QFileInfo temporaryFile(fileName);
    if(temporaryFile.isFile())
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        ui->MySendWin->setPlainText(in.readAll());
        return;
    }
    QMessageBox::warning(this, tr("文件"), tr("打开失败！"));
}

void UsartData::MyCirculSend_clicked(bool aBool)
{
    if(aBool)
    {
        if(mSerialPort.isOpen())
        {
            ui->MySend->setEnabled(false);
            mCur = 0;
            mSendTimer.start(mCirculPeriod);
        } else {
            ui->MyCirculSend->setChecked(false);
            QMessageBox::warning(this, tr("警告："), tr("串口未打开！"));
        }
    }
    else
    {
        ui->MySend->setEnabled(true);
        mSendTimer.stop();
    }
}

void UsartData::MyCirculPeriod_textChanged(const QString &aPeriod)
{
    if(aPeriod.isEmpty())
    {
        return;
    }
    mCirculPeriod = aPeriod.toInt();
}

#include<QFile>
#include<QDataStream>
#include<QFileDialog>
void UsartData::MySaveParity_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "保存校验文件", "./parity.bin", "*.bin");
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << ui->MyFormerParity->text() << ui->MyLastParity->text();
        file.close();
    }
}

void UsartData::MyLoadParity_clicked()
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

void UsartData::MyDebug_clicked()
{
    Debug::instance()->show();
    QWidget::hide();
    QWidget::show();
}

void UsartData::MyGotoCourse_clicked()
{
    QStringList temp;
    temp.append(ui->MyFormerParity->text());
    temp.append(ui->MyLastParity->text());
    new Course(this, temp);
}

void UsartData::mSerialPort_readyRead()
{
    QByteArray bits = mSerialPort.readAll();
    Debug::instance()->append(bits, Write_receive);
    QString buffer;
    static bool r_flag = false;
    for(int i = 0; i < bits.count(); i++)
    {
        char temp = bits.at(i);
        if(temp == '\r')
        {
            r_flag = true;
            continue;
        }
        if(r_flag)
        {
            if(temp == '\n')
            {
                if(ui->MyInsertTime->isChecked())
                {
                    buffer.append(tr("[%1]\r\n").arg(QTime::currentTime().toString()));
                }
                else {
                    buffer.append("\r\n");
                }
            } else {
                buffer.append('\r');
            }
            r_flag = false;
        } else {
            buffer.append(mEncode(temp));
        }
    }

    if(ui->MyIsHex->isChecked())
    {
        QString encode = ui->MyEncode->currentText();
        if(encode == "UTF8")
            buffer = buffer.toUtf8().toHex();
        else if(encode == "GBK")
            buffer = buffer.toLocal8Bit().toHex();
        for(int j = buffer.count(); j > 0; j=j-2)
        {
            buffer.insert(j, ' ');
        }
    }
    ui->MyReceWin->insertPlainText(buffer);

    emit Read(buffer);
}

void UsartData::USB_Insert()
{
    /* 查找可用串口 */
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        /* 判断端口是否能打开 */
        if(serial.open(QIODevice::ReadWrite))
        {
            serial.close();
            int index = ui->MySerialPort->findText(serial.portName());
            if(index == -1)//未找到，说明就是要添加的
            {
                ui->MySerialPort->addItem(serial.portName());
                continue;//最好是全部扫描
            }
        }
    }
}

void UsartData::USB_Remove()
{
    QStringList port_list;
    /* 查找可用串口 */
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        /* 判断端口是否能打开 */
        if(serial.open(QIODevice::ReadWrite))
        {
            serial.close();
            port_list.append(serial.portName());
        }
    }

    for(int i = 0; i < ui->MySerialPort->count(); i++)
    {
        if(port_list.contains(ui->MySerialPort->itemText(i)))
            continue;
        else {
            ui->MySerialPort->removeItem(i);
        }
    }
    ui->MyControl->setChecked(false);//会进入MyControl_clicked函数中关闭mSerialPort;
    //    mSerialPort.close();
}

bool UsartData::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);//第一层解算
    UINT msgType = msg->message;
    if(msgType==WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = PDEV_BROADCAST_HDR(msg->lParam);//第二层解算
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
            {
                USB_Insert();

                //                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = PDEV_BROADCAST_DEVICEINTERFACE(lpdb);
                //                QString device_name = "插入设备(name)："+QString::fromWCharArray(pDevInf->dbcc_name,int(pDevInf->dbcc_size)).toUtf8();

                //                qDebug()<< device_name;
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
            {
                USB_Remove();

                //                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = PDEV_BROADCAST_DEVICEINTERFACE(lpdb);
                //                QString device_name = "移除设备(name)："+QString::fromWCharArray(pDevInf->dbcc_name,int(pDevInf->dbcc_size)).toUtf8();

                //                qDebug()<< device_name;
            }
            break;
        }
    }
    return false;
}

/* QPoint QMouseEvent::pos() const
    Returns the position of the mouse cursor, relative to the widget that received the event.
    If you move the widget as a result of the mouse event, use the global position returned by globalPos() to avoid a shaking motion.
 */
#include<QMouseEvent>
//拖拽操作
//void UsartData::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton)
//    {
//        m_bDrag = true;
//        //获得鼠标的初始位置
//        mouseStartPoint = event->globalPos();
//        //mouseStartPoint = event->pos();
//        //获得窗口的初始位置
//        windowTopLeftPoint = this->frameGeometry().topLeft();
//    }
//}

//void UsartData::mouseMoveEvent(QMouseEvent *event)
//{
//    if(m_bDrag)
//    {
//        //获得鼠标移动的距离
//        QPoint distance = event->globalPos() - mouseStartPoint;
//        //QPoint distance = event->pos() - mouseStartPoint;
//        //改变窗口的位置
//        this->move(windowTopLeftPoint + distance);
//    }
//}

//void UsartData::mouseReleaseEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton)
//    {
//        m_bDrag = false;
//    }
//}

void UsartData::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_bDrag = true;
        mouseStartPoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void UsartData::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bDrag && (e->buttons() == Qt::LeftButton))
    {
        move(e->globalPos() - mouseStartPoint);
        e->accept();
    }
}

void UsartData::mouseReleaseEvent(QMouseEvent *)
{
    m_bDrag = false;
}

#include<QKeyEvent>
void UsartData::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        QWidget::close();
    }
}

#include<QPaintEvent>
#include<QPainter>
void UsartData::paintEvent(QPaintEvent *event)
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

void UsartData::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    Debug::instance()->close();
}

void UsartData::mSendTimer_timeout()
{
    if(mSerialPort.isReadable())
    {
        QString str;
        if(ui->MyByOneSend->isChecked())
        {
            QString one = ui->MySendWin->toPlainText();
            str = one.at(mCur);
            ui->MyProgress->setValue(100*(mCur+1)/one.count());
            if(mCur < one.count()-1)
                mCur++;
            else {
                mCur = 0;
            }
        }
        else {
            ui->MyProgress->setValue(0);
            str = ui->MySendWin->toPlainText();
            ui->MyProgress->setValue(100);
        }
        QString former = ui->MyFormerParity->text();
        QString last = ui->MyLastParity->text();
        if(!former.isEmpty())
        {
            str.insert(0, former);
        }
        if(!last.isEmpty())
        {
            str.append(last);
        }
        if(ui->MyAppendEnter->isChecked())
        {
            str.append("\r\n");
        }

        QString encode = ui->MyEncode->currentText();
        QByteArray buffer;
        if(encode == "UTF8")
        {
            buffer = str.toUtf8();
        }
        else if(encode == "GBK")
        {
            buffer = str.toLocal8Bit();
        }

        mSerialPort.write(buffer);
        qDebug()<< "Send:" << buffer;
        Debug::instance()->append(buffer, Write_send);
    }
}

void UsartData::mUTF8ToHex()//转换成十六进制格式
{
    QString str = ui->MyReceWin->toPlainText();

    QByteArray str2 = str.toUtf8().toHex().data();
    str.clear();
    for(int i = 0;i<str2.length ();i+=2)//填加空格
    {
        QString st = str2.mid (i,2);
        str += st;
        str += " ";
    }
    ui->MyReceWin->clear();
    ui->MyReceWin->append(str);
}

void UsartData::mGBKToHex()//转换成十六进制格式
{
    QString str = ui->MyReceWin->toPlainText();

    QByteArray str2 = str.toLocal8Bit().toHex().data();
    str.clear();
    for(int i = 0;i<str2.length ();i+=2)//填加空格
    {
        QString st = str2.mid (i,2);
        str += st;
        str += " ";
    }
    ui->MyReceWin->clear();
    ui->MyReceWin->append(str);
}

void UsartData::mUTF8FromHex()//转换成文本格式
{
    QString str = ui->MyReceWin->toPlainText();

    QByteArray ret;
    QStringList sl=str.split(" ");
    foreach(QString s,sl)
    {
        if(!s.isEmpty())
            ret.append(char(s.toInt(nullptr,16)&0xFF));
    }
    ui->MyReceWin->clear();
    ui->MyReceWin->append(ret);
}

void UsartData::mGBKFromHex()
{
    QString str = ui->MyReceWin->toPlainText();

    QByteArray ret;
    QStringList sl=str.split(" ");
    foreach(QString s,sl)
    {
        if(!s.isEmpty())
            ret.append(char(s.toInt(nullptr,16)&0xFF));
    }
    ui->MyReceWin->clear();
    ui->MyReceWin->append(QString::fromLocal8Bit(ret));
}

void UsartData::MyIsHex_clicked(bool aBool)
{
    if(aBool)
    {
        QString str = ui->MyEncode->currentText();
        if(str == "GBK")
            mGBKToHex();
        else if(str == "UTF8")
            mUTF8ToHex();
    } else {
        QString str = ui->MyEncode->currentText();
        if(str == "GBK")
            mGBKFromHex();
        else if(str == "UTF8")
            mUTF8FromHex();
    }
}

QString UsartData::utf8(char ch)
{
    static QByteArray buffer1;
    static QString buffer2;
    static int enable_bits = 0;
    if(enable_bits == 0)//没有可读的字节了
    {
        if((ch&0X80) == 0X00)//0xxxxxxx
        {
            enable_bits = 1;
            buffer1.append(ch);
            enable_bits = 0;

            buffer2 = QString::fromUtf8(buffer1);
            buffer1.clear();
            return buffer2;
        }
        else if((ch&0XE0) == 0XC0) enable_bits = 2;//110xxxxx 10xxxxxx
        else if((ch&0XF0) == 0XE0) enable_bits = 3;//1110xxxx 10xxxxxx 10xxxxxx
        else if((ch&0XF8) == 0XF0) enable_bits = 4;//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if((ch&0XFC) == 0XF8) enable_bits = 5;//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if((ch&0XFE) == 0XFC) enable_bits = 6;//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        if(enable_bits)
        {
            buffer1.append(ch);
            enable_bits = enable_bits - 1;
            return QString();
        }
    }
    if((ch&0XC0) == 0X80)
    {
        buffer1.append(ch);
        enable_bits = enable_bits-1;

        if(enable_bits == 0)//判断是否结束
        {
            buffer2 = QString::fromUtf8(buffer1);
            buffer1.clear();
            return buffer2;
        } else {//没有的话，返回空字符串
            return QString();
        }
    } else {//不符合编码规则放弃本次编码，重新编码，并返回空字符串
        buffer1.clear();
        enable_bits = 0;
        return QString();
    }
}

QString UsartData::gbk(char ch)
{
    static QByteArray buffer1;
    static QString buffer2;
    static int index = 2;
    buffer1.append(ch);
    index = index - 1;
    if(index == 0)
    {
        index = 2;
        buffer2 = QString::fromLocal8Bit(buffer1);
        buffer1.clear();
        return buffer2;
    } else {
        return QString();
    }
}
