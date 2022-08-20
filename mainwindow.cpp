#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ButtonsMain.h"
//#include "Styles.cpp"
#include "ComPort.cpp"
#include "IOComPort.cpp"

#include "IOComPort.h"


#include "circbuffqt.h"
//#include "CircBuff.h"




#include <QDebug>
//#include <QtSerialPort>


MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
}






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , serial (new QSerialPort(this))
    , ui(new Ui::MainWindow)
  //  , queueIn(new CircBuffQt)
{
    ui->setupUi(this);

   setWindowTitle("STM32-VCP");


   queueIn = new CircBuffQt(this);

   //BuffInit();

   ComPortActivating();




   connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceive()));

  // connect(this, SIGNAL(SignalReadBuff()), queueIn, SLOT(ReadingData()));

   connect(this, SIGNAL(SignalReadBuff()), this, SLOT(serialOutput()));

  connect(serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

  connect(this, SIGNAL(ComPortError()),this,SLOT(ComPortRefresh()));
}




















