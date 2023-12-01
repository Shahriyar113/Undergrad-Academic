#include <iostream>
#include <fstream>
#include "NecLib.h"
#include <stack>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <vector>
#include "bitmap_image.hpp"
using namespace std;


#define M_PI 2.0*acos(0.0)


Matrix current_transformation_matrix;


double dot_product(Point p1,Point p2)
{
    return (p1.x*p2.x + p1.y*p2.y + p1.z*p2.z);
}

Point cross_product(Point p1,Point p2)
{
    double x = p1.y*p2.z - p1.z*p2.y;
    double y = -(p1.x*p2.z - p1.z*p2.x);
    double z = p1.x*p2.y - p1.y*p2.x;

    return Point(x,y,z);
}

double get_z_value(Triangle triangle,double x, double y)
{
    //building the equation of the triamgular plane
    //the point normal form of this triangle is {p1,normal_vector}
    Point normal_vector = cross_product(triangle.p2-triangle.p1,triangle.p3-triangle.p1);
    double d = -(normal_vector.x*triangle.p1.x + normal_vector.y*triangle.p1.y + normal_vector.z*triangle.p1.z );
    double z_value = (-d-normal_vector.x*x-normal_vector.y*y)/normal_vector.z;
    return z_value;

}


Point Rodrigues_R(Point X,Point a ,double theta) //theta will be given as "degree" unit as input 
{
    theta = (M_PI*theta)/180.0;

    double temp = (1-cos(theta))*dot_product(a,X);
    Point cross_product_result = cross_product(a,X);
  
    Point result = X*cos(theta) + a*temp + cross_product_result*sin(theta);
    return result;

}


Matrix generate_view_transform(Point eye,Point look,Point up)
{
    Point l = look - eye;
    l.normalize();
    Point r = cross_product(l,up);
    r.normalize();
    Point u = cross_product(r,l);


    Matrix T;
    T.create_translate_matrix(-eye.x,-eye.y,-eye.z);
    //T.print();


    Matrix R;

    //printf("\n");
    
    R.matrix_elements[0][0] = r.x;
    R.matrix_elements[0][1] = r.y;
    R.matrix_elements[0][2] = r.z;

    R.matrix_elements[1][0] = u.x;
    R.matrix_elements[1][1] = u.y;
    R.matrix_elements[1][2] = u.z;

    R.matrix_elements[2][0] = -l.x;
    R.matrix_elements[2][1] = -l.y;
    R.matrix_elements[2][2] = -l.z;

    R.matrix_elements[3][3] = 1;

    //R.print();
    //printf("\n");


    Matrix view_transformation = R * T;

    return view_transformation;




}


Matrix generate_Projection_transformation(double fovy,double aspectRatio,double near,double far)
{
    double fovx = fovy * aspectRatio;
    double t = near * tan(((fovy/2)*M_PI)/180.0);
    double r = near * tan(((fovx/2)*M_PI)/180.0);

    Matrix Projection_matrix;
    Projection_matrix.matrix_elements[0][0] = near/r;
    Projection_matrix.matrix_elements[1][1] = near/t;
    Projection_matrix.matrix_elements[2][2] = -(far+near)/(far-near);
    Projection_matrix.matrix_elements[2][3] = -(2*far*near)/(far-near);
    Projection_matrix.matrix_elements[3][2] = -1;

    return Projection_matrix;




} 



