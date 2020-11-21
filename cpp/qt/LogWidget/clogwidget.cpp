#include "clogwidget.h"
#include <QDebug>

CLogWidget::CLogWidget(QWidget *parent)
    : QTabWidget(parent), m_curIndex(-1), m_autoSwitch(false)
{
}

int CLogWidget::createWindow(const QString &name)
{
    if (-1 == m_curIndex)
        m_curIndex = 0;
    return QTabWidget::addTab(new QTextBrowser(this), name);
}

bool CLogWidget::removeWindow(const QString &name)
{
    for (int i = QTabWidget::count() - 1; i >= 0; --i)
    {
        if (name != QTabWidget::tabText(i))
            continue;

        return CLogWidget::removeWindow(i);
    }
    return false;
}

CLogWidget &CLogWidget::operator()()
{
    return *this;
}

CLogWidget &CLogWidget::operator()(const QString &name)
{
    for (int i = QTabWidget::count() - 1; i >= 0; --i)
    {
        if (name != QTabWidget::tabText(i))
            continue;

        /* switch index position */
        m_curIndex = i;
        // if m_autoSwitch=true, log window synchronize with m_curIndex
        // else, log window do not synchronize with m_curIndex.
        if (m_autoSwitch)
            QTabWidget::setCurrentIndex(i);
    }
    return *this;
}

bool CLogWidget::write(const QString &text)
{
    if (-1 == m_curIndex)
        return false;

    return CLogWidget::write(m_curIndex, text);
}

CLogWidget &CLogWidget::operator<<(const QString &text)
{
    CLogWidget::write(text);
    return *this;
}

QString CLogWidget::read()
{
    if (-1 == m_curIndex)
        return "";

    return CLogWidget::read(m_curIndex);
}

CLogWidget &CLogWidget::operator>>(QString &text)
{
    text = CLogWidget::read();
    return *this;
}

bool CLogWidget::write(const QString &name, const QString &text)
{
    for (int i = QTabWidget::count() - 1; i >= 0; --i)
    {
        if (name != QTabWidget::tabText(i))
            continue;

        return CLogWidget::write(i, text);
    }
    return false;
}

QString CLogWidget::read(const QString &name)
{
    for (int i = QTabWidget::count() - 1; i >= 0; --i)
    {
        if (name != QTabWidget::tabText(i))
            continue;

        return CLogWidget::read(i);
    }
    return QString();
}

bool CLogWidget::clear()
{
    if (-1 == m_curIndex)
        return false; // lack of index, maybe is no window

    reinterpret_cast<QTextBrowser *>(QTabWidget::widget(m_curIndex))->clear();
    return true;
}

bool CLogWidget::clear(const QString &name)
{
    for (int i = QTabWidget::count() - 1; i >= 0; --i)
    {
        if (name != QTabWidget::tabText(i))
            continue;

        reinterpret_cast<QTextBrowser *>(QTabWidget::widget(i))->clear();
        return true;
    }
    return false;
}

bool CLogWidget::removeWindow(int index)
{
    QWidget *w = QTabWidget::widget(index);
    if (w == nullptr)
    {
        qDebug() << "error: can't found the print window";
        return false;
    }

    QTabWidget::removeTab(index);
    w->deleteLater();
    w->close();
    return true;
}

bool CLogWidget::write(int index, const QString &text)
{
    QWidget *w = QTabWidget::widget(index);
    if (w == nullptr)
    {
        qDebug() << "error: can't found the print window";
        return false;
    }

    static_cast<QTextBrowser *>(w)->append(text);
    return true;
}

QString CLogWidget::read(int index)
{
    QWidget *w = QTabWidget::widget(index);
    if (w == nullptr)
    {
        qDebug() << "error: can't found the print window";
        return QString();
    }

    return reinterpret_cast<QTextBrowser *>(w)->toPlainText();
}
