#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include "bitmap_image.hpp"
using namespace std;




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

        double length()
        {
            return sqrt(x*x+y*y+z*z);
        }


        void normalize()
        {
            double l = length();
            x = x/l;
            y = y/l;
            z = z/l;

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

        Point operator -()  
        {
            return Point(-x,-y,-z);
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

        bool operator==(Point point)
        {
            return (x == point.x && y == point.y && z == point.z);
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


extern Point pos;
extern Point l;
extern Point r;
extern Point u;
extern double pi;
extern int level_of_recursion;
extern double lambert;
extern double phong;
extern bool texture_enabled;
extern bitmap_image texture_white;
extern bitmap_image texture_black;
extern 



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

double angle_between_two_vector(Point vec1,Point vec2 )
{
    double dot = dot_product(vec1,vec2);
    double len1 = vec1.length();
    double len2 = vec2.length();

    double cos_theta = dot/(len1*len2);

    return acos(cos_theta) * (180.0/pi);
}


class Color{
    public:
        double r,g,b;
        Color()
        {
            r = g = b = 0.0;
        }

        Color(double r, double g, double b) 
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        void print()
        {
            cout << "r: " << r << " g: " << g << " b: " << b << endl;
        }
};



class Coeefficient{
    public:
        double ambient;
        double specular;
        double diffuse;
        double reflection;

        Coeefficient()
        {
            ambient = 0;
            specular = 0;
            diffuse = 0;
            reflection = 0;
        }

        Coeefficient(double a, double d, double s, double r)
        {
            ambient = a;
            diffuse = d;
            specular = s;
            reflection = r;
        }

        void print()
        {
            cout << "Ambient: " << ambient << " Diffuse: " << diffuse << " Specular: " << specular << " Reflection: " << reflection << endl;
        }

};

class Ray{

    public:
        Point origin,dir;
        
        Ray(Point origin, Point dir){
            this->origin = origin;
            dir.normalize();
            this->dir = dir;
        }


        void print()
        {
            cout << "Origin: ";
            origin.print();
            cout << "Direction: ";
            dir.print();
        }


  
};

class Normal_Light
{
    public:
        Point light_source;
        double falloff_parameter;
        Color color;

        Normal_Light(Point light_source, double falloff_parameter,Color color)
        {
            this->light_source = light_source;
            this->falloff_parameter = falloff_parameter;
            this->color = color;
        }

        void draw()
        {
             //drawing a small sphere for point source
            glColor3f(color.r,color.g,color.b);
            glPushMatrix();
            glTranslatef(light_source.x,light_source.y,light_source.z);
            glutSolidSphere(5,100,100);
            glPopMatrix();
           
        }

        void print()
        {
            cout << "Normal_Light Source: "<<endl;
            cout << "---------------------" << endl;

            light_source.print();
            cout << "Falloff Parameter: " << falloff_parameter << endl;
            cout << "Color: ";
            color.print();
        }
};

class Spot_Light
{
    public:
        Point light_source;
        double falloff_parameter;
        Color color;
        Point direction;
        double cutoff_angle;

        Spot_Light(Point light_source, double falloff_parameter,Color color, Point direction, double cutoff_angle)
        {
            this->light_source = light_source;
            this->falloff_parameter = falloff_parameter;
            this->direction = direction;
            this->cutoff_angle = cutoff_angle;
            this->color = color;
        }

        void draw()
        {
             //Drawing small cube for spot source Cube;
            glColor3f(color.r,color.g,color.b);
            glPushMatrix();
            glTranslatef(light_source.x,light_source.y,light_source.z);
            glutSolidCube(5);
            glPopMatrix();
           
        }
    

        void print()
        {
            cout << "Spot_Light Source: "<< endl;
            cout << "-------------------" << endl;
            light_source.print();
            cout << "Direction: ";
            direction.print();
            cout << "Falloff Parameter: " << falloff_parameter << endl;
            cout << "Color: ";
            color.print();
            cout << "Cutoff Angle: " << cutoff_angle << endl;
        }
};


class Object;
extern vector <Object*> objects;
extern vector <Normal_Light> normal_light_sources;
extern vector <Spot_Light> spot_light_sources;





class Object
{
    public:
        Point reference_point; // should have x, y, z
        double height, width, length;
        Color color;
        Coeefficient coeefficient; // ambient, diffuse,specular, reflection coefficients
        int shine; // exponent term of specular component
        string object_type;

        Object()
        {
            reference_point = Point(0,0,0);
            height = 0;
            width = 0;
            length = 0;
            shine = 0;
        }
        virtual void draw()=0;
        virtual void print()=0;
        virtual Ray get_normal(Point intersection_point, Ray incidentRay) = 0;


        virtual Color get_color(Point point){
            return Color(this->color.r, this->color.g, this->color.b);
        }

        //this function "initial_intersect" will just find the intersecting point with closest object. It will not calculate the color of the intersecting point
        virtual double initial_intersect(Ray *r, Color *color, int level) = 0;

        virtual double intersect(Ray *ray, Color *color, int level){
 
            double t = initial_intersect(ray, color, level);


            if(t < 0) return -1;
            if(level == 0) return t;

            // find intersection point and it's color
            Point intersectionPoint = ray->origin + ray->dir*t;
            // if(object_type == "PYRAMID" && level == 1)
            //     intersectionPoint.print();
            Color colorAtIntersection = get_color(intersectionPoint);
           // cout << "Color at intersection: ";
            //colorAtIntersection.print();
            // color->r = colorAtIntersection.r;
            // color->g = colorAtIntersection.g;
            // color->b = colorAtIntersection.b;
            //cout << "color_inside_NecLib: " ;
            //color->print();

           // update color with ambience (thing will become dimmer)
            color->r = colorAtIntersection.r * coeefficient.ambient;
            color->g = colorAtIntersection.g * coeefficient.ambient;
            color->b = colorAtIntersection.b * coeefficient.ambient;



            for(int i = 0; i < normal_light_sources.size(); i++){

                Point lightPosition = normal_light_sources[i].light_source;
                Point lightDirection = intersectionPoint - lightPosition;
                lightDirection.normalize();
                
                // cast incident ray, from light position to intersection point
                Ray lightRay = Ray(lightPosition, lightDirection);

                //if(normal.dir == Point(0,0,0)) {cout << "wrong in normal light" << endl;}


                 //check if incedent ray is not obstructed by any other object
                 
                
                double t2 = (intersectionPoint - lightPosition).length();
                if(t2 < 1e-5) continue; //checking if the object is attached with light source or not

                bool obscured = false;

                for(Object *obj : objects){
                    double t3 = obj->initial_intersect(&lightRay,color, 0);
                    if(t3 > 0 && t3 + 1e-5 < t2){
                        obscured = true;
                        break;
                    }
                }
                
                // if not obscured, calculate diffuse and specular components

                if(!obscured){

                    Point toSource = -lightRay.dir;
                    toSource.normalize();        
                    // calculate normal at intersectionPoint
                    Ray normal = get_normal(intersectionPoint,lightRay);
                    double distance = (intersectionPoint - lightPosition).length();
                    double scaling_factor = exp(-normal_light_sources[i].falloff_parameter*distance*distance);
                    lambert = max(0.0,dot_product(toSource,normal.dir))*scaling_factor;

                    Ray reflection = Ray(intersectionPoint,ray->dir-normal.dir*2*(dot_product(ray->dir,normal.dir)));

                    phong = pow(max(0.0,dot_product(toSource,reflection.dir)),shine)*scaling_factor;  
                    // if(this->object_type == "SPHERE" && this->reference_point == Point(-20,-20,20))
                    // {
                    //     //this->print();
                    //     //cout << "normallambert: " << lambert << endl;
                    //     //cout << "normal phong: " << phong << endl;
                    //     //cout << endl;
                    // }  


                    if((object_type == "CHECKERBOARD") && texture_enabled == true)
                    {
                        color->r += normal_light_sources[i].color.r * coeefficient.diffuse * lambert * colorAtIntersection.r;

                        color->g += normal_light_sources[i].color.g *coeefficient.diffuse  * lambert * colorAtIntersection.g;

                        color->b += normal_light_sources[i].color.b * coeefficient.diffuse  * lambert * colorAtIntersection.b;
                    }

                   else{
                        color->r += normal_light_sources[i].color.r * coeefficient.diffuse * lambert * colorAtIntersection.r;
                        color->r += normal_light_sources[i].color.r * coeefficient.specular  *phong * colorAtIntersection.r;

                        color->g += normal_light_sources[i].color.g *coeefficient.diffuse  * lambert * colorAtIntersection.g;
                        color->g += normal_light_sources[i].color.g *coeefficient.specular  * phong * colorAtIntersection.g;

                        color->b += normal_light_sources[i].color.b * coeefficient.diffuse  * lambert * colorAtIntersection.b;
                        color->b += normal_light_sources[i].color.b * coeefficient.specular  * phong * colorAtIntersection.b;
                   }
                
                }
            }

            //calculating color for all normal lights

            //cout << "spot light size: " << spot_light_sources.size() << endl;


             for(int i = 0; i < spot_light_sources.size(); i++){

                Point lightPosition = spot_light_sources[i].light_source;
                Point lightDirection = intersectionPoint - lightPosition;
                lightDirection.normalize();
                Point spot_light_direction = spot_light_sources[i].direction - lightPosition;
                spot_light_direction.normalize();

                //spot_light_sources[i].print();

                double dot = dot_product(lightDirection,spot_light_direction);
                double angle = acos(dot/(lightDirection.length()*spot_light_direction.length())) * (180.0/pi);

                 // cout << "angle: " << fabs(angle) << endl;
                //cout << "cutoff angle: " << spot_light_sources[i].cutoff_angle << endl;

              
                if(fabs(angle)<spot_light_sources[i].cutoff_angle){

                  //cout << "angle: " << fabs(angle) << endl;
                 // cout << "cutoff angle: " << spot_light_sources[i].cutoff_angle << endl;


                    Ray lightRay = Ray(lightPosition, lightDirection); 
                                       
                    double t2 = (intersectionPoint - lightPosition).length();
                    if(t2 < 1e-5) continue;
                    
                    bool obscured = false;
                    
                    for(Object *obj : objects){
                        double t3 = obj->initial_intersect(&lightRay,color, 0);
                        if(t3 > 0 && t3 + 1e-5 < t2){
                            obscured = true;
                            break;
                        }
                    }

                    //cout << "spotlight" << endl;
                    
                    if(!obscured){

                        Point toSource = -lightRay.dir;
                        toSource.normalize();        
                        // calculate normal at intersectionPoint
                        Ray normal = get_normal(intersectionPoint,lightRay);
                        double distance = (intersectionPoint - lightPosition).length();
                        double scaling_factor = exp(-normal_light_sources[i].falloff_parameter*distance*distance);
                        lambert = max(0.0,dot_product(toSource,normal.dir))*scaling_factor;

                        Ray reflection = Ray(intersectionPoint, ray->dir-normal.dir*2*(dot_product(ray->dir,normal.dir)));

                        phong = pow(max(0.0,dot_product(toSource,reflection.dir)),shine)*scaling_factor; 

                        if(this->object_type == "SPHERE" && this->reference_point == Point(20,20,20))
                        {
                           // this->print();
                          // cout << "spot lambert: " << lambert << endl;
                           // cout << "spot phong: " << phong << endl;
                            //cout << endl;
                        }  

                    if((object_type == "CHECKERBOARD") && texture_enabled == true)
                    {
                        color->r += normal_light_sources[i].color.r * coeefficient.diffuse * lambert * colorAtIntersection.r;

                        color->g += normal_light_sources[i].color.g *coeefficient.diffuse  * lambert * colorAtIntersection.g;

                        color->b += normal_light_sources[i].color.b * coeefficient.diffuse  * lambert * colorAtIntersection.b;
                    }

                   else{
                        color->r += normal_light_sources[i].color.r * coeefficient.diffuse * lambert * colorAtIntersection.r;
                        color->r += normal_light_sources[i].color.r * coeefficient.specular  *phong * colorAtIntersection.r;

                        color->g += normal_light_sources[i].color.g *coeefficient.diffuse  * lambert * colorAtIntersection.g;
                        color->g += normal_light_sources[i].color.g *coeefficient.specular  * phong * colorAtIntersection.g;

                        color->b += normal_light_sources[i].color.b * coeefficient.diffuse  * lambert * colorAtIntersection.b;
                        color->b += normal_light_sources[i].color.b * coeefficient.specular  * phong * colorAtIntersection.b;
                   }
                
                        
                    }
                }
            }


              if(level <= level_of_recursion){
                // if(level > 1) cout << "Recursion level " << level << endl;

                // find normal at intersectionPoint
                Ray ray_object = Ray(ray->origin,ray->dir);
                Ray normal = get_normal(intersectionPoint,ray_object);
               // if(normal.dir == Point(0,0,0)) {cout << "wrong in reflection" << endl;}


                // find reflected ray
                Ray reflectionRay = Ray(intersectionPoint,ray->dir -normal.dir*2*(dot_product(ray->dir,normal.dir)));

                
                 /* slightly forward from the point 
                 * (by moving the start a little bit towards the reflection direction)
                 * to avoid self intersection 
                 */
                reflectionRay.origin = reflectionRay.origin + reflectionRay.dir* 1e-5 ;
                

                // find nearest intersection object and do recursive call

                int nearestObjectIndex = -1;
                double t = -1,tMin = 1e9;

                for(int k=0;k<(int)objects.size();k++)
                {
                    t = objects[k]->intersect(&reflectionRay,color, 0);
                    if(t> 0 && t<tMin)
                        tMin = t , nearestObjectIndex = k;
                }

                if(nearestObjectIndex != -1)
                {
                    // cout<<"Object "<<nearestObjectIndex<<" intersected"<<endl;

                    Color colorTemp(0,0,0); // refelction color
                    // cout<<"Before Color "<<color.r<<" "<<color.g<<" "<<color.b<<endl;
                    double t = objects[nearestObjectIndex]->intersect(&reflectionRay,&colorTemp, level+1);

                    // colorTemp will be updated while in the subsequent call
                    // update color using the impact of reflection
                    
                    color->r += colorTemp.r * coeefficient.reflection;
                    color->g += colorTemp.g * coeefficient.reflection;
                    color->b += colorTemp.b * coeefficient.reflection;

                }
                
                
             
            }



       
            return t; 
       }


        void setColor(Color color)
        {
            this->color = color;
        }
        void setShine(int shine)
        {
            this->shine = shine;
        }
        void setCoEfficients(Coeefficient coeefficient){
            this->coeefficient = coeefficient;
        }

};




class Sphere: public Object
{
    public:
        Sphere(Point center, double radius, Color color,Coeefficient coeefficient, int shininess)
        {
            reference_point = center;
            length = radius;
            width = radius;
            height = radius;
            this->color = color;
            this->coeefficient = coeefficient;
            this->shine = shininess;
            object_type = "SPHERE";
        }

        Ray get_normal(Point intersection_point, Ray incidentRay)
        {
            Point normal_vector = intersection_point - reference_point;
            Ray normal_ray = Ray(intersection_point,normal_vector);
            return normal_ray;
        }

        double initial_intersect(Ray *ray, Color *color, int level)
        {
            //here the eqn of sphere (p-center).(p-center) = r*r

            //so after converting the above vector equation to a quatric equation of t(at^2 + bt+c = 0) ,we got the following a,b,c value

            //ray->print();
            //print();

            double a = dot_product(ray->dir,ray->dir);
            double b = 2*dot_product(ray->dir,ray->origin) - 2*dot_product(ray->dir,reference_point); //center = reference_point
            double c = dot_product(ray->origin,ray->origin) - 2*dot_product(ray->origin,reference_point) + dot_product(reference_point,reference_point) - length*length;

            double D = b*b - 4*a*c;
           // cout << "D: " << D << endl;

            if(D < 0)
                return -1.0;
            else
            {
                double t1 = (-b + sqrt(D))/(2*a);
                double t2 = (-b - sqrt(D))/(2*a);

                if(t1 < 0 && t2 < 0)
                    return -1.0;
                else if(t1 < 0)
                    return t2;
                else if(t2 < 0)
                    return t1;
                else
                    return min(t1,t2);
            }

        }



        void draw()
        {
            glColor3f(color.r,color.g,color.b);
            glPushMatrix();
            glTranslatef(reference_point.x,reference_point.y,reference_point.z);
            glutSolidSphere(length,100,100);
            glPopMatrix();
        }

        void print()
        {
            cout << "Sphere" << endl;
            cout << "-------" << endl;
            cout << "Center: ";
            reference_point.print();
            cout << "Radius: " << length << endl;
            cout << "Color: ";
            color.print();
            cout << "Coeefficient: ";
            coeefficient.print();
            cout << "Shine: " << shine << endl;
        }
};

class Pyramid: public Object
{
    public:
        Pyramid(Point lowest_point_coordinate, double width, double height, Color color,Coeefficient coeefficient, int shininess)
        {
            reference_point = lowest_point_coordinate;
            this->length = length;
            this->width = width;
            this->height = height;
            this->color = color;
            this->coeefficient = coeefficient;
            this->shine = shininess;
            object_type = "PYRAMID";

        }

        Point is_on_base(Point point,Ray incidentRay)
        {
            if(point.z >= reference_point.z- 1e-5 && point.z <= reference_point.z + 1e-5)
                return Point(0,0,-1);
            else{
                //cout << "on_base" << endl;
                return Point(0,0,0);
            }
           
        }

        Point is_on_front_face(Point point,Ray incidentRay)
        {
            
            Point A = Point(reference_point.x,reference_point.y,reference_point.z);
            Point B = Point(reference_point.x+width,reference_point.y,reference_point.z);
            Point C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);

            Point normal_vector = cross_product(B-A,C-A);
            //the eqn of plane n.p + D = 0
            double D = -dot_product(normal_vector,A);
             
            if(dot_product(normal_vector,point) + D >= 0 - 1e-5 && dot_product(normal_vector,point) + D <= 0 + 1e-5)
                //return normal_vector;
                if(dot_product(normal_vector,incidentRay.dir) > 0)
                    return normal_vector;
                else
                    return -normal_vector;
            else
                {// cout << "on_front_face" << endl;
                 return  Point(0,0,0);       }

        }


        Point is_on_left_face(Point point,Ray incidentRay)
        {
            
           Point A = Point(reference_point.x,reference_point.y,reference_point.z);
           Point B = Point(reference_point.x,reference_point.y+width,reference_point.z);
           Point C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);

            Point normal_vector = cross_product(B-A,C-A);
            //the eqn of plane n.p + D = 0
            double D = -dot_product(normal_vector,A);
             
            if(dot_product(normal_vector,point) + D >= 0 - 1e-5 && dot_product(normal_vector,point) + D <= 0 + 1e-5)
               // return normal_vector;
                if(dot_product(normal_vector,incidentRay.dir) > 0)
                    return normal_vector;
                else
                    return -normal_vector;
            else
                {// cout << "on_left_face" << endl;
                return  Point(0,0,0);}
        }

        Point is_on_right_face(Point point,Ray incidentRay)
        {
            
           Point A = Point(reference_point.x+width,reference_point.y,reference_point.z);
           Point B = Point(reference_point.x+width,reference_point.y+width,reference_point.z);
           Point C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);

            Point normal_vector = cross_product(B-A,C-A);
            //the eqn of plane n.p + D = 0
            double D = -dot_product(normal_vector,A);
             
            if(dot_product(normal_vector,point) + D >= 0 - 1e-5 && dot_product(normal_vector,point) + D <= 0 + 1e-5)
                //return normal_vector;
                 if(dot_product(normal_vector,incidentRay.dir) > 0)
                    return normal_vector;
                else
                    return  -normal_vector;
            else
                { //cout << "on_right_face" << endl;
                return  Point(0,0,0);}
        }

        Point is_on_back_face(Point point,Ray incidentRay)
        {
                
              Point  A = Point(reference_point.x,reference_point.y+width,reference_point.z);
              Point  B = Point(reference_point.x+width,reference_point.y+width,reference_point.z);
              Point  C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);
    
                Point normal_vector = cross_product(B-A,C-A);
                //the eqn of plane n.p + D = 0
                double D = -dot_product(normal_vector,A);
                
                if(dot_product(normal_vector,point) + D >= 0 - 1e-5 && dot_product(normal_vector,point) + D <= 0 + 1e-5)
                    //return normal_vector;
                    if(dot_product(normal_vector,incidentRay.dir) > 0)
                        return normal_vector;
                    else
                        return -normal_vector;
                else
                    { //cout << "on_back_face" << endl;
                    return  Point(0,0,0);}
        }

         
        Ray get_normal(Point intersection_point, Ray incidentRay)
        {
            Point nullpoint(0,0,0);
            if(is_on_base(intersection_point,incidentRay) != nullpoint)
                return Ray(intersection_point,is_on_base(intersection_point,incidentRay));
            else if(is_on_front_face(intersection_point,incidentRay) != nullpoint)
                return Ray(intersection_point,is_on_front_face(intersection_point,incidentRay));
            else if(is_on_left_face(intersection_point,incidentRay) != nullpoint)
                return Ray(intersection_point,is_on_left_face(intersection_point,incidentRay));
            else if(is_on_right_face(intersection_point,incidentRay) != nullpoint)
                return Ray(intersection_point,is_on_right_face(intersection_point,incidentRay));
            else if(is_on_back_face(intersection_point,incidentRay) != nullpoint)
                return Ray(intersection_point,is_on_back_face(intersection_point,incidentRay));
            //reference_point.print();    
            intersection_point.print();
            // cout << intersection_point.z << " " << reference_point.z << endl;
            // double z1 = intersection_point.z;
            // double z2 = reference_point.z;
            // cout << z1 << "==" << z2 <<": "<< (z1 == z2) << endl;
            // if((double)intersection_point.z == (double)reference_point.z)
            //      is_on_base(intersection_point,incidentRay).print();
            // printf("\n");

            // Point p1(1,4,8);
            // Point p2(1,4,8);
            // cout << p1 != p2    
            return Ray(Point(0,0,0),Point(0,0,0));    
        }

        double determinant(double matrix[3][3]){
                double v1 = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
                double v2 = matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
                double v3 = matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
                return v1 - v2 + v3;
            }


         double get_t_for_base_surface_ray_intersection(Ray *ray,Point a,Point b,Point c)
         {
  
            Point normal_vector_of_bottom_face = cross_product(b-a,c-a);
           // the eqn of plane n.p + D = 0
            double D = -dot_product(normal_vector_of_bottom_face,a);
            //now we will find the value of t from the eqn of ray and eqn of plane
            double t = -(D + dot_product(normal_vector_of_bottom_face,ray->origin))/dot_product(normal_vector_of_bottom_face,ray->dir);

            return t;

         }



         double get_t_for_triangular_surface_ray_intersection(Ray *ray,Point a,Point b,Point c)
        {

            //using the concept of Barycentric

            double A_Matrix[3][3] {
				{a.x - b.x, a.x - c.x, ray->dir.x},
				{a.y - b.y, a.y - c.y, ray->dir.y},
				{a.z - b.z, a.z - c.z, ray->dir.z}
			};


            double beta_Matrix[3][3] = {
				{a.x - ray->origin.x, a.x - c.x, ray->dir.x},
				{a.y - ray->origin.y, a.y - c.y, ray->dir.y},
				{a.z - ray->origin.z, a.z - c.z, ray->dir.z}
			};
			double gamma_Matrix[3][3] = {
				{a.x - b.x, a.x - ray->origin.x, ray->dir.x},
				{a.y - b.y, a.y - ray->origin.y, ray->dir.y},
				{a.z - b.z, a.z - ray->origin.z, ray->dir.z}
			};
			double t_Matrix[3][3] = {
				{a.x - b.x, a.x - c.x, a.x - ray->origin.x},
				{a.y - b.y, a.y - c.y, a.y - ray->origin.y},
				{a.z - b.z, a.z - c.z, a.z - ray->origin.z}
			};
			
            double A_det = determinant(A_Matrix);
            double beta = determinant(beta_Matrix) / A_det;
            double gamma = determinant(gamma_Matrix) / A_det;
            double t = determinant(t_Matrix) / A_det;
            if (beta + gamma < 1 && beta > 0 && gamma > 0 && t > 0)
              return t;
            else
              return -1;



        }

 


       
        double initial_intersect(Ray *ray, Color *color, int level)
        {
            //here i will try to find the t value for each surface of the pyramid and then take the minimum of them

            double minimum_t = -1.0;

            //base surface of pyramid
            //------------
            //vertices of base surface are
            //(reference_point.x,reference_point.y,reference_point.z)
            //(reference_point.x+width,reference_point.y,reference_point.z)
            //(reference_point.x+width,reference_point.y+width,reference_point.z)
            //(reference_point.x,reference_point.y+width,reference_point.z)
            

            Point A = Point(reference_point.x,reference_point.y,reference_point.z);
            Point B = Point(reference_point.x+width,reference_point.y,reference_point.z);
            Point C = Point(reference_point.x,reference_point.y+width,reference_point.z);
            
            double t = get_t_for_base_surface_ray_intersection(ray,A,B,C);
           
           if(t>0)
           {
                //checking if the intersection point is inside the base or not
                
                Point intersection_point = ray->origin + ray->dir*t;
                //the base surface of the pyramid will always parallel to the xy plane
                if(intersection_point.x >= reference_point.x && intersection_point.x <= reference_point.x+width && intersection_point.y >= reference_point.y && intersection_point.y <= reference_point.y+width)
                {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
                }
           }

            
            //front triangular surface of pyramid
            //------------
            //vertices of front surface are
            //(reference_point.x,reference_point.y,reference_point.z)
            //(reference_point.x+width,reference_point.y,reference_point.z)
            //(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height)

            A = Point(reference_point.x,reference_point.y,reference_point.z);
            B = Point(reference_point.x+width,reference_point.y,reference_point.z);
            C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);
            
            t = get_t_for_triangular_surface_ray_intersection(ray,A,B,C);
            if(t > 0)
            {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
            }


            //left surface of pyramid
            //------------
            //vertices of left surface are
            //(reference_point.x,reference_point.y,reference_point.z)
            //(reference_point.x,reference_point.y+width,reference_point.z)
            //(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height)

            A = Point(reference_point.x,reference_point.y,reference_point.z);
            B = Point(reference_point.x,reference_point.y+width,reference_point.z);
            C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);

            t = get_t_for_triangular_surface_ray_intersection(ray,A,B,C);
            if(t > 0)
            {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);              
                
            }


            //right surface of pyramid
            //------------
            //vertices of right surface are
            //(reference_point.x+width,reference_point.y,reference_point.z)
            //(reference_point.x+width,reference_point.y+width,reference_point.z)
            //(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height)

            A = Point(reference_point.x+width,reference_point.y,reference_point.z);
            B = Point(reference_point.x+width,reference_point.y+width,reference_point.z);
            C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);

            t = get_t_for_triangular_surface_ray_intersection(ray,A,B,C);
            if(t > 0)

            { 
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
            }


            //back surface of pyramid
            //------------
            //vertices of back surface are
            //(reference_point.x,reference_point.y+width,reference_point.z)
            //(reference_point.x+width,reference_point.y+width,reference_point.z)
            //(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height)

            A = Point(reference_point.x,reference_point.y+width,reference_point.z);
            B = Point(reference_point.x+width,reference_point.y+width,reference_point.z);
            C = Point(reference_point.x+width/2,reference_point.y+width/2,reference_point.z+height);

            t = get_t_for_triangular_surface_ray_intersection(ray,A,B,C);
            if(t > 0)
            {
                   if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
            }


            return minimum_t;




        }
    
        void draw()
        {
            //cout << "Drawing Pyramid" << endl;
            glColor3f(color.r,color.g,color.b);

            //drawing base of the pyramid
            glBegin(GL_QUADS);
                {
                    glVertex3f(reference_point.x ,reference_point.y ,reference_point.z);
                    glVertex3f(reference_point.x + width,reference_point.y,reference_point.z);
                    glVertex3f(reference_point.x + width , reference_point.y + width ,reference_point.z);
                    glVertex3f(reference_point.x , reference_point.y + width ,reference_point.z);
                }
            glEnd();

            //drawing the four triangles
            glBegin(GL_TRIANGLES);
                {
                    glVertex3f(reference_point.x ,reference_point.y ,reference_point.z);
                    glVertex3f(reference_point.x + width,reference_point.y,reference_point.z);
                    glVertex3f(reference_point.x + width/2 , reference_point.y + width/2 ,reference_point.z + height);
                }
            glEnd();

            glBegin(GL_TRIANGLES);
                {
                    glVertex3f(reference_point.x + width ,reference_point.y,reference_point.z);
                    glVertex3f(reference_point.x + width,reference_point.y + width,reference_point.z);
                    glVertex3f(reference_point.x + width/2 , reference_point.y + width/2 ,reference_point.z + height);
                }
            glEnd();

            glBegin(GL_TRIANGLES);
                {   
                    glVertex3f(reference_point.x + width,reference_point.y + width,reference_point.z);
                    glVertex3f(reference_point.x  ,reference_point.y + width,reference_point.z);
                    glVertex3f(reference_point.x + width/2 , reference_point.y + width/2 ,reference_point.z + height);
                }    
            glEnd();    


            glBegin(GL_TRIANGLES);
                {
                    glVertex3f(reference_point.x ,reference_point.y + width,reference_point.z);
                    glVertex3f(reference_point.x ,reference_point.y ,reference_point.z);
                    glVertex3f(reference_point.x + width/2 , reference_point.y + width/2 ,reference_point.z + height);
                }
            glEnd();

           

            
        }

        void print()
        {
            cout << "Pyramid" << endl;
            cout << "-------" << endl;
            cout << "Lowest Point: ";
            reference_point.print();
            cout << "Width: " << width << endl;
            cout << "Height: " << height << endl;
            cout << "Length: " << length << endl;
            cout << "Color: ";
            color.print();
            cout << "Coeefficient: ";
            coeefficient.print();
            cout << "Shine: " << shine << endl;
        }
};

