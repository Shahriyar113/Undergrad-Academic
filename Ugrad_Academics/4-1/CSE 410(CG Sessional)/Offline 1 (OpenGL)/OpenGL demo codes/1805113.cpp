#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <vector>


using namespace std;
int s=0;

bool grid_drawn = true;


/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black and opaque
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
}

struct point {
    GLfloat x, y, z;
};


float scale = 0;

//See this calculation details is in "keyboard_listener method"
float radius_scale_change = sqrt(3)/48;
float triangle_scale_change = sqrt(6)/48;


//For Base triangle initially A(1,0,0),B(0,1,0),C(0,0,1)
float ax=1,ay=0,az=0;
float bx=0,by=1,bz=0;
float cx=0,cy=0,cz=1;


float angle_of_cylindrical_curve = 70.5287794;
float dihedral_angle = 109.47;
float cylinder_radius = 0;
float sphere_radius = 0;

float cylinder_height = sqrt(2);//length of edge 
float sphere_final_radius = 1/sqrt(3); //distance between (0,0,0) and (1/3,1/3,1/3)

vector<struct point> sphere_vertices;//points of one face of sphere


struct point pos;   // position of the eye
struct point l;     // look/forward direction
struct point r;     // right direction
struct point u;     // up direction


int rotation_scale = 0; //this scale is for rotating the object along its own axis


//Drawing octahedron
//-------------------

void draw_base_triangle(float r,float g,float b) {
  
  glBegin(GL_TRIANGLES);
        glColor3f(r,g,b); 
        glVertex3f(ax,ay,az);
        glVertex3f(bx,by,bz);
        glVertex3f(cx,cy,cz);
  
    glEnd();
} 

void resize_base_triangle()
{
    //center of mass G(1/3,1/3,1/3)
    //AG(-2/3,1/3,1/3)
    //Unit vector of AG(-root (6)/3,1/root(6),1/root(6))
    //similarly, BG(1/3,-2/3,1/3)
   //Unit vector of BG(1/root(6),-root (6)/3,1/root(6))
   //similarly, CG(1/3,1/3,-2/3)
   //Unit vector of CG(1/root(6),1/root(6),-root (6)/3)

   //unit vector of AG ==> unit_AG
   //unit_AGx = x component of unit unit_AG
   float unit_AGx = -sqrt(6)/3,unit_AGy =1/sqrt(6),unit_AGz = 1/sqrt(6);
   float unit_BGx = 1/sqrt(6),unit_BGy =-sqrt(6)/3,unit_BGz = 1/sqrt(6);
   float unit_CGx = 1/sqrt(6),unit_CGy =1/sqrt(6),unit_CGz =-sqrt(6)/3;




   ax = 1 + scale*unit_AGx;
   ay = 0 + scale*unit_AGy;
   az = 0 + scale*unit_AGz;

   bx = 0 + scale*unit_BGx;
   by = 1 + scale*unit_BGy;
   bz = 0 + scale*unit_BGz;


   cx = 0 + scale*unit_CGx;
   cy = 0 + scale*unit_CGy;
   cz = 1 + scale*unit_CGz;

   cylinder_height = sqrt(pow(ax-bx,2)+pow(ay-by,2)+pow(az-bz,2)); //length of arm of base triangle




}



void draw_Octahedron()
{

    //drawing upper pyramid
     draw_base_triangle(1,1,1);

     glPushMatrix();

        glRotatef(90,0,0,1);
        draw_base_triangle(1,0,0);
         glRotatef(90,0,0,1);
        draw_base_triangle(1,0,1);
         glRotatef(90,0,0,1);
        draw_base_triangle(0,0,1);
        

     glPopMatrix();   

    //drawing lower pyramid

     glPushMatrix();

        glRotatef(180,1,0,0);
        draw_base_triangle(1,1,1);


        glPushMatrix();

          glRotatef(90,0,0,1);
          draw_base_triangle(1,0,0);
          glRotatef(90,0,0,1);
          draw_base_triangle(1,0,1);
          glRotatef(90,0,0,1);
          draw_base_triangle(0,0,1);
        

        glPopMatrix();  

     glPopMatrix();
     

}



//Drawing Cylinder surfaces
//-------------------------


void drawCylinder(double height, double radius, int segments) {
    double tempx = radius, tempy = 0;
    double currx, curry;
    glBegin(GL_QUADS);
        for (int i = 1; i <= segments; i++) {
            double theta = i * angle_of_cylindrical_curve / segments;
            currx = radius * cos((M_PI/180)*theta);
            curry = radius * sin((M_PI/180)*theta);

          //  GLfloat c = (2+cos(theta))/3;
            glColor3f(0,1,0);
            glVertex3f(currx, curry, height/2);
            glVertex3f(currx, curry, -height/2);

            glVertex3f(tempx, tempy, -height/2);
            glVertex3f(tempx, tempy, height/2);

            tempx = currx;
            tempy = curry;
        }
    glEnd();
}


