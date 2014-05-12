/********************************************************************/
/*  CircularBuffer.h - Library of functions that support a Circular */
/*                     Buffer                                       */
/********************************************************************/
#ifndef __CIRCULAR_BUFFER
#define __CIRCULAR_BUFFER

#define KEYSIZE     128
#define KEYMASK     0x7F
#define TRUE        1
#define FALSE       0

/**< Circular Buffer Types */
typedef unsigned char INT8U;    //typdef for main data type
typedef INT8U KeyType ;
typedef struct {  
    INT8U writePointer ; /**< write pointer */  
    INT8U readPointer ;  /**< read pointer */  
    INT8U size;         /**< size of circular buffer */
    INT8U mask;         /**< bit Mask of circular buffer size*/   
    KeyType keys[0];    /**< Element of ciruclar buffer */
} CircularBuffer ;

// Buffer full routine returns TRUE if buffer is full
inline int CircularBufferIsFull(CircularBuffer* que)
{ return (que->size == KEYSIZE); }
// Buffer empty routing returns TRUE if buffer is empty
inline int CircularBufferIsEmpty(CircularBuffer* que)
{ return !que->size; }
//Put a KeyType char in the circular buf if there is room
inline int CircularBufferEnque(CircularBuffer* que, KeyType k)
{
    if( CircularBufferIsFull(que) )    //No room
        return -1;   //Indicate error cond
    else {  //Put it in
        que->keys[que->writePointer++] = k;
        que->writePointer &= KEYMASK;   //wrap if necessary
        return ++que->size; //return the new size if successful
    }
}
//Take a KeyType char off the buffer and return it
inline int CircularBufferDeque(CircularBuffer* que, KeyType* pK)
{ 
    if( CircularBufferIsEmpty(que) )
        return -1;   //indicate error cond
    else {
        *pK = que->keys[que->readPointer++];
        que->readPointer &= KEYMASK;	//wrap if necessary
        return --que->size; //return new size if successful
    }
}
//Print out the KeyType chars currently on the buffer
//Not that if chars are not printable, there will be no output
inline int CircularBufferPrint(CircularBuffer* que)
{ 
    INT8U x = que->readPointer;
    if( CircularBufferIsEmpty(que) )
        return -1;  //Indicate empty que
    while( x != que->writePointer ) {
        printf("%c", que->keys[x++]);
        x &= KEYMASK;
    }
    return TRUE;
}
#endif
