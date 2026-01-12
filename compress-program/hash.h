#ifndef HASH_H
#define HASH_H
#include <fstream>
#include <vector>
using namespace std;

template <class Key, class Value>
class HashTable {
public:
    explicit HashTable( const Value & notFound, int size = 101 );         //Explicit constructor
    HashTable( const HashTable & rhs )
      : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
        array( rhs.array ), currentSize( rhs.currentSize ) { }

    const Value & find( const Key & x ) const;                             //find operations

    void makeEmpty( );                                                    //clear the hash table
    void insert( const Key & key, const Value & value );                  //insert new item to the hash table
    void remove( const Key & x );                                         //delete an item (given its key) from the hash table

    const HashTable & operator=( const HashTable & rhs );                 //operator overloading

    enum EntryType { ACTIVE, EMPTY, DELETED };                            //to tag entries as active, empty or deleted so that we don't stop on a deleted cell
private:
    struct HashEntry {                                                    //object in the hash table
        Key key;
        Value value;
        EntryType info;

        HashEntry( const Key & k = Key( ), const Value & v = Value( ), EntryType i = EMPTY )
          : key( k ), value( v ), info( i ) { }
    };

    vector<HashEntry> array;                                               //it is the hash table we will work on
    int currentSize;
    const Value ITEM_NOT_FOUND;

    bool isActive( int currentPos ) const;
    int findPos( const Key & x ) const;
    void rehash( );                                                        //since we are using linear probing, we need to rehash the table when the size is size/2

    //primes to be used while rehashing or creating hash table
    int nextPrime( int n );
    bool isPrime( int n );
};

//we define them as external function, distinguished only by the type of the argument, at compile time
int hash_func( const string & key, int tableSize );
int hash_func( int key, int tableSize );

template <class Key, class Value>
HashTable<Key, Value>::HashTable( const Value & notFound, int size )            //constructor
    : ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) ) {
    makeEmpty( );
}

template <class Key, class Value>
void HashTable<Key, Value>::makeEmpty() {                                      //update all cells as EMPTY
    currentSize = 0;
    for( int i = 0; i < array.size( ); i++ )
        array[ i ].info = EMPTY;
}

template <class Key, class Value>
int HashTable<Key, Value>::findPos( const Key & x ) const {                  //if we find it and it is not EMPTY than retun

    int p = hash_func( x, array.size( ) );

    while( array[ p ].info != EMPTY && array[ p ].key != x ) {

        p++;

        if( p >= array.size( ) ) {
            p -= array.size( );
        }
    }

    return p;
}

template <class Key, class Value>
bool HashTable<Key, Value>::isActive( int currentPos ) const {             //check status whether it is ACTIVE
    return array[ currentPos ].info == ACTIVE;
}

template <class Key, class Value>
void HashTable<Key, Value>::remove( const Key & x ) {                      //update status as DELETED
    int currentPos = findPos( x );

    if( isActive( currentPos ) ) {
        array[ currentPos ].info = DELETED;
    }
}

template <class Key, class Value>
const Value & HashTable<Key, Value>::find( const Key & x ) const {       //uses findPos and if it is active return value
    int currentPos = findPos( x );

    if (isActive( currentPos )) {
        return array[ currentPos ].value;
    }

    return ITEM_NOT_FOUND;
}

template <class Key, class Value>
void HashTable<Key, Value>::insert( const Key & key, const Value & value ) {    //if exists, return.
    int currentPos = findPos( key );

    if( isActive( currentPos ) ) {
        return;
    }

    array[ currentPos ] = HashEntry( key, value, ACTIVE );

    if( ++currentSize >= array.size( ) / 2 ) {                                  //after inserting it may be overcrowded so rehash
        rehash( );
    }
}

template <class Key, class Value>
void HashTable<Key, Value>::rehash( ) {
    vector<HashEntry> oldArray = array;

    array.resize( nextPrime( 2 * oldArray.size( ) ) );              //resize according to the closes bigger prime number

    for( int j = 0; j < array.size( ); j++ ) {                                //mark all entries as EMTPY
        array[ j ].info = EMPTY;
    }
    currentSize = 0;
    for( int i = 0; i < oldArray.size( ); i++ ) {                            //copy the old hash table
        if( oldArray[ i ].info == ACTIVE ) {
            insert( oldArray[ i ].key, oldArray[ i ].value );
        }
    }
}

template <class Key, class Value>
bool HashTable<Key, Value>::isPrime( int n ) {                              //check is the number prime (to use in nextPrime)
    if ( n == 2 || n == 3 ) return true;
    if ( n == 1 || n % 2 == 0 ) return false;
    for ( int i = 3; i * i <= n; i += 2 )
        if ( n % i == 0 ) return false;
    return true;
}

template <class Key, class Value>
int HashTable<Key, Value>::nextPrime( int n ) {                             //find the next bigger prime the rehash the table
    if ( n % 2 == 0 ) n++;
    for ( ; !isPrime( n ); n += 2 );
    return n;
}

int hash_func( const string & key, int tableSize ) {     //hash the given string object
    int hashVal = 0;
    for ( int i = 0; i < key.length(); i++ )
        hashVal = 37 * hashVal + key[ i ];

    hashVal %= tableSize;
    if ( hashVal < 0 ) hashVal += tableSize;
    return hashVal;
}

int hash_func( int key, int tableSize ) {               //hash the given integer object
    if( key < 0 ) key = -key;
    return key % tableSize;
}
#endif
