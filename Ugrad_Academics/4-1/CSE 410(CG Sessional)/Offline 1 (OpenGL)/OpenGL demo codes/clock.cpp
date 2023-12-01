#define _USE_MATH_DEFINES

#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <cmath>
#include <ctime>
#include <cstring>
#include <iostream>
#include <stdio.h>

using namespace std;


//float rotation_angle_of_pendulum = 0.0; //in degree unit
//float rotation_speed_of_pendulum = 0.5/45 ;
float t=0.0;
float second_hand_moving_speed = 6.0; //per sec
float minute_hand_moving_speed = 360.0/3600.0;   //per sec
float hour_hand_moving_speed = 360.0/(12*3600.0);   //per sec

float second_hand_rotation_angle = 0.0; //per sec
float minute_hand_rotation_angle = 0.0; //per sec
float hour_hand_rotation_angle = 0.0; //per sec



void draw_clock_body()
{
    glBegin(GL_LINE_LOOP);  // All vertices form a single loop of single pixel width
        glColor3f(1.0f,1.0f,1.0f); 
        glVertex2d( 0.5f, 0.8f);
        glVertex2d( -0.5f, 0.8f);
        glVertex2d( -0.5f, -0.45f);
        glVertex2d( 0.0f, -0.8f);
        glVertex2d( 0.5f, -0.45f);
    glEnd();

}

void draw_outer_circle()
{
    float cx, cy, r;
    //outer circle
    glBegin(GL_LINE_LOOP);  // All vertices form a single loop of single pixel width
        glColor3f(1.0f,1.0f,1.0f);  
        cx = 0.0;
        cy = 0.3;
        r = 0.4;
        for (float theta = 0; theta < 360; theta += 5) {
            float x = cx + r * cos(theta/180*M_PI);
            float y = cy + r * sin(theta/180*M_PI);
            glVertex2f(x,y);
        }
    glEnd();
  
}


void draw_inner_circle()
{
    float cx, cy, r;

     //inner circle
    glBegin(GL_LINE_LOOP);  // All vertices form a single loop of single pixel width
        glColor3f(1.0f,1.0f,1.0f);  
        cx = 0.0;
        cy = 0.3;
        r = 0.3;
        for (float theta = 0; theta < 360; theta += 5) {
            float x = cx + r * cos(theta/180*M_PI);
            float y = cy + r * sin(theta/180*M_PI);
            glVertex2f(x,y);
        }
    glEnd();

}

//base_bigger_marker
void draw_base_bigger_marker()
{
    glBegin(GL_LINES);  
        glColor3f(1.0f,1.0f,1.0f); 
        glVertex2f(0.0f,0.3f);
        glVertex2f(0.0f,0.24f);

    glEnd();
}

//base_smaller_marker

void draw_base_smaller_marker()
{
    glBegin(GL_LINES);  
        glColor3f(1.0f,1.0f,1.0f); 
        glVertex2f(0.0f,0.3f);
        glVertex2f(0.0f,0.28f);

    glEnd();
}

void draw_markers()
{
     //drawing bigger and smaller points
    glPushMatrix();
     
       glTranslatef(0.0,0.3,0.0);
      
       for(int i=0;i<12;i++)
       {
        if(i % 3 == 0)
          draw_base_bigger_marker();
        else
          draw_base_smaller_marker();  

        glRotatef(30,0,0,1);  
       }

    glPopMatrix();
}


