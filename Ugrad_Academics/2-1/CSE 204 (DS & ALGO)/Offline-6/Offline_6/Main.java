package Offline_6;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);


        int C,R,L,F ;

        //taking input for C,R,L and F..Besides checking the constraints for each
        while(true)
        {
            try {

                C = input.nextInt();

                if (C <= 1 && C > 1000) {
                    System.out.println("Invalid city number input! Try Again");
                    continue;
                }


                R = input.nextInt();

                if (R <= 1 && R > C * (C - 1) / 2) {
                    System.out.println("Invalid road number input! Try Again");
                    continue;
                }

                L = input.nextInt();

                if (L <= 1 && L > C) {
                    System.out.println("Invalid Location number input! Try Again");
                    continue;
                }

                F = input.nextInt();

                break;

            }catch (Exception e)
            {
                System.out.println("Only Integer input is Allowed.Try Again!");
                e.printStackTrace();
                continue;
            }



        }

       // System.out.println(C+" "+R+" "+L+" "+F);

        input.nextLine();  //for removing enter buffer

        Graph graph=new Graph(C,F); //Making the graph object

        //Taking input for edges of the graph..
        for(int i=0 ; i<R ;i++)
        {
            try {

                int C1 = input.nextInt();

                if(C1 < 0 && C1 >= C)
                {
                    System.out.println("Invalid input for C1.Try Again");
                    i--;
                    continue;
                }


                int C2 = input.nextInt();

                if(C2 < 0 && C2 >= C)
                {
                    System.out.println("Invalid input for C2.Try Again");
                    i--;
                    continue;
                }

                input.nextLine();  //for removing the enter buffer

                //As each roads are 2 way road thats why the graph is directed graph
                //For this reason, if there is a road(edge) between C1 and C2 ,there will alse be a
                //road (edge) between C2 and C1

                //System.out.println(C1 +" " +C2);
                graph.add_Nodes(C1,C2);
                graph.add_Nodes(C2,C1);



            }catch (Exception e)
            {
                System.out.println("Only Integer input is Allowed.Try Again!");
                e.printStackTrace();
                i--;
                continue;

            }
        }


        //taking inputs for location and pieces

        for(int i=0 ; i<L ;i++)
        {
            try {

                int Cx = input.nextInt();

                if(Cx < 0 && Cx >= C)
                {
                    System.out.println("Invalid input for Cx.Try Again");
                    i--;
                    continue;
                }


                int Px = input.nextInt();

                graph.set_Number_of_pieces_In_Location(Cx,Px); //setting the data in the graph


                input.nextLine(); //for removing the enter buffer

                //System.out.println(Cx+" "+Px);





            }catch (Exception e)
            {
                System.out.println("Only Integer input is Allowed.Try Again!");
                e.printStackTrace();
                i--;
                continue;

            }
        }

        //It is very important to observe that the friends will visit the city with the ascending order of their id
        //That's why we should traverse the graph according to the ascending order of there id
        //So to maintain this condition this "friends" array is created

        int[] friends =new int[F];




        for (int i=0;i<F;i++)
        {
            try {

                int Cy = input.nextInt();

                if(Cy < 0 && Cy >= C)
                {
                    System.out.println("Invalid input for Cy.Try Again");
                    i--;
                    continue;
                }


                int Fy = input.nextInt();

                if(Fy < 0 && Fy >= F)
                {
                    System.out.println("Invalid input for Fy.Try Again");
                    i--;
                    continue;
                }


                friends[Fy] = Cy;


                input.nextLine(); //for removing the enter buffer

                //System.out.println(Cy+" "+Fy);


            }catch (Exception e)
            {
                System.out.println("Only Integer input is Allowed.Try Again!");
                e.printStackTrace();
                i--;
                continue;

            }
        }

        //BFS Traversal
        for(int i=0;i<friends.length;i++)
        {
            //each friend will travers the graph independently with the ascending order of their id no
            graph.BFS_travarse(friends[i],i);
            //Reseting visiting flag of all the cities
            graph.Reset_Visiting_Info();
        }

        //DFS Traversal
//        for(int i=0;i<friends.length;i++)
//        {
//            //each friend will travers the graph independently with the ascending order of their id no
//            graph.DFS_travarse(friends[i],i);
//
//            //Reseting visiting flag of all the cities
//            graph.Reset_Visiting_Info();
//        }





        //Now this is the time for showing the outputs
        System.out.println();

        //Writing output into the file
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter("Output.txt"));

            if(graph.getTotal_Pieces_Exisits() == graph.getTotal_Collected_pieces())
            {
                bw.write("Mission Accomplished");
                bw.write("\n");
            }

            else
            {
                bw.write("Mission Impossible");
                bw.write("\n");
            }
            bw.write(graph.getTotal_Collected_pieces()+" out of "+graph.getTotal_Pieces_Exisits()+
                    " pieces are collected");
            bw.write("\n");


            int[] Friends = graph.getFriends();

            for (int i=0;i< Friends.length ;i++)
            {
                bw.write(i+" collecetd "+Friends[i]+" pieces");
                bw.write("\n");

            }

            bw.close();

        }catch(Exception e)
        {
            e.printStackTrace();
        }


        //Reading output from the file

        try
        {
            BufferedReader br = new BufferedReader(new FileReader("Output.txt"));
            String line="";

            while(true)
            {
                line = br.readLine();
                if(line == null)
                {
                    break;
                }
                System.out.println(line);
            }

            br.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }




    }
}
