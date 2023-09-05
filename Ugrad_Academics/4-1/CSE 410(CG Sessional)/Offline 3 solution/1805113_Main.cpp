#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <cmath>
#include <cstring>
#include <iomanip>
#include "bitmap_image.hpp"
#include "1805113_Header.h"

double pi = 2*acos(0.0);


void capture();



using namespace std;

// struct point {
//     GLfloat x, y, z;
// };


Point pos;   // position of the eye
Point l;     // look/forward direction
Point r;     // right direction
Point u;     // up direction
double window_width = 768;
double window_height = 768;
double screen_width;
double screen_height;
bitmap_image image;
bitmap_image texture_white;
bitmap_image texture_black;

bool texture_enabled = false;


double lambert = 0;
double phong = 0;


//input parameters

double near_plane_distance,far_plane_distance,fovY,aspect_ratio;
int level_of_recursion,number_of_pixel_along_both_axes;
double ambient_coeff,diffuse_coeff,specular_coeff,reflection_coeff,shine;
double checker_board_cell_width;
int num_of__objects;
int num_of_normal_light_sources;
int num_of_spot_light_sources;

vector <Object*> objects;
vector <Normal_Light> normal_light_sources;
vector <Spot_Light> spot_light_sources;


//after calling this function the values of input from "scene.txt" will be stored in the variables
void load_data()
{
    ifstream f_in("C:/Users/ASUS/Desktop/VS Code/CSE 410 Offline 3 Texture/scene.txt");

    //ifstream f_in("scene.txt"); //this line is not working..don't know why

    if(f_in.is_open())
    {
        cout << "Input File is open to read" << endl;
    }

    f_in >> near_plane_distance >> far_plane_distance >> fovY >> aspect_ratio;

    screen_height = 2*near_plane_distance*tan(fovY/2);
    double fovX = aspect_ratio * fovY;
    screen_width = 2*near_plane_distance*tan(fovX/2);

    f_in >> level_of_recursion ;
    f_in >> number_of_pixel_along_both_axes;

    f_in >> checker_board_cell_width;
    f_in >> ambient_coeff >> diffuse_coeff >> reflection_coeff;
    Coeefficient checker_board_coefficeint(ambient_coeff,diffuse_coeff,0,reflection_coeff);
    Object *checkerboard = new Checkerboard(checker_board_cell_width,checker_board_coefficeint);
    objects.push_back(checkerboard);

    f_in >> num_of__objects;

    for(int i=0;i<num_of__objects;i++)
    {
        string object_type;
        f_in >> object_type;

        if(object_type == "sphere")
        {
            double x,y,z,radius;
            double red,grean,blue;
            f_in >> x >> y >> z >> radius;
            Point center(x,y,z);
            f_in >> red >> grean >> blue;
            Color color(red,grean,blue);
            f_in >> ambient_coeff >> diffuse_coeff >> specular_coeff >> reflection_coeff >> shine;
            Coeefficient sphere_coefficeint(ambient_coeff,diffuse_coeff,specular_coeff,reflection_coeff);

            Object *sphere = new Sphere(center,radius,color,sphere_coefficeint,shine);
            objects.push_back(sphere);
        }
        
        else if(object_type == "pyramid")
        {
            double x,y,z;
            double red,grean,blue;
            double width,height;
            f_in >> x >> y >> z;
            Point lowest_point_coordinate(x,y,z);
            f_in >> width >> height ;
            f_in >> red >> grean >> blue;
            Color color(red,grean,blue);
            f_in >> ambient_coeff >> diffuse_coeff >> specular_coeff >> reflection_coeff >> shine;
            Coeefficient pyramid_coefficeint(ambient_coeff,diffuse_coeff,specular_coeff,reflection_coeff);

            Object *pyramid = new Pyramid(lowest_point_coordinate,width,height,color,pyramid_coefficeint,shine);
            objects.push_back(pyramid);

            
        }

         else if(object_type == "cube")
         {
            double x,y,z;
            double red,grean,blue;
            double side;

            f_in >> x >> y >> z;
            Point bottom_lower_left_point(x,y,z);
            f_in >> side;
            f_in >> red >> grean >> blue;
            Color color(red,grean,blue);
            f_in >> ambient_coeff >> diffuse_coeff >> specular_coeff >> reflection_coeff >> shine;
            Coeefficient cube_coefficeint(ambient_coeff,diffuse_coeff,specular_coeff,reflection_coeff);

            Object *cube = new Cube(bottom_lower_left_point,side,color,cube_coefficeint,shine);
            objects.push_back(cube);


         }
    }

    f_in >> num_of_normal_light_sources;

    for(int i=0;i< num_of_normal_light_sources ;i++)
    {
        double x,y,z,red,green,blue,fallof_parameter;
        f_in >> x >> y >> z ;
        Point source_position(x,y,z);
        f_in >> red >> green >> blue;
        Color color(red,green,blue);
        f_in >> fallof_parameter;


        Normal_Light normal_light(source_position,fallof_parameter,color);
        normal_light_sources.push_back(normal_light);

    }

    f_in >> num_of_spot_light_sources;

    for(int i=0;i< num_of_spot_light_sources ;i++)
    {
        double x,y,z,a,b,c,red,green,blue,fallof_parameter,cutoff_angle;
        f_in >> x >> y >> z ;
        Point source_position(x,y,z);
        f_in >> red >> green >> blue;
        Color color(red,green,blue);
        f_in >> fallof_parameter;
        f_in >> a >> b >> c >> cutoff_angle;
        Point direction(a,b,c);

        Spot_Light spot_light(source_position,fallof_parameter,color,direction,cutoff_angle);
        spot_light_sources.push_back(spot_light);

    }

     f_in.close();
    
    

}