//base_pendulum
void draw_base_pendulum()
{
    float cx,cy,r;
    //draw smaller circle
    glBegin(GL_POLYGON);    
        glColor3f(1.0f,1.0f,1.0f);  
        cx = 0.0;
        cy = 0.0;
        r = 0.035;
        for (float theta = 0; theta < 360; theta += 5) {
            float x = cx + r * cos(theta/180*M_PI);
            float y = cy + r * sin(theta/180*M_PI);
            glVertex2f(x,y);
        }
    glEnd();

 //L = 0.45
    glLineWidth(7);
    glBegin(GL_LINES);
    
      glVertex2f(0.0f,-0.0f);
      glVertex2f(0.0f,-0.45f);  
    
    glEnd();

    //draw larger circle

    glBegin(GL_POLYGON);    
        glColor3f(1.0f,1.0f,1.0f);  
        cx = 0.0;
        cy = -0.45;
        r = 0.08;
        for (float theta = 0; theta < 360; theta += 5) {
            float x = cx + r * cos(theta/180*M_PI);
            float y = cy + r * sin(theta/180*M_PI);
            glVertex2f(x,y);
        }
    glEnd();
    



}


void draw_pendulum()
{
    glPushMatrix();

        glTranslatef(0.0,-0.1,0.0);

        // if(rotation_angle_of_pendulum > 45 || rotation_angle_of_pendulum < -45)
        // {
        //     rotation_speed_of_pendulum = -rotation_speed_of_pendulum;
        // }
        // rotation_angle_of_pendulum = rotation_angle_of_pendulum + rotation_speed_of_pendulum;
       
        float theta_t = 45 * cos(((2*M_PI)/2)*t) ;
        t=t+0.005;
        glRotatef(theta_t,0,0,1);
        draw_base_pendulum();


    glPopMatrix();

}

// void moving_pendulum()
// {
//     glPushMatrix();
     
//       if(rotation_angle_of_pendulum > 45 || rotation_angle_of_pendulum < 45)
//       {
//         rotation_speed_of_pendulum = rotation_speed_of_pendulum;
//       }

//       rotation_angle_of_pendulum = rotation_angle_of_pendulum + rotation_speed_of_pendulum;
//       glRotatef(rotation_angle_of_pendulum,0,0,1);
//       draw_pendulum();
      

//     glPopMatrix();

// }

void timer_for_pendulum(int value)
{
   glutPostRedisplay(); 
   glutTimerFunc(5,timer_for_pendulum,0);
}




void draw_central_point()
{
    glPointSize(10);
    glBegin(GL_POINTS);  
        glColor3f(1.0f,1.0f,1.0f); 
        glVertex2f(0.0f,0.3f);     

    glEnd();
}

//base_hour_hand
void draw_base_hour_hand()
{
     glBegin(GL_POLYGON);  
        glColor3f(1.0f,1.0f,1.0f); 
        glVertex2f(-0.01f,0.0f);
        glVertex2f(0.01f,0.0f);
        glVertex2f(0.01f,0.09f);
        glVertex2f(0.00f,0.14f);
        glVertex2f(-0.01f,0.09f);

    glEnd();
}


//base_minute_hand
void draw_base_minute_hand()
{
     glBegin(GL_POLYGON);  
        glColor3f(1.0f,1.0f,1.0f); 
        glVertex2f(-0.007f,0.0f);
        glVertex2f(0.007f,0.0f);
        glVertex2f(0.007f,0.12f);
        glVertex2f(0.00f,0.18f);
        glVertex2f(-0.007f,0.12f);
         

    glEnd();
}

//base_second_hand

void draw_base_second_hand()
{
     glBegin(GL_POLYGON);  
        glColor3f(1.0f,1.0f,1.0f); 
        glVertex2f(-0.004f,0.0f);
        glVertex2f(0.004f,0.0f);
        glVertex2f(0.004f,0.16f);
        glVertex2f(0.00f,0.22f);
        glVertex2f(-0.004f,0.16f);
         

    glEnd();
}

void draw_second_hand()
{
    glPushMatrix();

      
      glTranslatef(0.0,0.3,0.0);
      glRotatef(-second_hand_rotation_angle,0,0,1);
      draw_base_second_hand();

    glPopMatrix();
}

void draw_minute_hand()
{
    glPushMatrix();

      
      glTranslatef(0.0,0.3,0.0);
      glRotatef(-minute_hand_rotation_angle,0,0,1);
      draw_base_minute_hand();

    glPopMatrix();
}

