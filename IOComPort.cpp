#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QDebug>


//extern MainWindow *w;
//extern QSerialPort *serial;;
//extern bool AdcFlag;
//extern  Ui::MainWindow *ui;;


//bool AdcFlag = false;

char OutBuf[512];
int index = 0;



void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
  //     QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        ui->statusbar->showMessage(serial->errorString());
        closeSerialPort();

    //    serial->close();serial->disconnect();

        // combo box 1st variant vibrat

        ui->comboBox->setCurrentIndex(0);

        // вызвать операцию по обновленю комбобокса

        emit ComPortError();

        //ComPortRefresh(); // не работает при переподключении
    }
}













void MainWindow::serialReceive()
{

    QByteArray rMsg;

       for(;;) {
           char buf[512]; // read data in this size chunks
           qint64 len = serial->read(buf, sizeof buf);

           if (len <= 0) {
               if (len < 0) {
                   qDebug() << "newData() read error" << serial->errorString();
                   ui->statusbar->showMessage("newData() read error"+serial->errorString());
               }
               break; // for(;;)
           }

        //   rMsg.append(buf, len); // постоянно добавляем в конец новые данные вот сюда нужно всунуть гет из циркулярки
           //serialOutput(buf, len); // нужно создать сигнал, который позовёт слот сериал аутпут





          queueIn->put(queueIn,buf ,len);

          if(queueIn->isReading()==false)
           emit SignalReadBuff();
       }

}

void MainWindow::serialOutput(){





        queueIn->ReadingState(true);

/*

     if(queueIn->isReading()==false){
     queueIn->ReadingState(true);
*/

 static     QString Buf;

  qDebug() << "bytes avail"<<queueIn->BytesAvail();
  //   while(queueIn->BytesAvail()>0){
char temp;
 do{


         queueIn->get(queueIn, &temp,1 );


         Buf.append(temp);

           qDebug() << temp; // buuf dots not gives number



    if(temp == '\0'){

          // if(Buf.contains('0')){

         qDebug() << "temp = /0";

                        if(Buf[0] == '0'||Buf [0]=='1'||Buf [0]=='2'||Buf [0]=='3'||Buf [0]=='4')
                        {


                          //     ui->progressBar->setValue(std::atoi(Buf));
                          //     ui->lcdNumber->display(std::atoi(Buf));

                          // Buf.remove(5,3);
                            Buf.truncate(4);
                            qDebug() << "first else"<<Buf;
                            ui->progressBar->setValue(Buf.toInt());
                            ui->lcdNumber->display(Buf.toInt());

                        } else if(Buf[0]== 'L')
                        {

                             if(Buf[5]=='N')
                             {
                                 LedSignal(true);
                                 //emit

                             }
                             if(Buf[5]=='F')
                             {

                                LedSignal(false);

                             }
                        } else
                        {
                               qDebug() << "last else"; // buuf dots not gives number
                            ui->label->setText(Buf);
                           // ui->label->setText("bbb");

                        }





                          Buf.clear();


                   } else {

               // захуярить всё обратно qchar v char nahui nado blyati
               // сука цикл вайл нахуй
              // взять нахуй длину этой залупы и через цикл фор брать через
               // квадрвтные нахй скобки блять

               /*
               temp = Buf.back().toLatin1();
               qDebug() <<"OBRATKA NAHUI"<< temp; // buuf dots not gives number
               queueIn->put(queueIn, &temp,1 );
               */

           }





}while(queueIn->BytesAvail()>0);

       //  qDebug<<Buf;
 //        ui->label->setText(Buf);




  //       char temp;

     //    CircBuffQt::get(this,&temp ,1);


         //MainWindow::serialOutput(temp);

  //   }



     // SerialOutput();


     /*
     }

  queueIn->ReadingState(false);
*/


   //  qDebug() << "slot reading data is working";








        queueIn->ReadingState(false);




}



void MainWindow::serialOutput(char *data, qint64 size)
{

    int endOfMes = 0;

    //OutBuf.append(data,size );
    for (int i = 0; i < size; i++)
    {
        OutBuf[index+i] = data[i];

        if(OutBuf[index+i] == '\0') endOfMes = 1;

    }






    index= index+size;  //прописать о переполнении через 512 в дебаг

    //вот шляпу сверху убрать


    if(endOfMes == 1)
    {


        if(OutBuf[0] >= '0' &&OutBuf [0]<'5')
        {

               ui->progressBar->setValue(std::atoi(OutBuf));
               ui->lcdNumber->display(std::atoi(OutBuf));

        } else if(OutBuf[0 ]== 'L')
        {

             if(OutBuf[5]=='N')
             {
                 LedSignal(true);
                 //emit

             }
             if(OutBuf[5]=='F')
             {

                LedSignal(false);

             }
        } else
        {

            ui->label->setText(OutBuf);

        }


        index = 0;
        endOfMes =0;

    }



}
