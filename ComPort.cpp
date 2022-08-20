#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QDebug>


//extern MainWindow *w;
//extern QSerialPort *serial;
//extern bool AdcFlag;
//extern  Ui::MainWindow *ui;


void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
//    console->setEnabled(false);
 //   ui->actionConnect->setEnabled(true);
//    ui->actionDisconnect->setEnabled(false);
//    ui->actionConfigure->setEnabled(true);
    //showStatusMessage(tr("Disconnected"));
    ui->statusbar->showMessage(" Disconnected");


}




void MainWindow::ComPortActivating()
{
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        //qWarning() << info.portName();
        // qDebug() << "serial ports:" << port.portName();
         //ui->comboBox->addItem( info.portName());
           ui->comboBox->addItem( port.portName());
    }

}
void MainWindow::ComPortRefresh()
{




    if(ui->comboBox->count() > QSerialPortInfo::availablePorts().count()){

        ui->comboBox->clear();// no on clean all
        //добавить нулевой элемент как-то снова
        ui->comboBox->addItem("");
        ComPortActivating();
    }


    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {

     //qDebug() << "serial ports:" << port.portName();

     //Q_foreach(QComboBox::itemText() ,QComboBox::count())

    // ui->comboBox->count();
     qDebug() << ui->comboBox->count();
     //прописать цикл где сравниваем новый и старый порт и сравниваем нет ли одинаковых




     for(int i=0;i<ui->comboBox->count();i++){

         if(port.portName() == ui->comboBox->itemText(i)){return;}
           //  ui->comboBox->addItem( port.portName());




     }

     ui->comboBox->setDuplicatesEnabled(false);
     ui->comboBox->addItem( port.portName());

    }

}


void MainWindow::setSerialPort(const QString *PortName){

    serial->setPortName(*PortName);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

   // qDebug() << "Connected port" << *PortName;
    ui->statusbar->showMessage("Connected port " + *PortName);

   // qDebug() << "Number of serial ports:" << QSerialPortInfo::availablePorts().count();

    // ui->comboBox->placeholderText(" ");



    // set statusBar bluepill only
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(4096);

}
