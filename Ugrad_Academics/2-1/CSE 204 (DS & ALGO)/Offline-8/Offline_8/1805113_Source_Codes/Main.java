package Offline_8;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.TreeMap;

public class Main {

    public static void main(String[] args) {

        int number_of_houses=0;

        Double[] X_coordinates=null;
        Double[] Y_coordinates=null;

        try
        {
            BufferedReader br = new BufferedReader(new FileReader("Input.txt"));
            String line="";

            number_of_houses=Integer.parseInt(br.readLine());

            X_coordinates =new Double[number_of_houses];
            Y_coordinates =new Double[number_of_houses];



            for (int i=0;i<number_of_houses;i++)
            {
                line = br.readLine();

                if(line == null)
                {
                    break;
                }

                String[] X_Y = line.split(" ");


                X_coordinates[i] = Double.parseDouble(X_Y[0]);
                Y_coordinates[i] = Double.parseDouble(X_Y[1]);


            }

            br.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }


        Point[] points=new Point[number_of_houses];

        for (int i=0;i<number_of_houses;i++)
        {
            points[i]=new Point(X_coordinates[i],Y_coordinates[i]);
        }

        Point[] original_points=new Point[number_of_houses]; //Unsorted Original Points

        for (int i=0;i<number_of_houses;i++)
        {
            original_points[i]=new Point(X_coordinates[i],Y_coordinates[i]);
        }





        //For 1st closest points
        Divide_And_Conquer divide_and_conquer=new Divide_And_Conquer();
        //Sorting the points with respect to X_Coordinates
        divide_and_conquer.Sorting_Points_BY_X(points);
        Double nearest_dis=divide_and_conquer.closest_point(points,0,points.length-1);

        Closest_Points closest_points=divide_and_conquer.getClosest_points();






        //for 2nd closest
        Divide_And_Conquer divide_and_conquer2=new Divide_And_Conquer();
        //Sorting the points with respect to X_Coordinates
        divide_and_conquer2.Sorting_Points_BY_X(points);

        divide_and_conquer2.closest_dis=nearest_dis; //important

        Double second_closest_dis=divide_and_conquer2.closest_point(points,0,points.length-1);

        Closest_Points second_closest_points=divide_and_conquer2.getClosest_points();

        int closest_index_1=0;
        int closest_index_2=0;

        for(int i=0;i<original_points.length;i++)
        {
            if(original_points[i].x == second_closest_points.p1.x && original_points[i].y == second_closest_points.p1.y )
            {
                closest_index_1=i;
                break;
            }
        }

        for(int i=0;i<original_points.length;i++)
        {
            if(original_points[i].x == second_closest_points.p2.x && original_points[i].y == second_closest_points.p2.y )
            {
                closest_index_2=i;
                break;
            }
        }


        if(closest_index_1 <= closest_index_2)
        {
            System.out.println("Second Closest Position: "+closest_index_1+" "+closest_index_2);
        }
        else
            System.out.println(closest_index_2+" "+closest_index_1);


        System.out.println();

        System.out.printf("Second Closest Distance: %.4f",second_closest_dis);
       // System.out.println(closest_points.p1);
        //System.out.println(closest_points.p2);


    }
}
