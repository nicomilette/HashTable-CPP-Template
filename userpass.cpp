#include <iostream>
#include <fstream>
#include <string>

#include "hashtable.h"
#include "pass_server.h"

using namespace std;

void menu()
{
   cout << "\n\n";
   cout << "l - Load From File" << endl;
   cout << "a - Add User" << endl;
   cout << "r - Remove User" << endl;
   cout << "c - Change User Password" << endl;
   cout << "f - Find User" << endl;
   cout << "d - Dump HashTable" << endl;
   cout << "s - HashTable Size" << endl;
   cout << "w - Write to Password File" << endl;
   cout << "x - Exit program" << endl;
   cout << "\nEnter choice : \n";
}

int main()
{
   bool toexit = false;
   string line;

   PassServer<string, string> ps{};

   while(!toexit){
      menu();
      cin >> line;
      switch(line[0]){
         case 'l': {
            string filename;
            cout << "Enter password file name to load from: \n";
            cin >> filename;

            if(ps.load(filename.c_str())){
               cout << "Success loading password file.\n";
            }
            else{
               cout << "Failure loading password file.\n";               
            }
            break;
         }
         case 'a': {
            string username, password;
            cout << "Enter username: \n";
            cin >> username;
            cout << "Enter password: \n";
            cin >> password;
            if(ps.addUser(make_pair(username, password))){
               cout << "Success adding " << username <<".\n";
            }
            else{
               cout << "Failure adding " << username <<".\n";
            }
            break;
         }
         case 'r': {
            string username;
            cout << "Enter username: \n";
            cin >> username;
            
            if(ps.removeUser(username)){
               cout << "Success removing " << username <<".\n";
            }
            else{
               cout << "Failure removing " << username <<".\n";
            }
            break;
         }
         case 'c': {
            string username, newpassword, password;
            cout << "Enter username: \n";
            cin >> username;
            cout << "Enter current password: \n";
            cin >> password;
            cout << "Enter new password: \n";
            cin >> newpassword;



            if(ps.changePassword(make_pair(username, password), newpassword)){
               cout << "Success updating password for " << username << ".\n";
            }
            else{
               cout << "Failure updating password for " << username << ".\n";
            }
            break;
         }

         case 'f': {
            string username;
            cout << "Enter username: \n";
            cin >> username;
            if(ps.find(username))
               cout << "User found!" << endl;
            else
               cout << "User not found!" << endl;
            break;
         }
         case 'd': {
            ps.dump();
            break;
         }
         case 's': {
            cout << "HashTable size is " << ps.size() << endl;
            break;
         }
         case 'w': {
            string filename;
            cout << "Enter password file name to write to: \n";
            cin >> filename;
            if(ps.write_to_file(filename.c_str()))
            {
               cout << "Success writing to file.\n";
            }
            else{
               cout << "Success writing to file.\n";
            }
            break;
         }
         case 'x': {
            toexit = true;
            cout << "Exiting...\n";
            break;
         }
         default: {
            cout << "Invalid choice." << endl;
            break;
         }
      }
   }



   return 0;
}






