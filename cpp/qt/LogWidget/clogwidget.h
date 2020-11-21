#ifndef CLOGWIDGET_H
#define CLOGWIDGET_H

#include <QTabWidget>
#include <QTextBrowser>

class CLogWidget : public QTabWidget
{
public:
    CLogWidget(QWidget *parent = nullptr);
    int createWindow(const QString &name);
    bool removeWindow(const QString &name);

    /* select current log widget */
    CLogWidget &operator()();
    /* switch to name log widget */
    CLogWidget &operator()(const QString &name);

    /* write to the current log widget */
    bool write(const QString &text);
    CLogWidget &operator<<(const QString &text);

    /* read from the current log widget */
    QString read(void);
    CLogWidget &operator>>(QString &text);

    /* write to the name's log widget */
    bool write(const QString &name, const QString &text);
    /* write from the name's log widget */
    QString read(const QString &name);

    /* clear the current log widget */
    bool clear(void);
    /* clear to the name's log widget */
    bool clear(const QString &name);

private:
    bool removeWindow(int index);

    bool write(int index, const QString &text);
    QString read(int index);
    int m_curIndex;

protected:
    bool m_autoSwitch;
};

#endif // CLOGWIDGET_H
