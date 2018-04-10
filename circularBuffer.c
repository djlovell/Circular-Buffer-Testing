/**
******************************************************************************
* @file circularBuffer.c
* @author Daniel Lovell
* @version V1.0
* @date 27-March-2018
* @brief Circular Buffer Implementation in C
******************************************************************************
*/

#include "circularBuffer.h"
#include <stdlib.h>
#include <stdio.h>

static void incPointer( uint32_t* );
void printBuffer( commBuffer_t* comm);

void InitBuffer( commBuffer_t* comm )
	{
	/* allocate buffer */
	//comm = malloc( sizeof( commBuffer_t ) );

	/* initialize members to 0 */
	comm->head = 0;
	comm->tail = 0;
	comm->newlineCnt = 0;
	}

bool haveStr( commBuffer_t* comm )
	{
	return ( comm->newlineCnt > 0 ) ? true : false;
	}

void putChar( commBuffer_t* comm, char ch )
	{
	if( comm->newlineCnt > 0 )
		return;
		
	if( ch == '\n' )
		{
		printf( "Newline is being entered.\n");
		}
	else
		{
		printf( "%c is being entered.\n", ch );
		}
	/* If this character would fill the buffer, force the
	 * last char to be the newline.
	 */
	if( getBufferSize( comm ) == ( MAXCOMMBUFFER - 1 ) )
		{
		ch = '\n';
		}
	comm->buffer[ comm->head ] = ch;
	incPointer( &comm->head );
	if( ch == '\n' )
		{
		comm->newlineCnt++;
		}
	printf( "Newline count: %d\n", comm->newlineCnt );
	printBuffer( comm );
	}

char getChar( commBuffer_t* comm )
	{
	char ret_ch;

	ret_ch = comm->buffer[ comm->tail ];
	incPointer( &comm->tail );

	if( ret_ch == '\n' )
		{
		comm->newlineCnt--;
		}
	return ret_ch;
	}

void putStr( commBuffer_t* comm, char* str, uint8_t length )
	{
	for( int i = 0; i < length; i ++)
		{
		putChar( comm, *( str + i ) );
		}
	}

void getStr( commBuffer_t* comm, char* str )
	{
	uint8_t idx = 0;
	char cur_ch;
	if( haveStr( comm ) )
		{
		do
			{
			cur_ch = getChar( comm ); // get one character at a time
			*( str + idx ) = cur_ch; // insert char in string
			idx++; // increment string pointer to next position
			}
		while( cur_ch != '\n' );
		*( str + idx ) = '\0';
		}
	}

int getBufferSize( commBuffer_t* comm)
	{
	return ( comm->head - comm->tail + MAXCOMMBUFFER + 1 ) % ( MAXCOMMBUFFER + 1 );
	}

/* Returns new index for head or tail */
static void incPointer( uint32_t* index )
	{
	uint8_t temp_idx = *index;
	*index = ( ( ( temp_idx + 1 ) + MAXCOMMBUFFER ) % MAXCOMMBUFFER );
	}

bool isEmptyBuffer( commBuffer_t * comm)
	{
	return ( getBufferSize( comm ) == 0 ) ? true : false;
	}

bool isFullBuffer( commBuffer_t * comm)
	{
	return ( getBufferSize( comm ) == MAXCOMMBUFFER ) ? true : false;
	}

void printBuffer( commBuffer_t* comm)
	{
	printf( "BUFFER CONTENTS AFTER INSERTION: \n");
	for( int i = 0; i < MAXCOMMBUFFER + 1; i++ )
		{
		printf( "INDEX %d: %c\n", i, comm->buffer[i] );
		}	
	printf( "END OF BUFFER OUTPUT\n\n" );
	}