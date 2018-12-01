#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <iostream>
using namespace std;
const double PI = 3.14159265;
const int WHOLELENGTH = 15000;


void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,800.0);
}
struct vertex{
    double x;
    double y;
    vertex(){}
    vertex(double xx, double yy):x(xx), y(yy){}
};
struct rgb{
    double r;
    double g;
    double b;
    rgb(){}
    rgb(double rr, double gg, double bb):r(rr), g(gg), b(bb){}
};
vector<rgb> randomColor;
vector<rgb> skinColor;
vector<int> randomStarY;

void initiateRandom(){
    for (int i = 0; i < 100; ++i) {
        randomColor.push_back(rgb(rand()%100/100.0, rand()%100/100.0, rand()%100/100.0));
    }
    skinColor.push_back(rgb(233/255.0, 150/255.0, 122/255.0));
    skinColor.push_back(rgb(139/255.0,69/255.0,19/255.0));
    skinColor.push_back(rgb(250/255.0,240/255.0,230/255.0));
    skinColor.push_back(rgb(160/255.0,82/255.0,45/255.0));
    skinColor.push_back(rgb(255/255.0,222/255.0,173/255.0));
    skinColor.push_back(rgb(210/255.0,105/255.0,30/255.0));
    skinColor.push_back(rgb(230/255.0,190/255.0,138/255.0));
    for (int j = 0; j < 1000; ++j) {
        randomStarY.push_back(rand()%1000);
    }
}

