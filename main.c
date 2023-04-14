/*
 * Animated Indian Flag using OpenGL
 * Project by ARITRA BOSE
 * Roll No. 2021ITB035
 * Course: Computer Graphics
 * Semester: 4th
 * Department: Information Technology
 *
 * Description: This program is a simple implementation of an animated Indian Flag using OpenGL.
 *              This uses the Bézier curve algorithm to determine the intermediate points of the flag.
 *              The flag is animated by moving up and down the 2 control points of the Bézier curve.
 */

#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define GL_SILENCE_DEPRECATION

GLdouble PI = 3.14159265;
GLfloat yMove = 50, xMove = 10;
GLfloat ySteps = 2, xSteps = 1;
int yFlag = 1, xFlag = 1, animateFlag = 1;

//TRIGGER ANIMATION
void Animate() {
    if(animateFlag == 1) {
        //Animate about y-axis
        if(yMove > -50 && yFlag == 1) {
            yMove -= ySteps;
            if(yMove <= -50) {
                yFlag = 0;
            }
        }
        if(yMove < 50 && yFlag == 0) {
            yMove += ySteps;
            if(yMove >= 50) {
                yFlag = 1;
            }
        }

        //Animate about x-axis
        if(xMove > -10 && xFlag == 1) {
            xMove -= xSteps;
            if(xMove <= -10) {
                xFlag = 0;
            }
        }
        if(xMove < 10 && xFlag == 0) {
            xMove += xSteps;
            if(xMove >= 10) {
                xFlag = 1;
            }
        }

        glutPostRedisplay(); //Redraw the screen
    }
}

//SKY
void DrawSky() {
    glColor3f(0.53f, 0.81f, 0.92f);
    glBegin(GL_QUADS);
        glVertex2i(0, 500);
        glVertex2i(500, 500);
        glVertex2i(500, 250);
        glVertex2i(0, 250);
    glEnd();
}

//SUN
void DrawSun() {
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
        GLdouble angle, x, y;
        GLdouble radianConversion = PI / 180;
        for (int i = 0; i < 360; i++) {
            angle = i * radianConversion;
            x = 450 + 50 * cos(angle);
            y = 450 + 50 * sin(angle);
            glVertex2d(x, y);
        }
    glEnd();
}

