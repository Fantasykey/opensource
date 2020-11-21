#include "debug.h"
#include "ui_debug.h"

Debug* Debug::instance()
{
    static Debug debug;
    return &debug;
}

void Debug::append(const QString a_str, const WriteType a_type)
{
    if(this->isHidden()) return;

    switch (a_type) {
    case WriteType::Write_debug:
        ui->MyDebug->append(a_str);
        break;
    case WriteType::Write_send:
        ui->MySend->append(a_str);
        break;
    case WriteType::Write_receive:
        ui->MyReceive->append(a_str);
        break;
    }
}

#include<QFile>
#include<QTextStream>
#include<QFileDialog>
void Debug::MyDebugSave_clicked()
{
    QFile file(QFileDialog::getSaveFileName(this, "保存调试窗口", "debug.txt", "*.txt"));
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << ui->MyDebug->toPlainText();
        file.close();
    }
}

void Debug::MySendSave_clicked()
{
    QFile file(QFileDialog::getSaveFileName(this, "保存发送窗口", "send.txt", "*.txt"));
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << ui->MySend->toPlainText();
        file.close();
    }
}

void Debug::MyReceiveSave_clicked()
{
    QFile file(QFileDialog::getSaveFileName(this, "保存接收窗口", "receive.txt", "*.txt"));
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << ui->MyReceive->toPlainText();
        file.close();
    }
}

/* QPoint QMouseEvent::pos() const
    Returns the position of the mouse cursor, relative to the widget that received the event.
    If you move the widget as a result of the mouse event, use the global position returned by globalPos() to avoid a shaking motion.
 */
#include<QMouseEvent>
//拖拽操作
void Debug::mousePressEvent(QMouseEvent *event)
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

void Debug::mouseMoveEvent(QMouseEvent *event)
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

void Debug::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}

#include<QKeyEvent>
void Debug::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        this->hide();
    }
}

#include<QPaintEvent>
#include<QPainter>
void Debug::paintEvent(QPaintEvent *event)
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

Debug::Debug(QWidget *parent) : QWidget(parent)
  , ui(new Ui::Debug)
{
    ui->setupUi(this);
    
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    
    ui->MyExitBtn->setFixedSize(24, 24);
    ui->MyExitBtn->setStyleSheet(
                "QPushButton{border-image: url(image/noun_False_normal.ico);border-width:0px;border-radius:12px;}"
                "QPushButton:pressed{ border-image: url(image/noun_False_press.ico);}"
                "QPushButton:hover{border-image: url(image/noun_False_hover.ico);}");
    connect(ui->MyExitBtn, &QPushButton::clicked, this, &QWidget::hide);

    connect(ui->MyDebugClear, &QPushButton::clicked, ui->MyDebug, &QTextBrowser::clear);
    connect(ui->MySendClear, &QPushButton::clicked, ui->MySend, &QTextBrowser::clear);
    connect(ui->MyReceiveClear, &QPushButton::clicked, ui->MyReceive, &QTextBrowser::clear);

    connect(ui->MyDebugSave, &QPushButton::clicked, this, &Debug::MyDebugSave_clicked);
    connect(ui->MySendSave, &QPushButton::clicked, this, &Debug::MySendSave_clicked);
    connect(ui->MyReceiveSave, &QPushButton::clicked, this, &Debug::MyReceiveSave_clicked);
}
