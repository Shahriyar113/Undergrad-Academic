#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


static unsigned long int g_seed = 1;
inline int random()
{
 g_seed = (214013 * g_seed + 2531011);
 return (g_seed >> 16) & 0x7FFF;
}


double getMinimum(double x,double y,double z)
{
    double min = x;
    if(y < min)
        min = y;
    if(z < min)
        min = z;

    return min;        

}


double getMaximum(double x,double y,double z)
{
    double max = x;
    if(y > max)
        max = y;
    if(z > max)
        max = z;

    return max;        

}




class Point{
    public:
        double x;
        double y;
        double z;
        double w; //for modeling transformation w=1

        Point()
        {
            x=0;y=0;z=0;
            w=1;
        }

        Point(double a,double b,double c)
        {
            x=a;
            y=b;
            z=c;
            w=1;
        }

         Point(double a,double b,double c,double scale_factor)
        {
            x=a;
            y=b;
            z=c;
            w=scale_factor;
        }

        double magnitude()
        {
            return sqrt(x*x+y*y+z*z);
        }


        void normalize()
        {
            double length = magnitude();
            x = x/length;
            y = y/length;
            z = z/length;

        }

        void scaledown()
        {
            x = x/w;
            y = y/w;
            z = z/w;
            
        }

        Point operator+(Point p2)
        {
            double x_coordinate = x + p2.x; 
            double y_coordinate = y + p2.y; 
            double z_coordinate = z + p2.z;

            return Point(x_coordinate,y_coordinate,z_coordinate);

        }

         Point operator-(Point p2)
        {
            double x_coordinate = x - p2.x; 
            double y_coordinate = y - p2.y; 
            double z_coordinate = z - p2.z;

            return Point(x_coordinate,y_coordinate,z_coordinate);

        }

        //scaler prpduct of a vector
        Point operator*(double d)
        {
            double x_coordinate = d * x; 
            double y_coordinate = d * y; 
            double z_coordinate = d * z;

            return Point(x_coordinate,y_coordinate,z_coordinate);
        }

        
        bool operator!=(Point point)
        {
            return !(x == point.x && y == point.y && z == point.z);
        }


        friend istream& operator>>(istream &in, Point &point)
        {
            in >> point.x >> point.y >> point.z;
            return in;
        }

        void print()
        {
            cout << "(" << x << "," << y << "," << z << ")" << endl;
        }

};


class Triangle{
    public:
        Point p1;
        Point p2;
        Point p3;

        int r,g,b ; //for coloring

        Triangle()
        {
            r = random();
            g = random();
            b = random();
        }

        Triangle(Point p1,Point p2,Point p3)
        {
            this->p1 = p1;
            this->p2 = p2;
            this->p3 = p3;

            
            r = random();
            g = random();
            b = random();

        }

        double getMin_x()
        {
            return getMinimum(p1.x,p2.x,p3.x);
        }

        double getMax_x()
        {     
            return getMaximum(p1.x,p2.x,p3.x);
        }

        double getMin_y()
        {
            return getMinimum(p1.y,p2.y,p3.y);
        }  
        
        double getMax_y()
        {
            return getMaximum(p1.y,p2.y,p3.y);
        }

        double getMin_z()
        {
            return getMinimum(p1.z,p2.z,p3.z);
        }  
        
        double getMax_z()
        {
            return getMaximum(p1.z,p2.z,p3.z);
        }

        Point get_the_point_of_max_y()
        {
            Point point_with_max_y = p1;
            double max = p1.y;

            if(p2.y > max)
            {
                max = p2.y;
                point_with_max_y = p2;
            } 
            if(p3.y > max)
            {
                max = p3.y;
                point_with_max_y = p3;
            } 
            return point_with_max_y;
        }


        Point get_the_point_of_min_y()
        {
            Point point_with_min_y = p1;
            double min = p1.y;

            if(p2.y < min)
            {
                min = p2.y;
                point_with_min_y = p2;
            } 
            if(p3.y < min)
            {
                min = p3.y;
                point_with_min_y = p3;
            } 
            return point_with_min_y;
        }

        Point get_the_other_point()
        {
            if(p1 !=  get_the_point_of_max_y() && p1 != get_the_point_of_min_y())
                return p1;
            if(p2 !=  get_the_point_of_max_y() && p2 != get_the_point_of_min_y())
                return p2;
            return p3;
        }


        
        
};

class Matrix{
    public:
        vector<vector<double> > matrix_elements;
        int dimension;
   
        //matrix size is always 4x4 (because homogenous coordinate system is used for 3D graphics)
        Matrix()
        {
            matrix_elements.resize(4,vector<double>(4,0));     
            dimension = 4; 
        }
        

        void create_identity_matrix()
        {
            for(int i=0;i<dimension;i++)
            {
                for(int j=0;j<dimension;j++)
                {
                    if(i==j)
                    {
                        matrix_elements[i][j] = 1;
                    }
                }
            }
        }


        void create_translate_matrix(double tx,double ty,double tz)
        {
            create_identity_matrix();
            matrix_elements[0][3] = tx;
            matrix_elements[1][3] = ty;
            matrix_elements[2][3] = tz;

        }

        void create_scale_matrix(double sx,double sy,double sz)
        {
            create_identity_matrix();
            matrix_elements[0][0] = sx;
            matrix_elements[1][1] = sy;
            matrix_elements[2][2] = sz;

        }


        void create_rotation_matrix(Point c1,Point c2,Point c3)
        {
            matrix_elements[0][0] = c1.x;
            matrix_elements[1][0] = c1.y;
            matrix_elements[2][0] = c1.z;

            matrix_elements[0][1] = c2.x;
            matrix_elements[1][1] = c2.y;
            matrix_elements[2][1] = c2.z;

            matrix_elements[0][2] = c3.x;
            matrix_elements[1][2] = c3.y;
            matrix_elements[2][2] = c3.z;

            matrix_elements[3][3] = 1;


        }



        //overloading "*" operator for "matrix-matrix" multiplication

        Matrix operator*(Matrix mat2)
        {
            Matrix resultant_matrix;

            for (int i=0;i<dimension;i++)
            {
                for (int j=0;j<dimension;j++)
                {
                    for (int k=0;k<dimension;k++)
                    {
                         resultant_matrix.matrix_elements[i][j] += matrix_elements[i][k]*mat2.matrix_elements[k][j];
                    }
                }
            }
            return resultant_matrix;

        }


        //overloading "*" operator for Matrix-Point Multiplication


        Point operator*(Point point)
        {
            double old_point[4];
            old_point[0] = point.x;
            old_point[1] = point.y;
            old_point[2] = point.z;
            old_point[3] = point.w;


            double new_point[4]={0,0,0,0};
           // this->print();
           // point.print();


            for (int i=0;i<dimension;i++)
            {
                //double sum =0;
                for (int j=0;j<dimension;j++)
                {
                    new_point[i] = new_point[i] + matrix_elements[i][j] * old_point[j];
                   // printf("(%lf * %lf) +",matrix_elements[i][j],old_point[j]);
                }
               // printf("=%lf\n",new_point[i]);
            }
            
            Point Resultant_point(new_point[0],new_point[1],new_point[2],new_point[3]);
            Resultant_point.scaledown();
            //Resultant_point.print();

            return Resultant_point;

        }

        void print()
        {
            for(int i=0;i<dimension;i++)
            {
                for(int j=0;j<dimension;j++)
                {
                    printf("%lf ",matrix_elements[i][j]);
                }
                printf("\n");
            }

        }





};