#ifndef MAX_HEAP_H_INCLUDED
#define MAX_HEAP_H_INCLUDED


#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Heap
{
private:
    int max_size;
    int *arr;
    int lastInsert = -1;

    int getParent(int i)
    {
        return (i-1)/2;
    }
    int getLeftChild(int i)
    {
        return 2*i+1;
    }
    int getRightChild(int i)
    {
        return 2*i+2;
    }


public:
    Heap(int max_size)
    {
        this->max_size = max_size;
        arr = new int[max_size];
    }
    int size() //returns the number of elements currently available
    {
        return lastInsert+1;
    }
    void insert(int value)
    {
        arr[++lastInsert] = value;
        int i = lastInsert;
        int parentValue = arr[getParent(i)];
        //in a already heaped structure, inserting a new element and then this iteration is bubbling up the element to its correct position
        //so that the max heap does not loss its property
        while(parentValue < arr[i])
        {
            swap(arr[getParent(i)], arr[i]);
            i = getParent(i);
            parentValue = arr[getParent(i)];
        }
    }
    //This function returns the root element of the max heap
    int getMax()
    {
        try
        {
            if(size() == 0)
            {
                throw out_of_range("Heap is empty");
            }
            return arr[0];
        }
        catch(const out_of_range &oor)
        {
            cout << oor.what() << endl;
        }
    }
    //This function deletes the root element of the max heap
    //To delete the root, first replacing the last inserted value with the root
    //Then bubbling it down to its correct position from the root
    void deleteKey()
    {
        arr[0] = arr[lastInsert--];
        int i = 0; //starting the iteration from root
        while(true)
        {
            int left = getLeftChild(i);
            int right = getRightChild(i);
            //This case means we have already reached to the end of the heap
            //if left child is greater than both parent and right child, then swapping parent with left child.
            if(left <= lastInsert && arr[left] > arr[right] && arr[left] > arr[i])
            {
                swap(arr[i], arr[left]);
                i = left; //now the current value is in left child's place.
            }
            //else if the right child is greater than both parent and left child, then swapping parent with right child.
            else if(right <= lastInsert && arr[right] > arr[left] && arr[right] > arr[i])
            {
                swap(arr[i], arr[right]);
                i = right; //now the current value is in right child's place
            }
            //else the current value is in its correct position. so we can break this loop
            else
            {
                break;
            }
        }
        return ;
    }

    void print()
    {
        for(int i=0; i<=lastInsert; i++)
            cout<<arr[i]<<" ";
        cout << endl;
    }
    ~Heap()
    {
        delete[] arr;
    }
};

// This heapsort function sorts vector v in descending order.
void heapsort(vector<int> &v)
{
    int n = v.size();
    Heap h(n);
    for(int i=0; i<n; i++)
    {
        h.insert(v[i]);
    }
    for(int i=0; i<n; i++)
    {
        v[i] = h.getMax();
        cout << "After deleting " << h.getMax() <<" : ";

        h.deleteKey();
        h.print();
    }
}



#endif // MAX_HEAP_H_INCLUDED
