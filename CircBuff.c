#define SIZE_OF_BUFFER_IN 128
#define SIZE_OF_BUFFER_OUT 256

 #include "CircBuff.h"
 #include <string.h>
 #include <stdlib.h>




    //#include "usbd_def.h"

#define max(x, y) ( (x) > (y) ? (x) : (y) )
#define min(x, y) ( (x) < (y) ? (x) : (y) )


struct queue queueIn, queueOut;
extern uint8_t BusyFlag;


//void MainWindow::on_pushButton_2_clicked()
int BuffInit()
{


			queueIn.buffer      = malloc(SIZE_OF_BUFFER_IN);  // проверить возвращаемое значение маллока на нуль
			queueIn.buffer_size = SIZE_OF_BUFFER_IN;
			queueIn.head        = 0;
			queueIn.tail        = 0;
			queueIn.bytes_avail = 0;

			queueOut.buffer      = malloc(SIZE_OF_BUFFER_OUT);
			queueOut.buffer_size = SIZE_OF_BUFFER_OUT;
			queueOut.head        = 0;
			queueOut.tail        = 0;
			queueOut.bytes_avail = 0;

			if (queueIn.buffer == NULL || queueOut.buffer == NULL)
			{
                /*
					while(BusyFlag != USBD_OK)
					{
						    BusyFlag = BusyCheck();

					    	if(BusyFlag == USBD_OK)
					    	{
						      	  BusyFlag = CDC_Transmit_FS ("\r\n No memory for buffer", 23);
						 	      break;
						  	}
					}

				//  ErrorNoMemForBuff();

                    */



			}

            return 0; //
}


int put (queue_t *q, uint8_t *data, size_t size)
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



int get (queue_t *q, uint8_t *data, size_t size)
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


