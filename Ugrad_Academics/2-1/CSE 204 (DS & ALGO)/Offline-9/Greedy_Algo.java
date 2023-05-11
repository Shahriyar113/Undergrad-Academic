package Offline_9;

import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;

public class Greedy_Algo {

    public static int Calculate_Minimum_Cost(int N,int K,Integer[] price_of_plants)
    {
        int[] Friends = new int[K]; // this array will store which friend buys how many times

        if(N <= K)
        {
            //Here the greedy approach is that each friend will buy at most one times so that the price can not
            //exceed the original price..hence the total cost will minimize

            int minimum_cost=0;

            for(int i=0;i<N;i++)
            {
                minimum_cost=minimum_cost+price_of_plants[i];
            }
            return minimum_cost;
        }
        else // N > K
        {
            //It is sure that at least one of friends have to buy more than once.So some plants will be
            //purchased higher than the originial price

            //So here the greedy choice to minimize the cost is that Friends will not suppose to allow to
            //increase the price of expensive plants.As they have to buy all the plants ,So,they will sequentially
            //buy the plants one by one starting from the expensive price...That's why they can buy the
            //expensive plants at original rate (As original as possible) and the cheaper plants will be
            //purchased at slight exceeding rate..and thus the cost will minimize

            int minimum_cost=0;
            int p=0; //index for friends

            for(int i=0;i<N;i++)
            {
                minimum_cost = minimum_cost + price_of_plants[i]*(Friends[p]+1);

                Friends[p] = Friends[p]+1 ; //Updating which friends buying how mny times
                p++;
                if(p == K)
                {
                    // p == k means a round of buying completed
                    //that means every friend's buying cycle is complete..so again the cycle will start again
                    p=0;

                }

            }
            return minimum_cost;



        }


    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        //taking inputs
        int N = input.nextInt(); //total number of plants
        int K =input.nextInt(); //total number of friends

        input.nextLine();

        Integer[] price_of_plants = new Integer[N]; //store the price of each plants;

        for(int i=0;i<N;i++)
        {
            price_of_plants[i]=input.nextInt();
        }

        //There are sometimes some preprocessing tasks have to do before greedy choice..that's why
        //the "price_of_plants" is sorting Descending order

        Arrays.sort(price_of_plants, Collections.reverseOrder()); //preprocessing

        System.out.println("Minimum Cost: "+Calculate_Minimum_Cost(N,K,price_of_plants));


    }
}