// regular star
vector<vertex> makeStar(int x, int y, double radius){
    vector<vertex> answer;
    double innerR = 0.39*radius;
    answer.push_back(vertex(x + radius*cos(PI/10.0), y + radius*sin(PI/10.0)));
    answer.push_back(vertex(x + innerR*cos(PI*0.3), y + innerR*sin(PI*0.3)));
    answer.push_back(vertex(x, y + radius));
    answer.push_back(vertex(x - innerR*cos(PI*0.3), y + innerR*sin(PI*0.3)));
    answer.push_back(vertex(x - radius*cos(PI/10.0), y + radius*sin(PI/10.0)));
    /////
    answer.push_back(vertex(x - innerR*cos(PI/10.0), y - innerR*sin(PI/10.0)));
    answer.push_back(vertex(x - radius*sin(PI/5.0), y - radius*cos(PI/5.0)));
    answer.push_back(vertex(x, y - innerR));
    answer.push_back(vertex(x + radius*sin(PI/5.0), y - radius*cos(PI/5.0)));
    answer.push_back(vertex(x + innerR*cos(PI/10.0), y - innerR*sin(PI/10.0)));
    return answer;
}
// slant star
vector<vertex> makeStar2(int x, int y, double radius){
    vector<vertex> answer;
    double innerR = 0.39*radius;
    answer.push_back(vertex(x + innerR*cos(PI/10.0), y + innerR*sin(PI/10.0)));
    answer.push_back(vertex(x + radius*cos(PI*0.3), y + radius*sin(PI*0.3)));
    answer.push_back(vertex(x, y + innerR));
    answer.push_back(vertex(x - radius*cos(PI*0.3), y + radius*sin(PI*0.3)));
    answer.push_back(vertex(x - innerR*cos(PI/10.0), y + innerR*sin(PI/10.0)));
    /////
    answer.push_back(vertex(x - radius*cos(PI/10.0), y - radius*sin(PI/10.0)));
    answer.push_back(vertex(x - innerR*sin(PI/5.0), y - innerR*cos(PI/5.0)));
    answer.push_back(vertex(x, y - radius));
    answer.push_back(vertex(x + innerR*sin(PI/5.0), y - innerR*cos(PI/5.0)));
    answer.push_back(vertex(x + radius*cos(PI/10.0), y - radius*sin(PI/10.0)));
    return answer;
}
//INSTANT STAR
void drawStar(int x, int y, double radius){
    double innerR = 0.39*radius;
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2d(x + innerR*cos(PI/10.0), y - innerR*sin(PI/10.0));
    glVertex2d(x + radius*sin(PI/5.0), y - radius*cos(PI/5.0));
    glVertex2d(x, y - innerR);
    glVertex2d(x - radius*sin(PI/5.0), y - radius*cos(PI/5.0));
    glVertex2d(x - innerR*cos(PI/10.0), y - innerR*sin(PI/10.0));
    /////
    glVertex2d(x - radius*cos(PI/10.0), y + radius*sin(PI/10.0));
    glVertex2d(x - innerR*cos(PI*0.3), y + innerR*sin(PI*0.3));
    glVertex2d(x, y + radius);
    glVertex2d(x + innerR*cos(PI*0.3), y + innerR*sin(PI*0.3));
    glVertex2d(x + radius*cos(PI/10.0), y + radius*sin(PI/10.0));
    glEnd();
}
// Equestrian WORDS
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
// draw circle
void circle (double x, double y, double r){
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    for(int i = 0; i<72; i++){
        glVertex2d(x+r*cos(i*PI/36), y-r*sin(i*PI/36));
    }
    glEnd();
}
// draw top half circle
void halfCircle (double x, double y, double r){
    glBegin(GL_POLYGON);
    for(int i = 0; i<38; i++){
        glVertex2d(x+r*cos((i+34)*PI/36), y-r*sin((i+34)*PI/36));
    }
    glEnd();
}
//SKY
void drawSky(){
    for (int m = 0; m < 32; ++m) {
        glLineWidth(1);
        glColor3d((0.0 - m) / 255.0, (191.0 - 2.5 * m) / 255.0, (255.0) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(0, 210+ m * 20);
        glVertex2i(WHOLELENGTH, 210+ m * 20);
        glVertex2i(WHOLELENGTH, 210+ m * 20 + 20);
        glVertex2i(0, 210+ m * 20 + 20);
        glEnd();
    }
}
void drawSky2(){
    for (int m = 0; m < 300; ++m) {
        glLineWidth(1);
        glColor3d((0.0 - m) / 255.0, (191.0 - 2.5 * m) / 255.0, (255.0-m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(10000, 210+ m * 20);
        glVertex2i(WHOLELENGTH, 210+ m * 20);
        glVertex2i(WHOLELENGTH, 210+ m * 20 + 20);
        glVertex2i(10000, 210+ m * 20 + 20);
        glEnd();
    }
}
void drawStars(){
    glColor3d(1,1,1);
    for (int j = 0; j < 500; ++j) {
        drawStar(12000+j*20, 3700+randomStarY[j], max(5, rand() % 15));
    }
}
//CLOUD
void drawCloud(){
    glColor3d(1,1,1);
    for (int i = 0; i < 200; ++i) {
        glPushMatrix();
        glTranslated(250+700*i, 680, 0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(0, 0);
        glVertex2i(70, 0);
        glVertex2i(70, 30);
        glVertex2i(0, 30);
        glEnd();
        circle(0,15,15);
        circle(70,15,15);
        halfCircle(35,20,35);
        glPopMatrix();
    }
    for (int i = 0; i < 200; ++i) {
        glPushMatrix();
        glTranslated(130+1100*i, 750, 0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(0, 0);
        glVertex2i(90, 0);
        glVertex2i(90, 30);
        glVertex2i(0, 30);
        glEnd();
        circle(0,15,15);
        circle(95,20,20);
        halfCircle(25,20,25);
        halfCircle(60,20,35);
        glPopMatrix();
    }
}
//GRASS
void drawGrass(){
    int distance = 700;
    int plus = 10;
    for (int i = 0; i < 20; ++i) {
        glColor3d(0/255.0, 128/255.0, 0/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance, 330+plus);
        glVertex2i(i*distance+5, 400+plus);
        glVertex2i(i*distance+10, 330+plus);
        glEnd();
        glColor3d(34/255.0, 139/255.0, 34/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance+0, 330+plus);
        glVertex2i(i*distance+25, 390+plus);
        glVertex2i(i*distance+20, 330+plus);
        glEnd();
        glColor3d(0/255.0, 100/255.0, 0/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance+5, 330+plus);
        glVertex2i(i*distance-10, 390+plus);
        glVertex2i(i*distance-10, 330+plus);
        glEnd();
    }
    distance = 1100;
    for (int i = 0; i < 15; ++i) {
        glColor3d(128/255.0, 128/255.0, 0/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance, 350);
        glVertex2i(i*distance+5, 420);
        glVertex2i(i*distance+10, 350);
        glEnd();
        glColor3d(85/255.0, 107/255.0, 47/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance+0, 350);
        glVertex2i(i*distance+25, 410);
        glVertex2i(i*distance+20, 350);
        glEnd();
        glColor3d(107/255.0, 142/255.0, 35/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance+5, 350);
        glVertex2i(i*distance-10, 410);
        glVertex2i(i*distance-10, 350);
        glEnd();
        glColor3d(107/255.0, 142/255.0, 35/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance+0, 350);
        glVertex2i(i*distance+40, 390);
        glVertex2i(i*distance+20, 350);
        glEnd();
        glColor3d(128/255.0, 128/255.0, 0/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(i*distance+5, 350);
        glVertex2i(i*distance-30, 400);
        glVertex2i(i*distance-10, 350);
        glEnd();
    }
}
void drawSingleGrass1(){
    int plus = 10-330;
    glColor3d(0/255.0, 128/255.0, 0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(0, 330+plus);
    glVertex2i(5, 400+plus);
    glVertex2i(10, 330+plus);
    glEnd();
    glColor3d(34/255.0, 139/255.0, 34/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(0, 330+plus);
    glVertex2i(25, 390+plus);
    glVertex2i(20, 330+plus);
    glEnd();
    glColor3d(0/255.0, 100/255.0, 0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(5, 330+plus);
    glVertex2i(-10, 390+plus);
    glVertex2i(-10, 330+plus);
    glEnd();
}
void drawSingleGrass2(){
    int plus = -350;
    glColor3d(128/255.0, 128/255.0, 0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(0, 350+plus);
    glVertex2i(5, 420+plus);
    glVertex2i(10, 350+plus);
    glEnd();
    glColor3d(85/255.0, 107/255.0, 47/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(0, 350+plus);
    glVertex2i(25, 410+plus);
    glVertex2i(20, 350+plus);
    glEnd();
    glColor3d(107/255.0, 142/255.0, 35/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(5, 350+plus);
    glVertex2i(10, 410+plus);
    glVertex2i(10, 350+plus);
    glEnd();
    glColor3d(107/255.0, 142/255.0, 35/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(0, 350+plus);
    glVertex2i(40, 390+plus);
    glVertex2i(20, 350+plus);
    glEnd();
    glColor3d(128/255.0, 128/255.0, 0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(5, 350+plus);
    glVertex2i(-30, 400+plus);
    glVertex2i(-10, 350+plus);
    glEnd();
}
//DESERT
void drawDesert(){
    for (int m = 0; m < 35; ++m) {
        glLineWidth(1);
        //grass
        //glColor3d(0.0/255.0, (128-3*m)/255.0, 0.0);
        //dessert
        glColor3d((255)/255.0, (228-m*2)/255.0, (181-m*2)/255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(0, m*10);
        glVertex2i(WHOLELENGTH, m*10);
        glVertex2i(WHOLELENGTH, m*10+20);
        glVertex2i(0, m*10+20);
        glEnd();
    }
}
//WALL
void drawWall(){

    for (int m = 0; m < 60; ++m) {
        glLineWidth(1);
        glColor3d((169.0 - 1.5*m) / 255.0, (169.0 - 1.5*m) / 255.0, (169.0-1.5*m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(0, 210+ m * 10);
        glVertex2i(800, 210+ m * 10);
        glVertex2i(800, 210+ m * 10 + 10);
        glVertex2i(0, 210+ m * 10 + 10);
        glEnd();
    }
/*
    int plus = 50;
    for (int m = 0; m < 600; ++m) {
        glLineWidth(1);
        glColor3d((169.0 - 0.2*m+plus) / 255.0, (169.0 - 0.2*m+plus) / 255.0, (169.0-0.2*m+plus) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(0, 210+ m);
        glVertex2i(800, 210+ m);
        glEnd();
    }*/
}
//Viewer AUDITORIUM
void drawAuditorium(){
    for (int m = 0; m < 27; ++m) {
        glLineWidth(1);
        glColor3d((75.0-2.2*23 + 2.5*m) / 255.0, (0.0 ) / 255.0, (130.0-2.2*23+ 2.5*m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2i(1050, 210+ m * 20);
        glVertex2i(4010, 210+ m * 20);
        glVertex2i(4010, 210+ m * 20 + 20);
        glVertex2i(1050, 210+ m * 20 + 20);
        glEnd();
    }
}
//VIEWERS
void drawViewerShirt(){
    int y = 0;
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(0+y, 0+y);
    glVertex2i(30+y, 0+y);
    glVertex2i(30+y, 35+y);
    glVertex2i(0+y, 35+y);
    glEnd();
}
void drawViewerHands(double speed, double t){
    //cout<<speed<<'\t'<<t<<endl;
    int y = 0;
    speed *= 6;
    double frequency = t;
    glPushMatrix();
    glRotated(speed*cos(frequency), 0,0,1);
    glLineWidth(7);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(20+y, 20+y);
    glVertex2i(50+y, 50+y);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glRotated(speed*cos(frequency), 0,0,1);
    glLineWidth(7);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);

    glVertex2i(13+y, 20+y);
    glVertex2i(-20+y, 50+y);
    glEnd();
    glPopMatrix();
}
void drawViewers(double t, int trans){
    //glPushMatrix();
    //glTranslated(trans,0,0);
    for (int i = 0; i < 5; ++i) {
        //glPushMatrix();
        //glTranslated(trans,0,0);
        for (int j = 0; j < 42; ++j) {
            int tmp = 17*i+j;
            tmp = tmp%39;
            int tmp2 = tmp%7;
            glPushMatrix();
            glTranslated(1070+j*70 + trans,400+i*70,0);
            glColor3d(skinColor[tmp2].r, skinColor[tmp2].g, skinColor[tmp2].b);
            circle(15, 46, 13);
            drawViewerHands(1, t+tmp2*10);
            glPopMatrix();
            glPushMatrix();
            glTranslated(1070+j*70 + trans,400+i*70,0);
            glColor3d(randomColor[tmp].r, randomColor[tmp].g, randomColor[tmp].b);
            drawViewerShirt();
            glPopMatrix();
        }
        //glPopMatrix();
    }
    //glPopMatrix();
}
//VIEWERS END

//FENCE
void drawFence(){
    for (int m = 0; m < 10; ++m) {
        glLineWidth(1);
        glColor3d((175 + 5*m) / 255.0, (175.0 + 5*m) / 255.0, (175.0+5*m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(0, 375+ m );
        glVertex2i(WHOLELENGTH, 375+ m);
        glEnd();
    }
    for (int m = 0; m < 10; ++m) {
        glLineWidth(1);
        glColor3d((175 + 5*m) / 255.0, (175.0 + 5*m) / 255.0, (175.0+5*m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(0, 405+ m );
        glVertex2i(WHOLELENGTH, 405+ m);
        glEnd();
    }
    for (int i = 0; i < 100; ++i) {
        for (int m = 0; m < 20; ++m) {
            glLineWidth(1);
            glColor3d((175 + 5*m) / 255.0, (175.0 + 5*m) / 255.0, (175.0+5*m) / 255.0);
            glPolygonMode(GL_FRONT, GL_FILL);
            glBegin(GL_LINE_STRIP);
            glVertex2i(i*250+m, 425);
            glVertex2i(i*250+m, 350);
            glEnd();
        }
    }
}
//ROD
void drawVerticalRod(){
    for (int m = 0; m < 30; ++m) {
        glLineWidth(1);
        glColor3d((175 + 3 * m) / 255.0, (175.0 + 3 * m) / 255.0, (175.0 + 3 * m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(m, 175);
        glVertex2i(m, 0);
        glEnd();
    }
}
void drawVerticalRod2(){
    for (int m = 0; m < 30; ++m) {
        glLineWidth(1);
        glColor3d((175 + 3 * m) / 255.0, (175.0 + 3 * m) / 255.0, (175.0 + 3 * m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(m, 3700);
        glVertex2i(m, 0);
        glEnd();
    }
}
void drawHorizontalRod(){
    for (int m = 0; m < 20; ++m) {
        glLineWidth(1);
        glColor3d((235 - 3 * m) / 255.0, (235.0 - 3 * m) / 255.0, (235.0 - 3 * m) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(0, m);
        glVertex2i(300, m);
        glEnd();
    }
}
//BARRIER
void drawBarrier1(){
    int x = 0;
    int y = 0;
    glPushMatrix();
    glTranslated(1775+x, 300, 0);
    drawSingleGrass2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1830+x, 290, 0);
    drawSingleGrass1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1800+x, 300, 0);
    drawVerticalRod();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1922+x, 180, 0);
    glRotated(110, 0, 0, 1);
    drawHorizontalRod();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1922+x, 80, 0);
    glRotated(110, 0, 0, 1);
    drawHorizontalRod();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1875+x, 20, 0);
    drawSingleGrass1();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1930+x, 30, 0);
    drawSingleGrass2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1900+x, 30, 0);
    drawVerticalRod();
    glPopMatrix();
}
void drawWater(){
    for (int m = 0; m < 40; ++m) {
        glLineWidth(5);
        glColor3d(0 / 255.0, (191.0 + 1.5 * m) / 255.0, (255.0 ) / 255.0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(0-3*m, 5*m);
        glVertex2i(600-3*m, 5*m);
        glEnd();
    }
}
void drawBarrier2(){
    int x = 0;
    glPushMatrix();
    glTranslated(2500+x, 150, 0);
    drawWater();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2450+x, 345, 0);
    drawSingleGrass2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(2600+x, 338, 0);
    drawSingleGrass1();
    glPopMatrix();
    glPushMatrix();
    glTranslated(2800+x, 347, 0);
    drawSingleGrass2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2500+x, 135, 0);
    drawSingleGrass1();
    glPopMatrix();
    glPushMatrix();
    glTranslated(2700+x, 145, 0);
    drawSingleGrass2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(2900+x, 135, 0);
    drawSingleGrass1();
    glPopMatrix();
}
void drawBarrier3(){
    int x = 0;
    int y = 0;
    glPushMatrix();
    glTranslated(1775+x, 300, 0);
    drawSingleGrass2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1830+x, 290, 0);
    drawSingleGrass1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1800+x, 300, 0);
    drawVerticalRod2();
    glPopMatrix();

    for (int i = 0; i < 18; ++i) {

        glPushMatrix();
        glTranslated(1922+x, 80+i*200, 0);
        glRotated(110, 0, 0, 1);
        drawHorizontalRod();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(1875+x, 20, 0);
    drawSingleGrass1();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1930+x, 30, 0);
    drawSingleGrass2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1900+x, 30, 0);
    drawVerticalRod2();
    glPopMatrix();
}

//BARRIER END
//FLAG
void drawFlag(double t){
    int plus = 25;
    /*glLineWidth(1);
    for (int k = 0; k < 300; ++k) {
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glColor3d((128)/255.0,k/255.0,k/255.0);
        glVertex2i( 150, 450+k*1);
        glVertex2i( 650, 450+k*1);
        glEnd();
    }*/
    if(t<14) {
        // U //
        glLineWidth(7);
        glColor3d(255 / 255.0, 215 / 255.0, 0);
        glEnable(GL_LINE_SMOOTH);
        glBegin(GL_LINE_STRIP);
        //mid
        glVertex2i(400, 575 + plus);
        glVertex2i(425, 580 + plus);
        glVertex2i(450, 595 + plus);
        glVertex2i(450, 700 + plus);
        glVertex2i(465, 700 + plus);
        //out low
        glVertex2i(465, 582 + plus);
        glVertex2i(445, 567 + plus);
        //mid low
        glVertex2i(415, 555 + plus);
        glVertex2i(385, 555 + plus);
        glVertex2i(355, 567 + plus);
        //out low
        glVertex2i(335, 582 + plus);
        glVertex2i(335, 700 + plus);
        glVertex2i(350, 700 + plus);
        glVertex2i(350, 595 + plus);
        glVertex2i(375, 580 + plus);
        glVertex2i(400, 575 + plus);
        glEnd();
    }

    // Star //
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 5-max(0, int((t-6.3)*0.8)); ++j) {
            double colorTmp = (155+i*5)/255.0;
            double colorTmp2 = (20+i*5)/255.0;
            if (j == 0)
                glColor3d(0, 0, colorTmp);
            else if (j == 1)
                glColor3d(colorTmp, colorTmp, 0);
            else if (j == 2)
                glColor3d(colorTmp2, colorTmp2, colorTmp2);
            else if (j == 3)
                glColor3d(0, colorTmp, 0);
            else if (j == 4)
                glColor3d(colorTmp, 0, 0);
            /*
            if (j == 0)
                glColor3d(0 / 255.0, 0 / 255.0, 128 / 255.0);
            else if (j == 1)
                glColor3d(204 / 255.0, 204 / 255.0, 0);
            else if (j == 2)
                glColor3d(0, 0, 0);
            else if (j == 3)
                glColor3d(0, 100 / 255.0, 0);
            else if (j == 4)
                glColor3d(139 / 255.0, 0 / 255.0, 0 / 255.0);*/

            glPolygonMode(GL_FRONT, GL_FILL);
            glBegin(GL_POLYGON);
            vector<vertex> starVertex;
            vector<vertex> starVertex2;
            int size = 40-2*i;
            if (j == 0) {
                starVertex = makeStar2(250, 590 + plus, size);
            } else if (j == 1) {
                starVertex = makeStar2(300, 500 + plus, size);
            } else if (j == 2) {
                starVertex = makeStar(400, 475 + plus, size);
            } else if (j == 3) {
                starVertex = makeStar2(500, 500 + plus, size);
            } else if (j == 4) {
                starVertex = makeStar2(550, 590 + plus, size);
            }

            if (j == 2) {
                for (int i = 0; i < 10; ++i) {
                    glVertex2i(starVertex[9 - i].x, starVertex[9 - i].y);
                }
            } else {
                for (int i = 0; i < 10; ++i) {
                    glVertex2i(starVertex[i].x, starVertex[i].y);
                }
            }
            glEnd();
        }
    }
}
//COUNT DOWN
void draw3(){
    glColor3d(55/255.0, 55/255.0, 55/255.0);
    circle(500,450,130);
    glColor3d(195/255.0, 195/255.0, 195/255.0);
    circle(500,450,115);
    glLineWidth(15);
    glColor3d(0/255.0, 0/255.0, 0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(450,500);
    glVertex2i(550,500);
    glVertex2i(550,450);
    glVertex2i(450,450);
    glVertex2i(550,450);
    glVertex2i(550,400);
    glVertex2i(450,400);
    glEnd();
}
void draw2(){
    glColor3d(55/255.0, 55/255.0, 55/255.0);
    circle(500,450,130);
    glColor3d(195/255.0, 195/255.0, 195/255.0);
    circle(500,450,115);
    glLineWidth(15);
    glColor3d(0/255.0, 0/255.0, 0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(450,500);
    glVertex2i(550,500);
    glVertex2i(550,450);
    glVertex2i(450,450);
    glVertex2i(450,400);
    glVertex2i(550,400);
    glEnd();
}
void draw1(){
    glColor3d(55/255.0, 55/255.0, 55/255.0);
    circle(500,450,130);
    glColor3d(195/255.0, 195/255.0, 195/255.0);
    circle(500,450,115);
    glLineWidth(15);
    glColor3d(0/255.0, 0/255.0, 0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(500,500);
    glVertex2i(500,400);
    glEnd();
}
//COUNT DOWN END

// Horse
void drawHorse(int x, int y, int mode, double t){ //mode 0 not moving, 1 moving slow
    int speed = 4;
    int moveScale = 15;
    int tailMoveScale = 2;
    if (mode==2){
        moveScale = 50;
        speed = 3;
        tailMoveScale = 4;
    }
    int xMin = -210;
    int yMin = -75;
    x += xMin;
    y += yMin;


    //legs
    //back
    if (mode!=0) {
        glPushMatrix();
        glTranslated(90, 80, 0);
        if (mode==1)
            glRotated(moveScale * cos(speed * t), 0, 0, 1);
        else if (mode==2)
            glRotated(moveScale * cos(speed * t+PI/3), 0, 0, 1);
        else if (mode==3 || mode==4)
            glRotated(-72, 0, 0, 1);

        glTranslated(-100, -75, 0);
        if (mode==2){
            glTranslated(8, 5, 0);
        } else if(mode==3 || mode==4){
            glTranslated(-10, 10, 0);

        }
    }
    glLineWidth(100);
    glColor3d(102.0/255.0, 51.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    if (mode!=0) {
        glVertex2i(x + 310, y + 150);
        glVertex2i(x + 335, y + 150);
        glVertex2i(x + 335, y + 75);
        glVertex2i(x + 310, y + 75);
    } else {
        glVertex2i(x + 310, y + 150);
        glVertex2i(x + 335, y + 150);
        glVertex2i(x + 360, y + 75);
        glVertex2i(x + 335, y + 75);
    }
    glEnd();
    if (mode==1 || mode==2) {
        glPopMatrix();
    }

    if (mode==1) {
        glPushMatrix();
        glTranslated(100, 80, 0);
        glRotated(-moveScale * cos(speed * t), 0, 0, 1);
        glTranslated(-100, -75, 0);
    } else if(mode==2){
        glPushMatrix();
        glTranslated(100, 80, 0);
        glRotated(moveScale * cos(speed * t+PI/3+PI/6), 0, 0, 1);
        glTranslated(-100, -75, 0);

    }
    glLineWidth(100);
    glColor3d(153.0/255.0, 76.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);

    if (mode!=0) {
        glVertex2i(x + 300, y + 150);
        glVertex2i(x + 325, y + 150);
        glVertex2i(x + 325, y + 75);
        glVertex2i(x + 300, y + 75);
    } else {
        glVertex2i(x + 300, y + 150);
        glVertex2i(x + 325, y + 150);
        glVertex2i(x + 300, y + 75);
        glVertex2i(x + 275, y + 75);
    }
    glEnd();
    if (mode!=0) {
        glPopMatrix();
    }
    //front
    if (mode!=0) {
        glPushMatrix();
        glTranslated(265, 80, 0);
        if (mode==3 || mode==4)
            glRotated(72, 0, 0, 1);
        else
            glRotated(-moveScale * cos(speed * t), 0, 0, 1);

        glTranslated(-265, -75, 0);
    }
    glColor3d(102.0/255.0, 51.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    if (mode!=0) {
        glVertex2i(x + 470, y + 150);
        glVertex2i(x + 495, y + 150);
        glVertex2i(x + 495, y + 75);
        glVertex2i(x + 470, y + 75);
    } else {
        glVertex2i(x + 470, y + 150);
        glVertex2i(x + 495, y + 150);
        glVertex2i(x + 520, y + 75);
        glVertex2i(x + 495, y + 75);
    }
    glEnd();
    if (mode==1 || mode==2) {
        glPopMatrix();
    }

    if (mode==1) {
        glPushMatrix();
        glTranslated(266, 80, 0);
        glRotated(moveScale * cos(speed * t), 0, 0, 1);
        glTranslated(-265, -75, 0);
    } else if (mode==2) {
        glPushMatrix();
        glTranslated(266, 80, 0);
        glRotated(-moveScale * cos(speed * t+PI/6), 0, 0, 1);
        glTranslated(-265, -75, 0);
    }
    glLineWidth(100);
    glColor3d(153.0/255.0, 76.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    if (mode!=0) {
        glVertex2i(x + 475, y + 150);
        glVertex2i(x + 500, y + 150);
        glVertex2i(x + 500, y + 75);
        glVertex2i(x + 475, y + 75);
    } else {
        glVertex2i(x + 475, y + 150);
        glVertex2i(x + 500, y + 150);
        glVertex2i(x + 475, y + 75);
        glVertex2i(x + 450, y + 75);
    }
    glEnd();
    if (mode!=0) {
        glPopMatrix();
    }
    //legs end

    //horse body
    glColor3d(153.0/255.0, 76.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(x+300, y+150);
    glVertex2i(x+500, y+150);
    glVertex2i(x+500, y+250);
    glVertex2i(x+300, y+250);
    glEnd();

    //saddle
    glColor3d(188.0/255.0, 188.0/255.0, 188.0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(x+380, y+200);
    glVertex2i(x+450, y+200);
    glVertex2i(x+450, y+253);
    glVertex2i(x+370, y+253);
    glEnd();
    glColor3d(0, 0, 0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(x+385, y+205);
    glVertex2i(x+445, y+205);
    glVertex2i(x+445, y+253);
    glVertex2i(x+375, y+253);
    glEnd();
    //head
    glColor3d(153.0/255.0, 76.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(x+500, y+200);
    glVertex2i(x+450, y+250);
    glVertex2i(x+520, y+350);
    glVertex2i(x+550, y+300);
    glEnd();
    glLineWidth(100);
    //face
    glColor3d(153.0/255.0, 76.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(x+520, y+350);
    glVertex2i(x+565, y+275);
    glVertex2i(x+550, y+250);
    glVertex2i(x+525, y+280);
    glEnd();
    glColor3d(1,1,1);
    circle(x+533, y+310,5);
    glColor3d(0,0,0);
    circle(x+533, y+310,3);
    //fur
    glColor3d(51.0/255.0, 25.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+448, y+245);
    glVertex2i(x+520, y+350);
    glEnd();

    //tail
    if (mode!=0) {
        glPushMatrix();
        glTranslated(90, 175, 0);
        glRotated( tailMoveScale*cos(speed * t), 0, 0, 1);
        glTranslated(-90, -175, 0);
    }
    glLineWidth(100);
    glColor3d(51.0/255.0, 25.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(x+240, y+210);
    glVertex2i(x+210, y+125);
    glVertex2i(x+300, y+250);
    glEnd();
    if (mode!=0) {
        glPopMatrix();
    }
}
// draw Rider
void drawRiderNormal(int x, int y, int mode, double t){
    int moveScale = 4;
    int speed = 3;
    if (mode==2){
        moveScale = 8;
        speed = 3;
    }
    int xMin = -210;
    int yMin = -75;
    x += xMin;
    y += yMin;
    //people
    //below waist
    glLineWidth(20);
    glEnable(GL_LINE_SMOOTH);
    glColor3d(255.0/255.0, 255.0/255.0, 255.0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+392, y+250);
    glVertex2i(x+445, y+220);
    glEnd();
    glEnable(GL_LINE_SMOOTH);
    glColor3d(255.0/255.0, 255.0/255.0, 255.0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+440, y+225);
    glVertex2i(x+410, y+185);
    glEnd();
    //shoe
    glLineWidth(20);
    glEnable(GL_LINE_SMOOTH);
    glColor3d(0.0/255.0, 0.0/255.0, 0.0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(x+400, y+190);
    glVertex2i(x+435, y+180);
    glVertex2i(x+433, y+165);
    glVertex2i(x+400, y+168);
    glEnd();
    //shirt
    glLineWidth(30);
    glColor3d(0.0/255.0, 0.0/255.0, 100.0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+400, y+315);
    glVertex2i(x+400, y+245);
    glEnd();
    //hand
    if (mode==1 || mode==2) {
        glPushMatrix();
        glTranslated(230, 260, 0);
        glRotated(moveScale * cos(speed * t), 0, 0, 1);
        glTranslated(-230, -260, 0);
    }
    glLineWidth(30);
    glColor3d(0.0/255.0, 0.0/255.0, 100.0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+440, y+268);
    glVertex2i(x+400, y+300);
    glEnd();
    glLineWidth(30);
    //glColor3d(255.0/255.0, 160.0/255.0, 122.0/255.0);
    glColor3d(103.0/255.0, 56.0/255.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+440, y+268);
    glVertex2i(x+450, y+260);
    glEnd();
    if (mode==1 || mode==2) {
        glPopMatrix();
    }
    //people's head
    //glColor3d(255.0/255.0, 160.0/255.0, 122.0/255.0);
    glColor3d(103.0/255.0, 56.0/255.0, 0.0);
    circle(x+400, y+335, 25);
    if (mode==3 || mode==4){
        glColor3d(0,0,0);
        glLineWidth(2);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(x + 412, y + 344);
        glVertex2i(x + 418, y + 340);
        glVertex2i(x + 412, y + 336);
    } else if(mode==5){
        glColor3d(0,0,0);
        glLineWidth(2);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(x + 412, y + 333);
        glVertex2i(x + 416, y + 345);
        glVertex2i(x + 420, y + 333);

    } else {
        glColor3d(1,1,1);
        circle(x+414, y+337,5);
        glColor3d(0,0,0);
        circle(x+414, y+337,3);
        glLineWidth(3);
        glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_LINE_STRIP);
        glVertex2i(x + 418, y + 340);
        glVertex2i(x + 414, y + 343);
    }
    glEnd();

    //hat
    glColor3d(51.0/255.0, 51.0/255.0, 51.0/255.0);
    halfCircle(x+398, y+345, 28);

    glLineWidth(3);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+398, y+345);
    glVertex2i(x+435, y+348);
    glEnd();

    //hat strip
    glLineWidth(1);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+395, y+345);
    glVertex2i(x+400, y+310);
    glEnd();

    //strip
    glLineWidth(5);
    glColor3d(51.0/255.0, 51.0/255.0, 51.0/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    if (mode==1 || mode==2)
        glVertex2i(x+450+moveScale*cos(speed*t), y+260-moveScale/2*cos(speed*t));
    else
        glVertex2i(x+450, y+260);

    if (mode==1 || mode==2)
        glVertex2i(x+500+moveScale/2*cos(speed*t), y+245);
    else
        glVertex2i(x+500, y+245);
    glVertex2i(x+550, y+255);
    glEnd();
}
//CRACK
void drawCrack1(){
    glLineWidth(3);
    glColor3d(0,0,0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_LINE_STRIP);
    glVertex2i(0, 0);
    glVertex2i(30, 10);
    glVertex2i(20, 15);
    glVertex2i(30, 10);
    glVertex2i(50, 5);
    glVertex2i(45, 0);
    glVertex2i(65, 15);
    glVertex2i(80, 10);
    glEnd();
}
//CHI
void drawChi(){
    glColor3d(0,0,0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(-33, -3);
    glVertex2i(103, -3);
    glVertex2i(103, 38);
    glEnd();
    circle(100,25,28);
    glColor3d(1,1,1);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(-30, 0);
    glVertex2i(100, 0);
    glVertex2i(100, 35);
    glEnd();
    circle(100,25,25);
}
//MEDAL
void drawMedal(){
    int x = -500;
    int y = -700;
    glColor3d(0,0,205/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(650+x, 700+y);
    glVertex2i(350+x, 700+y);
    glVertex2i(350+x, 0+y);
    glVertex2i(400+x, 600+y);
    glVertex2i(650+x, 0+y);
    glVertex2i(650+x, 700+y);
    glEnd();
    glColor3d(1,1,1);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(620+x, 700+y);
    glVertex2i(620+x, 80+y);
    glVertex2i(500+x, 400+y);
    glVertex2i(380+x, 80+y);
    glVertex2i(380+x, 700+y);
    glEnd();
    glColor3d(255/255.0,20/255.0,60/255.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(590+x, 700+y);
    glVertex2i(590+x, 160+y);
    glVertex2i(500+x, 400+y);
    glVertex2i(410+x, 160+y);
    glVertex2i(410+x, 700+y);
    glEnd();
    glColor3d(255/255.0,140/255.0,0);
    circle(500+x,700+y,220);
    glColor3d(255/255.0, 215/255.0, 0);
    circle(500+x,700+y,200);

    glLineWidth(1);
    glColor3d(255/255.0,140/255.0,0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(475+x, 800+y);
    glVertex2i(525+x, 800+y);
    glVertex2i(525+x, 600+y);
    glVertex2i(475+x, 600+y);
    glEnd();

    glLineWidth(1);
    glColor3d(255/255.0,140/255.0,0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(445+x, 630+y);
    glVertex2i(555+x, 630+y);
    glVertex2i(555+x, 590+y);
    glVertex2i(445+x, 590+y);
    glEnd();

    glLineWidth(1);
    glColor3d(255/255.0,140/255.0,0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex2i(475+x, 800+y);
    glVertex2i(435+x, 760+y);
    glVertex2i(460+x, 745+y);
    glVertex2i(500+x, 775+y);
    glEnd();
}
double xLookAt = 0;
void Animation(void)
{
    int multiplier = 3;
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0*multiplier;
    //cout<<t<<endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    int x = 0;
    int y = 0;
    double timePlus = 5;
    double timeCamera1 = 11;
    double timeCamera2 = 35;
    double timeCamera3 = 51+5;
    double timeCamera4 = 57.5+5;
    double timeCameraStop = 40;
    double timeCameraStop2 = 132.3;
    double timeCamera5 = 140;
    double timeHorse1 = 13;
    double timeHorse2 = 62.1;
    double timeHorseJump1 = timeHorse2+6;
    double timeHorseJump2 = timeHorse2+19;
    double timeHorseJump3 = timeHorse2+33;
    double timeHorseJump4 = timeHorse2+43;
    double timeHorseJump5 = timeHorse2+49;
    double timeHorseJump6 = timeHorse2+55;
    double timeHorseJump7 = timeHorse2+70;
    double timeHorseJump8 = timeHorse2+73;
    double timeHorseJump9 = timeHorse2+78.5;
    double shootY9 = 1*(480*(t-timeHorseJump9)-15*(t-timeHorseJump9)*(t-timeHorseJump9));
    double shootYH9 = 1*(450*(t-timeHorseJump9)-15*(t-timeHorseJump9)*(t-timeHorseJump9));
    double lastJumpX = 30;
    double timeHorseLast = 177;

    if (t>timeCamera1 && t<timeCamera2){
        xLookAt += (((t-timeCamera1)*7.9*multiplier/8.5));
        if (xLookAt>=12130){
            xLookAt = 12200;
        }
        gluLookAt(xLookAt, y, 1,
                  xLookAt, y, 0,
                  0, 1, 0);
        cout<<xLookAt<<endl;
    } else if (t>=timeCamera2 && t<timeCameraStop){
        xLookAt = 12200;
        gluLookAt(xLookAt, y, 1,
                  xLookAt, y, 0,
                  0, 1, 0);
    } else if(t>=timeCameraStop && t<timeCamera3 && xLookAt>=800){
        xLookAt += (((t-timeCamera3)*16*multiplier/8.5));
        if (xLookAt<800)
            xLookAt = 800;
        gluLookAt(xLookAt, y, 1,
                  xLookAt, y, 0,
                  0, 1, 0);

    } else{
        double toLook = xLookAt+ (t-timeCamera4) * 80*2;
        if (t>=timeCamera4 && t<timeCameraStop2 && toLook<11800){
            gluLookAt(toLook, y, 1,
                      toLook, y, 0,
                      0, 1, 0);
        } else if((t>=timeCameraStop2 || toLook>=11800)&&t<132.1){
            xLookAt = 11800;
            gluLookAt(xLookAt, y, 1,
                      xLookAt, y, 0,
                      0, 1, 0);
        } else if(t>=132.1 && t<135){
            double shakeX = 30*cos(8*t);
            double shakeY = abs(30*sin(8*t));
            gluLookAt(xLookAt+shakeX, y+shakeY, 1,
                      xLookAt+shakeX, y+shakeY, 0,
                      0, 1, 0);
        } else if(t>=timeCamera5){
            //cout<<shootY9<<endl;
            if (shootY9>=0) {
                gluLookAt(xLookAt + (t - timeHorseJump9) * lastJumpX, shootY9, 1,
                          xLookAt + (t - timeHorseJump9) * lastJumpX, shootY9, 0,
                          0, 1, 0);
            } else if(t<=timeCamera5+9){
                gluLookAt(xLookAt, y, 1,
                          xLookAt, y, 0,
                          0, 1, 0);
            }else {
                gluLookAt(xLookAt + 1000, y, 1,
                          xLookAt + 1000, y, 0,
                          0, 1, 0);
            }
        }else {
            gluLookAt(xLookAt, y, 1,
                      xLookAt, y, 0,
                      0, 1, 0);
        }
    }

    //Sky
    drawSky();
    drawSky2();
    drawStars();
    //Cloud
    drawCloud();
    //Auditorium
    drawAuditorium();
    drawViewers(t,0);

    glPushMatrix();
    glTranslated(4500,0,0);
    drawAuditorium();
    glPopMatrix();

    glPushMatrix();
    glTranslated(9000,0,0);
    drawAuditorium();
    glPopMatrix();

    drawViewers(t,4500);
    drawViewers(t,9000);
    //Desert
    drawDesert();
    //Fence
    drawFence();
    //Grass
    drawGrass();
    //Wall
    drawWall();
    drawStars();
    //Barriers
    glPushMatrix();
    glTranslated(550,-50,0);
    drawBarrier1();
    glTranslated(1250,0,0);
    drawBarrier2();
    glTranslated(3050,0,0);
    drawBarrier1();
    glTranslated(-50,0,0);
    drawBarrier1();
    glTranslated(1600,0,0);
    drawBarrier1();
    glTranslated(900,0,0);
    drawBarrier1();
    glTranslated(900,0,0);
    drawBarrier1();
    glTranslated(2680,0,0);
    drawBarrier3();
    glPopMatrix();
    //Flag
    glPushMatrix();
    //glTranslated(0,t*30,0);
    glTranslated(100,0,0);
    drawFlag(t);
    //Words
    char s[14] = "EQUESTRIAN";
    for (int l = 0; l < 11-int(t*1.5); ++l) {
        glLineWidth(6);
        glColor3d((128.0+10.5*l)/255.0, (0.0+5.5*l)/255.0, (0.0+12.5*l)/255.0);
        char tmp[2] = "a";
        tmp[0] = s[l];
        renderBitmapString(190+500/11*l,425,GLUT_BITMAP_HELVETICA_18,tmp);
        glEnd();
    }


    glPopMatrix();

    glPushMatrix();
    glTranslated(800,0,0);
    if (t>=56 && t<58)
        draw3();
    else if(t>=58 && t<60)
        draw2();
    else if(t>=60 && t<62)
        draw1();
    glPopMatrix();

    //Horse & people
    //CRACK
    if (t>=timeHorseJump7+2.5){
        glPushMatrix();

        glTranslated(timeHorse1 * 80+(timeHorseJump7-timeHorse2)*160, 0, 0);
        glScaled(1, 0.5, 1);
        for (int i = 0; i < 6; ++i) {

            glPushMatrix();
            glTranslated(-130, 268, 0);
            glRotated(60 * i, 0, 0, 1);
            drawCrack1();
            glPopMatrix();
        }
        if (t<timeHorseJump7+8) {
            glScaled(1, 2, 1);
            glTranslated(0, 130, 0);
            if (t < timeHorseJump7 + 5)
                glTranslated((t - (timeHorseJump7 + 2.5)) * 80, 0, 0);
            else
                glTranslated(2.5 * 80, 0, 0);
            drawChi();
        }
        glPopMatrix();

        if (t<timeHorseJump7+8) {
            glPushMatrix();
            glTranslated(timeHorse1 * 80 + (timeHorseJump7 - timeHorse2) * 160 - 280, 130, 0);
            if (t < timeHorseJump7 + 5)
                glTranslated(-(t - (timeHorseJump7 + 2.5)) * 80, 0, 0);
            else
                glTranslated(-2.5 * 80, 0, 0);
            glRotated(180, 0, 1, 0);
            drawChi();
            glPopMatrix();
        }
    }
    double tGround = 171.5;
    double crack2X = xLookAt+630;
    if (t>=tGround+2.5){
        glPushMatrix();
        glTranslated(crack2X+1000, 20, 0);
        glScaled(1, 0.5, 1);
        for (int i = 0; i < 6; ++i) {

            glPushMatrix();
            glTranslated(-130, 268, 0);
            glRotated(60 * i, 0, 0, 1);
            drawCrack1();
            glPopMatrix();
        }
        if (t<tGround+8) {
            glScaled(1, 2, 1);
            glTranslated(0, 130, 0);
            if (t < tGround + 5)
                glTranslated((t - (tGround + 2.5)) * 80, 0, 0);
            else
                glTranslated(2.5 * 80, 0, 0);
            drawChi();
        }
        glPopMatrix();

        if (t<tGround+8) {
            glPushMatrix();
            glTranslated(crack2X+1000-250, 150, 0);
            if (t < tGround + 5)
                glTranslated(-(t - (tGround + 2.5)) * 80, 0, 0);
            else
                glTranslated(-2.5 * 80, 0, 0);
            glRotated(180, 0, 1, 0);
            drawChi();
            glPopMatrix();
        }
    }
    double lastT = 0;
    double turningPoint = 155.6;
    glScalef(1.0f, 0.8f, 1.0f);
    glPushMatrix();
    glTranslated(-300,200,0);
    if (t>=0 && t<timeHorse1) {
        glTranslated(t * 80, 0, 0);
        glTranslated(0,2*sin(t*6),0);
        drawHorse(0, 0, 1, t);
        drawRiderNormal(0, 0, 1, t);

    } else if(t>=timeHorse1 && t<timeHorse2){
        glTranslated(timeHorse1 * 80, 0, 0);
        drawHorse(0, 0, 0, t);
        drawRiderNormal(0, 0, 0, t);
    } else if(t>=timeHorse2&&t<timeHorseJump7){
        glTranslated(timeHorse1 * 80+(t-timeHorse2)*160, 0, 0);
        glTranslated(0,3*sin(t*3),0);
        double shootY = 1*(80*(t-timeHorseJump1)-15*(t-timeHorseJump1)*(t-timeHorseJump1));
        double shootY2 = 1*(140*sin(PI/4)*(t-timeHorseJump2)-15*(t-timeHorseJump2)*(t-timeHorseJump2));
        double shootY3 = 1*(95*(t-timeHorseJump3)-15*(t-timeHorseJump3)*(t-timeHorseJump3));
        double shootY4 = 1*(80*(t-timeHorseJump4)-15*(t-timeHorseJump4)*(t-timeHorseJump4));
        double shootY5 = 1*(80*(t-timeHorseJump5)-15*(t-timeHorseJump5)*(t-timeHorseJump5));
        double shootY6 = 1*(80*(t-timeHorseJump6)-15*(t-timeHorseJump6)*(t-timeHorseJump6));
        if(t>=timeHorseJump1 && shootY>=0) {
            glTranslated(0, shootY, 0);
            drawHorse(0, 0, 3, t);
            drawRiderNormal(0, 0, 3, t);
        } else if(t>=timeHorseJump2 && shootY2>=0) {
            glTranslated(0, shootY2, 0);
            drawHorse(0, 0, 3, t);
            drawRiderNormal(0, 0, 3, t);
        } else if(t>=timeHorseJump3 && shootY3>=0){
            glTranslated(0, shootY3, 0);
            drawHorse(0, 0, 3, t);
            drawRiderNormal(0, 0, 3, t);
        }else if(t>=timeHorseJump4 && shootY4>=0){
            glTranslated(0, shootY4, 0);
            drawHorse(0, 0, 3, t);
            drawRiderNormal(0, 0, 3, t);
        }else if(t>=timeHorseJump5 && shootY5>=0){
            glTranslated(0, shootY5, 0);
            drawHorse(0, 0, 3, t);
            drawRiderNormal(0, 0, 3, t);
        }else if(t>=timeHorseJump6 && shootY6>=0 &&t<timeHorseJump7){
            glTranslated(0, shootY6, 0);
            drawHorse(0, 0, 4, t);
            drawRiderNormal(0, 0, 4, t);
        }else{
            //cout<<"else"<<endl;
            drawHorse(0, 0, 2, t);
            drawRiderNormal(0, 0, 2, t);
        }
    }else if(t>=timeHorseJump7 && t<timeHorseJump8){

        glTranslated(timeHorse1 * 80+(timeHorseJump7-timeHorse2)*160, 0, 0);
        glTranslated(200,150,0);
        glRotated(60,0,0,1);
        glTranslated(-200,-150,0);
        drawHorse(0, 0, 4, t);
        drawRiderNormal(0, 0, 4, t);
    } else if(t>=timeHorseJump8 && t<timeHorseJump9){
        glTranslated(timeHorse1 * 80+(timeHorseJump7-timeHorse2)*160+(t-timeHorseJump8)*30, (t-timeHorseJump7)*200, 0);
        glTranslated(200,150,0);
        glRotated(60,0,0,1);
        glTranslated(-200,-150,0);
        drawHorse(0, 0, 4, t);
        drawRiderNormal(0, 0, 4, t);
    } else if(t>=timeHorseJump9){
        glTranslated(timeHorse1 * 80+(timeHorseJump7-timeHorse2)*160+(timeHorseJump9-timeHorseJump8)*30, (timeHorseJump9-timeHorseJump7)*200, 0);

        if(shootYH9>=-1700) {
            //cout<<"YH9: "<<shootYH9<<endl;
            glTranslated((t - timeHorseJump9) * lastJumpX, shootYH9, 0);
            //lastT = (t - timeHorseJump9) * lastJumpX;
            //cout<<lastT<<endl;
        }
        else {
            glTranslated(1000, -(timeHorseJump9-timeHorseJump7)*200, 0);
        }
        if(t<timeHorseLast) {
            glTranslated(200, 150, 0);
            if (t >= turningPoint)
                glRotated(-60, 0, 0, 1);
            else
                glRotated(60, 0, 0, 1);
            cout << t << endl;
            glTranslated(-200, -150, 0);
            drawHorse(0, 0, 4, t);
            drawRiderNormal(0, 0, 4, t);
        } else{
            drawHorse(0, 0, 0, t);
            drawRiderNormal(0, 0, 5, t);
        }
    }
    glPopMatrix();
    glScalef(1.0f, 1/0.8f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslated(400,400,0);
    glPopMatrix();
    /*glPushMatrix();
    glTranslated(-200,-150,0);
    drawHorse(0, 0, 4, t);
    drawRiderNormal(0, 0, 4, t);
    glPopMatrix();*/
    //glPushMatrix();
    //glScaled(1,0.8,1);
    if (t>181) {
        glPushMatrix();
        glTranslated(500,500,0);
        glScaled(abs(sin(t*0.5)),abs(sin(t*0.5)),1);
        drawMedal();
        glScaled(1/abs(sin(t*0.5)),1/abs(sin(t*0.5)),1);
        glPopMatrix();
    }
    //glScaled(1,1/0.8,1);
    //glPopMatrix();
    glutSwapBuffers();
}
/*
void  display(void)
{

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    if(t>5){
        glutDisplayFunc(Animation);
    }
}*/

static void
idle(void)
{
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    initiateRandom();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(300,0);
    glutInitWindowSize(900,900);
    glutCreateWindow("FISU Equestrian");
    init();
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    glutDisplayFunc(Animation);

    glutIdleFunc(idle);
    glutMainLoop();
}
