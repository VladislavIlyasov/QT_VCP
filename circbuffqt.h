#ifndef CIRCBUFFQT_H
#define CIRCBUFFQT_H

#include <QObject>



class CircBuffQt : public QObject
{
    Q_OBJECT
public:
    explicit CircBuffQt(QObject *parent = nullptr);



signals:
   void isNotEmpty(); // &&

public:

   //int put (CircBuffQt *q, uint8_t *data, size_t size);
   //int get (CircBuffQt *q, uint8_t *data, size_t size);
   int put (CircBuffQt *q, char *data, size_t size);
   int get (CircBuffQt *q, char *data, size_t size);

   bool isReading();

   void ReadingState(bool state);

   size_t BytesAvail();

   public slots:


   void ReadingData();


   private:

   uint8_t *buffer;
   size_t   buffer_size;
   size_t   head;
   size_t   tail;
   size_t   bytes_avail;


    bool stateOfBuff;

};

#endif // CIRCBUFFQT_H
