#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <GL/GLU.h>	
#include <GL/glut.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

GLfloat Delta = 0.0;
static int Day = 0, Time = 0;

void MyTimer(int Value) {
	Delta = Delta + 0.001;
	Day = (Day + 2) % 360;
	Time = (Time + 1) % 360;
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vec3 position[2];
	position[0] = vec3(0, 2, 4);  
	position[1] = vec3(0, 0, 0);
	vec3 normal = normalize(cross(position[0] - position[1], vec3(1, 0, 0)));
	gluLookAt(0, 2, 4, 0, 0, 0, normal[0], normal[1], normal[2]);
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16);
	glPushMatrix();
		glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
		glTranslatef(0.7, 0.0, 0.0);
		glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
		glColor3f(0.5, 0.6, 0.7);
		glutWireSphere(0.1, 10, 8);
		glPushMatrix();
			glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
			glTranslatef(0.2, 0.0, 0.0);
			glColor3f(0.9, 0.8, 0.2);
			glutWireSphere(0.04, 10, 8);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		Day = (Day + 2) % 360;
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 1) % 360;
		glutPostRedisplay();
		break;
	default:
		break;

	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);  //윈도우 운영체제와 세션 연결
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("182583");  //윈도우 생성
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 100.0);
	glutDisplayFunc(MyDisplay);  //drawscene 함수를 디스플레이 이벤트에 대한 콜백함수로 등혹
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();//이벤트별로 콜백 함수 등록을 모두 마쳤으니 이벤트 루프로 진입하라는 의미,항상 메인함수는 이걸로 끝남
	return 0;
}