void clear_memory()
{
    for(int i=0;i<objects.size();i++)
    {
        delete objects[i];
    }
    objects.clear();

    normal_light_sources.clear();
    spot_light_sources.clear();
    image.clear();
    texture_black.clear();
    texture_white.clear();
}

void print_load_data()
{
    cout << near_plane_distance << " " << far_plane_distance << " " << fovY << " " << aspect_ratio << endl;
    cout << level_of_recursion << endl;
    cout << number_of_pixel_along_both_axes << endl;
    cout << checker_board_cell_width << endl;
    cout << num_of__objects << endl;

    for(int i=0;i<num_of__objects;i++)
    {
        objects[i]->print();
        printf("\n");
    }

    cout << num_of_normal_light_sources << endl;

    for(int i=0;i< num_of_normal_light_sources ;i++)
    {
        normal_light_sources[i].print();
        printf("\n");

    }

    cout << num_of_spot_light_sources << endl;

    for(int i=0;i< num_of_spot_light_sources ;i++)
    {
        spot_light_sources[i].print();
        printf("\n");

    }
}









/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black and opaque
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
}




void drawAxes() {
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1,0,0);   // Red
        // X axis
        glVertex3f(0,0,0);
        glVertex3f(2000,0,0);

        glColor3f(0,1,0);   // Green
        // Y axis
        glVertex3f(0,0,0);
        glVertex3f(0,2000,0);

        glColor3f(0,0,1);   // Blue
        // Z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,2000);
    glEnd();
}




void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, pos.z, 
			pos.x + l.x, pos.y + l.y, pos.z + l.z, 
			u.x, u.y, u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	drawAxes();

    for (int i=0; i<objects.size(); i++){
		objects[i]->draw();
	}

	for (int i=0; i<normal_light_sources.size(); i++){
		normal_light_sources[i].draw();
	}

	for(int i=0;i<spot_light_sources.size();i++){
		spot_light_sources[i].draw();
	}



	glutSwapBuffers();
}


