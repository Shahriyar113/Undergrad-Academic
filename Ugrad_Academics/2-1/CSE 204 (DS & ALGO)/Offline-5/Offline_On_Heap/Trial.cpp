#include<iostream>
#include<fstream>
#include<cstdio>
#include<queue>
#include<ctime>
#include "heap.h"
using namespace std;

int main()
{
    vector<int> numbers;


   numbers.push_back(18);
   numbers.push_back(26);
   numbers.push_back(84);
   numbers.push_back(77);
   numbers.push_back(36);
   numbers.push_back(26);
   numbers.push_back(18);
   numbers.push_back(46);
   numbers.push_back(8);
   numbers.push_back(0);
   numbers.push_back(3);
   numbers.push_back(4);
   numbers.push_back(1);
   numbers.push_back(6);
   numbers.push_back(-3);
   numbers.push_back(7);
   numbers.push_back(-19);
   numbers.push_back(-35);
   numbers.push_back(-15);
   numbers.push_back(-23);






   Heap h(numbers.size());


   for (int i=0;i<numbers.size();i++)
   {
      // cout << "inserting " << numbers[i]<<endl;
       h.insert(numbers[i]);
   }

      cout << "Before Sorting The heap is:" << endl <<endl;

   h.print_heap();


   cout << endl;
   cout << endl;

   heapsort(numbers);

   cout << "After Sorting The heap is:" << endl <<endl;

   for (int i=0;i<numbers.size();i++)
   {
       cout << numbers[i] << " ";
   }

   cout << endl;




}


