#include <cstdlib>
#include <cmath>

#include "draw.hpp"
#include "util.hpp"

// 동차 좌표계로 표시함.
static double P[12] =
{
    0.3, 0.2, 0.1, 1,
    0.7, 0.2, 0.1, 1,
    0.5, 0.7, 0.1, 1
};
static double Q[12];
static double R[12];

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 일반적인 삼각형 대신 시어핀스키 삼각형 출력.
    glColor3f(1.0, 0.0, 0.0);
    drawSierpinskiGasket4dV(P);
    glColor3f(0.0, 0.0, 1.0);
    drawSierpinskiGasket4dV(Q);
    glColor3f(0.0, 1.0, 0.0);
    drawSierpinskiGasket4dV(R);
    coord();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) 
{
    double m1[16], m2[16], m3[16];

    // 새로운 변환을 적용하는 경우에 기존 Q, R, S 행렬 초기화.
    if (key != 'i')
    {
        memset(Q, 0, 12 * sizeof(double));
        memset(R, 0, 12 * sizeof(double));
    }

    if (key == 'i') 
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else if (key == 't') 
    {
        matTrans(m1, -1, -0.5, 0);
        matPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (key == 's')
    {
        matScale(m1, 1.5, 1.2, 1.4);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'x') 
    {
        matRotateX(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'y') 
    {
        matRotateY(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'z') 
    {
        matRotateZ(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'Z') 
    {
        double temp[12];

        // 복합 변환: 고정점 회전.
        /*
         * 첫 변환으로 회전 변환을 수행한다.
         * 신축 변환 이후 기준점끼리의 거리차를 구해 평행이동한다.
         */
        matRotateZ(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);

        double dx = Q[0] - P[0];
        double dy = Q[1] - P[1];
        double dz = Q[2] - P[2];

        memcpy(temp, Q, 12 * sizeof(double));
        matTrans(m1, -dx, -dy, -dz);
        matPrint(m1);
        transformTri(m1, temp, Q);
    } 
    else if (key == 'c') 
    {
        double temp[12];

        // 복합 변환: 고정점 스케일링.
        /*
         * 첫 변환으로 신축 변환을 수행한다.
         * 신축 변환 이후 기준점끼리의 거리차를 구해 평행이동한다.
         */
        matScale(m1, 1.5, 1.2, 1.4);
        matPrint(m1);
        transformTri(m1, P, Q);

        double dx = Q[0] - P[0];
        double dy = Q[1] - P[1];
        double dz = Q[2] - P[2];

        memcpy(temp, Q, 12 * sizeof(double));
        matTrans(m1, -dx, -dy, -dz);
        matPrint(m1);
        transformTri(m1, temp, Q);
    } 
    else if (key == 'h') 
    {
        matShearX(m1, 0.5, 0);
        matPrint(m1);
        transformTri(m1, P, Q);
    } 
    else if (key == 'C')
    {
        // 커스텀 복합 변환.

        double temp[12];

        // 서로 다른 회전 변환을 차례로 적용하여 복합 변환을 수행할 수 있다.
        /*
         * 일반적으로 T1, T2라는 일련의 변환을 차례로 적용한 것은 아래 변환과 동일하다.
         * 
         * T = T2 * T1
         * T * M
         * 
         * 단, 회전과 같은 변환은 변환 행렬 적용 순서에 따라서
         * 다른 변환이 될 수 있으므로 주의가 필요하다.
         * 
         * 특히 아래의 경우 위쪽의 변환은 X축 -> Y축의 순서로 변환을 수행한다. (파란 삼각형)
         * 반면에 아래쪽의 변환은 X축 -> Y축의 순서로 변환을 수행한다. (녹색 삼각형)
         * 두 변환은 서로 순서만 다르지만 그 결과가 다름을 확인할 수 있다.
         */
        matRotateX(m1, 60);
        matPrint(m1);
        transformTri(m1, P, Q);

        memcpy(temp, Q, 12 * sizeof(double));
        matRotateY(m1, 60);
        matPrint(m1);
        transformTri(m1, temp, Q);

        matRotateY(m1, 60);
        matPrint(m1);
        transformTri(m1, P, R);

        memcpy(temp, R, 12 * sizeof(double));
        matRotateZ(m1, 60);
        matPrint(m1);
        transformTri(m1, temp, R);
    }
    else if (key == 'q')
    {
        exit(0);
    }

    glutPostRedisplay();
}

static double PrevX, PrevY;

void mouseClick(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        PrevX = x;
        PrevY = y;
    }
}

void mouseMotion(GLint x, GLint y) 
{
    glMatrixMode(GL_MODELVIEW);
    glRotated(x - PrevX, 0, 1, 0);
    glRotated(y - PrevY, 1, 0, 0);
    PrevX = x;
    PrevY = y;
    glutPostRedisplay();
}

// 메뉴와 키보드 입력을 일대일 대응시키기 위에 int -> unsigned char로 변환하여 keyboard 함수 호출.
void menuEnable(int entryID)
{
    keyboard((unsigned char)entryID, 0, 0);
}

int main(int argc, char* argv[]) 
{
    glutInit(&argc, argv);                      // GLUT 초기화.
    glutInitWindowSize(500, 500);               // 윈도우 크기.
    glutInitWindowPosition(1, 0);               // 윈도우 위치.
    glutCreateWindow("Geometric Transform");    // 윈도우 생성.
    glClearColor(1.0, 1.0, 1.0, 1.0);           // 배경색 설정.

    glutDisplayFunc(display);                   // 디스플레이 콜백 등록.
    glutKeyboardFunc(keyboard);                 // 키보드 콜백 등록.
    glutMouseFunc(mouseClick);                  // 마우스 콜백 등록.
    glutMotionFunc(mouseMotion);                // 마우스 모션 콜백 등록.

    glutCreateMenu(menuEnable);                 // 메뉴 콜백 등록.
	glutAddMenuEntry("단위 행렬 복원", 'i');
	glutAddMenuEntry("이동 변환", 't');
	glutAddMenuEntry("신축 변환", 's');
	glutAddMenuEntry("X축 회전 (Pitch, YZ)", 'x');
	glutAddMenuEntry("Y축 회전 (Roll, XZ)", 'y');
	glutAddMenuEntry("Z축 회전 (Yaw, XY)", 'z');
	glutAddMenuEntry("밀림 변환", 'h');
	glutAddMenuEntry("복합 변환: 고정점 Z축 회전 (Yaw, XY)", 'Z');
	glutAddMenuEntry("복합 변환: 고정점 스케일링", 'c');
	glutAddMenuEntry("복합 변환: 커스텀 복합 변환 (회전 변환)", 'C');
	glutAddMenuEntry("종료", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();                             // GLUT event processing loop.
    return 0;
}