//MOving camera and objects
//-----------------------------
void keyboardListener(unsigned char key, int xx,int yy){
    double rate = 0.05;

	switch(key){

        case '0':
			capture();
			break;

		case '1':
			r.x = r.x*cos(rate)+l.x*sin(rate);
			r.y = r.y*cos(rate)+l.y*sin(rate);
			r.z = r.z*cos(rate)+l.z*sin(rate);

			l.x = l.x*cos(rate)-r.x*sin(rate);
			l.y = l.y*cos(rate)-r.y*sin(rate);
			l.z = l.z*cos(rate)-r.z*sin(rate);
			break;

        case '2':
			r.x = r.x*cos(-rate)+l.x*sin(-rate);
			r.y = r.y*cos(-rate)+l.y*sin(-rate);
			r.z = r.z*cos(-rate)+l.z*sin(-rate);

			l.x = l.x*cos(-rate)-r.x*sin(-rate);
			l.y = l.y*cos(-rate)-r.y*sin(-rate);
			l.z = l.z*cos(-rate)-r.z*sin(-rate);
			break;

        case '3':
			l.x = l.x*cos(rate)+u.x*sin(rate);
			l.y = l.y*cos(rate)+u.y*sin(rate);
			l.z = l.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-l.x*sin(rate);
			u.y = u.y*cos(rate)-l.y*sin(rate);
			u.z = u.z*cos(rate)-l.z*sin(rate);
			break;

        case '4':
			l.x = l.x*cos(-rate)+u.x*sin(-rate);
			l.y = l.y*cos(-rate)+u.y*sin(-rate);
			l.z = l.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-l.x*sin(-rate);
			u.y = u.y*cos(-rate)-l.y*sin(-rate);
			u.z = u.z*cos(-rate)-l.z*sin(-rate);
			break;

        case '5':
			u.x = u.x*cos(rate)+r.x*sin(rate);
			u.y = u.y*cos(rate)+r.y*sin(rate);
			u.z = u.z*cos(rate)+r.z*sin(rate);

			r.x = r.x*cos(rate)-u.x*sin(rate);
			r.y = r.y*cos(rate)-u.y*sin(rate);
			r.z = r.z*cos(rate)-u.z*sin(rate);
			break;

        case '6':
			u.x = u.x*cos(-rate)+r.x*sin(-rate);
			u.y = u.y*cos(-rate)+r.y*sin(-rate);
			u.z = u.z*cos(-rate)+r.z*sin(-rate);

			r.x = r.x*cos(-rate)-u.x*sin(-rate);
			r.y = r.y*cos(-rate)-u.y*sin(-rate);
			r.z = r.z*cos(-rate)-u.z*sin(-rate);
			break;

        // case '7':
        //     DRAW_LINES = (DRAW_LINES + 1) % 2;
        //     break;

        
        case ' ':
            texture_enabled = !texture_enabled;
            if(texture_enabled)
            {
                texture_white = bitmap_image("C:/Users/ASUS/Desktop/VS Code/CSE 410 Offline 3 Texture/texture_w.bmp");
                texture_black = bitmap_image("C:/Users/ASUS/Desktop/VS Code/CSE 410 Offline 3 Texture/texture_b.bmp");
                cout << "texture enabled" << endl;
                
            }
            else
            {
                texture_white.clear();
                texture_black.clear();
                cout << "texture disabled" << endl;
            }
            
            break;
   
          

		default:
			break;
	}

	glutPostRedisplay();

}

void specialKeyListener(int key, int x,int y)
{
    float speed = 5;
	switch(key){
		case GLUT_KEY_UP:		//up arrow key
			pos.x+=speed*l.x;
			pos.y+=speed*l.y;
			pos.z+=speed*l.z; 

            // objects[0]->width = objects[0]->width + 50;
            // far_plane_distance = pos.z + 1000;
			break;
		case GLUT_KEY_DOWN:		// down arrow key
			pos.x-=speed*l.x;
			pos.y-=speed*l.y;
			pos.z-=speed*l.z;
            // objects[0]->width = objects[0]->width + 50;     
            // far_plane_distance = pos.z + 1000;
			break;
            


		case GLUT_KEY_RIGHT:
			pos.x+=speed*r.x;
			pos.y+=speed*r.y;
			pos.z+=speed*r.z;
           // objects[0]->width = objects[0]->width + 50;       

			break;
		case GLUT_KEY_LEFT :
			pos.x-=speed*r.x;
			pos.y-=speed*r.y;
			pos.z-=speed*r.z;

           // objects[0]->width = objects[0]->width + 0.1;     

			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+=speed*u.x;
			pos.y+=speed*u.y;
			pos.z+=speed*u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos.x-=speed*u.x;
			pos.y-=speed*u.y;
			pos.z-=speed*u.z;
			break;          

		default:
			break;
	}
	glutPostRedisplay();
}


