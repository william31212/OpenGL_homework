#include <iostream>
#include <GL/glut.h>

#define TORSO_HEIGHT 4.0
#define TORSO_RADIUS 3.0
#define UPPER_ARM_RADIUS 0.5
#define UPPER_ARM_HEIGHT 1.0
#define LOWER_ARM_RADIUS 0.8
#define LOWER_ARM_HEIGHT 2.0
#define LOWER_LEG_RADIUS 0.5
#define LOWER_LEG_HEIGHT 0.5
#define UPPER_LEG_RADIUS 0.8
#define UPPER_LEG_HEIGHT 5.0
#define HEAD_HEIGHT 3.0
#define HEAD_RADIUS 2.5

typedef float point[3];
static GLfloat rotX, rotY, rotZ;
static GLfloat lfandrf = 0;
static GLfloat upanddown = 0;
static int situation = 1;
static int index = 9;
static int q = 0;

/*
0 身體
1 頭上下
2 頭左右
3 整隻右手
4 右手腕
5 整隻左手
6 左手腕
7 右腳
8 右小腿
9 左腳
10 左小腿
*/

static GLfloat theta[11] = {
    45.0, 90.0, 320.0, 145.0, 0.0,
    180.0, -45.0, 180.0, 0.0, 180.0,
    0.0};

int axis = 0;
GLfloat x=1,y=0,z=0;

static GLint angle = 2;
double size = 1.0;
GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;

GLfloat colors[7][3] = {
    {1.0, 1.0, 1.0},
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
};
GLfloat color_r = 1;
GLfloat color_g = 1;
GLfloat color_b = 1;

void myinit()
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess = {100.0};
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 10.0, 10.0, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    h = gluNewQuadric();
    gluQuadricDrawStyle(h, GLU_FILL);
    t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    lua = gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_FILL);
    lla = gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_FILL);
    rua = gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_FILL);
    rla = gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_FILL);
    lul = gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_FILL);
    lll = gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_FILL);
    rul = gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_FILL);
    rll = gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
}

void head()
{
    glPushMatrix();
    glTranslatef(0.0, 2 * HEAD_HEIGHT, 0.0);
    glScalef(0.5 * HEAD_RADIUS, 0.5 * HEAD_HEIGHT, 0.5 * HEAD_RADIUS);
    gluSphere(h, 1.0, 10, 10);
    glPushMatrix();
    glTranslatef(0.4, 0.4, 1.0);
    gluSphere(h, 0.1, 10, 3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.4, 0.4, 1.0);
    gluSphere(h, 0.1, 10, 3);
    glPopMatrix();
    glPopMatrix();
}

void neck()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(t, 0.4, 0.4, 1.5, 10, 10);
    glPopMatrix();
}

void torso()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(t,TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
   glPopMatrix();
}

void left_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lla, LOWER_ARM_RADIUS*0.5, LOWER_ARM_RADIUS*2, LOWER_ARM_HEIGHT*2, 10, 10);
    glPopMatrix();
}

void right_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla, LOWER_ARM_RADIUS * 0.5, LOWER_ARM_RADIUS * 2, LOWER_ARM_HEIGHT*2, 10, 10);
    glPopMatrix();
}

void left_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void left_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS * 3, LOWER_LEG_HEIGHT + 1, 10, 10);
    glPopMatrix();
}