class Cube: public Object
{
    public:
        Cube(Point bottom_lower_left_point, double side, Color color,Coeefficient coeefficient, int shininess)
        {
            reference_point = bottom_lower_left_point;
            this->length = side;
            this->width = side;
            this->height = side;
            this->color = color;
            this->coeefficient = coeefficient;
            this->shine = shininess;
            object_type = "CUBE";

        }

        
         Ray get_normal(Point intersection_point,Ray incidentRay)
        {
            //if the intersection point is on the bottom face of the cube
            if(intersection_point.z >= reference_point.z - 1e-5 && intersection_point.z <= reference_point.z + 1e-5 )
            {
                Point normal_vector = Point(0,0,-1);
                Ray normal_ray = Ray(intersection_point,normal_vector);
                return normal_ray;
            }

            //if the intersection point is on the top face of the cube
            else if(intersection_point.z >= reference_point.z + height - 1e-5 && intersection_point.z <= reference_point.z + height + 1e-5)
            {
                Point normal_vector = Point(0,0,1);
                Ray normal_ray = Ray(intersection_point,normal_vector);
                return normal_ray;
            }

            //if the intersection point is on the left face of the cube
            else if(intersection_point.y >= reference_point.y - 1e-5 && intersection_point.y <= reference_point.y + 1e-5)
            {
                Point normal_vector = Point(0,-1,0);
                Ray normal_ray = Ray(intersection_point,normal_vector);
                return normal_ray;
            }

            //if the intersection point is on the right face of the cube
            else if(intersection_point.y >= reference_point.y + width - 1e-5 && intersection_point.y <= reference_point.y + width + 1e-5)
            {
                Point normal_vector = Point(0,1,0);
                Ray normal_ray = Ray(intersection_point,normal_vector);
                return normal_ray;
            }

            //if the intersection point is on the front face of the cube
            else if(intersection_point.x >= reference_point.x + length - 1e-5 && intersection_point.x <= reference_point.x + length + 1e-5)
            {
                Point normal_vector = Point(1,0,0);
                Ray normal_ray = Ray(intersection_point,normal_vector);
                return normal_ray;
            }

            //if the intersection point is on the back face of the cube
            else if(intersection_point.x >= reference_point.x - 1e-5 && intersection_point.x <= reference_point.x + 1e-5)
            {
                Point normal_vector = Point(-1,0,0);
                Ray normal_ray = Ray(intersection_point,normal_vector);
                return normal_ray;
            }

            else
                intersection_point.print();
                return Ray(Point(0,0,0),Point(0,0,0));

           
            
        }