void capture()
{
    //implementing ray casting for each pixel
    //cout << "capture function called" << endl;

   // initialize bitmap image and set background color to black
   for(int i=0;i<number_of_pixel_along_both_axes;i++) //image width = image height = number_of_pixel_along_both_axes
		for(int j=0;j<number_of_pixel_along_both_axes;j++)
			image.set_pixel(i, j, 0, 0, 0);

   double plane_distance = ((window_height/2) * tan((pi*fovY)/360.0)) +150;
  // cout << "plane distance = " << plane_distance << endl;
    
   Point top_left_point_of_near_plane = pos + l*plane_distance - r*(window_width/2) + u*(window_height/2);
    //cout << "top_left_point_of_near_plane: ";
    //top_left_point_of_near_plane.print();

   double du = window_width/number_of_pixel_along_both_axes;
   double dv = window_height/number_of_pixel_along_both_axes;
  // cout << "du = " << du << " dv = " << dv << endl;

   Point mid_point_of_1st_pixel = top_left_point_of_near_plane + r*(du/2) - u*(dv/2);
//    cout << "pos: " ;
//    pos.print();
//    cout << "l: ";
//     l.print();
//     cout << "r: ";
//     r.print();
//     cout << "u: ";
//     u.print();
//     cout << "mid_point_of_1st_pixel: ";
//    mid_point_of_1st_pixel.print();
//    cout << "mid point of view plane: ";
//     (pos + l*plane_distance).print();

   for (int i=0;i<number_of_pixel_along_both_axes;i++)
   {
       for(int j=0;j<number_of_pixel_along_both_axes;j++)
       {
           Point mid_point_of_current_pixel = mid_point_of_1st_pixel + (r*du*i) - (u*dv*j);

           Point direction = mid_point_of_current_pixel - pos;

           Ray ray(pos,direction); //here "the mid point of the pixel" is considered as the origin of the ray

           double t_minimum = 10000;
           Object *closest_object = NULL; 

           //for current ray we have to traverse each object to see which object is intersecting with the ray and which object is the closest to the near plane

           for (int k=0;k<objects.size();k++)
           {
               Color dummycolor(0,0,0);

            //    if(objects[k]-> object_type != "CHECKERBOARD" && objects[k]-> object_type != "SPHERE" && objects[k]-> object_type != "CUBE" && objects[k]-> object_type != "PYRAMID")
            //      continue;
               double t = objects[k]->intersect(&ray,&dummycolor,0);
               
               //if (i == 384 && j == 384 )
                //cout << "pixel (" << i << "," << j << ")" <<" t =" << t  << endl;
                //ray.print();
                if(t > 0 && t<t_minimum){
                
                     t_minimum = t;
                     closest_object = objects[k];
                }

           }

          //if closest object is found then we have to color the pixel with the color of the closest object with lighting impact

           if(t_minimum != 10000) //t_minimum = 10000 means kono object paoa jay nai
			{
				// cout<<"Object "<<nearestObjectIndex<<" intersected"<<endl;
				// color = objects[nearestObjectIndex]->color;
                Point intersection_point = ray.origin + ray.dir*t_minimum;
                // Point Mid_point = pos + l*plane_distance;

                // if(intersection_point.x < (Mid_point-r*(window_width/2)).x || intersection_point.x > (Mid_point+r*(window_width/2)).x || intersection_point.y < (Mid_point-u*(window_height/2)).y || intersection_point.y > (Mid_point+u*(window_height/2)).y || intersection_point.z < (Mid_point-l*(window_height/2)).z || intersection_point.z > (Mid_point+l*(window_height/2)).z
                //     continue;

                // if(closest_object-> object_type == "CUBE")   
                //   intersection_point.print();
                // cout << "intersecting point found for "<< closest_object->object_type << " at pixel (" << i << "," << j << ")" <<" t =" << t_minimum  << endl;
				Color color = Color(0,0,0);
				// cout<<"Before Color "<<color.r<<" "<<color.g<<" "<<color.b<<endl;
                //  if(closest_object-> object_type != "CHECKERBOARD" && closest_object-> object_type != "SPHERE" && closest_object-> object_type != "CUBE" && closest_object-> object_type != "PYRAMID" )
                //      continue;
                //  cout << "checkerboard " << t_minimum<< endl;    

				double t = closest_object->intersect(&ray,&color, 1);
                //cout << "color: ";
                //color.print();

                //  if(closest_object-> object_type == "SPHERE")
                //  {
                //     Point center(20,20,20);
                //     if (closest_object->reference_point == center)
                //     {
                //     closest_object->print();
                //      color.print();
                //      cout  << endl;

                //     }
                   
                //  }

				if(color.r > 1) color.r = 1;
				if(color.g > 1) color.g = 1;
				if(color.b > 1) color.b = 1;

				if(color.r < 0) color.r = 0;
				if(color.g < 0) color.g = 0;
				if(color.b < 0) color.b = 0;
				
				// cout<<"After Color "<<color.r<<" "<<color.g<<" "<<color.b<<endl;
				image.set_pixel(i,j,255*color.r, 255*color.g, 255*color.b);
			}

          //debugging
        //    if(t_minimum != 10000)
        //    {
        //         Point intersection_point = ray.origin + ray.dir*t_minimum;
        //         cout << "intersecting point found for "<< closest_object->object_type << " at pixel (" << i << "," << j << ")" <<" t =" << t_minimum  << endl;
        //         As.push_back(ray.origin);
        //         Bs.push_back(intersection_point);
        //    }


           //Color color = ray_trace(ray,level_of_recursion);
        //image.set_pixel(i,j,color.red,color.green,color.blue);


       }
   }

   image.save_image("C:/Users/ASUS/Desktop/VS Code/CSE 410 Offline 3 Texture/out.bmp");


   cout << "image captured succeddfully" << endl;

}



