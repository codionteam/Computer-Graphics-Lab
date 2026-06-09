#include <OpenGL/gl.h>
#include<GLUT/glut.h>
#include <math.h>
#include <iostream>
using namespace std;
int signalState = 0;
int directionControl = 0;

float c1x=-120,c1y=-8;
float c1xx=-140, c1yy=-8;
float c1xxx=-160, c1yyy=-8;
float c1xxxx=-180, c1yyyy=-8;
float c1xxxxx=-200, c1yyyyy=-8;
float c2x=120,c2y=-33;
float c2xx=160,c2yy=-33;
//float c3x=12,c3y=120;
float c3x=12,c3y=90;
float c3xx=12,c3yy=110;
float c3xxx=12,c3yyy=130;
float c3xxxx=12,c3yyyy=150;
float c4x=-12,c4y=-120;
float c4xx=-12,c4yy=-180;

float h1y=-48;
int hDirection = 0;

void playHorn()
{
    system("afplay ./horn.wav &");
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'h' || key == 'H')
    {
        playHorn();
    }
}

void MidPoint(float xc, float yc, float r)
{
    float x = 0;
    float y = r;

    float p = 1 - r;

    glPointSize(4);
    glBegin(GL_POINTS);
    while (x <= y)
    {
        glVertex2f(xc + x, yc + y);
        glVertex2f(xc - x, yc + y);
        glVertex2f(xc + x, yc - y);
        glVertex2f(xc - x, yc - y);

        glVertex2f(xc + y, yc + x);
        glVertex2f(xc - y, yc + x);
        glVertex2f(xc + y, yc - x);
        glVertex2f(xc - y, yc - x);

        x++;

        if (p < 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y--;
            p = p + 2 * (x - y) + 1;
        }
    }
    glEnd();
}


void DDA (float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    int counter=0;

    if (dx == 0)
    {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POINTS);
        for (float j = y1; j <= y2; j++)
        {
            if (counter % 20 < 10)
            {
                    glVertex3f(x1, j, 0.0);
            }
            counter++;
        }
        glEnd();
        return;
    }

    float m = dy / dx;
    if (m<0) m*=(-1);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POINTS);


    if (m <= 1)
    {
        for (float i=x1,j=y1; i<=x2; i+=1,j+=m)
        {
            if (counter % 20 < 10)
                glVertex3f(i, j, 0.0);
            counter++;
        }
    }
    else
    {
        for (float i = x1, j = y1; j <= y2; i += 1/m, j += 1)
        {
            if (counter % 20 <10)
                glVertex3f(i, j, 0.0);
            counter++;
        }
    }

    glEnd();
}

void Line(int x1,int y1, int x2, int y2, int n, int gap)
{
    //glColor3f(1,1,1);
    //glLineWidth(5);
    glBegin (GL_LINES);
    glVertex3f(x1,y1,0);
    glVertex3f(x2,y2, 0);
    glEnd();

    n-=1;
    if (n!=1)
    {
        while (y1==y2 && n!=0)
        {
            glBegin (GL_LINES);
            glVertex3f(x1,y1-=gap,0);
            glVertex3f(x2,y2-=gap, 0);
            glEnd();
            n-=1;
        }
        while (x1==x2 && n!=0)
        {
            glBegin (GL_LINES);
            glVertex3f(x1+=(gap-1),y1,0);
            glVertex3f(x2+=(gap-1),y2, 0);
            glEnd();
            n-=1;
        }
    }
}


void circle(GLfloat rx,GLfloat ry,GLfloat cx,GLfloat cy)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);

    for(int i=0;i<=100;i++)
    {
        float angle = 2.0f * 3.1416f * i/100;

        float x = rx * cosf(angle);
        float y = ry * sinf(angle);

        glVertex2f((x+cx),(y+cy));
    }

    glEnd();
}


void car(float r, float g, float b)
{
    glColor3f(r,g,b);

    //body
    glBegin(GL_POLYGON);
    glVertex3f(-6,-3,0);
    glVertex3f(6,-3,0);
    glVertex3f(6,3,0);
    glVertex3f(-6,3,0);
    glEnd();

    //top
    glBegin(GL_POLYGON);
    glVertex3f(-3,3,0);
    glVertex3f(3,3,0);
    glVertex3f(2,6,0);
    glVertex3f(-2,6,0);
    glEnd();

    //wheel
    glColor3f(0,0,0);
    circle(2,2,-3,-3);
    circle(2,2,3,-3);
    //wheel hub
    glColor3f(0.7,0.7,0.7);
    circle(1,1,-3,-3);
    circle(1,1,3,-3);

}


void tree(float x, float y, float r)
{
    int h=5;
    glColor3f(0.5,0.3,0.1);
    glRectf(x-1,y-h,x+1,y+h);

    glColor3f(0.0,0.7,0.0);
    circle(r,r-0.5,x,y+h);
}

