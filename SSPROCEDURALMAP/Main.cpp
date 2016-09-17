/*
https://www.raywenderlich.com/70610/procedural-level-generation-games-using-cellular-automaton-part-2
https://www.raywenderlich.com/66062/procedural-level-generation-games-using-cellular-automaton-part-1
http://www.roguebasin.com/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels
http://gamedevelopment.tutsplus.com/tutorials/how-to-use-bsp-trees-to-generate-game-maps--gamedev-12268

http://www.roguebasin.com/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels
zzl
https://www.raywenderlich.com/51786/procedural-level-generation-in-games-part-2
https://www.raywenderlich.com/66062/procedural-level-generation-games-using-cellular-automaton-part-1
http://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/

//--> Creacion paths A*

http://www.policyalmanac.org/games/aStarTutorial.htm
http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include <GLES/gl.h>
#include <GLES/egl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>

#include <SDL.h>
#include <SDL_opengles.h>
#include <SDL_image.h>
#undef main

#include "ProceduralMapCaveGenerator.h"
#include "ProceduralMapIndoorGenerator.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 512
#define WINDOW_BPP     16
#define SIZE_TILE      64

#define SIZE_MAP_X 30
#define SIZE_MAP_Y 30

#define X_INF 0
#define X_SUP 9
#define Y_INF 0
#define Y_SUP 7

SDL_DisplayMode mode;
SDL_Window *window;
SDL_GLContext context;

ProceduralMapCaveGenerator *pMCG;
ProceduralMapIndoorGenerator *pMIG;

GLuint id_texture1;
GLuint id_texture2;
GLuint id_texture3;

int lim_ini_x = 0; //OJO x = j; y = i
int lim_ini_y = 0;
int lim_fin_x = 9;
int lim_fin_y = 7;

float movement_x = 0;
float movement_y = 0;

float dmovement_x =0;
float dmovement_y =0;

float size_world_x = 0;
float size_world_y = 0;

GLfloat square[] = {
	0.0, 0.0, 0.0,
	0.0, 100.0, 0.0,
	100.0, 100.0, 0.0,
	100.0, 0.0, 0.0
};


void Terminate_1()
{
SDL_GL_DeleteContext(context);
SDL_DestroyWindow(window);
SDL_Quit();
}

SDL_Surface *ConvertToRGBA_1(SDL_Surface *frame){

    GLuint it;
    GLuint jt;

            for (jt=0; jt<frame->h; jt++)
            {
                for (it=0; it<frame->w; it++)
                {GLuint *id;
                    switch (frame->format->BytesPerPixel)
                    {
                        case 3:
                             {
                                 unsigned char rvalue;
                                 unsigned char bvalue;

                                 rvalue=*((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel);
                                 bvalue=*((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel+2);
                                 *((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel)=bvalue;
                                 *((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel+2)=rvalue;
                             }
                             break;
                        case 4:
                             {
                                 unsigned long rgbvalue;

                                 rgbvalue=*(unsigned long*)((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel);
                                 rgbvalue=(rgbvalue & 0xFF00FF00) | ((rgbvalue<<16) & 0x00FF0000) |
                                          ((rgbvalue>>16) & 0x000000FF);
                                 *(unsigned long*)((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel)=rgbvalue;
                             }
                             break;
                    }
                }
            }

        switch (frame->format->BytesPerPixel)
        {
            case 3:
                 {
                     GLuint it;
                     GLuint jt;
                     unsigned char rvalue;
                     unsigned char gvalue;
                     unsigned char bvalue;

                     for (jt=0; jt<frame->h/2; jt++)
                     {
                         for (it=0; it<frame->w; it++)
                         {
                             rvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel);
                             gvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+1);
                             bvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+2);

                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel);
                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+1)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+1);
                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+2)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+2);

                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel)=rvalue;
                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+1)=gvalue;
                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+2)=bvalue;

                         }
                     }
                 }
                 break;

    }

    return frame;
}




void loadImage_1(){

    SDL_Surface *surface = SDL_LoadBMP("./data/background.bmp");

    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }

    surface = ConvertToRGBA_1(surface);

    glGenTextures(1, &id_texture1);
    glBindTexture(GL_TEXTURE_2D, id_texture1);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);


    surface = SDL_LoadBMP("./data/mapa_2.bmp");

    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }

    surface = ConvertToRGBA_1(surface);

    glGenTextures(1, &id_texture2);
    glBindTexture(GL_TEXTURE_2D, id_texture2);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./data/Ship_1_Tot.bmp");

    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }

    surface = ConvertToRGBA_1(surface);

    glGenTextures(1, &id_texture3);
    glBindTexture(GL_TEXTURE_2D, id_texture3);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);
}

//perspective
/////////////////////////////////////////////////////////////////////////////////
void InitGL_1(){
	glShadeModel( GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClearDepthf(1.0f);
	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void perspectiveGL(double fovY, double aspect, double zNear, double zFar) {
	double fW, fH;
	fH = tan(fovY / 360 * M_PI) * zNear;
	fW = fH * aspect;
	glFrustumf(-fW, fW, -fH, fH, zNear, zFar);
}


void resizeWindow_1(int width, int height){

	GLfloat ratio;
	if (height == 0) {height = 1;}
	ratio = (GLfloat) width / (GLfloat) height;
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	perspectiveGL(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}

void draw_screen_1(){

    GLfloat vertices[4][3];
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glLoadIdentity();
    glTranslatef(0.5f, 0.0f, -6.0f);
    glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
    vertices[0][0]=0.0f; vertices[0][1]=1.0f; vertices[0][2]=0.0f;
    vertices[1][0]=-1.0f; vertices[1][1]=-1.0f; vertices[1][2]=0.0f;
    vertices[2][0]=1.0f; vertices[2][1]=-1.0f; vertices[2][2]=0.0f;
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFinish();
}
/////////////////////////////////////////////////////////////////////////////////

//ortho.
/////////////////////////////////////////////////////////////////////////////////
void InitGL_2(){

}

void resizeWindow_2(int width, int height){
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //glOrthof(0, width, 0, height, -5, 1);
    glOrthof(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw_screen_polygon_2(){

    /*
    static const GLfloat squareVertices[] = {
        5.0f, 150.0f,
        5.0f, 250.0f,
        100.0f, 250.0f,
        100.0f, 150.0f
    };*/

    static const GLfloat squareVertices[] = {
        0.0f, 100.0f,
        0.0f, 200.0f,
        100.0f, 200.0f,
        100.0f, 100.0f
    };

    glPushMatrix();
    glLineWidth(3.0);
    glColor4f(0.0, 0.0, 1.0, 1.0); // blue
    glTranslatef(5.0, 0.0, 0.0);
    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glTranslatef(100.0, 0.0, 0.0);
    glColor4f(1.0, 0.0, 0.0, 1.0);  // Red
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glTranslatef(100.0, 0.0, 0.0);
    glColor4f(1.0, 1.0, 0.0, 1.0);  // Yellow
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    glFlush();

}

