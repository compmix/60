        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include "vector.h"
        #include "mystring.h"
        #include "maxfinder.h"
        #include "LinkedList.h"

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings

        
        class Edge2 {
        public:
            short capacity;
            short dest;
            long destAddr;

            bool operator> (const Edge2 &rhs) const {
                return capacity != rhs.capacity;
            }
        };

        class Vertex {
        public:
            short index;
            long intAddr;

            Vertex(): index(-1), intAddr(-1) {};

            Vector<Edge2> edges;

            void operator= (Computer comp) {
                intAddr = 0;
                for (int i = 0; comp.address[i] != '\0'; ++i) {
                    if(comp.address[i] == '.') continue;
                    intAddr = intAddr*10 + comp.address[i] - '0';
                }
            }

            bool operator!= (const Vertex &rhs) const {
                return intAddr != rhs.intAddr;
            }

        }; // class Vertex


        template <class HashedObj>
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable( const HashedObj & notFound, int size = 101 );
            QuadraticHashTable( const QuadraticHashTable & rhs )
              : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                array( rhs.array ), currentSize( rhs.currentSize ) { }

            const HashedObj & find( const HashedObj & x ) const;

            void makeEmpty( );
            void insert( const HashedObj & x );
            void remove( const HashedObj & x );

            const QuadraticHashTable & operator=( const QuadraticHashTable & rhs );

            enum EntryType { ACTIVE, EMPTY, DELETED };
          private:
            struct HashEntry
            {
                HashedObj element;
                EntryType info;

                HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
                  : element( e ), info( i ) { }
            };

            vector<HashEntry> array;
            int currentSize;
            const HashedObj ITEM_NOT_FOUND;
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            int findPos( const HashedObj & x ) const;
            int hash( const string & key, int tableSize ) const;
            int hash( int key, int tableSize ) const;
            int hash( Vertex key, int tableSize ) const;
            void rehash( );
        };

        #include "QuadraticProbing.cpp"
        #endif