        double get_t_for_surface_ray_intersection(Ray *ray,Point A,Point B,Point C)
        {
            Point normal_vector = cross_product(B-A,C-A);
            //the eqn of plan n.p + D = 0
            double D = -dot_product(normal_vector,A);
            //now we will find the value of t from the eqn of ray and eqn of plane
            double t = -(D + dot_product(normal_vector,ray->origin))/dot_product(normal_vector,ray->dir);

            return t;

        }



        double initial_intersect(Ray *ray, Color *color, int level)
        {
            //here i will try to find the intersector for each plane of the cube and then take the minimum of them

            double minimum_t = -1.0;

            //Bottom face(along -z axis)
            //------------
            //vertices of bottom face are 
            //(reference_point.x,reference_point.y,reference_point.z)
            //(reference_point.x+length,reference_point.y,reference_point.z)
            //(reference_point.x+length,reference_point.y+width,reference_point.z)
            //(reference_point.x,reference_point.y+width,reference_point.z)
            Point A = Point(reference_point.x,reference_point.y,reference_point.z);
            Point B = Point(reference_point.x,reference_point.y+width,reference_point.z);
            Point C = Point(reference_point.x+length,reference_point.y,reference_point.z);
            
            //double t = get_t_for_surface_ray_intersection(ray,A,B,C);
            Point normal_vector = Point(0,0,-1);
             double D = -dot_product(normal_vector,A);
            //now we will find the value of t from the eqn of ray and eqn of plane
             double t = -(D + dot_product(normal_vector,ray->origin))/dot_product(normal_vector,ray->dir);

             if(t>0)
             {
                //ckecking whether the intersection_point is on the bottom face or not
                Point intersection_point = ray->origin + ray->dir*t;
                if(intersection_point.x >= reference_point.x && intersection_point.x <= reference_point.x + length && intersection_point.y >= reference_point.y && intersection_point.y <= reference_point.y + width)
                {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
                }
             }



            
            // top face(along z axis)
            // ------------
            // vertices of top face are
            // (reference_point.x,reference_point.y,reference_point.z+height)
            // (reference_point.x+length,reference_point.y,reference_point.z+height)
            // (reference_point.x+length,reference_point.y+width,reference_point.z+height)
            // (reference_point.x,reference_point.y+width,reference_point.z+height)

            A = Point(reference_point.x,reference_point.y,reference_point.z+height);
            B = Point(reference_point.x+length,reference_point.y,reference_point.z+height);
            C = Point(reference_point.x,reference_point.y+width,reference_point.z+height);

           // t = get_t_for_surface_ray_intersection(ray,A,B,C);

             normal_vector = Point(0,0,1);
             D = -dot_product(normal_vector,A);
            //now we will find the value of t from the eqn of ray and eqn of plane
             t = -(D + dot_product(normal_vector,ray->origin))/dot_product(normal_vector,ray->dir);


             if(t>0)
             {
                //ckecking whether the intersection_point is on the top face or not
                Point intersection_point = ray->origin + ray->dir*t;
                if(intersection_point.x >= reference_point.x && intersection_point.x <= reference_point.x + length && intersection_point.y >= reference_point.y && intersection_point.y <= reference_point.y + width)
                {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
                }
             }


            //left face (along -x axis)
            //------------
            //vertices of left face are
            //(reference_point.x,reference_point.y,reference_point.z)
            //(reference_point.x,reference_point.y,reference_point.z+height)
            //(reference_point.x,reference_point.y+width,reference_point.z+height)
            //(reference_point.x,reference_point.y+width,reference_point.z)   


            A = Point(reference_point.x,reference_point.y,reference_point.z);
            B = Point(reference_point.x,reference_point.y+width,reference_point.z);
            C = Point(reference_point.x,reference_point.y,reference_point.z+height);

            //t = get_t_for_surface_ray_intersection(ray,A,B,C);

             normal_vector = Point(-1,0,0);
             D = -dot_product(normal_vector,A);
            //now we will find the value of t from the eqn of ray and eqn of plane
             t = -(D + dot_product(normal_vector,ray->origin))/dot_product(normal_vector,ray->dir);

            if(t>0)
            {
               //ckecking whether the intersection_point is on the back face or not
                Point intersection_point = ray->origin + ray->dir*t;
                if(intersection_point.y >= reference_point.y && intersection_point.y <= reference_point.y + width && intersection_point.z >= reference_point.z && intersection_point.z <= reference_point.z + height)
                {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
                }
            }




            //right face(along +x axis)
            //----------
            //vertices of right face are
            //(reference_point.x+length,reference_point.y,reference_point.z)
            //(reference_point.x+length,reference_point.y,reference_point.z+height)
            //(reference_point.x+length,reference_point.y+width,reference_point.z+height)
            //(reference_point.x+length,reference_point.y+width,reference_point.z)        

            A = Point(reference_point.x+length,reference_point.y,reference_point.z);
            B = Point(reference_point.x+length,reference_point.y+width,reference_point.z);
            C = Point(reference_point.x+length,reference_point.y,reference_point.z+height);

            //t = get_t_for_surface_ray_intersection(ray,A,B,C);
              normal_vector = Point(1,0,0);
             D = -dot_product(normal_vector,A);
            //now we will find the value of t from the eqn of ray and eqn of plane
             t = -(D + dot_product(normal_vector,ray->origin))/dot_product(normal_vector,ray->dir);

            if(t>0)
            {
                //ckecking whether the intersection_point is on the front face or not
                Point intersection_point = ray->origin + ray->dir*t;
                if(intersection_point.y >= reference_point.y && intersection_point.y <= reference_point.y + width && intersection_point.z >= reference_point.z && intersection_point.z <= reference_point.z + height)
                {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
                }
            }

            //front face(alnog -y axis)
            //------------
            //vertices of front face are
            //(reference_point.x,reference_point.y,reference_point.z)
            //(reference_point.x,reference_point.y,reference_point.z+height)
            //(reference_point.x+length,reference_point.y,reference_point.z+height)
            //(reference_point.x+length,reference_point.y,reference_point.z)

            A = Point(reference_point.x,reference_point.y,reference_point.z);
            B = Point(reference_point.x,reference_point.y,reference_point.z+height);
            C = Point(reference_point.x+length,reference_point.y,reference_point.z);

            //t = get_t_for_surface_ray_intersection(ray,A,B,C);

             normal_vector = Point(0,-1,0);
             D = -dot_product(normal_vector,A);
            //now we will find the value of t from the eqn of ray and eqn of plane
             t = -(D + dot_product(normal_vector,ray->origin))/dot_product(normal_vector,ray->dir);

            if(t>0)
            {
                //ckecking whether the intersection_point is on the left face or not
                Point intersection_point = ray->origin + ray->dir*t;
                if(intersection_point.x >= reference_point.x && intersection_point.x <= reference_point.x + length && intersection_point.z >= reference_point.z && intersection_point.z <= reference_point.z + height)
                {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
                }
            }

            //back face(along +y axis)
            //------------
            //vertices of right face are
            //(reference_point.x,reference_point.y+width,reference_point.z)
            //(reference_point.x,reference_point.y+width,reference_point.z+height)
            //(reference_point.x+length,reference_point.y+width,reference_point.z+height)
            //(reference_point.x+length,reference_point.y+width,reference_point.z)

            A = Point(reference_point.x,reference_point.y+width,reference_point.z);
            B = Point(reference_point.x,reference_point.y+width,reference_point.z+height);
            C = Point(reference_point.x+length,reference_point.y+width,reference_point.z);


           // t = get_t_for_surface_ray_intersection(ray,A,B,C);

             normal_vector = Point(0,1,0);
             D = -dot_product(normal_vector,A);
            //now we will find the value of t from the eqn of ray and eqn of plane
             t = -(D + dot_product(normal_vector,ray->origin))/dot_product(normal_vector,ray->dir);

            if(t>0)
            {
                //ckecking whether the intersection_point is on the right face or not
                Point intersection_point = ray->origin + ray->dir*t;
                if(intersection_point.x >= reference_point.x && intersection_point.x <= reference_point.x + length && intersection_point.z >= reference_point.z && intersection_point.z <= reference_point.z + height)
                {
                    if(minimum_t < 0)
                        minimum_t = t;
                    else
                        minimum_t = min(minimum_t,t);
                }
            }


            return minimum_t;



        }

