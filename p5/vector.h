#ifndef _VECTOR_H
#define _VECTOR_H

/*
 * The next line is used because Codewarrior has a conflict with
 * the STL vector. Make sure to put the #include of this file
 * AFTER all the system includes.
 */
#define vector Vector
#include <cstddef> // for NULL

class ArrayIndexOutOfBounds { };

template <class Object>
class vector
{
  public:
    explicit vector( int theSize = 1 ) : maxCapacity(theSize), currentSize( theSize -1  ) { objects = new Object[ maxCapacity ]; }
    vector( const vector & rhs ) : objects( NULL )  { operator=( rhs ); }
    ~vector( )          { delete [ ] objects; }


    int size( ) const   { return currentSize; }
    int maxSize() const { return maxCapacity; }
    int end() const    {return currentSize - 1; }

    Object & operator[]( int index ) {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= currentSize )
            throw ArrayIndexOutOfBounds( );
                                                     #endif
        return objects[ index ];
    }


    // felix insert function
    void insert(Object ob) {
      if(currentSize == maxCapacity) resize(maxCapacity * 2);

      objects[currentSize++] = ob;

    }


    const vector & operator = ( const vector & rhs );
    void resize( int newSize );

  private:
    
    int maxCapacity;
    int currentSize;
    
    Object * objects;
};

#include "vector.cpp"
#endif


