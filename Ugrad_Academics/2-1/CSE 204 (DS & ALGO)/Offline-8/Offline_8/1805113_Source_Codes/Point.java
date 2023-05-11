package Offline_8;

import java.util.Comparator;

public class Point {
    public double x;
    public double y;

    Point(double x,double y)
    {
        this.x=x;
        this.y=y;
    }

    @Override
    public String toString() {
        return "("+x+","+y+")";
    }
}

class Point_Sorting_WRT_X implements Comparator<Point>
{
    @Override
    public int compare(Point p1, Point p2) {
        if( p1.x-p2.x < 0)
        {
            return -1;
        }
        else if(p1.x-p2.x > 0)
        {
            return 1;
        }
        else
            return 0;
    }


}

class Point_Sorting_WRT_Y implements Comparator<Point>
{
    @Override
    public int compare(Point p1, Point p2) {
        if( p1.y-p2.y < 0)
        {
            return -1;
        }
        else if(p1.y-p2.y > 0)
        {
            return 1;
        }
        else
            return 0;
    }
}