        void draw()
        {
            //printf("Drawing Cube %lf\n",length);
            // glColor3f(color.r,color.g,color.b);
            // glPushMatrix();
            // glTranslatef(reference_point.x+length/2,reference_point.y+height/2,reference_point.z+width/2);
            // glutSolidCube(length);
            // glPopMatrix();

            glColor3f(color.r,color.g,color.b);
            glBegin(GL_QUADS);
                {  //drawing bottom face
                    glVertex3f(reference_point.x ,reference_point.y ,reference_point.z);
                    glVertex3f(reference_point.x + length,reference_point.y,reference_point.z);
                    glVertex3f(reference_point.x + length , reference_point.y + width ,reference_point.z);
                    glVertex3f(reference_point.x , reference_point.y + width ,reference_point.z);
        


                    //drawing top face
                    glVertex3f(reference_point.x ,reference_point.y ,reference_point.z+height);
                    glVertex3f(reference_point.x + length,reference_point.y,reference_point.z+height);
                    glVertex3f(reference_point.x + length , reference_point.y + width ,reference_point.z+height);
                    glVertex3f(reference_point.x , reference_point.y + width ,reference_point.z+height);

                    //drawing left face
                    glVertex3f(reference_point.x ,reference_point.y ,reference_point.z);
                    glVertex3f(reference_point.x ,reference_point.y ,reference_point.z+height);
                    glVertex3f(reference_point.x , reference_point.y + width ,reference_point.z+height);
                    glVertex3f(reference_point.x , reference_point.y + width ,reference_point.z);

                    //drawing right face
                    glVertex3f(reference_point.x + length,reference_point.y,reference_point.z);
                    glVertex3f(reference_point.x + length,reference_point.y+width,reference_point.z);
                    glVertex3f(reference_point.x + length,reference_point.y+width,reference_point.z+height);
                    glVertex3f(reference_point.x + length,reference_point.y,reference_point.z+height);

                    //drawing from face
                    glVertex3f(reference_point.x,reference_point.y,reference_point.z);
                    glVertex3f(reference_point.x,reference_point.y,reference_point.z+height);
                    glVertex3f(reference_point.x+length,reference_point.y,reference_point.z+height);
                    glVertex3f(reference_point.x+length,reference_point.y,reference_point.z);

                    //drawing back face
                    glVertex3f(reference_point.x,reference_point.y+width,reference_point.z);
                    glVertex3f(reference_point.x,reference_point.y+width,reference_point.z+height);
                    glVertex3f(reference_point.x+length,reference_point.y+width,reference_point.z+height);
                    glVertex3f(reference_point.x+length,reference_point.y+width,reference_point.z);
                    
                }
            glEnd();

        }

