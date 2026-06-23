#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h> // fabs() ফাংশনের জন্য এটি প্রয়োজন

// math.h এর সাথে কনফ্লিক্ট এড়াতে বড় হাতের অক্ষরে নাম রাখা হয়েছে
float X0, Y0, X1, Y1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);

    // টাইপ কাস্টিং ছাড়া ফ্লোটের পরম মান বের করার জন্য fabs() ব্যবহার করা হয়েছে
    int dx = fabs(X1 - X0);
    int dy = fabs(Y1 - Y0);

    int sx = (X1 >= X0) ? 1 : -1;
    int sy = (Y1 >= Y0) ? 1 : -1;

    int x = X0;
    int y = Y0;

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
    else // slope >= 1
    {
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
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 100, 0, 100, -1, 1);
}

int main(int argc, char** argv) {
    printf("Enter First Point (X0 Y0): ");
    scanf("%f %f", &X0, &Y0);
    printf("Enter Second Point (X1 Y1): ");
    scanf("%f %f", &X1, &Y1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
