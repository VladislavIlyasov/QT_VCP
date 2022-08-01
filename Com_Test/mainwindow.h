#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void serialReceive();

    void serialOutput(char *data, qint64 maxSize);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();



//signals:
    void LedSignal(int State);



//public slots:
//     void LedOnSign();
 //    void LedOffSign();

    void on_LedButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
};
#endif // MAINWINDOW_H