void right_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void right_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS * 3, LOWER_LEG_HEIGHT + 1, 10, 10);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(lfandrf, upanddown, 0.0);

    if(axis == 0)
    {
        x = 1, y = 0, z = 0;
    }
    else if(axis == 1)
    {
        x = 0, y = 0, z = 1;
    }
    //HEAD
    glPushMatrix();
    glTranslatef(0.0, TORSO_HEIGHT + 0.5 * HEAD_HEIGHT, 0.0);
    glRotatef(theta[1], 0.0, 0.0, 1.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.5 * HEAD_HEIGHT, 0.0);
    glPopMatrix();
    head();

    //NECK
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, TORSO_HEIGHT + 0.5 * HEAD_HEIGHT, 0.0);
    glTranslatef(0.0, -0.5, 0.0);
    neck();

    //TORSO
    glPopMatrix();
    glPushMatrix();
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    torso();

    //LEFT HAND
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS + UPPER_ARM_RADIUS), TORSO_HEIGHT, 0.0);
    glRotatef(theta[3], x, y, z);
    left_upper_arm();

    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[4], x, y, z);
    left_lower_arm();


    //RIGHT HAND
    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS + UPPER_ARM_RADIUS, TORSO_HEIGHT, 0.0);
    glRotatef(theta[5], x, y, z);
    right_upper_arm();

    glTranslatef(0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[6], x, y, z);
    right_lower_arm();


    //LEFT LEG
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS + UPPER_LEG_RADIUS), 0.1 * UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[7], x, y, z);
    left_upper_leg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[8], x, y, z);
    left_lower_leg();

    //RIGHT LEG
    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS + UPPER_LEG_RADIUS, 0.1 * UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[9], x, y, z);
    right_upper_leg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[10], x, y, z);
    right_lower_leg();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

int save_color = 0;
int auto_change_color = 0;


void get_menu_num(int num)
{
    index = num;
    if(index == 8)
        exit(0);
    else if(index == 7)
    {
        auto_change_color ^= 1;
    }
    std::cout << index << '\n';
}

void color_change()
{
    GLfloat light_diffuse[4];
    light_diffuse[0] = color_r;
    light_diffuse[1] = color_g;
    light_diffuse[2] = color_b;
    light_diffuse[3] = 1.0;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    if (auto_change_color)
    {
        if (save_color % 7 == 0)
        {
            color_r = colors[save_color][0];
            color_g = colors[save_color][1];
            color_b = colors[save_color][2];
        }
        else if (save_color % 7 == 1)
        {
            color_r = colors[save_color][0];
            color_g = colors[save_color][1];
            color_b = colors[save_color][2];
        }
        else if (save_color % 7 == 2)
        {
            color_r = colors[save_color][0];
            color_g = colors[save_color][1];
            color_b = colors[save_color][2];
        }
        else if (save_color % 7 == 3)
        {
            color_r = colors[save_color][0];
            color_g = colors[save_color][1];
            color_b = colors[save_color][2];
        }
        else if (save_color % 7 == 4)
        {
            color_r = colors[save_color][0];
            color_g = colors[save_color][1];
            color_b = colors[save_color][2];
        }
        else if (save_color % 7 == 5)
        {
            color_r = colors[save_color][0];
            color_g = colors[save_color][1];
            color_b = colors[save_color][2];
        }
        else if (save_color % 7 == 6)
        {
            color_r = colors[save_color][0];
            color_g = colors[save_color][1];
            color_b = colors[save_color][2];
        }

        save_color += 1;
        if (save_color >= 7)
            save_color = 0;
        std::cout << save_color << "\n";
    }
    else
    {
        color_r = colors[save_color][0];
        color_g = colors[save_color][1];
        color_b = colors[save_color][2];
    }
}

