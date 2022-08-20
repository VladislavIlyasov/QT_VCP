#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort>

//#include "CircBuff.h"

#include "circbuffqt.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void BufferIsFilled();

    /*
     void Changei(void);
     void Write(const char c);
     void SetAdcWidgets(const int i);
     void LedButtonState(bool b);
*/



private slots:
    void serialReceive();

    void serialOutput(char *data, qint64 maxSize);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void setSerialPort(const QString *PortName);

//signals:
    void LedSignal(bool State);

    void ComPortActivating();

    void ComPortRefresh();

    void on_LedButton_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void closeSerialPort();

    void handleError(QSerialPort::SerialPortError error);

   // int BuffInit();

//public slots:

     void serialOutput();

    //void serialOutput(char *data);



signals:
    void SignalReadBuff();
    void ComPortError();



private:


     QSerialPort *serial = nullptr;

     Ui::MainWindow *ui= nullptr;

     CircBuffQt *queueIn = nullptr;

   //  queue *queueIn;
  //   queue *queueOut;


};
#endif // MAINWINDOW_H