        void print()
        {
            cout << "Cube" << endl;
            cout << "-------" << endl;
            cout << "Bottom Lower Left Point: ";
            reference_point.print();
            cout << "Side: " << length << endl;
            cout << "Color: ";
            color.print();
            cout << "Coeefficient: ";
            coeefficient.print();
            cout << "Shine: " << shine << endl;
        }
};

class Checkerboard: public Object
{
    public:
        int num_of_cells;
        double width_of_each_cell;
        Checkerboard(double width_of_each_cell,Coeefficient coeefficient)
        {
            this->width_of_each_cell = width_of_each_cell;
            this->length = this->width = 800;  
            this->height = 0;
            this->coeefficient = coeefficient;
            this->shine = 0;
            object_type = "CHECKERBOARD";
            reference_point = Point(-width/2,-width/2,0);
       
        }

        Color get_color(Point point){

            //tileX = x direction borabor koto tomo tiles
            //tileY = y direction borabor koto tomo tiles  

            int tileX = (point.x - reference_point.x) / width_of_each_cell;
            int tileY = (point.y - reference_point.y) / width_of_each_cell;

            // int x = (point.x - reference_point.x);
            // int y = (point.y - reference_point.y);
            // int i = x/width_of_each_cell;
            // int j = y/width_of_each_cell;

            if(point.x < reference_point.x || point.x >= reference_point.x + width || point.y < reference_point.y || point.y>=reference_point.y + length)
            {
                return Color(0,0,0);
            }

            if(texture_enabled)
            {
              

                if (((tileX + tileY) % 2) == 0)
                {
                    int x_pixel = int((((point.x - reference_point.x) - (tileX * width_of_each_cell))/width_of_each_cell) * texture_white.width());

                    int y_pixel = int((((point.y - reference_point.y) - (tileY * width_of_each_cell))/width_of_each_cell) * texture_white.height());

                   // cout <<point.y <<" " <<reference_point.y<< " "<< tileY << " "<< width_of_each_cell <<" " << x_pixel << " " << y_pixel << endl;

                    unsigned char texture_r ;  
                    unsigned char texture_g ;
                    unsigned char texture_b ; 


                    texture_white.get_pixel(x_pixel,y_pixel,texture_r,texture_g,texture_b);
                    //cout << texture_r << " " << texture_g << " " << texture_b << endl;

                    return Color(texture_r/255.0,texture_g/255.0,texture_b/255.0);
                }

                else
                {
                    int x_pixel = int((((point.x - reference_point.x) - (tileX * width_of_each_cell))/width_of_each_cell) * texture_black.width());

                    int y_pixel = int((((point.y - reference_point.y) - (tileY * width_of_each_cell))/width_of_each_cell) * texture_black.height());

                   // cout <<point.y <<" " <<reference_point.y<< " "<< tileY << " "<< width_of_each_cell <<" " << x_pixel << " " << y_pixel << endl;

                    unsigned char texture_r ;  
                    unsigned char texture_g ;
                    unsigned char texture_b ; 


                    texture_black.get_pixel(x_pixel,y_pixel,texture_r,texture_g,texture_b);
                    //cout << texture_r << " " << texture_g << " " << texture_b << endl;

                    return Color(texture_r/255.0,texture_g/255.0,texture_b/255.0);
                }
                
            }
            else
            {

                if(tileX<0 || tileX>=num_of_cells || tileY<0 || tileY>=num_of_cells){
                    return Color(0,0,0);
                }

                if (((tileX + tileY) % 2) == 0)
                {
                    return Color(1,1,1);
                }
                else
                {
                    return Color(0,0,0);
                }
        }
    }

