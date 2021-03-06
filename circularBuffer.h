#ifndef JAH_CIRCULAR_BUFFER_H
#define JAH_CIRCULAR_BUFFER_H

// #include "stm32f4xx.h"
#include <stdint.h>
#define MAXCOMMBUFFER 6

// likely useless boolean defs
typedef uint8_t bool;
enum { false, true };

typedef struct _commBuffer_t
	{
	uint32_t head;
	uint32_t tail;
	char buffer[ MAXCOMMBUFFER + 1 ];
	uint8_t newlineCnt;
	} commBuffer_t;

//Initializes the struct commBuffer_t to zero
void InitBuffer( commBuffer_t* comm );

//Test if a complete string is in buffer delimiter is \n
bool haveStr( commBuffer_t* comm );

//Put character in buffer and update head
void putChar( commBuffer_t* comm, char ch );

//Get character from buffer and update tail;
char getChar( commBuffer_t* comm );

//put C string into buffer
void putStr( commBuffer_t* comm, char* str, uint8_t length );

//get C string from buffer
void getStr( commBuffer_t* comm, char* str );

//get Size of Buffer
int getBufferSize( commBuffer_t* comm );
#endif

/* buffer empty/full status functions */
bool isEmptyBuffer( commBuffer_t* comm );
bool isFullBuffer( commBuffer_t * comm);