void human(float r, float g, float b)
{
    // head
    glColor3f(1, 0.8, 0.6);
    circle(1.2, 1, 0, 3);

    //arm
    glRectf(-2.2, 0, -1.5, 2);
    glRectf(1.5, 0, 2.2, 2);

    //Body
    glColor3f(r, g, b);
    glRectf(-1.5, -1, 1.5, 2.5);

    //Pants
    glColor3f(0.1, 0.1, 0.1);
    glRectf(-1.5, -4, -0.2, -1);
    glRectf(0.2, -4, 1.5, -1);

    //shoes
    glColor3f(1, 1, 1);
    glRectf(-1.6, -4.5, -0.1, -4);
    glRectf(0.1, -4.5, 1.6, -4);
}



void TrafficBox(float x, float y, int active)
{
    // pole
    glColor3f(0.3,0.3,0.3);
    glRectf(x,y,x+2,y+12);

    // box
    glColor3f(0.1,0.1,0.1);
    glRectf(x-3,y+12,x+5,y+28);

    // stand
    glRectf(x-1,y-2,x+3,y+1);


    if(active)
    {
        //red
        if(signalState == 2) glColor3f(1,0,0);
        else glColor3f(0.3,0,0);
        circle(2,2,x+1,y+25);

        //yellow
        if(signalState == 1) glColor3f(1,1,0.2);
        else glColor3f(0.3,0.3,0);
        circle(2,2,x+1,y+20);

        //green
        if(signalState == 0) glColor3f(0,1,0);
        else glColor3f(0,0.3,0);
        circle(2,2,x+1,y+15);
    }
    else
    {
        glColor3f(1,0,0);
        circle(2,2,x+1,y+25);

        glColor3f(0.3,0.3,0);
        circle(2,2,x+1,y+20);

        glColor3f(0,0.3,0);
        circle(2,2,x+1,y+15);
    }
}


