        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include "vector.h"
        #include "mystring.h"

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
        
        class Location
        {
        public:
          int origLocation;
          int newLocation;
          Location(): origLocation(0), newLocation(0) {}
          bool operator!= (const Location &rhs) const {return origLocation != rhs.origLocation;}
        }; // class Location
        

        class StoredBlock {
        public:
            unsigned origLocation; 
            DiskBlock* diskBlock;

            StoredBlock(): origLocation(0), diskBlock(NULL) {};
            StoredBlock(unsigned origLoc, DiskBlock* diskBlk): origLocation(origLoc), diskBlock(diskBlk) {};

            bool operator!= (const StoredBlock &rhs)const {return origLocation != rhs.origLocation;}

            void makeEmpty() {origLocation = 0; diskBlock = NULL ;}

        }; // class StoredBlock

        
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
            int hash( Location key, int tableSize ) const; // added
            int hash( StoredBlock key, int tableSize ) const; // added
            void rehash( );
        };

        #include "QuadraticProbing.cpp"
        #endif