void draw_screen_with_textures(){

    float vtxcoords[12];
    float texcoords[8];

    //ProceduralMapIndoorGenerator *pMIG = new ProceduralMapIndoorGenerator(SIZE_MAP_Y,SIZE_MAP_X,0);

    int **mapText = pMCG->getMatrix();
    //int **mapText = pMIG->getMatrix();

    /*
    int mapText[SIZE_MAP_Y][SIZE_MAP_X] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,1,1,1,0,1,1,1,1},
    {1,0,0,0,0,1,1,0,1,0,1,0,1,0,0,1},
    {1,0,0,0,1,0,1,1,1,0,1,1,1,0,0,1},
    {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    */

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /*
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrthof(0.0f, float(WINDOW_WIDTH), float(WINDOW_HEIGHT) ,0.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    */

    glEnable(GL_TEXTURE_2D);

    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D, id_texture1);

    vtxcoords[0] = 0.0f;
    vtxcoords[1] = 0.0f;
    vtxcoords[2] = 0.0f;

    vtxcoords[3] = (float)WINDOW_WIDTH;
    vtxcoords[4] = 0.0f;
    vtxcoords[5] = 0.0f;

    vtxcoords[6] = 0.0f;
    vtxcoords[7] = (float)WINDOW_HEIGHT;
    vtxcoords[8] = 0.0f;

    vtxcoords[9] = (float)WINDOW_WIDTH;
    vtxcoords[10] = (float)WINDOW_HEIGHT;
    vtxcoords[11] = 0.0f;


    texcoords[0] = 0.0f;
    texcoords[1] = 0.0f;

    texcoords[2] = 1.0f;
    texcoords[3] = 0.0f;

    texcoords[4] = 0.0f;
    texcoords[5] = 1.0f;

    texcoords[6] = 1.0f;
    texcoords[7] = 1.0f;


    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_ALPHA);
    glAlphaFunc(GL_GREATER, GL_ZERO);
    glEnable(GL_ALPHA_TEST);

    glPushMatrix();

    for(int i=lim_ini_y; i<=lim_fin_y; i++){
        for (int j=lim_ini_x; j<=lim_fin_x; j++){
             if (mapText[i][j]==1){

                    glBindTexture(GL_TEXTURE_2D, id_texture2);

                    vtxcoords[0] = 0.0f;
                    vtxcoords[1] = 0.0f;
                    vtxcoords[2] = 0.0f;

                    vtxcoords[3] = 0.0f;
                    vtxcoords[4] = float(SIZE_TILE);
                    vtxcoords[5] = 0.0f;

                    vtxcoords[6] = float(SIZE_TILE);
                    vtxcoords[7] = float(SIZE_TILE);
                    vtxcoords[8] = 0.0f;

                    vtxcoords[9] = float(SIZE_TILE);
                    vtxcoords[10] = 0.0f;
                    vtxcoords[11] = 0.0f;


                    texcoords[0] = 0.0f;
                    texcoords[1] = 0.0f;

                    texcoords[2] = 0.1f;
                    texcoords[3] = 0.0f;

                    texcoords[4] = 0.1f;
                    texcoords[5] = 0.1f;

                    texcoords[6] = 0.0f;
                    texcoords[7] = 0.1f;

                    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
                    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

             }else if (mapText[i][j]==2){

                    glBindTexture(GL_TEXTURE_2D, id_texture2);

                    vtxcoords[0] = 0.0f;
                    vtxcoords[1] = 0.0f;
                    vtxcoords[2] = 0.0f;

                    vtxcoords[3] = 0.0f;
                    vtxcoords[4] = float(SIZE_TILE);
                    vtxcoords[5] = 0.0f;

                    vtxcoords[6] = float(SIZE_TILE);
                    vtxcoords[7] = float(SIZE_TILE);
                    vtxcoords[8] = 0.0f;

                    vtxcoords[9] = float(SIZE_TILE);
                    vtxcoords[10] = 0.0f;
                    vtxcoords[11] = 0.0f;


                    texcoords[0] = 0.1f;
                    texcoords[1] = 0.1f;

                    texcoords[2] = 0.2f;
                    texcoords[3] = 0.1f;

                    texcoords[4] = 0.2f;
                    texcoords[5] = 0.2f;

                    texcoords[6] = 0.1f;
                    texcoords[7] = 0.2f;

                    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
                    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

             }else if (mapText[i][j]==3){

                    glBindTexture(GL_TEXTURE_2D, id_texture2);

                    vtxcoords[0] = 0.0f;
                    vtxcoords[1] = 0.0f;
                    vtxcoords[2] = 0.0f;

                    vtxcoords[3] = 0.0f;
                    vtxcoords[4] = float(SIZE_TILE);
                    vtxcoords[5] = 0.0f;

                    vtxcoords[6] = float(SIZE_TILE);
                    vtxcoords[7] = float(SIZE_TILE);
                    vtxcoords[8] = 0.0f;

                    vtxcoords[9] = float(SIZE_TILE);
                    vtxcoords[10] = 0.0f;
                    vtxcoords[11] = 0.0f;


                    texcoords[0] = 0.1f;
                    texcoords[1] = 0.1f;

                    texcoords[2] = 0.3f;
                    texcoords[3] = 0.1f;

                    texcoords[4] = 0.3f;
                    texcoords[5] = 0.3f;

                    texcoords[6] = 0.1f;
                    texcoords[7] = 0.3f;

                    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
                    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

             }else if (mapText[i][j]==4){

                    glBindTexture(GL_TEXTURE_2D, id_texture2);

                    vtxcoords[0] = 0.0f;
                    vtxcoords[1] = 0.0f;
                    vtxcoords[2] = 0.0f;

                    vtxcoords[3] = 0.0f;
                    vtxcoords[4] = float(SIZE_TILE);
                    vtxcoords[5] = 0.0f;

                    vtxcoords[6] = float(SIZE_TILE);
                    vtxcoords[7] = float(SIZE_TILE);
                    vtxcoords[8] = 0.0f;

                    vtxcoords[9] = float(SIZE_TILE);
                    vtxcoords[10] = 0.0f;
                    vtxcoords[11] = 0.0f;


                    texcoords[0] = 0.2f;
                    texcoords[1] = 0.2f;

                    texcoords[2] = 0.3f;
                    texcoords[3] = 0.2f;

                    texcoords[4] = 0.3f;
                    texcoords[5] = 0.3f;

                    texcoords[6] = 0.2f;
                    texcoords[7] = 0.3f;

                    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
                    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
             }

             glTranslatef(64.0f,0.0f,0.0f);
        }
        glTranslatef(-640.0f,0.0f,0.0f);
        glTranslatef(0.0f, 64.0f,0.0f);
    }

    glPopMatrix();

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, id_texture3);

    glTranslatef(movement_x-dmovement_x,movement_y-dmovement_y,0.0f);

    vtxcoords[0] = 0.0f;
    vtxcoords[1] = 0.0f;
    vtxcoords[2] = 0.0f;

    vtxcoords[3] = 0.0f;
    vtxcoords[4] = float(SIZE_TILE);
    vtxcoords[5] = 0.0f;

    vtxcoords[6] = float(SIZE_TILE);
    vtxcoords[7] = float(SIZE_TILE);
    vtxcoords[8] = 0.0f;

    vtxcoords[9] = float(SIZE_TILE);
    vtxcoords[10] = 0.0f;
    vtxcoords[11] = 0.0f;

    //0.375 0.0 0.5 0.0 0.375 1.0 0.5 1.0

    texcoords[0] = 0.375f;
    texcoords[1] = 0.0f;

    texcoords[2] = 0.5f;
    texcoords[3] = 0.0f;

    texcoords[4] = 0.375f;
    texcoords[5] = 1.0f;

    texcoords[6] = 0.5f;
    texcoords[7] = 1.0f;

    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glPopMatrix();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_ALPHA);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    glFlush();
    /*
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    */

}



