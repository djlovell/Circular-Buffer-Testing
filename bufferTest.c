/* Author: Daniel J. Lovell
   Date: 10 March, 2018 */

#include "circularBuffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void getBufferContents( commBuffer_t* );

main( void )
    {
    int haveString = 0;
    char* helloStr = "Hello\n";
    printf( "%s", helloStr );

    commBuffer_t rx_buffer;
    InitBuffer( &rx_buffer );

    while( 1 ) 
        {
        /* Get char from command line */
        char t = getchar();

        if( t == '\n' )
            {
            haveString = true;
            }

        putChar( &rx_buffer, t ); 

        if( haveString )
            {
            putChar( &rx_buffer, t ); 
            getBufferContents( &rx_buffer );
            return;
            }
        }
    return;
    
    }

void getBufferContents( commBuffer_t* buff )
    {
    if( haveStr( buff ) )
        {
        /* Extract full string from receive buffer */
        char txStr[ MAXCOMMBUFFER + 1 ];
        getStr( buff, txStr );

        /* Place full string in the transmit buffer */
        uint8_t tx_size = strlen( txStr );

        printf( "\n%s was extracted from the buffer. \n" );
        }	
    }