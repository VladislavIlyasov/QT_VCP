#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QDebug>

#include "Styles.cpp"

//extern MainWindow *w;
//extern QSerialPort *serial;;
//extern bool AdcFlag;
//extern  Ui::MainWindow *ui;;





void MainWindow::on_pushButton_2_clicked()
{


    serial->write("e");


   // AdcFlag = false;

   // SetAdcWidgets(0);



    ui->progressBar->setValue(0);
    ui->lcdNumber->display(0);

}


void MainWindow::on_pushButton_clicked()
{
      serial->write("a");
    // AdcFlag = true;
}




void MainWindow::on_pushButton_3_clicked()
{


    serial->write("v");
   // SetAdcWidgets(2280);
}


void MainWindow::on_pushButton_4_clicked()
{
    // Write('l');
     serial->write("l");

}
void MainWindow::on_LedButton_clicked()
{
   // Write('l');
    serial->write("l");
}



void MainWindow::on_comboBox_activated(const QString &arg1)
{

    if(arg1.length() == 0)
    {
         if(serial->isOpen())
         {
         serial->close(); // не прожимать дважды

         ui->progressBar->setValue(0);
         ui->lcdNumber->display(0);

         }

    }
    else
    {

         setSerialPort(&arg1);

    }

}

void MainWindow::LedSignal(bool State){

    if(State == true)
    {
       // LedButtonState(True);
        ui->LedButton->setStyleSheet(LedButtonOn);

    }
    if(State == false)
    {

       ui->LedButton->setStyleSheet(LedButtonOff);

    }


}


void MainWindow::on_pushButton_5_clicked()
{
    this->ComPortActivating();
}

void MainWindow::on_pushButton_6_clicked()
{
    this->ComPortRefresh();
}