void draw_base_cylinder()
{
   float d = cylinder_radius/sin((M_PI/180)*(109.47/2));

   glPushMatrix();
   
     glRotatef(-45,0,1,0);
     glTranslatef(1/sqrt(2)-d,0,0); //not clear
     glRotatef(-angle_of_cylindrical_curve/2,0,0,1);  

     drawCylinder(cylinder_height,cylinder_radius,50);

   glPopMatrix();
}



void draw_all_cylinder_faces()
{
   draw_base_cylinder(); //1

   glPushMatrix();
      glRotatef(90,0,1,0);
      draw_base_cylinder();//2

      glRotatef(90,0,1,0);
      draw_base_cylinder();//3

      glRotatef(90,0,1,0);
      draw_base_cylinder();//4

   glPopMatrix();


   glPushMatrix();
      glRotatef(90,0,0,1);
      draw_base_cylinder();//5

      glRotatef(90,0,1,0);
      draw_base_cylinder();//6

      glRotatef(90,0,1,0);
      draw_base_cylinder();//7

      glRotatef(90,0,1,0);
      draw_base_cylinder();//8

   glPopMatrix();


   glPushMatrix();
      glRotatef(-90,0,1,0);
      glRotatef(90,0,0,1);

      draw_base_cylinder();//9

      glRotatef(90,0,1,0);
      draw_base_cylinder();//10

      glRotatef(90,0,1,0);
      draw_base_cylinder();//11

      glRotatef(90,0,1,0);
      draw_base_cylinder();//12

   glPopMatrix();


}

//Drawing spherical surfaces
//-------------------------


void Generating_points_for_one_face(int subdivision)
{
    sphere_vertices.clear();

    const float DEG2RAD = acos(-1) / 180.0f;

    float n1[3];        // normal of longitudinal plane rotating along Y-axis
    float n2[3];        // normal of latitudinal plane rotating along Z-axis
    float v[3];         // direction vector intersecting 2 planes, n1 x n2
    float a1;           // longitudinal angle along Y-axis
    float a2;           // latitudinal angle along Z-axis

    // compute the number of vertices per row, 2^n + 1
    int pointsPerRow = (int)pow(2, subdivision) + 1;

    // rotate latitudinal plane from 45 to -45 degrees along Z-axis (top-to-bottom)
    for(unsigned int i = 0; i < pointsPerRow; ++i)
    {
        // normal for latitudinal plane
        // if latitude angle is 0, then normal vector of latitude plane is n2=(0,1,0)
        // therefore, it is rotating (0,1,0) vector by latitude angle a2
        a2 = DEG2RAD * (45.0f - 90.0f * i / (pointsPerRow - 1));
        n2[0] = -sin(a2);
        n2[1] = cos(a2);
        n2[2] = 0;

        // rotate longitudinal plane from -45 to 45 along Y-axis (left-to-right)
        for(unsigned int j = 0; j < pointsPerRow; ++j)
        {
            // normal for longitudinal plane
            // if longitude angle is 0, then normal vector of longitude is n1=(0,0,-1)
            // therefore, it is rotating (0,0,-1) vector by longitude angle a1
            a1 = DEG2RAD * (-45.0f + 90.0f * j / (pointsPerRow - 1));
            n1[0] = -sin(a1);
            n1[1] = 0;
            n1[2] = -cos(a1);

            // find direction vector of intersected line, n1 x n2
            v[0] = n1[1] * n2[2] - n1[2] * n2[1];
            v[1] = n1[2] * n2[0] - n1[0] * n2[2];
            v[2] = n1[0] * n2[1] - n1[1] * n2[0];

            // normalize direction vector
            float scale = sphere_radius / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
            v[0] *= scale;
            v[1] *= scale;
            v[2] *= scale;

            // add a vertex into array
            struct point a_point;
            a_point.x = v[0];
            a_point.y = v[1];
            a_point.z = v[2];

        
            sphere_vertices.push_back(a_point);
        }
    }

}


