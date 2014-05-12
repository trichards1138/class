/*************************************************************************************/
/*  main.cpp - Main program entry point.  Creates a Circular buffer and spawns some  */
/*             tests to verify the circular buffer operation                         */
/*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //just for delay element

#include "CircularBuffer.h"

//Set a test to one (1) to enable test
#define TEST_FULL       1
#define TEST_MULTPASS   1
#define TEST_WRAPPING   1

int main(void)
{
    unsigned int x, y;
    INT8U wP=0, rP=0;
    KeyType myKey=0;
    // Create the circular buffer with KEYSIZE elements
    CircularBuffer *myBuf = (CircularBuffer *)malloc( (sizeof(CircularBuffer)+KEYSIZE) );
    myBuf->size = 0;    //Initialize the members of the struct
    myBuf->mask = KEYMASK;  //Mask that is used to wrap the pointers
    myBuf->writePointer = 0;
    myBuf->readPointer = 0; 
    
#if TEST_FULL   //test 3 - verify buffer full and empty work correctly
    wP=55;
    for( y = 0; y < 10; y++ ) {
        CircularBufferEnque( myBuf, 'a' );  //increment the pointers each time through
        CircularBufferDeque( myBuf, &rP );  //Verify they track correctly
        for( x=0; x<500; x++ )      //try to put 500 chars in buf
            if( CircularBufferEnque( myBuf, wP ) == -1 )    //Verify we break at the right point
                break;
        //Print out some statistics and verify everything happened as expected
        printf("Size=%d, w=%d, r=%d, wP=%c\r", myBuf->size, myBuf->writePointer, myBuf->readPointer, wP );
        for( x=0; x<500; x++ )      //Now read them out
            if( CircularBufferDeque( myBuf, &rP ) == -1 )   //verify we only read until que empty
                break;  
        //Print out some stats and verify them
        printf("Size=%d, w=%d, r=%d, rP=%c\r", myBuf->size, myBuf->writePointer, myBuf->readPointer, rP );
    }
#endif
#if TEST_MULTPASS   //test2 - verify multiple passes wrap correctly and the correct character is read
    wP=49;
    for( x=0; x<1000; x++ ) {   //Put 1000 chars on the que and immediately read them out
        CircularBufferEnque( myBuf, wP );
        CircularBufferDeque( myBuf, &rP );
        //print out stats to verify pointers and size are tracking correctly
        printf("Size=%d, w=%d, r=%d, rP=%c\r", myBuf->size, myBuf->writePointer, myBuf->readPointer, rP );
        rP = 0;
        for( y=0; y<10000; y++ )  //Delay some so we can watch output
            strcmp( "Well WEll", "Well well");
        
    }  
#endif  //test2
#if TEST_WRAPPING   //test1 - Verify wrapping with long que fills and correct readback of the chars
    printf("\r\n\r\n");
    printf("Size is: %d ", myBuf->size);
    printf("Write Pointer is: %d ", myBuf->writePointer);
    printf("Read Pointer is: %d\r\n", myBuf->readPointer);
    for( x=48; x < (KEYSIZE); x++ )     //Put a succession of chars on que
        CircularBufferEnque( myBuf, x );
    printf("\r\n");
    printf("Size is: %d ", myBuf->size);
    printf("Write Pointer is: %d ", myBuf->writePointer);
    printf("Read Pointer is: %d\r\n", myBuf->readPointer);
    CircularBufferPrint(myBuf);     //verify they print out correctly
    printf("\r\n");
    printf("Size is: %d\r\n", myBuf->size);
    printf("Write Pointer is: %d ", myBuf->writePointer);
    printf("Read Pointer is: %d\r\n", myBuf->readPointer);
    for( x=0; x < KEYSIZE; x++ ) {  //Deque the chars and print them out
        CircularBufferDeque( myBuf, &myKey );  
        printf("%c ", myKey);   //verify chars are correct
    }
    printf("Size is: %d ", myBuf->size);
    printf("Write Pointer is: %d ", myBuf->writePointer);
    printf("Read Pointer is: %d\r\n\r\n", myBuf->readPointer);
    
    for( x=33; x < (KEYSIZE); x++ )     //do it again to watch wrap
        CircularBufferEnque( myBuf, x );
    printf("\r\n");
    printf("Size is: %d ", myBuf->size);
    printf("Write Pointer is: %d ", myBuf->writePointer);
    printf("Read Pointer is: %d\r\n", myBuf->readPointer);
    CircularBufferPrint(myBuf);     //print them out again
    printf("\r\n");
    printf("Size is: %d\r\n", myBuf->size);
    printf("Write Pointer is: %d ", myBuf->writePointer);
    printf("Read Pointer is: %d\r\n", myBuf->readPointer);
    for( x=0; x < KEYSIZE; x++ ) {
        CircularBufferDeque( myBuf, &myKey );   //verify chars are correct
        printf("%c ", myKey);
    }
    printf("Size is: %d ", myBuf->size);    //last stats print verify all
    printf("Write Pointer is: %d ", myBuf->writePointer);   //pointers and size
    printf("Read Pointer is: %d\r\n", myBuf->readPointer);  //are correct
#endif //test1
}
