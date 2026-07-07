#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

int radius;
//int xc,yc;

void init()
{
   glClearColor(0,0,0,0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-100,100,-100,100,-1,1);
   glPointSize(2.5);
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(1,1,1);

   glBegin(GL_POINTS);
    //step1
   int x=0;
   int y=radius;
    //step2
   int p=1-radius;
    //step3
   while(x<=y)
   {
       //Plot all 8 symmetric points center 0,0
      glVertex2i( x, y);
      glVertex2i(-x, y);
      glVertex2i( x,-y);
      glVertex2i(-x,-y);

      glVertex2i( y, x);
      glVertex2i(-y, x);
      glVertex2i( y,-x);
      glVertex2i(-y,-x);
        //Plot all 8 symmetric points center xc,yc
      /*glVertex2i( xc+x, yc+y);
      glVertex2i( xc-x, yc+y);
      glVertex2i( xc+x, yc-y);
      glVertex2i( xc-x, yc-y);

      glVertex2i( xc+y, yc+x);
      glVertex2i( xc-y, yc+x);
      glVertex2i( xc+y, yc-x);
      glVertex2i( xc-y, yc-x);
      */
        //case 1
      if(p<0)
      {
         x=x+1;
         p=p+2*x+1;
      }
        //case 2
      else
      {
         x=x+1;
         y=y-1;
         p=p+2*x+1-2*y;
      }
   }

   glEnd();

   glFlush();
}

int main(int argc,char** argv)
{
    //center xc,yc
   /*printf("Enter Center (x y) : ");
   scanf("%d%d",&xc,&yc);*/

   printf("Enter Radius : ");
   scanf("%d",&radius);

   glutInit(&argc,argv);

   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

   glutInitWindowSize(600,600);

   glutCreateWindow("Midpoint Circle");

   init();

   glutDisplayFunc(display);

   glutMainLoop();

   return 0;
}
