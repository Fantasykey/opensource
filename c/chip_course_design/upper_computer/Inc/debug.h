#ifndef DEBUG_H
#define DEBUG_H

#include <QWidget>

namespace Ui {
    class Debug;
} // namespace Ui

typedef enum {
    Write_debug,
    Write_send,
    Write_receive,
} WriteType;

class Debug : public QWidget
{
    Q_OBJECT
public:
    static Debug* instance(void);
    void append(const QString a_str, const WriteType a_type);

private slots:
    void MyDebugSave_clicked(void);
    void MySendSave_clicked(void);
    void MyReceiveSave_clicked(void);

    /* 使用鼠标来移动界面 */
private:
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

    /* 绘制窗口边框 */
    void paintEvent(QPaintEvent *event);

private:
    Ui::Debug *ui;

    explicit Debug(QWidget *parent = nullptr);
};

#endif // DEBUG_H