void update(int a)
{
    color_change();
    switch (index)
    {
        case 0:
            axis = 0;
            if (q >= 2)
            {
                theta[3] = 200.0;
                theta[4] = -20.0;
                theta[5] = 170.0;
                theta[6] = -20.0;
                theta[7] = 150.0;
                theta[8] = 60.0;
                theta[9] = 180.0;
                theta[10] = 0.0;
            }
            else
            {
                theta[3] = 170.0;
                theta[4] = -20.0;
                theta[5] = 200.0;
                theta[6] = -20.0;
                theta[7] = 180.0;
                theta[8] = 0.0;
                theta[9] = 150.0;
                theta[10] = 60.0;
            }
            q = (q + 1) % 4;
            break;

        case 1:
            axis = 0;
            if (q == 1)
            {
                theta[3] = 230.0;
                theta[4] = -90.0;
                theta[5] = 150.0;
                theta[6] = -90.0;
                theta[7] = 200.0;
                theta[8] = 30.0;
                theta[9] = 170.0;
                theta[10] = 20.0;
            }
            else
            {
                theta[3] = 130.0;
                theta[4] = -90.0;
                theta[5] = 200.0;
                theta[6] = -90.0;
                theta[7] = 170.0;
                theta[8] = 30.0;
                theta[9] = 210.0;
                theta[10] = 20.0;
            }
            q = q ? 0 : 1;
            break;

        case 2:
            if (q % 4 == 3)
            {
                theta[0] = 45.0;
                theta[3] = 120.0;
                theta[4] = -90.0;
                theta[5] = 120.0;
                theta[6] = -90.0;
                theta[7] = 180.0;
                theta[8] = 0.0;
                theta[9] = 120.0;
                theta[10] = 100.0;
            }
            else if (q % 4 == 2)
            {
                theta[0] = 45.0;
                theta[3] = 180.0;
                theta[4] = 0.0;
                theta[5] = 180.0;
                theta[6] = 0.0;
                theta[7] = 180.0;
                theta[8] = 0.0;
                theta[9] = 120.0;
                theta[10] = 0.0;
            }
            else if (q % 4 == 1)
            {
                theta[0] = 315.0;
                theta[3] = 120.0;
                theta[4] = -90.0;
                theta[5] = 120.0;
                theta[6] = -90.0;
                theta[7] = 120.0;
                theta[8] = 100.0;
                theta[9] = 180.0;
                theta[10] = 0.0;
            }
            else if(q % 4 == 0)
            {
                theta[0] = 315.0;
                theta[3] = 180.0;
                theta[4] = 0.0;
                theta[5] = 180.0;
                theta[6] = 0.0;
                theta[7] = 120.0;
                theta[8] = 0.0;
                theta[9] = 180.0;
                theta[10] = 0.0;
            }
            q++;
            break;
        case 3:
            axis = 0;
            theta[0] = 45.0, theta[1] = 90.0, theta[2] = 320.0, theta[3] = 145.0, theta[4] = 0.0, theta[5] = 225.0, theta[6] = 145.0, theta[7] = 180.0, theta[8] = 0.0, theta[9] = 180.0, theta[10] = 0.0;
            break;
        case 4:
            axis = 0;
            theta[0] = 45.0, theta[1] = 90.0, theta[2] = 320.0, theta[3] = 145.0, theta[4] = 200.0, theta[5] = 225.0, theta[6] = 0.0, theta[7] = 180.0, theta[8] = 0.0, theta[9] = 180.0, theta[10] = 0.0;
            break;
        case 5:
            axis = 1;
            if (q % 3 == 0)
            {
                theta[0] = 45.0, theta[1] = 90.0, theta[2] = 320.0, theta[3] = 145.0, theta[4] = 0.0, theta[5] = 225.0, theta[6] = 0.0, theta[7] = 180.0, theta[8] = 0.0, theta[9] = 180.0, theta[10] = 0.0;
            }
            else if (q % 3 == 1)
            {
                theta[3] = 90;
                theta[5] = 270;
                theta[6] = 0;
                theta[7] = 135;
                theta[9] = 225;
            }
            else if (q % 3 == 2)
            {
                theta[3] = 0;
                theta[5] = 0;
                theta[7] = 180;
                theta[9] = 180;
            }
            q++;
            break;
        case 6:
            axis = 1;
            theta[0] = 45.0, theta[1] = 90.0, theta[2] = 320.0, theta[3] = 145.0, theta[4] = 0.0, theta[5] = 30.0, theta[6] = 0.0, theta[7] = 180.0, theta[8] = 0.0, theta[9] = 180.0, theta[10] = 0.0;
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
    }

    display();
    glutPostRedisplay();
    glutTimerFunc(200, update, 0);
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
                10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
                10.0 * (GLfloat)w / (GLfloat)h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("robot");

    //menu
    glutCreateMenu(get_menu_num);
    glutAddMenuEntry("WALK", 0);
    glutAddMenuEntry("RUN", 1);
    glutAddMenuEntry("NORMAL DANCE", 2);
    glutAddMenuEntry("RAISE LEFT HAND", 3);
    glutAddMenuEntry("RAISE RIGHT HAND", 4);
    glutAddMenuEntry("JUMPING JACK", 5);
    glutAddMenuEntry("SALUTE", 6);
    glutAddMenuEntry("Color_change ON/OFF",7);
    glutAddMenuEntry("EXIT", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    myinit();

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutTimerFunc(200, update, 0);

    glutMainLoop();
}