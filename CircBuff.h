#pragma once

//#ifdef CircBuff_H
//#define CircBuff_H


//#include "main.h"//

typedef __UINT8_TYPE__ __uint8_t;
typedef __uint8_t uint8_t ;


typedef __SIZE_TYPE__ size_t;



typedef struct queue {
    uint8_t *buffer;
    size_t   buffer_size;
    size_t   head;
    size_t   tail;
    size_t   bytes_avail;
} queue_t ;





 int BuffInit();
 int put(struct queue *q, uint8_t *data, size_t size);
 int get(struct queue *q, uint8_t *data, size_t size);

//#endif
