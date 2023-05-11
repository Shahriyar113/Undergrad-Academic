package Offline_7;

public class Merge_Sort {

    int[] sorted_Array;

    void merge(int[] Arr,int left,int mid,int right)
    {
        int Left_subArray_size=mid - left +1;
        int right_subArray_size = right - mid;

        int[] Left_subArray = new int[Left_subArray_size];
        int[] Right_subArray = new int[right_subArray_size];

        //creating the left_subArray and Right_subArray from "Arr"
        for(int i=0;i<Left_subArray_size;i++)
        {
            Left_subArray[i]=Arr[left+i];
        }

        for(int i=0;i<right_subArray_size;i++)
        {
            Right_subArray[i]=Arr[mid+1+i];
        }

        //Now i have to merge these two arrays and also sort them parallely

        int Left_subArray_index=0;
        int right_subArray_index=0;

        int Main_Array_index=left;

        while(Left_subArray_index < Left_subArray_size && right_subArray_index < right_subArray_size)
        {
            if(Left_subArray[Left_subArray_index] < Right_subArray[right_subArray_index])
            {
                Arr[Main_Array_index] = Left_subArray[Left_subArray_index];
                Left_subArray_index++;
            }

            else
            {
                Arr[Main_Array_index] = Right_subArray[right_subArray_index];
                right_subArray_index++;
            }

            Main_Array_index++;
        }

        //left_subArray or right_subArray has remaining element which has to be push in the main Array "Arr"

        //That's why The remining elements in the left subArray or Right SubArray will be included by the two while loop below
        //Here only one loop between the two while loop below will execute


        //if Left_subArray has remaining elements,this while loop will execute
        while(Left_subArray_index < Left_subArray_size)
        {
            Arr[Main_Array_index]=Left_subArray[Left_subArray_index];
            Left_subArray_index++;
            Main_Array_index++;

        }

        //if Right_subArray has remaining elements,this while loop will execute
        while(Left_subArray_index < Left_subArray_size)
        {
            Arr[Main_Array_index]=Right_subArray[right_subArray_index];
            right_subArray_index++;
            Main_Array_index++;

        }




    }


    void merge_Sort(int[] Arr,int left,int right)
    {
        //if there is only one number or no number in array then the array is already sorted.
        sorted_Array=Arr;

        if(left >= right)
        {
            return;
        }

        int mid= (left+right)/2;

        //Dividing
        merge_Sort(Arr,left,mid);
        merge_Sort(Arr,mid+1,right);

        //Combining
        merge(Arr,left,mid,right);
    }

    int[] getSorted_Array()
    {
        return sorted_Array;
    }


}
