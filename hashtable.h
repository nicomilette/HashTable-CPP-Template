#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>     // string.c_str(), string();
#include <cstring>
#include <algorithm>  // std::find
#include <functional> // std::hash
#include <iostream>   // std::cout, std::cerr
#include <fstream>    // ifstream and ofstream
#include <string.h>   // strcpy, strtok, 
#include <sstream> 


using namespace std;

// max_prime is used by the helpful functions provided to you.
static const unsigned int max_prime = 1301081;
 
// SeparateChaining Hash table class
namespace cop4530 {
   template <typename K, typename V>
      class HashTable
      {
         public:
            explicit HashTable(size_t size = 101); //constructor. Create a hash table, where the size of the vector is set to prime_below(size) (where size is default to 101), where prime_below() is a private member function of the HashTable and provided to you.
	         size_t size() const;
            ~HashTable(); //destructor. Delete all elements in hash table.
            bool contains(const K & x); //check if key k is in the hash table.
            bool match(const std::pair<K, V> & kv) const; //check if key-value pair is in the hash table.
            bool insert(const std::pair<K, V> & kv); //add the key-value pair kv into the hash table. Don't add if kv or key is already in the hash table. Return true if kv is inserted; return false otherwise (i.e., if kv is in the hash table).
            bool insert (std::pair<K, V> && kv); //move version of insert.
            bool remove(const K & k); //delete the key k and the corresponding value if it is in the hash table. Return true if k is deleted, return false otherwise (i.e., if key k is not in the hash table).
            void clear(); //delete all elements in the hash table
            bool load(const char * filename); //load the content of the file with name filename into the hash table. In the file, each line contains a single pair of key and value, separated by a white space.
            void dump(); //display all entries in the hash table. If an entry contains multiple key-value pairs, separate them by a vertical bar (|) (see the provided executable for the exact output format).
            bool write_to_file(const char *filename); //write all elements in the hash table into a file with name filename. Similar to the file format in the load function, each line contains a pair of key-value pair, separated by a white space.
            string getValue(const K & x) const;
            void update(const std::pair<K,V> & kv);
         private:
            void setPrimes(std::vector<unsigned long>& vprimes);
            unsigned long prime_below(unsigned long n);
            void makeEmpty(); //delete all elements in the hash table. The public interface clear() will call this function.
            void rehash(); //Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
            size_t myhash(const K & x) const; //return the index of the vector entry where k should be stored.
            vector<list<std::pair<K, V>>> table;
            size_t currentSize;
      };

} // end of namespace cop4530

#include "hashtable.hpp"

#endif
