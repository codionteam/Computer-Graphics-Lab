#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float x, y;

// ব্রেসেনহাম (Bresenham) লাইন ফাংশন
void drawLine(float x1, float y1, float x2, float y2)
{
    int dx = fabs(x2 - x1);
    int dy = fabs(y2 - y1);

    int sx, sy;

    // sx এর জন্য if-else কন্ডিশন
    if (x2 >= x1) {
        sx = 1;
    } else {
        sx = -1;
    }

    // sy এর জন্য if-else কন্ডিশন
    if (y2 >= y1) {
        sy = 1;
    } else {
        sy = -1;
    }

    int x = round(x1);
    int y = round(y1);

    glBegin(GL_POINTS);

    // slope < 1
    if (dx >= dy) {
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            glVertex2i(x, y);
            x += sx;
            if (p < 0) {
                p = p + 2 * dy;
            } else {
                y += sy;
                p = p + 2 * dy - 2 * dx;
            }
        }
    }
    // slope >= 1
    else {
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            glVertex2i(x, y);
            y += sy;
            if (p < 0) {
                p = p + 2 * dx;
            } else {
                x += sx;
                p = p + 2 * dx - 2 * dy;
            }
        }
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);

    // House
    drawLine(20, 20, 80, 20);
    drawLine(80, 20, 80, 60);
    drawLine(20, 60, 80, 60);
    drawLine(20, 60, 20, 20);

    // Roof
    drawLine(10, 60, 50, 90);
    drawLine(50, 90, 90, 60);

    // Door
    drawLine(45, 20, 45, 45);
    drawLine(45, 45, 55, 45);
    drawLine(55, 45, 55, 20);

    // Window
    drawLine(60, 35, 75, 35);
    drawLine(75, 35, 75, 50);
    drawLine(75, 50, 60, 50);
    drawLine(60, 50, 60, 35);

    // Cross
    drawLine(65, 35, 65, 50);
    drawLine(60, 40, 75, 40);

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 100, 0, 100, -1, 1);
    glPointSize(2.5);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bresenham House (No Input)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