//CLOUDS
void DrawEllipse(float x, float y, float xRadius, float yRadius) {
    glBegin(GL_POLYGON);
    GLdouble radianConversion = PI / 180;
    for (int i = 0; i < 360; i++) {
        float angle = i * radianConversion;
        float xPos = x + xRadius * cos(angle);
        float yPos = y + yRadius * sin(angle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
}
void DrawClouds(int numberOfClouds) {
    glColor3f(1, 1, 1);
    srand(time(NULL));
    for (int i = 0; i < numberOfClouds; i++) {
        float xPos = rand() % 500;
        float yPos = 300 + (rand() % 150);
        float xRadius = 20 + (rand() % 30);
        float yRadius = 10 + (rand() % 20);

        for (int j = 0; j < 3; j++) {
            DrawEllipse(xPos + j * xRadius / 2, yPos, xRadius, yRadius);
        }
    }
}

//GRASSLAND
void DrawGrassland() {
    glColor3f(0.30f, 0.78f, 0.30f);
    glBegin(GL_QUADS);
        glVertex2i(0, 250);
        glVertex2i(500, 250);
        glVertex2i(500, 0);
        glVertex2i(0, 0);
    glEnd();
}

//TREE
void DrawTree(GLint x, GLint y) {
    // Draw the stem
    glColor3f(0.35f, 0.16f, 0.14f);
    glBegin(GL_QUADS);
        glVertex2i(395 + x, 250 + y);
        glVertex2i(405 + x, 250 + y);
        glVertex2i(405 + x, 150 + y);
        glVertex2i(395 + x, 150 + y);
    glEnd();

    // Draw the green leaves
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.4f, 0.0f);
        glVertex2i(380 + x, 200 + y);
        glVertex2i(420 + x, 200 + y);
        glVertex2i(400 + x, 300 + y);

        glColor3f(0.0f, 0.5f, 0.0f);
        glVertex2i(370 + x, 250 + y);
        glVertex2i(430 + x, 250 + y);
        glVertex2i(400 + x, 350 + y);

        glColor3f(0.0f, 0.6f, 0.0f);
        glVertex2i(360 + x, 300 + y);
        glVertex2i(440 + x, 300 + y);
        glVertex2i(400 + x, 400 + y);
    glEnd();
}

//MOUNTAINS
void DrawMountains() {
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2i(0, 250);
        glVertex2i(100, 400);
        glVertex2i(200, 250);

        glColor3f(0.55f, 0.55f, 0.55f);
        glVertex2i(200, 250);
        glVertex2i(300, 400);
        glVertex2i(400, 250);

        glColor3f(0.6f, 0.6f, 0.6f);
        glVertex2i(400, 250);
        glVertex2i(500, 400);
        glVertex2i(600, 250);
    glEnd();
}

//RIVER
void DrawRiver() {
    glColor3f(0.25f, 0.47f, 0.87f);
    glBegin(GL_QUADS);
        glVertex2i(350, 0);
        glVertex2i(150, 0);
        glVertex2i(210, 250);
        glVertex2i(280, 250);
    glEnd();
}

//PODIUM
void DrawPodium() {
    glColor3f(0.5f, 0.25f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2i(80, 50);
        glVertex2i(110, 50);
        glVertex2i(110, 40);
        glVertex2i(80, 40);
    glEnd();
}

//ASHOKA CHAKRA
void DrawAshokaChakra(GLdouble xCenter, GLdouble yCenter, GLdouble radius) {
    int numSpokes = 24;
    int i;
    GLdouble angle, x, y;

    //Draw the circle
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    GLdouble radianConversion = PI / 180;
    for (i = 0; i < 360; i++) {
        angle = i * radianConversion;
        x = xCenter + radius * cos(angle);
        y = yCenter + radius * sin(angle);
        glVertex2d(x, y);
    }
    glEnd();

    //Draw the spokes
    glBegin(GL_LINES);
    GLdouble angleIncrement = 2 * PI / numSpokes;
    for (i = 0; i < numSpokes; i++) {
        angle = i * angleIncrement;
        x = xCenter + radius * cos(angle);
        y = yCenter + radius * sin(angle);
        glVertex2d(xCenter, yCenter);
        glVertex2d(x, y);
    }
    glEnd();
}

//MAIN DRAW FUNCTION
void Draw() {
    GLfloat x[4], y1[4], y2[4], y3[4], y4[4];
    glClear(GL_COLOR_BUFFER_BIT);

    /* Initialize the control points */
    x[0] = 100; x[1] = 200; x[2] = 200;  x[3] = 300 - xMove;
    y1[0] = 450; y1[1] = 450 + yMove; y1[2] = 450 - yMove; y1[3] = 450; //Upper boundary of orange
    y2[0] = 400; y2[1] = 400 + yMove; y2[2] = 400 - yMove; y2[3] = 400; //Upper boundary of white
    y3[0] = 350; y3[1] = 350 + yMove; y3[2] = 350 - yMove; y3[3] = 350; //Upper boundary of green
    y4[0] = 300; y4[1] = 300 + yMove; y4[2] = 300 - yMove; y4[3] = 300; //Lower boundary of green

    /* Bézier curve algorithm to determine the intermediate points */
    GLdouble xt[200], y1t[200], y2t[200], y3t[200], y4t[200], t;
    int i,c; //c is the number of intermediate points
    for (i = 0, t = 0, c = 0; t <= 1; i++, t += 0.01) {
       xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
       y1t[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];
       y2t[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];
       y3t[i] = pow(1 - t, 3) * y3[0] + 3 * t * pow(1 - t, 2) * y3[1] + 3 * pow(t, 2) * (1 - t) * y3[2] + pow(t, 3) * y3[3];
       y4t[i] = pow(1 - t, 3) * y4[0] + 3 * t * pow(1 - t, 2) * y4[1] + 3 * pow(t, 2) * (1 - t) * y4[2] + pow(t, 3) * y4[3];
       c++;
    }

    /* Draw the sky */
    DrawSky();

    /* Draw the sun */
    DrawSun();

    /* Draw the mountain */
    DrawMountains();

    /* Draw clouds */
    DrawClouds(3);

    /* Draw the grassland */
    DrawGrassland();

    /* Draw the river */
    DrawRiver();

    /* Draw tree */
    DrawTree(0, 0);
    DrawTree(50, -60);

    /* Draw the podium */
    DrawPodium();

    /* Draw the flag */

    //Draw the orange part
    glColor3f(1, 0.25f, 0);
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i < c; i++) {
            glVertex2d(xt[i], y1t[i]);
            glVertex2d(xt[i], y2t[i]);
        }
    glEnd();

    //Draw the white part
    glColor3f(1, 1, 1);
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i < c; i++) {
            glVertex2d(xt[i], y2t[i]);
            glVertex2d(xt[i], y3t[i]);
        }
    glEnd();

    //Draw the green part
    glColor3f(0.1f, 0.5f, 0.1f);
    glBegin(GL_QUAD_STRIP);
        for (i = 0; i < c; i++) {
            glVertex2d(xt[i], y3t[i]);
            glVertex2d(xt[i], y4t[i]);
        }
    glEnd();

    /* Draw the Ashoka Chakra */
    GLdouble chakraXCenter = xt[c / 2];
    GLdouble chakraYCenter = (y2t[c / 2] + y3t[c / 2]) / 2;
    GLdouble chakraRadius = (y2t[c / 2] - y3t[c / 2]) / 2;
    DrawAshokaChakra(chakraXCenter, chakraYCenter, chakraRadius);

    /* Draw the pole */
    glColor3f( 0.6f, 0.6f, 0.3f);
    glRecti(90, 460, 100, 50);

    glFlush();
}

void Menu(int n) {
    switch (n) {
        case 1:
            animateFlag = 1;
            break;
        case 2:
            animateFlag = 0;
            break;
        default:
            exit(0);
    }

    glutPostRedisplay(); //Redraw the screen
}

void MyInit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);

    //Create the menu
    glutCreateMenu(Menu);
    glutAddMenuEntry("Start",1);
    glutAddMenuEntry("Stop",2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argC, char *argV[]) {
    glutInit(&argC, argV);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Animate Flag");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Animate);
    glutMainLoop();
    return 0;
}