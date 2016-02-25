#include <iostream>
#include "Reader.h"
#include "Utils.h"
#include "Detecting.h"
#include "GL\glut.h"
#include "Ray.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
// http://gdcm.sourceforge.net/html/ConvertToQImage_8cxx-example.html#a9
using namespace std;
Reader* reader;
vector<int> outputValues;
vector<int> cropedValues;
vector<int> outputValuesOld;
int* HUValues;
Detecting* detect;
set<Point> edge;
vector<Point> RoI;
int windowWidthValue;
int windowCenterValue;
int screenWidth;
int screenHeight;

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); // Black background

	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	GLbyte* textureData = (GLbyte*)&outputValues[0];
    GLsizei width = reader->getWidth();
    GLsizei height = reader->getHeight();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) &outputValues[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q': {
			windowWidthValue += 20;
			outputValues = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
				windowCenterValue, windowWidthValue);
			cout << "Window width : " << windowWidthValue << "  Window center : " << windowCenterValue << endl;
		}
		break;
		case 'w': {
			windowWidthValue -= 20;
			outputValues = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
				windowCenterValue, windowWidthValue);
			cout << "Window width : " << windowWidthValue << "  Window center : " << windowCenterValue << endl;
		}
		break;
		case 'a': {
			windowCenterValue += 20;
			outputValues = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
				windowCenterValue, windowWidthValue);
			cout << "Window width : " << windowWidthValue << "  Window center : " << windowCenterValue << endl;
		}
		break;
		case 's': {
			windowCenterValue -= 20;
			outputValues = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
				windowCenterValue, windowWidthValue);
			cout << "Window width : " << windowWidthValue << "  Window center : " << windowCenterValue << endl;
		}
		break;
	}
	detect->setMonotonePicture(outputValues);
	SetupRC();
	glutPostRedisplay();

}

void mouse(int button, int state, int x, int y)
{
    if((button==GLUT_LEFT_BUTTON)&(state==GLUT_DOWN))
    {
		RoI.push_back(Point(x, screenHeight - y));
		cout << y << endl;
		cout << screenHeight - y << endl;
    }
	if ((button == GLUT_RIGHT_BUTTON)&(state == GLUT_DOWN)) {
		RoI.push_back(Point(RoI[0]));
		cropImage(outputValues, screenWidth, screenHeight, RoI);
		cv::Mat test;
		cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
		cv::imshow("Display window", test);                   // Show our image inside it.

		cv::waitKey(0);                                          // Wait for a keystroke in the window
		//detect->setRoI(RoI);
	}
	SetupRC();
	glutPostRedisplay();
}

void TextureRender(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window with current clearing color
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glPushMatrix();
    glDisable(GL_LIGHTING); // Draw plane that the cube rests on
    glEnable(GL_TEXTURE_2D); // should use shader, but for an example fixed pipeline is ok
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_TRIANGLE_STRIP); // draw something with the texture on

    glTexCoord2f(0.0, 0.0);
    glVertex2f(0, screenHeight);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(screenWidth, screenHeight);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(0, 0);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(screenWidth, 0);

    glEnd();

    glPopMatrix();

	//here we draw our polygon for croping
	if (RoI.size() > 1) {
		for (int i = 1; i < RoI.size(); i++) {
			glBegin(GL_LINES);
			glVertex3f(RoI[i - 1].getX(), RoI[i - 1].getY(), 0.0);
			glVertex3f(RoI[i].getX(), RoI[i].getY(), 0.0);
			glEnd();
		}
	}
    glFlush();
    glutSwapBuffers(); // Flush drawing commands
	
	
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
    	cout << "Wrong count of arguments" <<endl;
		return 0;
    }
    string nameOfFile(argv[1]);
    reader = new Reader(nameOfFile);
    char* buffer = reader->readFile();
    //Parse DICOM and fill corresponding fields (such as HU, width/center of transform etc)
	reader->initializeHUValuesFromUInt16(buffer);
	//Get this values
    HUValues =  reader->getHUArray();
	windowCenterValue = reader->getWindowCenter();
	windowWidthValue = reader->getWindowWidth();
	cout << "Window width : " << windowWidthValue << "  Window center : " << windowCenterValue << endl;
    outputValues = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
		windowCenterValue, windowWidthValue);
    outputValuesOld = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
		windowCenterValue, windowWidthValue);
	detect = new Detecting(reader->getWidth(), reader->getHeight());
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_LUMINANCE | GLUT_DEPTH);
	screenWidth = reader->getWidth();
	screenHeight = reader->getHeight();
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("2D Image Texture");
	glutDisplayFunc(&TextureRender);
	SetupRC();
    glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

    return 0;
}
