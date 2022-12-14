#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtSerialPort/QSerialPortInfo> // maybe its enough

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    serial->setPortName("COM5");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
 //   serial->write("a");

   connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceive()));

 //  connect(serial,SIGNAL(LedSignal(true)), this,SLOT(LedOnSign()));

       qDebug() << "Number of serial ports:" << QSerialPortInfo::availablePorts().count();

       Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
          // box.addItem(port.portName());

           qDebug() << "serial ports:" << port.portName();
       }



    //ui->progressBar->setStyleSheet("QStatusBar {background-color: black; }");
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
}

void MainWindow::serialReceive()
{
   // QByteArray ba;
    //ba = serial->readAll();
   // ui->label->setText(ba);


    QByteArray rMsg;
       for(;;) {
           char buf[512]; // read data in this size chunks
           qint64 len = serial->read(buf, sizeof buf);

           if (len <= 0) {
               if (len < 0) {
                   qDebug() << "newData() read error" << serial->errorString();
               }
               break; // for(;;)
           }

           rMsg.append(buf, len);
           serialOutput(buf, len);
       }
      // qDebug() << "newData() got byte array" << rMsg.size() << ":" << rMsg;
      // ui->label->setText(rMsg);
     //  rMsg.clear();



     //   QProgressBar
}

bool AdcFlag = false;

char OutBuf[512];
int index= 0;
void MainWindow::serialOutput(char *data, qint64 size){

    int endOfMes=0;

    //OutBuf.append(data,size );
    for (int i = 0;i<size;i++){
        OutBuf[index+i]=data[i];

        if(OutBuf[index+i]== '\0') endOfMes =1;

    }

    index= index+size;  //?????????????????? ?? ???????????????????????? ?????????? 512 ?? ??????????

    if(endOfMes == 1){


        if(AdcFlag == true){
            if(OutBuf[0]>='0'&&OutBuf[0]<'5')
            {
                ui->progressBar->setValue(std::atoi(OutBuf));
                ui->lcdNumber->display(std::atoi(OutBuf));
            }




        } else if(OutBuf[0]=='L')
        {


            if(OutBuf[5]=='N'){
                 LedSignal(true);
                 //emit


            }
            if(OutBuf[5]=='F'){

                LedSignal(false);

            }
        } else {ui->label->setText(OutBuf);

            //OutBuf = {0, }; // hz kak pochistit
            }


        index = 0;
        endOfMes =0;





        //qDebug() << "newData() got byte array allo" << index << ":" <<OutBuf ;



    }

     ui->progressBar->setMinimum(0);
     ui->progressBar->setMaximum(4096);
















}



void MainWindow::on_pushButton_clicked()
{
     serial->write("a");
     AdcFlag = true;
}

void MainWindow::on_pushButton_2_clicked()
{
    serial->write("e");
    AdcFlag = false;
    ui->progressBar->setValue(0);
     ui->lcdNumber->display(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    serial->write("v");
    ui->progressBar->setValue(1500);
}

void MainWindow::on_pushButton_4_clicked()
{
    serial->write("l");


}



void MainWindow::LedSignal(int State){


    QString LedButtonOn = "QPushButton { "
                          "color: #333;"
                          "border: 2px solid #555;"
                          "border-radius: 10px; "
                          "border-style: outset;"
                          "background: qradialgradient( "
                           "   cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, "
                            "  radius: 1.5, stop: 0 #fff, stop: 1 #00aa00 "
                            "  ); "

                        "  } "

                     " QPushButton:pressed { "
                      "    border-style: inset; "
                          "background: qradialgradient( "
                              "cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, "
                              "radius: 1.5, stop: 0 #fff, stop: 1 #cbffcd"
                              ");"
                          "} ";








    QString LedButtonOff =
            "QPushButton { "
            "color: #333;"
            "border: 2px solid #555;"
            "border-radius: 10px; "
            "border-style: outset;"
            "background: qradialgradient( "
             "   cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, "
              "  radius: 1.5, stop: 0 #fff, stop: 1 #92ff96 "
              "  ); "

          "  } "

       " QPushButton:pressed { "
        "    border-style: inset; "
            "background: qradialgradient( "
                "cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, "
                "radius: 1.5, stop: 0 #fff, stop: 1 #cbffcd"
                ");"
            "} ";

    if(State == true){


        ui->LedButton->setStyleSheet(LedButtonOn);


    }
    if(State == false){
           ui->LedButton->setStyleSheet(LedButtonOff);

    }

}


void MainWindow::on_LedButton_clicked()
{
    serial->write("l");
}
