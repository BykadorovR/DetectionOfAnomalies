#include <iostream>
#include "Reader.h"
#include "Utils.h"
#include "Detecting.h"
#include <GL/glut.h>
#include "Ray.h"
// http://gdcm.sourceforge.net/html/ConvertToQImage_8cxx-example.html#a9
using namespace std;
Reader* reader;
int* outputValues;
int* outputValuesOld;
int* HUValues;
Detecting* detect;
set<Point> edge;


void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); // Black background
    GLbyte* textureData = (GLbyte*)outputValues;
    GLsizei width = reader->getWidth();
    GLsizei height = reader->getHeight();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) outputValues);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


void mouse(int button, int state, int x, int y)
{
    if((button==GLUT_LEFT_BUTTON)&(state==GLUT_DOWN))
    {
        detect->setNullForArray();
        edge.clear();
        detect->stepOfRays(x, y);
        /*vector<Point> afterDetecting = *detect->getArrayOfPoints();
        for (int i = 0; i < afterDetecting.size(); i++) {
            outputValues[afterDetecting[i].getX()+afterDetecting[i].getY()*reader->getWidth()] = 255;
        }
        */
        //int distLe = distL;
        //int distRe = distR;
        //cout << distLe << "  " << distRe << "  "<< x <<endl;
        //cout << x << " " << y << endl;
        //Сделать пропорционально длине деление на куски *чем длиннее, тем больше кусков разбиения*
        //for (int i=1; i<=3; i++) {
           //stepOfRays(x, y);
          // cout <<(x-distLe)+i*(distLe)/4<<endl;
          // cout <<(x+distRe)-i*(distRe)/4<<endl;
           //stepOfRays((x-distLe)+i*(distLe)/4, y);

        //}
        //for (int i=3; i<=1; i--) {
          //  stepOfRays((x+distRe)-i*(distRe)/4, y);
        //}
/*
        int tres = dispersion(edge, pt) + mean(edge, pt);
        set<Point>::iterator i;
        for (i = edge.begin(); i != edge.end(); i++) {
            int local = abs (x - (*i).getX());
            //cout << local << endl;
            if (local < tres) {
                for (int j = x; j < (*i).getX(); j++) {
                    outputValues[j+(*i).getY()*reader->getWidth()] = 255;
                }
                for (int j = x; j > (*i).getX(); j--) {
                    outputValues[j+(*i).getY()*reader->getWidth()] = 255;
                }
            }
        }
*/


        //for (int i = 0; i < ; i++) {
          //  outputValues[(*i).getX()+(*i).getY()*reader->getWidth()] = 255;

        //}

        //cout << dispersion(edge, pt) << " DISPERSION" << endl;
        //cout << mean(edge, pt) << " Math. Ojidanie" << endl;
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
    glVertex2f(-1.0, 1.0);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(1.0, 1.0);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(-1.0, -1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);

    glEnd();

    glPopMatrix();

    glFlush();
    glutSwapBuffers(); // Flush drawing commands
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
    	cout << "Wrong count of arguments" <<endl;
    }
    string nameOfFile(argv[1]);
    reader = new Reader(nameOfFile);
    char* buffer = reader->readFile();
    reader->initializeHUValuesFromUInt16(buffer);
    HUValues =  reader->getHUArray();

    outputValues = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
        reader->getWindowCenter(), reader->getWindowWidth());
    outputValuesOld = fromUInt16ToUInt8(HUValues, reader->getWidth()*reader->getHeight(),
        reader->getWindowCenter(), reader->getWindowWidth());

    detect = new Detecting(outputValues, reader->getWidth(), reader->getHeight());


    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_LUMINANCE | GLUT_DEPTH);
	glutInitWindowSize(reader->getWidth(),reader->getHeight());
	glutCreateWindow("2D Image Texture");
	glutDisplayFunc(&TextureRender);
	SetupRC();
    glutMouseFunc(mouse);
	glutMainLoop();

    return 0;
}
