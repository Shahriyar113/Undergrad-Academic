package Offline_8;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Divide_And_Conquer {


    public Closest_Points closest_points; // actually this "closest point" is the closest point for distance d
//    public Closest_Points closest_points_for_dl;
//    public Closest_Points closest_points_for_dr;
   public Closest_Points closest_points_for_strip;
    public boolean flag=true;
    public double So_far_min=Double.MAX_VALUE;


    public double closest_dis=Double.MIN_VALUE;

    Divide_And_Conquer()
    {
        this.closest_points = new Closest_Points();
       this.closest_points_for_strip=new Closest_Points();

    }

    public Closest_Points getClosest_points()
    {
        return closest_points;
    }

    double dist(Point p1,Point p2)

    {

        return Math.sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    }



    double minimum_between_three_points(Point p1,Point p2,Point p3)
    {

        double[] min_arr = new double[3];

        min_arr[0]=dist(p1,p2);
        min_arr[1]=dist(p2,p3);
        min_arr[2]=dist(p1,p3);

        Arrays.sort(min_arr);
        if(min_arr[0] == closest_dis)
        {
            //upgrading 2nd closest points
            if(min_arr[1] == dist(p1, p2))
            {
                closest_points.p1=p1;
                closest_points.p2=p2;

            }
            else if(min_arr[1] == dist(p2, p3))
            {
                closest_points.p1=p2;
                closest_points.p2=p3;
            }

            else if(min_arr[1] == dist(p1, p3))
            {
                closest_points.p1=p1;
                closest_points.p2=p3;
            }

            return min_arr[1];
        }
        //upgrading 2nd closest points
        if(min_arr[0] == dist(p1, p2))
        {
            closest_points.p1=p1;
            closest_points.p2=p2;

        }
        else if(min_arr[0] == dist(p2, p3))
        {
            closest_points.p1=p2;
            closest_points.p2=p3;

        }

        else if(min_arr[0] == dist(p1, p3))
        {
            closest_points.p1=p1;
            closest_points.p2=p3;


        }



        return min_arr[0];

    }



void Sorting_Points_BY_X(Point[] points)
{
    List<Point> point_list= Arrays.asList(points);
    Point_Sorting_WRT_X obj=new Point_Sorting_WRT_X();
    Collections.sort(point_list,obj);

    point_list.toArray(points);


}

    void Sorting_Points_BY_Y(Point[] points)
    {
        List<Point> point_list= Arrays.asList(points);

        Point_Sorting_WRT_Y obj=new Point_Sorting_WRT_Y();
        Collections.sort(point_list,obj);

        point_list.toArray(points);


    }

    double stripClosest(Point strip[], int size, double d)
    {


        flag=false;
        double min = d; // Initialize the minimum distance as d

       // sorting the points in strip wrt Y
        //System.out.println("strip_size: "+size);
        Sorting_Points_BY_Y(strip);
        //System.out.println("strip_size: "+size);



        // Pick all points one by one and try the next points till the difference
        // between y coordinates is smaller than d.
        // This is a proven fact that this loop runs at most 6 times
        for (int i = 0; i < size; i++) {

            for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++) {
                if (dist(strip[i], strip[j]) < min && dist(strip[i], strip[j]) != closest_dis) {
                    min = dist(strip[i], strip[j]);
                    closest_points_for_strip.set(strip[i], strip[j]);
//                    System.out.println("Dis: "+min);
//                    System.out.println(closest_points_for_strip.p1);
//                    System.out.println(closest_points_for_strip.p2);
//                    System.out.println("IN Strip");
//
//                    System.out.println();
                }
            }
        }


        return min;
    }


    double closest_point(Point[] points,int low,int high) {

        Closest_Points closest_points_for_dl = new Closest_Points();
        Closest_Points closest_points_for_dr = new Closest_Points();

        if (low >= high) // for 1 point
        {
            flag=true;
            return Double.MAX_VALUE;
        }

        if (high - low == 1) // for 2 point
        {
            flag=true;

            closest_points.set(points[low],points[high]);

            return dist(points[low], points[high]);
        }

        if (high - low == 2) {  // for 3 points
            flag=true;
            return minimum_between_three_points(points[low], points[low + 1], points[high]);
        }

        int mid = (low + high) / 2;
        Point midPoint = points[mid];
        double dl = closest_point(points, low, mid);

        closest_points_for_dl.set(closest_points.p1, closest_points.p2);

        if(closest_points_for_strip.p1 != null && closest_points_for_strip !=null)
        {
            closest_points_for_dl.set(closest_points_for_strip.p1,closest_points_for_strip.p2);

            closest_points_for_strip.p1=null;
            closest_points_for_strip.p2=null;
        }


        double dr = closest_point(points, mid + 1, high);


        closest_points_for_dr.set(closest_points.p1, closest_points.p2);

        if(closest_points_for_strip.p1 != null && closest_points_for_strip.p2 !=null)
        {
            closest_points_for_dr.set(closest_points_for_strip.p1,closest_points_for_strip.p2);
            closest_points_for_strip.p1=null;
            closest_points_for_strip.p2=null;
        }


        // Find the smaller of two distances
        double d = Math.min(dl, dr);

//        System.out.println("Dis: " + d);
//        System.out.println("Dl: " + dl);
//        System.out.println("Dr: " + dr);

        if(dl == closest_dis || dr == closest_dis) {
            //System.out.println("Ignored");
            if (dl == closest_dis) {
                d = dr;
                closest_points.set(closest_points_for_dr.p1, closest_points_for_dr.p2);
            }

            if (dr == closest_dis) {
                d = dl;
                closest_points.set(closest_points_for_dl.p1, closest_points_for_dl.p2);
            }
        }
        else


        {
            if (dl <= dr) {
                closest_points.set(closest_points_for_dl.p1, closest_points_for_dl.p2);
//                System.out.println(closest_points.p1);
//                System.out.println(closest_points.p2);
//                System.out.println("IN dl");
//                System.out.println();

            }

            if (dr < dl) {
                closest_points.set(closest_points_for_dr.p1, closest_points_for_dr.p2);
//                System.out.println(closest_points.p1);
//                System.out.println(closest_points.p2);
//                System.out.println("IN dr");
//
//                System.out.println();
            }

        }



        if(dl==closest_dis && dr==closest_dis)
        {
            d=d+Double.MIN_VALUE;
        }


        int length_of_points= high-low+1;

        ArrayList<Point> strip_list=new ArrayList<>();
        //int j = 0;
        for (int i = low; i <= high; i++) {
            if (Math.abs(points[i].x - midPoint.x) < d) {
                strip_list.add(points[i]);

            }
        }

        Point[] strip=new Point[strip_list.size()];
        strip_list.toArray(strip);
        //System.out.println("strip_length: "+strip.length);



        double minimum_in_strip = stripClosest(strip, strip.length, d);

        if(d <= minimum_in_strip)
        {
            So_far_min=d;

            return d;
        }

        else
        {
            closest_points.set(closest_points_for_strip.p1,closest_points_for_strip.p2);
            So_far_min=minimum_in_strip;
            return minimum_in_strip;
        }

    }



}