void draw_hour_hand()
{
    glPushMatrix();

      
      glTranslatef(0.0,0.3,0.0);
      glRotatef(-hour_hand_rotation_angle,0,0,1);
      draw_base_hour_hand();

    glPopMatrix();
}


void timer_for_clock_hands(int value)
{
   glutPostRedisplay();

   
   second_hand_rotation_angle = second_hand_rotation_angle + second_hand_moving_speed;
   if(second_hand_rotation_angle >= 360.0)
        second_hand_rotation_angle = 0;

   minute_hand_rotation_angle = minute_hand_rotation_angle + minute_hand_moving_speed;
   if(minute_hand_rotation_angle >= 360.0)
        minute_hand_rotation_angle = 0;  

   hour_hand_rotation_angle = hour_hand_rotation_angle + hour_hand_moving_speed;
   if(hour_hand_rotation_angle >= 360.0)
        hour_hand_rotation_angle = 0;        


   glutTimerFunc(1000,timer_for_clock_hands,0);

}

void sync_with_current_time()
{
    time_t currentTime = time(nullptr);

    // Convert the time_t to a struct tm
    struct tm* timeinfo = localtime(&currentTime);

    // Extract the individual components of the time
    int current_hours = timeinfo->tm_hour;
    int current_minutes = timeinfo->tm_min;
    int current_seconds = timeinfo->tm_sec;

    // Determine if it's AM or PM
    string meridian = (current_hours < 12) ? "AM" : "PM";

    // Convert hours to 12-hour format
    if (current_hours > 12) {
        current_hours -= 12;
    } else if (current_hours == 0) {
        current_hours = 12;
    }

    // Print the current time in 12-hour format
   cout << "Current time: " << current_hours << ":" << current_minutes << ":" << current_seconds << " " << meridian << endl; 

//    current_hours = 12;
//    current_minutes = 45;
//    current_seconds = 40; 

   //initialize timer_hands
   second_hand_rotation_angle = second_hand_moving_speed * current_seconds;
   minute_hand_rotation_angle = minute_hand_moving_speed * (current_minutes*60.0+current_seconds);
   hour_hand_rotation_angle =  hour_hand_moving_speed * (current_hours*3600.0+current_minutes*60.0+current_seconds);



   if(second_hand_rotation_angle > 360)
      second_hand_rotation_angle = second_hand_rotation_angle - 360;
   if(minute_hand_rotation_angle > 360)
      minute_hand_rotation_angle = minute_hand_rotation_angle - 360;   
   if(hour_hand_rotation_angle > 360)
      hour_hand_rotation_angle = hour_hand_rotation_angle - 360;  

 //cout << "Current angles: " << hour_hand_rotation_angle << ":" << minute_hand_rotation_angle << ":" << second_hand_rotation_angle << " " << meridian << endl; 


}



void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
    glLoadIdentity();               // Reset the model-view matrix
    //reseting the line_width
    glLineWidth(1);


    draw_clock_body();

    draw_outer_circle();

    draw_inner_circle();

    draw_markers();

    draw_central_point();

    //Moving Pendulum 
    draw_pendulum();

    //moving clock hands

    draw_second_hand();
    draw_minute_hand();
    draw_hour_hand();



    glFlush();


}


int main(int argc, char** argv) {
    glutInit(&argc, argv);                  // Initialize GLUT
    glutInitWindowSize(640, 640);           // Set the window's initial width & height
    glutInitWindowPosition(50, 50);         // Position the window's initial top-left corner
    glutCreateWindow("Analog Clock");  // Create a window with the given title
    
    sync_with_current_time();
    glutDisplayFunc(display);               // Register display callback handler for window re-paint
    glutTimerFunc(0,timer_for_pendulum,0);
    glutTimerFunc(0,timer_for_clock_hands,0);


    glutMainLoop();                         // Enter the infinitely event-processing loop
    return 0;
}