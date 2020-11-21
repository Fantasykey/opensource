/**
  *最重要的是解码
  */

#ifndef USART_DATA_H
#define USART_DATA_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

#ifndef MyBufferSize
#define MyBufferSize (1000)
#endif

namespace Ui {
class Form;
}

class UsartData : public QWidget
{
    Q_OBJECT

public:
    explicit UsartData(QWidget *parent = nullptr);
    ~UsartData();
    void Write(QString a_str);

signals:
    void Read(QString);

private:
    Ui::Form *ui;

    QSerialPort mSerialPort;

    void USB_Init();//为了能检测USB插拔，而必要的初始化工作
    void SerialPortUpdate();//刚开始对所有串口进行扫描一遍

private slots:
    void MySerialPort_currentIndexChanged(const QString &aPort);    //串口号更改
    void MyBaud_currentIndexChanged(const QString &aBaud);          //波特率更改
    void MyStops_currentIndexChanged(const QString &aStop);         //停止位更改
    void MyDatas_currentIndexChanged(const QString &aData);         //数据位更改
    void MyOddEven_currentIndexChanged(const QString &aOE);         //奇偶校验更改
    void MyControl_clicked();                                       //串口开关

    void MySaveRec_clicked();                                       //保存接收窗
    void MyEncode_currentIndexChanged(const QString& encode);       //修改编码方式

    void MyReceWin_textChanged(void);                               //自动滚行

    void MySend_clicked();                                          //发送数据
    void MyOpenFile_clicked();                                      //打开文件
    void MyCirculSend_clicked(bool aBool);                          //循环发送开关

    void MyCirculPeriod_textChanged(const QString &aPeriod);        //循环周期更改

    void MySaveParity_clicked(void);                                //保存校验
    void MyLoadParity_clicked(void);                                //加载校验

    void MyDebug_clicked(void);                                     //显示调试窗口
    void MyGotoCourse_clicked(void);                                //goto 课设

private slots:
    void mSerialPort_readyRead();                                   //接收数据的槽

protected:
    void USB_Insert(void);
    void USB_Remove(void);
    bool nativeEvent(const QByteArray & eventType, void * message, long*result);

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

    /* 辅助循环发送数据 */
private:
    int mCirculPeriod;
    int mCur;
    QTimer mSendTimer;
private slots:
    void mSendTimer_timeout();

    /* 辅助文本与十六进制格式之间的转换 */
private:
    void mUTF8ToHex();//文本转UTF十六进制
    void mGBKToHex();//文本转GBK十六进制
    void mUTF8FromHex();//UTF十六进制转文本
    void mGBKFromHex();//GBK十六进制转文本
private slots:
    void MyIsHex_clicked(bool aBool);                               //是否十六进制显示的开关

private:
    QString (*mEncode)(char);
    static QString utf8(char ch);
    static QString gbk(char ch);
};

#endif // USART_DATA_H
