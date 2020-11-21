#ifndef COURSE_H
#define COURSE_H

#include <QDialog>
#define CHIP "CHIP"

namespace Ui{
class Course;
}
class UsartData;

class Course : public QDialog
{
    Q_OBJECT
public:
    explicit Course(QWidget *parent = nullptr, const QStringList a_parity = QStringList());

private:
    void Write(QString a_str);

    QColor mColor;
    void setColor(void);                                            //设置颜色按钮颜色
    QString Complement(QString a_str, int max);
private slots:
    void MyGetFileNameBtn_clicked(void);                            //获取文件名
    void MySaveSetting_clicked(void);                               //保存设置
    void MyLoadSetting_clicked(void);                               //加载设置

    void MyRedSlider_valueChanged(int a_value);                     //红色滑动条的值改变
    void MyGreenSlider_valueChanged(int a_value);                   //绿色滑动条的值改变
    void MyBlueSlider_valueChanged(int a_value);                    //蓝色滑动条的值改变
    void MyRedEdit_returnPressed(void);                             //红色文本框的值改变
    void MyGreenEdit_returnPressed(void);                           //绿色文本框的值改变
    void MyBlueEdit_returnPressed(void);                            //蓝色文本框的值改变
    void MyColorBtn_clicked(void);                                  //颜色按钮触发

    void MyLED_clicked(bool a_bool);                                //LED按钮触发

    void MyKEY_clicked(bool a_bool);                                //KEY按钮触发

    void MyMotorBtn_clicked(bool a_bool);                           //启动/关闭电机
    void MySpeedSpin_valueChanged(int a_value);                     //电机速度滑动条的值改变
    void MyReverseMotor_clicked(void);                              //电机反转

    void MyBeepBtn_clicked(bool a_bool);                            //蜂鸣器按钮触发
    void MyBeepFreq_returnPressed(void);                            //蜂鸣器频率文本框的值改变

    void MySaveParity_clicked(void);                                //保存校验
    void MyLoadParity_clicked(void);                                //加载校验

    /* 分步解析 */
    void mResolveColor(QString &a_str);                             //解析七彩灯
    void mResolveLED(QString &a_str);                               //解析LED
    void mResolveKEY(QString &a_str);                               //解析按键
    void mResolveMotor(QString &a_str);                             //解析电机
    void mResolveLCDNumber(QString &a_str);                         //解析数码管
    void mResolveBeep(QString &a_str);                              //解析蜂鸣器

    void mParent_Read(QString a_str);                               //解析从下位机获取到的数据

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

    /* 显示父窗口 */
    void closeEvent(QCloseEvent *event);

private:
    Ui::Course *ui;
    UsartData *mParent;

    QString mLCD_H;
    QString mLCD_L;
};

#endif // COURSE_H