void draw_sphere_face()
{
    //if subdivision_size = 2 ,then the point matrix for single face
    //0 1 2 3 4
    //5 6 7 8 9
    //10 11 12 13 14
    //15 16 17 18 19
    //20 21 22 23 24

    //so there will be total 9 quads..the quads should be
    //1) 0 5 6 1
    //2) 5 10 11 6
    //......
    //.....
    //9) 18 23 24 19
    int subdivision_size = 5;
    Generating_points_for_one_face(subdivision_size);
    int  size =(int)pow(2,subdivision_size)+1;  //point_matrix_size_for_one_face 

   //generating single face of sphere
    glBegin(GL_QUADS); 
         for(int i=0;i<size-1 ;i++)
            {
                for(int j=0;j<size-1 ;j++)
                {
                    int index = size*j+i;
                    glVertex3d(sphere_vertices.at(index).x,sphere_vertices.at(index).y,sphere_vertices.at(index).z);
                    glVertex3d(sphere_vertices.at(size+index).x,sphere_vertices.at(size+index).y,sphere_vertices.at(size+index).z);
                    glVertex3d(sphere_vertices.at(size+index+1).x,sphere_vertices.at(size+index+1).y,sphere_vertices.at(size+index+1).z);
                    glVertex3d(sphere_vertices.at(index+1).x,sphere_vertices.at(index+1).y,sphere_vertices.at(index+1).z);

                }
            }
            
    glEnd();
}

void draw_base_sphere_face()
{
     glPushMatrix();
        //here center(specially x co-ordinate of the center) of the sphere is adjusted with the change of its radius
        //initially, x=1(as initially center (1,0,0)) and radius = 0
        //and finally(after converting the shape into sphere) x=0(as finally center (0,0,0)) and radius = 1/sqrt(3)
        //so using the concept of 2 point linear equation, x=1-sqrt(3)*radius

        glTranslatef(1-sqrt(3)*sphere_radius,0,0);
        draw_sphere_face();


    glPopMatrix();
}



void draw_all_sphere_faces()
{
    glColor3f(0,0,1); 
    draw_base_sphere_face();//+x

    glPushMatrix();
      glColor3f(1,0,0); 
      glRotatef(90,0,1,0); 
      draw_base_sphere_face();//-z

      glColor3f(0,0,1); 
      glRotatef(90,0,1,0);
      draw_base_sphere_face();//-x

      glColor3f(1,0,0); 
      glRotatef(90,0,1,0);
      draw_base_sphere_face();//+z
    glPopMatrix();


    glPushMatrix();
      glColor3f(1,0,1); 
      glRotatef(90,0,0,1);
      draw_base_sphere_face();//+y
    glPopMatrix(); 

    glPushMatrix();
        glColor3f(1,0,1); 
        glRotatef(-90,0,0,1);
        draw_base_sphere_face();//-y
    glPopMatrix();
     

    
}


void drawAxes() {
    glLineWidth(5);
    glBegin(GL_LINES);
        glColor3f(1,1,1);   // Red
        // X axis
        glVertex3f(-700,0,0);
        glVertex3f(700,0,0);

        glColor3f(1,1,1);   // Green
        // Y axis
        glVertex3f(0,-700,0);
        glVertex3f(0,700,0);

       
    glEnd();
}

void drawGridXY(){
    

    glPushMatrix();
      glLineWidth(5);

      glColor3f(1,1,1); 
      glTranslatef(0,0,-1/sqrt(3));
      glRotatef(-45,0,0,1);
      drawAxes();  
    glPopMatrix(); 


}

void drawGrid(){

      int scale = 0.2;
   
      for(int i=0;i<10;i++)
      {
        glPushMatrix();
          glLineWidth(1);
      glTranslatef(0,0,-1/sqrt(3));

          glTranslated(scale,scale,0);
          drawAxes();  
        glPopMatrix(); 
        scale = scale +1 ;
      }

      scale = 0.2;

      for(int i=0;i<10;i++)
      {
        glPushMatrix();
          glLineWidth(1);
      glTranslatef(0,0,-1/sqrt(3));

          glTranslated(-scale,-scale,0);
          drawAxes();  
        glPopMatrix(); 
        scale = scale +1 ;

      }
     

}