        Ray get_normal(Point intersection_point, Ray incidentRay)
        {
            Point normal_vector = Point(0,0,1);
            Ray normal_ray = Ray(intersection_point,normal_vector);
            return normal_ray;
        }

        double initial_intersect(Ray *ray, Color *color, int level)
        {
    
            //Here the normal vector of checker board n = (0.0,1) and eqn of checkerboard is z = 0 (D = 0)
            double t = -dot_product(ray->origin,Point(0,0,1))/dot_product(ray->dir,Point(0,0,1));
            if(t < 0) return -1.0;
            return t;

            // Point normal = Point(0, 0, 1);
            // double dotP = dot_product(normal, ray->dir);
            
            // if (round(dotP * 100) == 0)
            //     return -1;

            // double t = -dot_product(normal,ray->origin) / dotP;

            // Point p = ray->origin + ray->dir * t;

            // if(p.x <= reference_point.x || p.x >= abs(reference_point.x) && p.y <= reference_point.y && p.y >= abs(reference_point.y)){
            //     return -1;
            // }
            
            // return t;
    

        }


        void draw()
        {
           // cout << "Drawing Checkerboard" << endl;

            num_of_cells = ceil(this->width/width_of_each_cell);


           // glPushMatrix();
            //Point traslated_point = pos + l*500;
            //glTranslatef(traslated_point.x,traslated_point.y-100,traslated_point.z);
            //traslated_point.print();
           
            for (int i = 0; i < num_of_cells; i++)
            {
                for (int j = 0; j < num_of_cells; j++)
                {
                    if (((i + j) % 2) == 0) glColor3f(1, 1, 1);
                    else glColor3f(0, 0, 0);

                    glBegin(GL_QUADS);
                    {
                        glVertex3f(reference_point.x + i * width_of_each_cell,reference_point.y + j * width_of_each_cell,0);
                        glVertex3f(reference_point.x + (i + 1) * width_of_each_cell,reference_point.y + j * width_of_each_cell,0);
                        glVertex3f(reference_point.x + (i + 1) * width_of_each_cell,reference_point.y + (j + 1) * width_of_each_cell,0);
                        glVertex3f(reference_point.x + i * width_of_each_cell ,reference_point.y + (j + 1) * width_of_each_cell,0);
                    }
                    glEnd();
                }
            }

           // glPopMatrix();
        
        }

        void print()
        {
            cout << "Checkerboard" << endl;
            cout << "-------------" << endl;
            cout << "Width of each cell: " << width << endl;
            cout << "Coeefficient: ";
            coeefficient.print();
            cout << "Shine: " << shine << endl;
        }
};