void quad(int x1,int y1,int x2,int y2,int y3)
{
    glBegin(GL_QUADS);
    glVertex3f(x1,y1,0);
    glVertex3f(x1,y2,0);
    glVertex3f(x2,y1,0);
    glVertex3f(x2,y3,0);
    glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //road
    glColor3f(0.15,0.15,0.15);
    glRectf(-100,-40,100,0);
    glRectf(-20,-100,20,100);

    //Road Border
    glColor3f(1,1,1);
    //border left - right
    glRectf(-100, 0, -20, 1);
    glRectf(20, 0, 100, 1);
    glRectf(-100, -41, -20, -40);
    glRectf(20, -41, 100, -40);
    //border top - bottom
    glRectf(-21, 1, -20, 100);
    glRectf(-21, -100, -20, -40);
    glRectf(20, 1, 21, 100);
    glRectf(20, -100, 21, -40);


    //footway
    //glColor3f(0.9,0.85,0.7);
    glColor3f(0.7,0.7,0.7);

    glRectf(-100,1,-21,10);
    glRectf(-100,-50,-21,-41);
    glRectf(21,1,100,10);
    glRectf(21,-50,100,-41);

    glRectf(-30,1,-21,100);
    glRectf(-30,-100,-21,-41);
    glRectf(21,1,30,100);
    glRectf(21,-100,30,-41);


    //road border line
    glLineWidth(1);
    glColor3f(0,0,0);

    Line(-100,1,-21,1,1,0);
    Line(-100,10,-21,10,1,0);
    Line(-30,100,-30,1,1,0);
    Line(-21,100,-21,1,1,0);

    Line(-100,-50,-21,-50,1,0);
    Line(-100,-41,-21,-41,1,0);
    Line(-30,-100,-30,-41,1,0);
    Line(-21,-100,-21,-41,1,0);

    Line(21,1,100,1,1,0);
    Line(21,10,100,10,1,0);
    Line(30,100,30,1,1,0);
    Line(21,100,21,1,1,0);

    Line(21,-41,21,-100,1,0);
    Line(30,-41,30,-100,1,0);
    Line(21,-41,100,-41,1,0);
    Line(30,-50,100,-50,1,0);


    //footway divider
    Line(-100,1,-100, 10, 8, 10);
    Line(-100,-50,-100, -41, 8, 10);
    Line(21,1,21, 10, 10, 10);
    Line(21,-50,21, -41, 10, 10);

    Line(-30,100,-21, 100, 10, 10);
    Line(-30,-50,-21, -50, 8, 10);
    Line(21,100,30, 100, 10, 10);
    Line(21,-41,30, -41, 10, 10);



    //Road divider
    glColor3f(1,1,1);
    glPointSize(2);

    DDA(-100,-20,100,-20);
    //DDA(0,-100,0,100);
    DDA (0,-100,0,70);

    glLineWidth(5);
    //zeebra crossing
    Line(-31,-2,-31,-38,1,3);
    Line(-28,-4,-22, -4,12,3);

    Line(31,-2,31, -38,1,3);
    Line(28,-4,22, -4,12,3);

    Line(-18,12,18, 12,1,3);
    Line(-17,9,-17, 1,18,3);

    Line(-18,-52,18, -52,1,3);
    Line(-17,-41,-17, -49,18,3);


    //4way Center
    MidPoint(0, -20, 4);



    //building -1
    tree(-96,27,4);
    tree(-94,15,6);

    glColor3f(0,0.75,1);
    glRectf(-90,10,-60,50);

    glColor3f(1,1,1);
    glRectf(-88,48,-82,40);
    glRectf(-78,48,-72,40);
    glRectf(-68,48,-62,40);

    glRectf(-88,38,-82,30);
    glRectf(-78,38,-72,30);
    glRectf(-68,38,-62,30);

    glRectf(-88,28,-82,20);
    glRectf(-68,28,-62,20);

    glRectf(-80,28,-70,10);

    tree(-62,15,6);
    circle(4,3,-88,13);


    //building -2
    glColor3f(0.0,0.8,0.0);
    tree(57,24,5);
    circle(6,5,59,15);
    tree(93,24,6);
    circle(4,3,98,15);

    glColor3f(1,0.65,0);
    glRectf(60,10,90,50);

    glColor3f(1,1,1);
    glRectf(62,48,68,40);
    glRectf(72,48,78,40);
    glRectf(82,48,88,40);

    glRectf(62,38,68,30);
    glRectf(72,38,78,30);
    glRectf(82,38,88,30);

    glRectf(62,28,68,20);
    glRectf(82,28,88,20);

    glRectf(70,28,80,10);

    //grass
    glColor3f(0.0,0.7,0.0);
    circle(6,5,59,15);
    circle(6,5,90,15);





    //tree
    tree(-90,-90,5);tree(-90,-75,5);
    tree(-80,-90,4);tree(-80,-75,6);
    tree(-70,-90,5);tree(-70,-75,4);
    tree(-60,-90,4);tree(-60,-75,5);
    tree(-50,-90,5);tree(-50,-75,5);
    tree(-40,-90,5);tree(-40,-75,4);



    //car
    glPushMatrix();
    glTranslatef(c1x,c1y,0);
    car(1,0,0);
    glPopMatrix();

    //car 1xx
    glPushMatrix();
    glTranslatef(c1xx,c1yy,0);
    car(0,0.5,1);
    glPopMatrix();

    //car 1xxx
    glPushMatrix();
    glTranslatef(c1xxx,c1yyy,0);
    car(0,0.6,0.2);
    glPopMatrix();

    //car 1xxxx
    glPushMatrix();
    glTranslatef(c1xxxx,c1yyyy,0);
    car(1,0.8,0);
    glPopMatrix();

    //car 1xxxxx
    glPushMatrix();
    glTranslatef(c1xxxxx,c1yyyyy,0);
    car(0.5,0,0.5);
    glPopMatrix();

    //car 2x
    glPushMatrix();
    glTranslatef(c2x,c2y,0);
    car(1,0.4,0);
    glPopMatrix();

    //car2xx
    glPushMatrix();
    glTranslatef(c2xx,c2yy,0);
    car(0,1,0);
    glPopMatrix();

    //car3x
    glPushMatrix();
    glTranslatef(c3x,c3y,0);
    glRotatef(90,0,0,1);
    car(1,0,0.6);
    glPopMatrix();

    //car3xx
    glPushMatrix();
    glTranslatef(c3xx,c3yy,0);
    glRotatef(90,0,0,1);
    car(0.5,0.8,1);
    glPopMatrix();

    //car3xxx
    glPushMatrix();
    glTranslatef(c3xxx,c3yyy,0);
    glRotatef(90,0,0,1);
    car(0.4,0.2,0);
    glPopMatrix();

    //car3xxxx
    glPushMatrix();
    glTranslatef(c3xxxx,c3yyyy,0);
    glRotatef(90,0,0,1);
    car(1,1,0);
    glPopMatrix();

    //car4x
    glPushMatrix();
    glTranslatef(c4x,c4y,0);
    glRotatef(90,0,0,1);
    car(0,0,1);
    glPopMatrix();

    //car4xx
    glPushMatrix();
    glTranslatef(c4xx,c4yy,0);
    glRotatef(90,0,0,1);
    car(0,0.8,0.8);
    glPopMatrix();


    //TrafficLight
    glPushMatrix();
    glTranslatef(-58, 6, 0);
    glRotatef(-90, 0, 0, 1);
    TrafficBox(0, 0, directionControl==0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(58, -46, 0);
    glRotatef(90, 0, 0, 1);
    TrafficBox(0, 0, directionControl==0);
    glPopMatrix();


    TrafficBox(-26, -78, directionControl==1);


    glPushMatrix();
    glTranslatef(26, 38, 0);
    glRotatef(180, 0, 0, 1);
    TrafficBox(0, 0, directionControl==1);
    glPopMatrix();


    //Helepad
    glColor3f(0.5,0.5,0.5);
    circle(21,21,65,-75);
    glColor3f (1,1,1);
    MidPoint(65, -75, 20);
    glLineWidth(10);
    glColor3f (1,1,0);
    Line(53,-80,77,-80,1,0);
    Line(53,-70,77,-70,1,0);
    Line(65,-70,65,-80,1,0);
    tree(36,-92,5);tree(94,-92,5);
    tree(36,-62,5);tree(94,-62,5);



    //human
    if (h1y <= -44)
    {
        glPushMatrix();
        glTranslatef(-26, -45, 0);
        human(0.2, 0.5, 1);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslatef(-26, h1y, 0);
        human(0.2, 0.5, 1);
        glPopMatrix();
    }


    glutSwapBuffers();
}


void update (int value)
{
    static int timer = 0;
    timer++;

    //lights stand by
    if(signalState == 0 && timer > 120)
    {
        signalState = 1;
        timer = 0;
    }
    else if(signalState == 1 && timer > 30)
    {
        signalState = 2;
        timer = 0;
    }
    else if(signalState == 2 && timer > 90)
    {
        signalState = 0;
        directionControl = !directionControl;
        timer = 0;
    }

    //moving car c1x
    if ((directionControl == 0 && signalState == 0) || c1x > -38) {
        c1x += 1;
    }
    if (c1x > 120) c1x = -120;

    //c1xx
    if ((directionControl == 0 && signalState == 0) || c1xx > -38 )
    {
        c1xx += 1;
    }
    if (c1xx > 120) c1xx = -140;

    //c1xxx
    if ((directionControl == 0 && signalState == 0) || c1xxx > -38) {
        c1xxx += 1;
    }
    if (c1xxx > 120) c1xxx = -160;

    //c1xxxx
    if ((directionControl == 0 && signalState == 0) || c1xxxx > -38) {
        c1xxxx += 1;
    }
    if (c1xxxx > 120) c1xxxx = -180;

    //c1xxxxx
    if ((directionControl == 0 && signalState == 0) || c1xxxxx > -38) {
        c1xxxxx += 1;
    }
    if (c1xxxxx > 120) c1xxxxx = -200;

    //c2x
    if ((directionControl == 0 && signalState == 0) || c2x < 38) {
        c2x -= 1;
    }
    if (c2x < -120) c2x = 120;

    //c2xx
    if ((directionControl == 0 && signalState == 0) || c2xx < 38) {
        c2xx -= 1;
    }
    if (c2xx < -120) c2xx = 160;

    //c3y
    if ((directionControl == 1 && signalState == 0) || c3y < 12) {
        c3y -= 1;
    }
    if (c3y < -120) c3y = 90;

    //c3yy
    if ((directionControl == 1 && signalState == 0) || c3yy < 12) {
        c3yy -= 1;
    }
    if (c3yy < -120) c3yy = 110;

    //c3yyy
    if ((directionControl == 1 && signalState == 0) || c3yyy < 12) {
        c3yyy -= 1;
    }
    if (c3yyy < -120) c3yyy = 130;

    //c3yyyy
    if ((directionControl == 1 && signalState == 0) || c3yyyy < 12) {
        c3yyyy -= 1;
    }
    if (c3yyyy < -120) c3yyyy = 150;

    //c4y
    if ((directionControl == 1 && signalState == 0) || c4y > -52) {
        c4y += 1;
    }
    if (c4y > 120)  c4y = -120;

    //c4yy
    if ((directionControl == 1 && signalState == 0) || c4yy > -92) {
        c4yy += 1;
    }
    if (c4yy > 120)  c4yy = -180;


    //ping pong moving
    if (signalState == 2 && directionControl == 0)
    {
        if (hDirection == 0)
        {
            if (h1y < 6.0) h1y += 0.6;
            else           h1y = 6.0;
        }
        else if (hDirection == 1)
        {
            if (h1y > -48.0) h1y -= 0.6;
            else h1y = -48.0;
        }
    }


    if (signalState == 0)
    {
        if (h1y >= 6.0) hDirection = 1;
        if (h1y <= -48.0) hDirection = 0;
    }



    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}





void init (void)
{
    glClearColor(0.70,1,0.70,0);
    //glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho (-100,100.0,-100.0,100,-1.0,1.0);
    glOrtho (-100,100.0,-100.0,70,-1.0,1.0);

}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(350,150);

    glutCreateWindow("City Traffic Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0,update,0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}