int main()
{
    Point eye,look,up;
    double fovy,aspectRatio,near,far;
    int total_triangle_count=0;

    ifstream f_in("scene.txt");
    //ifstream f_in("C:/Users/ASUS/Desktop/Test Cases (Updated 2 Aug)/Test Cases (Updated 2 Aug)/3/scene.txt");

    ofstream f_out("stage1.txt");

    //reading eye,look and up vector co-ordinates from file
    f_in >> eye.x >> eye.y >> eye.z;
    f_in >> look.x >> look.y >> look.z;
    f_in >> up.x >> up.y >> up.z;

    //reading fovy,aspectRatio,near,far values from file
    f_in >> fovy >> aspectRatio >> near >> far;

    

    //starting Stage:1 ==> "Modeling Transformation"

    //creating empty stack for transformation matrix
    stack<Matrix> Stack;

    //ctreating identity matrix "I"
    Matrix I;
    I.create_identity_matrix();
    current_transformation_matrix = I;

    //initially the identity matrix will be pushed onto the stack
    Stack.push(I);


    while (true)
    {
        string command;

        f_in >> command;
       // cout << command << endl;

        if(command == "triangle")
        {
            Point p1,p2,p3;
            //reading the points of triangle from the file
            f_in >> p1.x >> p1.y >> p1.z;
            f_in >> p2.x >> p2.y >> p2.z;
            f_in >> p3.x >> p3.y >> p3.z;

            Point new_p1 = current_transformation_matrix * p1;
            Point new_p2 = current_transformation_matrix * p2;
            Point new_p3 = current_transformation_matrix * p3;


            //writing the transformed points of the triangle on the "stage1.txt" file

            //due to the below line all the double values will be written on file at 6th precision
            f_out << std::fixed << std::setprecision(7); 

            f_out << new_p1.x << " " << new_p1.y << " " << new_p1.z << endl; 
            f_out << new_p2.x << " " << new_p2.y << " " << new_p2.z << endl; 
            f_out << new_p3.x << " " << new_p3.y << " " << new_p3.z << endl; 
            f_out << endl; 


            total_triangle_count++;



        }

        else if (command == "translate")
        {
            //reading tx,ty and tz
            double tx,ty,tz;
            f_in >> tx >> ty >> tz;

            //building translation matrix
            Matrix translation_matrix;
            translation_matrix.create_translate_matrix(tx,ty,tz);
            current_transformation_matrix = current_transformation_matrix * translation_matrix;

        }

        else if (command == "scale")
        {
            //reading tx,ty and tz
            double sx,sy,sz;
            f_in >> sx >> sy >> sz;

            //building translation matrix
            Matrix scale_matrix;
            scale_matrix.create_scale_matrix(sx,sy,sz);
            current_transformation_matrix = current_transformation_matrix * scale_matrix;
        }

        else if (command == "rotate")
        {
            double angle;
            Point a;
            f_in >> angle >> a.x >> a.y >> a.z;

            Point i(1,0,0);
            Point j(0,1,0);
            Point k(0,0,1);

            a.normalize();
            Point c1 = Rodrigues_R(i,a,angle);
            Point c2 = Rodrigues_R(j,a,angle);
            Point c3 = Rodrigues_R(k,a,angle);

            Matrix rotation_matrix;
            rotation_matrix.create_rotation_matrix(c1,c2,c3);
            current_transformation_matrix = current_transformation_matrix * rotation_matrix;


        }

        else if (command == "push")
        {
            Stack.push(current_transformation_matrix);
        }

        else if (command == "pop")
        {
           if(Stack.empty())
           {
            cout << "Error! Stack is empty" << endl;
            return 0;
           } 

           current_transformation_matrix = Stack.top();
           Stack.pop();
        }

        else if(command == "end")
        {
            break;
        }
        else
        {
            cout<<"Invalid Command"<<endl;
            break;
        }
        


    }

    f_in.close();
    f_out.close();


    //starting Stage:2 ==> "View Transformation"


    f_in.open("stage1.txt");
    f_out.open("stage2.txt");

    

    Matrix view_transformation_matrix = generate_view_transform(eye,look,up);
    
    for(int i=0;i<total_triangle_count;i++)
    {
        Point p1,p2,p3;
        f_in >> p1.x >> p1.y >> p1.z;
        f_in >> p2.x >> p2.y >> p2.z;
        f_in >> p3.x >> p3.y >> p3.z;

        Point new_p1 = view_transformation_matrix*p1;
        Point new_p2 = view_transformation_matrix*p2;
        Point new_p3 = view_transformation_matrix*p3;

        //due to the below line all the double values will be written on file at 6th precision
        f_out << std::fixed << std::setprecision(7); 

        f_out << new_p1.x << " " << new_p1.y << " " << new_p1.z << endl; 
        f_out << new_p2.x << " " << new_p2.y << " " << new_p2.z << endl; 
        f_out << new_p3.x << " " << new_p3.y << " " << new_p3.z << endl; 
        f_out << endl; 
    }

    f_in.close();
    f_out.close();

    //starting Stage:3 ==> "Projection Transformation"
    
    f_in.open("stage2.txt");
    f_out.open("stage3.txt");

    Matrix Projection_Transformation_matrix = generate_Projection_transformation(fovy,aspectRatio,near,far);
    
    for(int i=0;i<total_triangle_count;i++)
    {
        Point p1,p2,p3;
        f_in >> p1.x >> p1.y >> p1.z;
        f_in >> p2.x >> p2.y >> p2.z;
        f_in >> p3.x >> p3.y >> p3.z;

        Point new_p1 = Projection_Transformation_matrix*p1;
        Point new_p2 = Projection_Transformation_matrix*p2;
        Point new_p3 = Projection_Transformation_matrix*p3;

        //due to the below line all the double values will be written on file at 6th precision
        f_out << std::fixed << std::setprecision(7); 


        f_out << new_p1.x << " " << new_p1.y << " " << new_p1.z << endl; 
        f_out << new_p2.x << " " << new_p2.y << " " << new_p2.z << endl; 
        f_out << new_p3.x << " " << new_p3.y << " " << new_p3.z << endl; 
        f_out << endl; 
    }

    f_in.close();
    f_out.close();


    //stage-4 : Z-buffer algorithm

    f_in.open("config.txt");
    //f_in.open("C:/Users/ASUS/Desktop/Test Cases (Updated 2 Aug)/Test Cases (Updated 2 Aug)/3/config.txt");

    
    int Screen_Width,Screen_Height;
    double right_limit_x = 1;
    double left_limit_x = -1;
    double top_limit_y = 1;
    double bottom_limit_y = -1;
    double z_max = 1; //not sure
    double z_min = -1;

    f_in >> Screen_Width >> Screen_Height;
    f_in.close();

    double dx = (right_limit_x - left_limit_x)/ Screen_Width;
    double dy = (top_limit_y - bottom_limit_y) / Screen_Height;
    double Top_Y = top_limit_y - dy/2;
    double Bottom_Y = -Top_Y;
    double Left_X = left_limit_x + dx/2;
    double Right_X = -Left_X;

    // creating z-buffer (a 2D array)
    vector<vector<double> > z_buffer;
    z_buffer.resize(Screen_Height,vector<double>(Screen_Width,z_max)); 
    

    // initializing image as all black cells
    //this "frame_buffer" is the required image file
    bitmap_image frame_buffer(Screen_Width, Screen_Height);
    for(int i=0;i<Screen_Width;i++)
    {
        for(int j=0;j<Screen_Height;j++)
        {
            frame_buffer.set_pixel(i,j,0,0,0);
        }
    }

    
    f_in.open("stage3.txt");
    f_out.open("z_buffer.txt");



    for (int t=0;t<total_triangle_count;t++)
    {
        Point p1,p2,p3;
        //reading the co_ordinates  of the triangle
        f_in >> p1.x >> p1.y >> p1.z;
        f_in >> p2.x >> p2.y >> p2.z;
        f_in >> p3.x >> p3.y >> p3.z;

        Triangle triangle(p1,p2,p3);

        //doing clippping along y axis

        double Max_y = min(Top_Y,triangle.getMax_y());
        double Min_y = max(Bottom_Y,triangle.getMin_y());

        //clippping along y axis done


        int starting_row_no = (int)floor((top_limit_y - Max_y)/dy);
        int ending_row_no = (int)floor((top_limit_y - Min_y)/dy);

        double Y_start =  Top_Y - starting_row_no*dy;
        double Y_end =    Top_Y - ending_row_no*dy;

        for (int row_no = starting_row_no ; row_no <= ending_row_no; row_no++ )
        {
            //a scan line is horizontal line(e.g y=0.5)
            double current_scanline = Top_Y - row_no*dy;

            // p1 = triangle.get_the_point_of_max_y();
            // p2 = triangle.get_the_point_of_min_y();
            // p3 = triangle.get_the_other_point();


            //for p1p2
            double infinity=5; //'5' means infinitiy as highest x_value is 1;
            double x1=infinity;
            double x2=infinity;
            double x3=infinity; 

            //here the x co-ordinate of the intersection point for the intersection of p1p2 and current_scanline = x1
            //here the x co-ordinate of the intersection point for the intersection of p2p3 and current_scanline = x2
            //here the x co-ordinate of the intersection point for the intersection of p3p1 and current_scanline = x3

            // printf("row_no %d\n\n",row_no);


            if(p1.y - p2.y != 0.0)
                {
                    x1 = ((current_scanline-p1.y)/(p1.y-p2.y))*(p1.x-p2.x)+p1.x;
                    
                    // printf("In p1p2\n");

                    // printf("Curr Sca: %lf\n",current_scanline);
                    // printf("p1.x: %lf\n",p1.x);
                    // printf("p1.y : %lf\n",p1.y);

                    // printf("p2.x: %lf\n",p2.x);
                    // printf("p2.y: %lf\n",p2.y);

                    // printf("p3.x: %lf\n",p3.x);
                    // printf("p3.y: %lf\n",p3.y);
                    //  printf("x1: %lf\n",x1);



                    
                    double min_x_p1p2 = min(p1.x,p2.x);
                    double max_x_p1p2 = max(p1.x,p2.x);

                    //  printf("min_x_p1p2: %lf\n",min_x_p1p2);
                    // printf("max_x_p1p2: %lf\n",max_x_p1p2);



                    if(x1 < min_x_p1p2 || x1 > max_x_p1p2)
                        x1=infinity;

                    // printf("x1: %lf\n",x1);

                }
            //for p2p3
            if(p2.y - p3.y != 0.0)
            {
                x2 = ((current_scanline-p2.y)/(p2.y-p3.y))*(p2.x-p3.x)+p2.x;


                // printf("In p2p3\n");

                //   printf("Curr Sca: %lf\n",current_scanline);
                //     printf("p1.x: %lf\n",p1.x);
                //     printf("p1.y : %lf\n",p1.y);

                //     printf("p2.x: %lf\n",p2.x);
                //     printf("p2.y: %lf\n",p2.y);

                //     printf("p3.x: %lf\n",p3.x);
                //     printf("p3.y: %lf\n",p3.y);
                //      printf("x2: %lf\n",x2);



                double min_x_p2p3 = min(p2.x,p3.x);
                double max_x_p2p3 = max(p2.x,p3.x);
                    
                    // printf("min_x_p2p3: %lf\n",min_x_p2p3);
                    // printf("max_x_p2p3: %lf\n",max_x_p2p3);



                if(x2 < min_x_p2p3 || x2 > max_x_p2p3)
                    x2=infinity;

                    // printf("x2: %lf\n",x2);

            }
            //for p1p3
            if(p1.y - p3.y != 0.0)
            {
                x3 = ((current_scanline-p1.y)/(p1.y-p3.y))*(p1.x-p3.x)+p1.x;

                // printf("In p1p3\n");

                //  printf("Curr Sca: %lf\n",current_scanline);
                //     printf("p1.x: %lf\n",p1.x);
                //     printf("p1.y : %lf\n",p1.y);

                //     printf("p2.x: %lf\n",p2.x);
                //     printf("p2.y: %lf\n",p2.y);

                //     printf("p3.x: %lf\n",p3.x);
                //     printf("p3.y: %lf\n",p3.y);
                //     printf("x3: %lf\n",x3);



                
                double min_x_p1p3 = min(p1.x,p3.x);
                double max_x_p1p3 = max(p1.x,p3.x);

                //  printf("min_x_p1p3: %lf\n",min_x_p1p3);
                //     printf("max_x_p1p3: %lf\n",max_x_p1p3);


                if(x3 < min_x_p1p3 || x3 > max_x_p1p3)
                    x3=infinity;

                // printf("x3: %lf\n",x3);
   
            }

            // printf("x1: %lf ",x1);
            // printf("x2: %lf ",x2);
            // printf("x3: %lf ",x3);
            // printf("\n");

            if((x1 == infinity && x2 == infinity) || (x2 == infinity && x3 == infinity) || (x1 == infinity && x3 == infinity))
            {
                //if any 2 of these 3 intersecting points x cordinates are infinity that means this scanline does not intersect the triangle
                continue;
            }

        
            //clipping along current scan line

 
            double leftmost_x,rightmost_x,Min_x,Max_x;

            if(x1 == infinity)
            {
                leftmost_x = min(x2,x3);
                rightmost_x = max(x2,x3);
            }
            if(x2 == infinity)
            {
                leftmost_x = min(x1,x3);
                rightmost_x = max(x1,x3);
            }
            if(x3 == infinity)
            {
                leftmost_x = min(x1,x2);
                rightmost_x = max(x1,x2);
            }

            if(leftmost_x > Right_X || rightmost_x < Left_X)
            {
                //that means both the intersection points are out of boundary
                continue;
            }


        
            //cipping is actually happenning below..because leftmost_x can be less than Left_X and Rightmost_x can be greater than Right_X
            Min_x = max(Left_X,leftmost_x);
            Max_x = min(Right_X,rightmost_x);

                //  printf("min_x: %lf\n",Min_x);
                //  printf("max_x: %lf\n",Max_x);
                //  printf("\n");



            
            int starting_column_no = (int)floor((Min_x - left_limit_x)/dx);
            int ending_column_no = (int)floor((Max_x - left_limit_x)/dx);

            for(int column_no = starting_column_no ; column_no <= ending_column_no ; column_no++)
            {   
                double current_x_value = Left_X + column_no*dx;
                double current_y_value = current_scanline;
                double z = get_z_value(triangle,current_x_value,current_y_value);
               
                if(z > z_min && z < z_buffer[row_no][column_no])
                {
                    z_buffer[row_no][column_no] = z;
                    frame_buffer.set_pixel(column_no,row_no,triangle.r,triangle.g,triangle.b);

                }
            }


        }

//break;

    }

    //writing z_buffer values to z_buffer.txt

    for(int i=0;i<Screen_Height;i++)
    {
        for(int j=0;j<Screen_Width;j++)
        {
            if(z_buffer[i][j] > z_min && z_buffer[i][j] < z_max)
                f_out << std::fixed << std::setprecision(6) << z_buffer[i][j] << "\t";
        }
        f_out << endl;
    } 

    frame_buffer.save_image("out.bmp");


    f_in.close();
    f_out.close();

    z_buffer.clear();
    frame_buffer.clear();


    

}