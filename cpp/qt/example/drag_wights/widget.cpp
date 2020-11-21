#include "widget.h"
#include <QDrag>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QApplication>
#include <windows.h>
#include <QMimeData>
#include <QPainter>
#include <QDebug>
#include "qboxwidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(new QVBoxLayout(this))
    , m_moveWidget(nullptr)
{
    for(int i = 0; i < 10; ++i) {
        QHBoxWidget *hBox = new QHBoxWidget(this);
        hBox->addWidget(new QLabel("Address:"));
        hBox->addWidget(new QLineEdit(QString("0x%1").arg(i, 4, 16, QChar('0'))));
        hBox->addWidget(new QLabel("Write:"));
        hBox->addWidget(new QLineEdit(QString("0x%1").arg(i<<8, 4, 16, QChar('0'))));
        hBox->addWidget(new QLabel("Check:"));
        hBox->addWidget(new QLineEdit(QString("0x%1").arg(i<<16, 4, 16, QChar('0'))));
        m_mainLayout->addWidget(hBox);
    }
    m_mainLayout->addStretch();

    this->setAcceptDrops(true);
}

Widget::~Widget()
{
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        for(int i = 0; i < m_mainLayout->count(); ++i) {
            QWidget *widget = m_mainLayout->itemAt(i)->widget();
            if(widget == nullptr) continue;

            if(widget->underMouse()) {
                m_moveWidget = widget;
                m_moveWidget->setEnabled(false);

                QDrag dg(this);
#if 0
                QPixmap pixmap = m_moveWidget->grab();
                QPainter painter(&pixmap);
                painter.drawRect(0, 0, pixmap.size().width()-1, pixmap.size().height()-1);
#else
                QPixmap pixmap(":/drag.png");
                pixmap = pixmap.scaled(40, 40, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
#endif
                dg.setPixmap(pixmap);
                dg.setMimeData(new QMimeData);
                if(dg.exec() != Qt::MoveAction)
                    m_moveIndex = i;

                m_mainLayout->insertWidget(m_moveIndex, m_moveWidget);
                m_moveWidget->hide();
                m_moveWidget->show();
                QApplication::processEvents();
                Sleep(150);
                m_moveWidget->setEnabled(true);
                m_moveWidget = nullptr;
                return;
            }
        }
    }
}

void Widget::dropEvent(QDropEvent *event)
{
    event->accept();

    QWidget *widget = m_mainLayout->itemAt(0)->widget();
    if(widget->geometry().y() > event->pos().y()) {
        m_moveIndex = 0;
        return;
    }

    for(int i = 0; i < m_mainLayout->count(); ++i) {
        QWidget *widget = m_mainLayout->itemAt(i)->widget();
        if(widget == nullptr) continue;

        if(widget && widget->geometry().y() < event->pos().y()) {
            m_moveIndex = i;
        }
    }
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if(m_moveWidget) event->accept();
}
