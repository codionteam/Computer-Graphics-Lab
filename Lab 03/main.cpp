/*#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Global Variables

float x1, y_1, x2, y2;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_POINTS);

    // DDA Algorithm
    float dx = x2 - x1;
    float dy = y2 - y_1;

    float steps;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    float Xinc = dx / steps;
    float Yinc = dy / steps;

    float x = x1;
    float y = y_1;

    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(round(x), round(y));

        x += Xinc;
        y += Yinc;
    }

    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 100, 0, 100, -1, 1);
}

int main(int argc, char** argv)
{
    printf("Enter First Point (x1 y_1): ");
    scanf("%f %f", &x1, &y_1);

    printf("Enter Second Point (x2 y2): ");
    scanf("%f %f", &x2, &y2);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(600, 600);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("DDA Line Drawing");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}*/

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Global Variables
float x1, y_1, x2, y2;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_POINTS);

    // DDA Algorithm
    float dx = x2 - x1;
    float dy = y2 - y_1;

    float steps;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    float Xinc = dx / steps;
    float Yinc = dy / steps;

    float x = x1;
    float y = y_1;

    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(round(x), round(y));

        x += Xinc;
        y += Yinc;
    }

    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 100, 0, 100, -1, 1);

    glPointSize(3.0);
}

int main(int argc, char** argv)
{
    printf("Enter First Point (x1 y1): ");
    scanf("%f %f", &x1, &y_1);

    printf("Enter Second Point (x2 y2): ");
    scanf("%f %f", &x2, &y2);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(600, 600);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("DDA Line Drawing");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