/////////////////////////////////////////////////////////////////////////////////


void evaluateCamera_1(){


    dmovement_x = (movement_x) - floor(float(WINDOW_WIDTH)*0.5f);
    if (dmovement_x < 0.0f){dmovement_x = 0.0f;}
    else if ((int(dmovement_x)+WINDOW_WIDTH)>size_world_x){dmovement_x  = float(size_world_x-WINDOW_WIDTH);}
    else{dmovement_x  = dmovement_x ;}

    dmovement_y  = (movement_y) - floor(float(WINDOW_HEIGHT)*0.5f);
    if (dmovement_y < 0.0f){dmovement_y  = 0.0f;}
    else if ((int(dmovement_y )+WINDOW_HEIGHT)>size_world_y){dmovement_y = float(size_world_y-WINDOW_HEIGHT);}
    else{dmovement_y = dmovement_y;}


    lim_ini_x = int(floor((float(dmovement_x))/float(SIZE_TILE))) + X_INF;
    lim_ini_y = int(floor((float(dmovement_y))/float(SIZE_TILE))) + Y_INF;
    lim_fin_x = int(floor((float(dmovement_x))/float(SIZE_TILE))) + X_SUP;
    lim_fin_y = int(floor((float(dmovement_y))/float(SIZE_TILE))) + Y_SUP;

    printf("limites player [%f,%f] ref [%f,%f] (%d %d) x (%d %d)\r\n",movement_x,movement_y,dmovement_x,dmovement_y,lim_ini_x,lim_ini_y,lim_fin_x,lim_fin_y);

}


