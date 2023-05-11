package Offline_7;

import java.util.Random;
import java.util.Scanner;

public class Main {


    public static void main(String[] args) {


//        int[] Arr1 = {8,8,5,7,9,4,6,4,7,6,9,7,8,7};
//        Quick_Sort q_sort = new Quick_Sort();
//        Merge_Sort m_sort=new Merge_Sort();
//
//
//        q_sort.quick_sort(Arr1,0,Arr1.length-1);
//
//        System.out.print("After Quick Sort: ");
//        for (int i : Arr1)
//        {
//            System.out.print(i+" ");
//        }
//        System.out.println();
//
//        int[] Arr2 = {8,8,5,7,9,4,6,4,7,6,9,7,8,7};
//
//        m_sort.merge_Sort(Arr2,0,Arr2.length-1);
//
//        System.out.print("After Merge Sort: ");
//
//        for (int i : Arr2)
//        {
//            System.out.print(i+" ");
//        }
//        System.out.println();
//
        Scanner input=new Scanner(System.in);

        System.out.print("Enter the length of the array: ");
        int n=input.nextInt(); //n = number of integers in the array
        System.out.println();
        input.nextLine(); // avoiding the enter buffer

        String order ="";

        int[] Arr=new int[n];

        while(true)
        {
            System.out.print("Enter the order: A or D or R: ");
            order = input.next();

            if(order.equalsIgnoreCase("A") || order.equalsIgnoreCase("D") ||
               order.equalsIgnoreCase("R"))
            {
                break;
            }
            else
            {
                System.out.println("Wrong input for order.Try Again");
                System.out.println();
            }
        }


        Random random=new Random();

        //generating random ordered array of n integers
        if(order.equalsIgnoreCase("R"))
        {


            for (int i = 0; i < n; i++) {
                Arr[i] = random.nextInt(n);
            }


        }


        //generating Ascending ordered array of n integers
        if(order.equalsIgnoreCase("A"))

        {

            Arr[0]= 10 + random.nextInt(n);

            for(int i=1;i<n;i++)
            {
                Arr[i] = Arr[i-1]+random.nextInt(10);
            }


        }


        //generating Descending ordered array of n integers
        if(order.equalsIgnoreCase("D"))

        {

            Arr[0]= n*3 - random.nextInt(n);

            for(int i=1;i<n;i++)
            {
                Arr[i] = Arr[i-1] - random.nextInt(5);
            }

        }

        //for Quick_sort ,original copy "Arr" will be used
        //for Merge_Sort,Identical copy of Arr "Array_copy" will be used

        //Creating an identical copy of "Arr"
        int[] Array_copy = new int[n];

        for(int i=0;i<n;i++)
        {
            Array_copy[i]=Arr[i];
        }

        System.out.println();
        System.out.println("Before Sorting:");
        System.out.println("---------------");

        for(int x:Arr)
        {
            System.out.print(x+" ");
        }
        System.out.println();
        System.out.println();

        Quick_Sort q_sort = new Quick_Sort();
        Merge_Sort m_sort=new Merge_Sort();

        long quick_sort_start = System.currentTimeMillis();

        //Quick_sorting
        q_sort.quick_sort(Arr,0,Arr.length-1);

        long quick_sort_end = System.currentTimeMillis();

        long quick_sort_time=quick_sort_end-quick_sort_start;

      System.out.println("After Quick sorting:");
        System.out.println("---------------------");
        for(int x:Arr)
        {
            System.out.print(x+" ");
        }
        System.out.println();

        System.out.println("Quick Sort takes: "+quick_sort_time+" ms for "+n+" integers");
        System.out.println();



        //Merge Sorting

        long Merge_sort_start = System.currentTimeMillis();

        m_sort.merge_Sort(Array_copy,0,Array_copy.length-1);

        long Merge_sort_end = System.currentTimeMillis();

        long Merge_sort_time=Merge_sort_end-Merge_sort_start;

        System.out.println("After Merge sorting:");
        System.out.println("----------------------");

        for(int x:Array_copy)
        {
            System.out.print(x+" ");
        }
        System.out.println();

        System.out.println("Merge Sort takes: "+Merge_sort_time+" ms for "+n+" integers");
        System.out.println();





    }
}