void init(){

    // pos.x=2.5;pos.y=2.5;pos.z=2.5;

    // l.x=-1/sqrt(3);l.y=-1/sqrt(3);l.z=-1/sqrt(3);
    // u.x=-1/sqrt(6);u.y=2/sqrt(6);u.z=-1/sqrt(6);
    // r.x = (l.y*u.z - u.y*l.z);
    // r.y = -(l.x*u.z - l.z*u.x);
    // r.z = (l.x*u.y - u.x*l.y);

    pos = Point(0,-300,70);
    Point center(0,0,70);
    Point up(0,0,1);
    Point look = center - pos;
    l = look;
    l.normalize();
    r = cross_product(l,up);
    r.normalize();
    u = cross_product(r,l);

	//codes for initialization
	// drawgrid=1;
	// drawaxes=1;
	// cameraHeight=150.0;
	// cameraAngle=1.0;
	// angle=0;
	// numSegments = 36;

    //initializing the image buffer

	load_data();
	//image = bitmap_image(imageWidth, imageHeight);
    image = bitmap_image(number_of_pixel_along_both_axes, number_of_pixel_along_both_axes);
    //print_load_data();


	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(fovY,aspect_ratio,near_plane_distance,far_plane_distance);
	
}

int main(int argc, char **argv){

	
	glutInit(&argc,argv);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Ray Tracing");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMainLoop();		//The main loop of OpenGL

	clear_memory();

	return 0;
}