int main (int argc, char *argv[])
{
    int status;
    int done=0;
    SDL_Event event;
    SDL_bool isActive=SDL_TRUE;

    size_world_x = SIZE_TILE * SIZE_MAP_X;
    size_world_y = SIZE_TILE * SIZE_MAP_Y;

    lim_ini_x = X_INF;
    lim_ini_y = Y_INF;
    lim_fin_x = X_SUP;
    lim_fin_y = Y_SUP;


    if  (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0){
        printf("ENTORNO SDL VIDEO, AUDIO, JOYSTICK NO INICIALIZADO %s",SDL_GetError());
        exit(-1);
    }

	status = SDL_GetDesktopDisplayMode(0, &mode);

	if (status<0){
        printf("ERROR AL CAPTURAR EL MODO NATIVO DE PANTALLA %s",SDL_GetError());
        exit(-1);
	}else{
	    Uint32 f;
	    f = mode.format;
        printf("DISPLAY(0) (%d x %d) @ %i bpp %s", mode.w, mode.h, SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f));
	}

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);


    window=SDL_CreateWindow("Prueba XX",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (window==0){
        printf("ERROR AL CREAR LA VENTANA: %s \r\n", SDL_GetError());
        exit(-1);
    }

    context=SDL_GL_CreateContext(window);

    if (context==NULL){
        printf("ERROR AL CREAR EL CONTEXTO OPENGL ES: %s \r\n", SDL_GetError());
        exit(-1);
    }

    status=SDL_GL_MakeCurrent(window, context);

    if (status<0){
        printf("GLLaunchSystemsGL11::initOpenGLESSystems --> ERROR AL ASOCIAR EL ACTUAL CONTEXTO OPENGL ES: %s \r\n", SDL_GetError());
        exit(-1);
    }

    SDL_GL_SetSwapInterval(1);

    printf("GLLaunchSystemsGL11::initOpenGLESSystems --> INIT \r\n");


    InitGL_2();
    resizeWindow_2(WINDOW_WIDTH, WINDOW_HEIGHT);

    char* extensionList = (char*)glGetString(GL_EXTENSIONS);

    printf("GLExtensions --> [%s]\r\n",extensionList);

    pMCG = new ProceduralMapCaveGenerator(SIZE_MAP_Y,SIZE_MAP_X,0);
    pMIG = new ProceduralMapIndoorGenerator(SIZE_MAP_Y,SIZE_MAP_X,1);

    loadImage_1();

    bool DONE = false;

    long dX = SDL_GetTicks();

    while (!DONE){
         while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN:
                    SDL_Keysym *keysym = &event.key.keysym;

                    if (keysym->sym == SDLK_LEFT){
                         movement_x -= 4.0f;
                         //movement_x -= 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_RIGHT){

                        movement_x += 4.0f;
                        //movement_x += 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_UP){

                        movement_y -= 4.0f;
                        //movement_y -= 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_DOWN){

                        movement_y += 4.0f;
                        //movement_y += 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_ESCAPE){
                        DONE = true;

                    }else{

                    }

                    if ((keysym->sym == SDLK_LEFT) || (keysym->sym == SDLK_RIGHT) || (keysym->sym == SDLK_DOWN) || (keysym->sym == SDLK_UP)){
                       dX = SDL_GetTicks();
                       evaluateCamera_1();
                    }

                break;
            }
         }

         //printf( "dibujando escena \r\n");
         draw_screen_with_textures();
         //draw_screen_polygon_2();
         //printf( "escena dibujada, delay 2000 \r\n");
         SDL_GL_SwapWindow(window);
         //SDL_Delay(2000);
    }


    Terminate_1();
	return 0;
}
