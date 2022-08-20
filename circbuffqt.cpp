#include "circbuffqt.h"



#include <string.h>
#include <stdlib.h>
#include <cstdlib>


#include <QDebug>


#define SIZE_OF_BUFFER_IN 128
#define SIZE_OF_BUFFER_OUT 256


#define max(x, y) ( (x) > (y) ? (x) : (y) )
#define min(x, y) ( (x) < (y) ? (x) : (y) )


CircBuffQt::CircBuffQt(QObject *parent) : QObject(parent)
{
   buffer      = (uint8_t *)malloc(SIZE_OF_BUFFER_IN);  // проверить возвращаемое значение маллока на нуль
   buffer_size = SIZE_OF_BUFFER_IN;
   head        = 0;
   tail        = 0;
   bytes_avail = 0;

   stateOfBuff = false;

  // qDebug() << "constructor is workind";


   if (buffer == nullptr)
   {


       qDebug() << "malloc is not working";

   }

}


//int CircBuffQt::put (CircBuffQt *q, uint8_t *data, size_t size)
int CircBuffQt::put (CircBuffQt *q, char *data, size_t size)
{
        if (q->buffer_size - q->bytes_avail < size)
        {
            return 0;
        }

    const size_t part1 = min (size, q->buffer_size - q->tail);
    const size_t part2 = size - part1;

    memcpy (q->buffer + q->tail, data,  part1);
    memcpy (q->buffer, data + part1, part2);

    q->tail = (q->tail + size) % q->buffer_size;
    q->bytes_avail += size;
    return 1;

}



int CircBuffQt::get (CircBuffQt *q, char *data, size_t size)
{

    if (q->bytes_avail < size)
    {
        return 0;
    }

    const size_t part1 = min (size, q->buffer_size - q->head);
    const size_t part2 = size - part1;

    memcpy (data, q->buffer + q->head, part1);
    memcpy (data + part1, q->buffer, part2);

    q->head = (q->head + size) % q->buffer_size;
    q->bytes_avail -= size;
    return 1;

}







bool CircBuffQt::isReading(){

    return stateOfBuff;

}

void CircBuffQt::ReadingState(bool state){
    stateOfBuff = state;
}








size_t CircBuffQt::BytesAvail(){

    return bytes_avail;
}






void CircBuffQt::ReadingData()
{


//    if(isReading==false){
//    isReading = true;
//    while(bytes_avail!=0){


 //       char temp;

    //    CircBuffQt::get(this,&temp ,1);


        //MainWindow::serialOutput(temp);





    // SerialOutput();



//    isReading = false;

    qDebug() << "slot reading data is working";

}
