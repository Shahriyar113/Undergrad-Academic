#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include<vector>
#include <iostream>

using namespace std;

class Heap
{
    int heap_capacity;
    int heap_length ; // current element number in the array
    int *heap_array;

public:
    Heap(int size)
    {

        heap_capacity = size;
        heap_length = 0;
        heap_array = (int*)malloc((heap_capacity+2) * sizeof(int));
        //heap array should be start indexing from 1 (not 0)
        heap_array[0]=0;

    }

    int left(int index)
    {
        return 2*index;
    }

    int right(int index)
    {
        return 2*index + 1;
    }

    int parent(int index)
    {
        return index/2;
    }

    //this function will build the array a max heap during each insertion
    //this is known as bubble up process
    //beacuse due to the recursive call the index moves at upward of the complete binary tree(heap)
    //and thus it ensures to make every individual node into a max heap
    //and thus the whole array beacames a max heap
    //complexity O(log n)


    void insert_heapify(int index)
    {

        int parent_index= parent(index);
        int temp;

        if(parent_index >= 1  && heap_array[index] < heap_array[parent_index])
        {
            temp = heap_array[index];
            heap_array[index] = heap_array[parent_index];
            heap_array[parent_index] = temp;
            insert_heapify(parent_index);

        }


    }


//to build an array into a max_heap, then every element(node) of that array (complete binary tree) should be made
//a heap individually

//this function makes the node of given index a "max heap"
//by recursive call the the bottom nodes also becaome heaps
//in this way it makes all the non heap node into a max heap individually
//Complexity O(log n)

    void Max_Heapify(int index)
    {
        int l,r,largest,temp;

        l=left(index);
        r=right(index);

        if( l <= heap_length && heap_array[l] < heap_array[index] )
        {
            largest = l;
        }
        else
        {
            largest = index;
        }

        if(r <= heap_length && heap_array[r] < heap_array[largest])
        {
            largest = r;
        }

        if(largest != index)
        {
            temp = heap_array[index];
            heap_array[index] = heap_array[largest];
            heap_array[largest] = temp;

            Max_Heapify(largest);
        }






    }

  /*  //So far it is not used
    //but it is used to make an unordered array into a max heap
    void Build_Max_Heap()
    {
        if(heap_length < 2)
        {
            return;
        }
        //calling the Max_Heapify() function for each node (except the leaf nodes)
        for (int i=heap_length/2 ; i>=1; i--)
        {
            Max_Heapify(i);
        }
    }

*/


    void insert(int number)
    {
        //cout << "Inserting" <<endl;

        //For inserting the very first element
        if(heap_length == 0)
        {
            heap_length++;
            heap_array[heap_length]=number;
            return;

        }


        heap_length++;
        heap_array[heap_length]=number;



        //resizing and extending the capacity of the array if the current capacity overflows
        if(heap_length == heap_capacity)
        {
            heap_capacity=heap_capacity * 2;
            heap_array = (int*)realloc(heap_array,(heap_capacity+1)*sizeof(int) ) ;
        }

        insert_heapify(heap_length);


    }

    int getMax()
    {
        return heap_array[1];
    }

    void deleteKey()
    {
        //swaping the largest node(root node) with the last node of the heap..(node = element of the array)
        int temp;
        temp=heap_array[1];
        heap_array[1] = heap_array[heap_length];
        heap_array[heap_length] = temp;

        heap_length--;

        if(heap_length == heap_capacity/4)
        {
            heap_array = (int*)realloc(heap_array,(heap_capacity/2+1)*sizeof(int));
        }

        //making the heap into max heap
        Max_Heapify(1);



    }

    int size()
    {
        return heap_length;
    }

    void print_heap()
    {
        if(heap_length==0)
        {
            cout << "[Empty]" <<endl;
        }

        for(int i=1; i<=heap_length; i++)
        {
            cout << heap_array[i] <<" ";
        }
    }

    ~Heap()
    {
        free(heap_array);
    }


};


void heapsort(vector<int> &numbers)
{
    Heap h(numbers.size());
    for(int i=0; i < numbers.size() ; i++)
    {
        h.insert(numbers[i]);
    }

    int index = 0;
    while(h.size() !=0)
    {
        numbers.at(index++) = h.getMax();

        //cout << "After deleting " << h.getMax() <<" : ";
        h.deleteKey();
        //h.print_heap();
    }



}

#endif // HEAP_H_INCLUDED


