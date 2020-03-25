/* vector.h
 *
 * ULTN: slim07 (Sean Lim)
 *
 * Define the Vector class type and the type name that will be used to refer to
 * the Data in a Vector (using a typedef).
 *
 */

 #include <iostream>
 #include <string>
 #include "card.h"
 #include "termfuncs.h"
 using namespace std;

 typedef Card *Data;

 class Vector {
 public:
   Vector();
   ~Vector();
   int size();
   bool empty();
   void push_back(Data value);
   void pop_back();
   Data front();
   Data back();
   Data at(int index);
   void insert(int index, Data value);
   void erase(int index);
 private:
   int vCapacity; //Number of locations in the vector
   int vSize;     //Number of elements stored in the vector
   Data *vBuffer;  //Pointer to the vector's dynamically allocated array
   void reserve(int n);
 };
