package Offline_7;

public class Quick_Sort {

    //l = first index of the array "Arr"
    //h= last index of thr array "Arr"

    int[] sorted_Array;

    int Partition(int[] Arr,int l,int h)
    {
        int p=l-1 ; // P is used to determine the suitable position for pivot in the array
        int pivot = Arr[h];
        int t; //swapping variable

        for(int i=l;i<h;i++)
        {
            if(Arr[i] < pivot)
            {
                p++;
                t=Arr[p];
                Arr[p] = Arr[i];
                Arr[i]=t;

            }
        }

        //After executing the loop "p+1"th index is the suitable position for pivot
        t=Arr[p+1];
        Arr[p+1] = Arr[h];
        Arr[h]=t;

        return p+1;
    }

    void quick_sort(int[] Arr,int l,int h)
    {
        //if there is only one number or no number in array then the array is already sorted.
        sorted_Array = Arr;

        if(l>=h)
        {
            return;
        }

        int pivot_index=Partition(Arr,l,h);

        quick_sort(Arr,l,pivot_index-1);
        quick_sort(Arr,pivot_index+1,h);

    }

    int[] getSorted_Array()
    {
        return sorted_Array;
    }


}