void display() {
    // glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);             // To operate on Model-View matrix
    glLoadIdentity();                       // Reset the model-view matrix

   
    // control viewing (or camera)
    gluLookAt(pos.x,pos.y,pos.z,
              pos.x+l.x,pos.y+l.y,pos.z+l.z,
              u.x,u.y,u.z); 

    //for rotating along own axis when 'a' or 'd' will be pressed

    glRotatef(5*rotation_scale,0,1,0);

   
    glTranslatef(s,0,0);

    
    glPushMatrix();
      glRotatef(-5*rotation_scale,0,1,0);    
      glTranslatef(-s,0,0);

      drawGrid();

    glPopMatrix();

    

    draw_Octahedron();

    draw_all_cylinder_faces();   

    draw_all_sphere_faces();     


    glutSwapBuffers();  // Render now
    grid_drawn == false;
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeListener(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    /*if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }*/
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

//MOving camera and objects
//-----------------------------
void keyboardListener(unsigned char key, int xx,int yy){
    double rate = 0.01;
    int theta = 0;
	switch(key){

        case 'a':
            rotation_scale--;
            grid_drawn = false;

            theta = 5*rotation_scale;
            s = 1/sqrt(3)*((M_PI*theta)/180);

            break;
        case 'd':
            rotation_scale++;
            grid_drawn = false;

            theta = 5*rotation_scale;
            s = -(1/sqrt(3)*((M_PI*theta)/180));

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

        case ',':
        { 

            
            //printf("(ax,by,cz) = (%f %f %f)\n",ax,by,cz);
            //printf("Radius of cylinder : %f\n",cylinder_radius);
            // printf("Radius of cylinder : %f\n\n",sphere_radius);

            //shrinking_base_triangles
            if(ax > 1/3.0)
            {
              //1 + scale *(-sqrt(6)/3) = 1/3 
              //==> scale = sqrt(6)/3 
              //==> scale/16 =sqrt(6)/48 =0.051 (i.e. 16 bar "," press korle octahedron sphere a convert hobe) 
              //thats why [triangle_scale_change = sqrt(6)/48]

              //final_radius_of_cylinder = final radius of sphere = 1/sqrt(3)
              //thats why final_radius_of_cylinder/16 =sqrt(3)/48 =0.036  (i.e. 16 bar "," press korle octahedron sphere a convert hobe)
              //thats why [radius_scale_change = sqrt(3)/48]


              cylinder_radius += radius_scale_change;
              sphere_radius += radius_scale_change;


              scale += triangle_scale_change; 
              resize_base_triangle();
              
              // printf("Scale: %f,translation: %f \n",scaleX,translation);
              glutPostRedisplay();
            }
            
              
            break;
        
        }
     case '.':
        { 
            //printf("(ax,by,cz) = (%f %f %f)\n",ax,by,cz);
            //printf("Radius of cylinder : %f\n",cylinder_radius);
            //printf("Radius of cylinder : %f\n\n",sphere_radius);

            //expanding_base_triangles
            if(ax < 1.0)
            {
                cylinder_radius -= radius_scale_change;
                sphere_radius -= radius_scale_change;

 
                scale -= triangle_scale_change; 
                resize_base_triangle();
                // printf("Scale: %f,translation: %f \n",scaleX,translation)
                glutPostRedisplay();
              
            }
               
           
            break;
        
        }       

		default:
			break;
	}

	glutPostRedisplay();

}

void specialKeyListener(int key, int x,int y)
{
    float speed = 0.2;
	switch(key){
		case GLUT_KEY_UP:		//up arrow key
			pos.x+=speed*l.x;
			pos.y+=speed*l.y;
			pos.z+=speed*l.z;
			break;
		case GLUT_KEY_DOWN:		// down arrow key
			pos.x-=speed*l.x;
			pos.y-=speed*l.y;
			pos.z-=speed*l.z;
			break;

		case GLUT_KEY_RIGHT:
			pos.x+=speed*r.x;
			pos.y+=speed*r.y;
			pos.z+=speed*r.z;
			break;
		case GLUT_KEY_LEFT :
			pos.x-=speed*r.x;
			pos.y-=speed*r.y;
			pos.z-=speed*r.z;
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

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
	glutPostRedisplay();
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    pos.x=5;pos.y=5;pos.z=5;

    l.x=-1/sqrt(3);l.y=-1/sqrt(3);l.z=-1/sqrt(3);
    u.x=-1/sqrt(6);u.y=2/sqrt(6);u.z=-1/sqrt(6);
    r.x = (l.y*u.z - u.y*l.z);
    r.y = -(l.x*u.z - l.z*u.x);
    r.z = (l.x*u.y - u.x*l.y);


    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitWindowSize(640, 640);               // Set the window's initial width & height
    glutInitWindowPosition(50, 50);             // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("Magic cube");      // Create a window with the given title
    glutDisplayFunc(display);                   // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeListener);           // Register callback handler for window re-shape
    glutKeyboardFunc(keyboardListener);         // Register callback handler for normal-key event
    glutSpecialFunc(specialKeyListener);        // Register callback handler for special-key event
    initGL();                                   // Our own OpenGL initialization
    glutMainLoop();                             // Enter the event-processing loop
    return 0;
}
