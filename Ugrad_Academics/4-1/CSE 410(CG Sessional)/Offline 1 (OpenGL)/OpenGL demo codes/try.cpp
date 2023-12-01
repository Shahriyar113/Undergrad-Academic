#define _USE_MATH_DEFINES

#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
#include <vector>

#include <stdio.h>
#include <iostream>
using namespace std;


struct point {
    GLfloat x, y, z;
};

vector<struct point> sphere_vertices;


float cylinder_height = sqrt(2);
float cylinder_radius = 0.2;

float r=1;

void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black and opaque
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
}

GLfloat eyex = 2, eyey = 2, eyez = 2;
GLfloat centerx = 0, centery = 0, centerz = 0;
GLfloat upx = 0, upy = 1, upz = 0;
float height = 2;
float radius = 1;

void drawAxes() {
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(1,0,0);   // Red
        // X axis
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);

        glColor3f(0,1,0);   // Green
        // Y axis
        glVertex3f(0,0,0);
        glVertex3f(0,2,0);

        glColor3f(0,0,1);   // Blue
        // Z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,2);
    glEnd();
}

void draw_cylinder_surface(double height, double radius) {

    double start = 90-35;
    double end = 90+35.5287794;

    
    glBegin(GL_QUADS);
        for (int theta = start ; theta <= end; theta=theta+1) {

            glColor3f(0,1,0);

            float x1 = radius * cos(theta*M_PI/180.0);
            float y1 = radius * sin(theta*M_PI/180.0);
            float x2 = radius * cos((theta+1)*M_PI/180.0);
            float y2 = radius * sin((theta+1)*M_PI/180.0);
            
            glVertex3f(x1, y1, height/2);
            glVertex3f(x1, y1, -height/2);
            glVertex3f(x2, y2, -height/2);
            glVertex3f(x2, y2, height/2);
        }
    glEnd();
}



void drawCylinder(double height, double radius, int segments) {
    double tempx = radius, tempy = 0;
    double currx, curry;
    glBegin(GL_QUADS);
        for (int i = 1; i <= segments; i++) {
            double theta = i * 70.5 / segments;
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
   float d = cylinder_radius/sin((M_PI/180)*(109.4/2));

   glPushMatrix();
   
     glRotatef(-45,0,1,0);
     glTranslatef(1/sqrt(2)-d,0,0); //not clear
     glRotatef(-70.5/2,0,0,1);  

     drawCylinder(cylinder_height,cylinder_radius,50);

   glPopMatrix();
}



void draw_cylinders_at_edges()
{
   draw_base_cylinder(); //1

   glPushMatrix();
      glRotatef(90,0,1,0);
      draw_base_cylinder();//2

      glRotatef(-90,1,0,0);
      draw_base_cylinder();//3

      //glRotatef(90,0,1,0);
      //draw_base_cylinder();//4

   glPopMatrix();

}

void buildUnitPositiveX(int subdivision)
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
            float scale = r / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
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


void display() {
    // glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);             // To operate on Model-View matrix
    glLoadIdentity();                       // Reset the model-view matrix

    // default arguments of gluLookAt
    // gluLookAt(0,0,0, 0,0,-100, 0,1,0);

    // control viewing (or camera)
    gluLookAt(eyex,eyey,eyez,
              centerx,centery,centerz,
              upx,upy,upz);
    // draw
    drawAxes() ;
//     glPushMatrix();
//   //  glTranslatef(0,0,-height/2);
//    // draw_cylinder_surface(height,radius);
//     drawSphere(1,3,3);
//     glPushMatrix();

    //draw_cylinders_at_edges();

    buildUnitPositiveX(2);
    int  size =(int)pow(2,2)+1;  //point_matrix_size_for_one_face 

   
   // glPointSize(10); // Make next points look bigger
    glBegin(GL_QUADS); // Each vertex is drawn as a single pixel
        glColor3f(0.0f,1.0f,0.0f); // Magenta
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

//    glBegin(GL_POINT); // Each vertex is drawn as a single pixel

//         glColor3d(0,1,0);
       
//         for(int i=0;i<size;i++)
//            glVertex3d(sphere_vertices.at(i).x,sphere_vertices.at(i).y,sphere_vertices.at(i).z);

            
//     glEnd();


    
    


    glBegin(GL_QUADS); // Each vertex is drawn as a single pixel

        glColor3d(0,0,1);
       
        glVertex3d(sphere_vertices.at(0).x,sphere_vertices.at(0).y,sphere_vertices.at(0).z);
        glVertex3d(sphere_vertices.at(20).x,sphere_vertices.at(20).y,sphere_vertices.at(20).z);
        glVertex3d(sphere_vertices.at(24).x,sphere_vertices.at(24).y,sphere_vertices.at(24).z);
        glVertex3d(sphere_vertices.at(4).x,sphere_vertices.at(4).y,sphere_vertices.at(4).z);

            
    glEnd();

    
    


    glutSwapBuffers();  // Render now
}

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


void keyboardListener(unsigned char key, int x, int y) {
    float v = 0.1;
    switch (key) {
    // Control eye (location of the eye)
    // control eyex
    case '1':
        eyex += v;
        break;
    case '2':
        eyex -= v;
        break;
    // control eyey
    case '3':
        eyey += v;
        break;
    case '4':
        eyey -= v;
        break;
    // control eyez
    case '5':
        eyez += v;
        break;
    case '6':
        eyez -= v;
        break;

    // Control center (location where the eye is looking at)
    // control centerx
    case 'q':
        centerx += v;
        break;
    case 'w':
        centerx -= v;
        break;
    // control centery
    case 'e':
        centery += v;
        break;
    case 'r':
        centery -= v;
        break;
    // control centerz
    case 't':
        centerz += v;
        break;
    case 'y':
        centerz -= v;
        break;

     case ',':
        radius += 0.1;
        r+=0.1;
        height -= 0.1;
        printf("%f %f\n",r,height);
        break;   

     case '.':
        radius -= 0.1;
                r-=0.1;

        height += 0.1;
        printf("%f %f\n",r,height);

        break;       

    // Control exit
    case 27:    // ESC key
        exit(0);    // Exit window
        break;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

void specialKeyListener(int key, int x,int y) {
    double v = 0.25;
    double lx = centerx - eyex;
    double lz = centerz - eyez;
    double s;
    switch (key) {
    case GLUT_KEY_LEFT:
        eyex += v * (upy*lz);
        eyez += v * (-lx*upy);
        s = sqrt(eyex*eyex + eyez*eyez) / (4 * sqrt(2));
        eyex /= s;
        eyez /= s;
        break;
    case GLUT_KEY_RIGHT:
        eyex += v * (-upy*lz);
        eyez += v * (lx*upy);
        s = sqrt(eyex*eyex + eyez*eyez) / (4 * sqrt(2));
        eyex /= s;
        eyez /= s;
        break;
    case GLUT_KEY_UP:
        eyey += v;
        break;
    case GLUT_KEY_DOWN:
        eyey -= v;
        break;
    
    default:
        return;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitWindowSize(640, 640);               // Set the window's initial width & height
    glutInitWindowPosition(50, 50);             // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("OpenGL 3D Drawing");      // Create a window with the given title
    glutDisplayFunc(display);                   // Register display callback handler for window re-paint
    glutReshapeFunc(reshapeListener);           // Register callback handler for window re-shape
    glutKeyboardFunc(keyboardListener);         // Register callback handler for normal-key event
    glutSpecialFunc(specialKeyListener);        // Register callback handler for special-key event
    initGL();                                   // Our own OpenGL initialization
    glutMainLoop();                             // Enter the event-processing loop
    return 0;
}
