#include <vector>
#include <list>
#include <string>     // string.c_str(), string();
#include <algorithm>  // std::find
#include <functional> // std::hash
#include <iostream>   // std::cout, std::cerr
#include <fstream>    // ifstream and ofstream
#include <string.h>   // strcpy, strtok, 
#include <unistd.h>   // crypt()
#include <cstring>
#include <stdlib.h>   
#include <crypt.h>
#include "hashtable.h"

#include "pass_server.h"

using namespace std;
using namespace cop4530;
 
template <typename K, typename V>
size_t PassServer<K,V>::size()
{
   return Passwords.size();
}

template <typename K, typename V>
PassServer<K, V>::PassServer(size_t size)
{
   Passwords = HashTable<std::string,std::string>(size);
}

template <typename K, typename V>
PassServer<K, V>::~PassServer()
{
   Passwords.clear();
}

template <typename K, typename V>
bool PassServer<K, V>::load(const char *filename)
{
       std::ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        K k;
        V v;
        if (iss >> k >> v) {
            std::pair<K, V> kv(k, v);
            addUser(kv);
        }
    }
    infile.close();
    return true;
}

template <typename K, typename V>
bool PassServer<K, V>::addUser(std::pair<string, string> & kv){
      pair<string, string> kv1 = make_pair(kv.first, encrypt(kv.second));
      return Passwords.insert(kv1);
}

template <typename K, typename V>
bool PassServer<K, V>::addUser(std::pair<string, string> && kv){
      pair<string, string> kv1 = make_pair(kv.first, encrypt(kv.second));
      
      return Passwords.insert(std::move(kv1));
}

template <typename K, typename V>
bool PassServer<K, V>::removeUser(const string & k){
      return Passwords.remove(k);
}

template <typename K, typename V>
bool PassServer<K, V>::find(const string & user){
      return Passwords.contains(user);
}

template <typename K, typename V>
void PassServer<K, V>::dump(){
      Passwords.dump();
}

template <typename K, typename V>
bool PassServer<K, V>::write_to_file(const char *filename){
   return Passwords.write_to_file(filename);
}

template <typename K, typename V>
string PassServer<K,V>::encrypt(const string & str) {
    char salt[] = "$1$########";
    char *encrypted_password = crypt(str.c_str(), salt);
    return string(encrypted_password).substr(12);
}



template <typename K, typename V>
bool PassServer<K, V>::changePassword(const pair<string, string> &p, const string & newpassword) {
 // Encrypt the new password
    string encrypted_newpass = encrypt(newpassword);

    // Check if the user is in the hash table
    if (!Passwords.contains(p.first)) {
            cout << "User not found\n";
        return false;
    }


    // Get the current password for the user
    string current_password = Passwords.getValue(p.first);

    // Check if the current password matches p.second
    if (current_password != encrypt(p.second)) {
      cout << "Incorrect current password\n";
        return false;
    }

    // Check if the new password is the same as the old password
    if (encrypted_newpass == current_password) {
      cout << "New password cannot be the same as current\n";
        return false;
    }

    // Update the password in the hash table
    Passwords.update(make_pair(p.first, encrypted_newpass));

    return true;
}



/* XXX: Please keep this line at the very end */
template class PassServer<string, string>;
