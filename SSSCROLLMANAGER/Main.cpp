#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "GLES/gl.h"
#include "GLES/egl.h"
#include "GLES/glext.h"
#include "GLES/glplatform.h"

#include <SDL.h>
#include <SDL_opengles.h>
#include <SDL_image.h>
#undef main


#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 512
#define WINDOW_BPP     16
#define SIZE_TILE      64

#define SIZE_MAP_X 16
#define SIZE_MAP_Y 12

#define X_INF 0
#define X_SUP 10
#define Y_INF 0
#define Y_SUP 8

SDL_DisplayMode mode;
SDL_Window *window;
SDL_GLContext context;

GLuint id_texture1;
GLuint id_texture2;
GLuint id_texture3;

GLuint _idlevel;

GLuint id_texture4;

int lim_ini_x = X_INF;
int lim_ini_y = Y_INF;
int lim_fin_x = X_SUP;
int lim_fin_y = Y_SUP;

float lim_ini_fx = 0.0f;
float lim_ini_fy = 0.0f;
float lim_fin_fx = WINDOW_WIDTH;
float lim_fin_fy = WINDOW_HEIGHT;

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

typedef void * (*MapBufferOESType)(GLenum, GLenum);
MapBufferOESType MapBufferOES = NULL;

void evaluateExtensions(){

    if (SDL_GL_ExtensionSupported("GL_OES_mapbuffer")) {
        MapBufferOES = (MapBufferOESType)SDL_GL_GetProcAddress("MapBufferOES");
        printf("\r\n[MAIN] Extension GL_OES_mapbuffer ENCONTRADO!");
    }else{
        printf("\r\n[MAIN] Extension GL_OES_mapbuffer NO ENCONTRADA");
    }
}

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

/*
void draw_screen_with_textures(){

    float vtxcoords[12];
    float texcoords[8];

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

    //glMatrixMode(GL_PROJECTION);
    //glPopMatrix();
    //glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();

}
*/
/////////////////////////////////////////////////////////////////////////////////

//http://stackoverflow.com/questions/20730900/creating-a-new-texture-from-several-textures-sdl-2
//http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php
/////////////////////////////////////////////////////////////////////////////////

GLubyte* ConvertToTransparent(SDL_Surface *frame){

	GLubyte color_trans[3] = {0x00, 0x00, 0x00};

	GLubyte* colores;

	GLuint it;
    GLuint jt;

	GLubyte rvalue;
    GLubyte gvalue;
    GLubyte bvalue;

	int textpos = 0;
	unsigned long rgbvalue;


	colores = new GLubyte[frame->h*frame->w*4];



	for (jt=0; jt<frame->h; jt++){
        for (it=0; it<frame->w; it++){

			if (frame->format->BytesPerPixel==3){

				rvalue=*((GLubyte*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel);
				gvalue=*((GLubyte*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel+1);
				bvalue=*((GLubyte*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel+2);

            }else if (frame->format->BytesPerPixel==4){

				rgbvalue=*(unsigned long*)((unsigned char*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel);
				rvalue = (rgbvalue & 0xFF00FF00);
				gvalue = ((rgbvalue<<16) & 0x00FF0000);
                bvalue = ((rgbvalue>>16) & 0x000000FF);
			}


			colores[textpos] = rvalue;
			colores[textpos+1] = gvalue;
			colores[textpos+2] = bvalue;

			if ((rvalue==color_trans[0]) && (gvalue==color_trans[1]) && (bvalue==color_trans[2])){
				colores[textpos+3]=0x00;
			}else{
				colores[textpos+3]=0xFF;
			}

			textpos += 4;
		}
    }
	return colores;
}

//MOTOR CREACION DE UNA IMAGE A PARTIR DE UN MAPA DE TILES
/*
void processCustomTileImage()
{

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


    SDL_Surface *surface = SDL_LoadBMP("./data/mapa_2.bmp");
    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }
    surface = ConvertToRGBA_1(surface);


    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_Surface *level = SDL_CreateRGBSurface(SDL_SWSURFACE, SIZE_MAP_X*SIZE_TILE, SIZE_MAP_Y*SIZE_TILE, 24, rmask, gmask, bmask, amask);
    if(level == NULL) {
        printf("CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Rect a;
    a.x = 0;
    a.y = 0;
    a.w = SIZE_MAP_X*SIZE_TILE;
    a.h = SIZE_MAP_Y*SIZE_TILE;
    SDL_FillRect(level, &a, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));


    SDL_Rect area;
    area.x = 64.0f;
    area.y = 64.0f;
    area.w = 64.0f;
    area.h = 64.0f;

    SDL_Rect area_1;


    for(int fileY=0; fileY<SIZE_MAP_Y; fileY++){
        for(int fileX=0; fileX<SIZE_MAP_X; fileX++){
             if (mapText[fileY][fileX]==1){
                 area_1.x = fileX * SIZE_TILE;
                 area_1.y = fileY * SIZE_TILE;
                 area_1.w = SIZE_TILE;
                 area_1.h = SIZE_TILE;

                 SDL_BlitSurface(surface, &area, level, &area_1);

             }
        }
    }

    //surface --> dibujo_1
    //area --> area;
    //level --> destino
    //area_1 --> area_destino


    SDL_SaveBMP(level, "./data/level.bmp");

    GLubyte *datapixels = ConvertToTransparent(level);

    glGenTextures(1, &_idlevel);
    glBindTexture(GL_TEXTURE_2D, _idlevel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, level->w, level->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, datapixels);

    SDL_FreeSurface(level);
    SDL_FreeSurface(surface);
}
*/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
/*
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

}*/
/////////////////////////////////////////////////////////////////////////////////

//MOTOR CREACION DE UNA IMAGE A PARTIR DE UN MAPA DE TILES
/////////////////////////////////////////////////////////////////////////////////
/*
void evaluateCamera_1(){

    lim_ini_fx = movement_x;
    lim_ini_fy = movement_y;
    lim_fin_fx = movement_x+WINDOW_WIDTH;
    lim_fin_fy = movement_y+WINDOW_HEIGHT;

    if (lim_ini_fx < 0){lim_ini_fx = 0; lim_fin_fx = lim_ini_fx + WINDOW_WIDTH;}
    if (lim_fin_fx > (SIZE_MAP_X*SIZE_TILE)){lim_fin_fx = (SIZE_MAP_X*SIZE_TILE) -1.0f; lim_ini_fx = lim_fin_fx - WINDOW_WIDTH;}

    if (lim_ini_fy < 0){lim_ini_fy = 0; lim_fin_fy = lim_ini_fy + WINDOW_HEIGHT;}
    if (lim_fin_fy > (SIZE_MAP_Y*SIZE_TILE)){lim_fin_fy = (SIZE_MAP_Y*SIZE_TILE) -1.0f; lim_ini_fy = lim_fin_fy - WINDOW_HEIGHT;}

}
*/
/////////////////////////////////////////////////////////////////////////////////

bool collision(SDL_Rect a, SDL_Rect b){

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}

//EVAUATE CAMERA SMOOTH RENDERING
void evaluateCamera_1(){

    lim_ini_fx = ( movement_x + float(SIZE_TILE/2) ) - float(WINDOW_WIDTH/2);
	lim_ini_fy = ( movement_y + float(SIZE_TILE/2) ) - float(WINDOW_HEIGHT/2);


	if( lim_ini_fx < 0 )
	{
		lim_ini_fx = 0;
	}

	if( lim_ini_fy < 0 )
	{
		lim_ini_fy = 0;
	}

	if( lim_ini_fx > (float(SIZE_MAP_X * SIZE_TILE) - float(WINDOW_WIDTH)))
	{
		lim_ini_fx = (float(SIZE_MAP_X * SIZE_TILE) - float(WINDOW_WIDTH));
	}

	if( lim_ini_fy > (float(SIZE_MAP_Y * SIZE_TILE) - float(WINDOW_HEIGHT)))
    {
		lim_ini_fy = (float(SIZE_MAP_Y * SIZE_TILE) - float(WINDOW_HEIGHT));
	}

	lim_fin_fx = lim_ini_fx + float(WINDOW_WIDTH);
	lim_fin_fy = lim_ini_fy + float(WINDOW_HEIGHT);

	printf("\r\nSCREEN (%f,%f) x (%f,%f)",lim_ini_fx,lim_ini_fy,lim_fin_fx,lim_fin_fy);

	lim_ini_x = int(int(lim_ini_fx)/SIZE_TILE);
	lim_fin_x = int(int(lim_fin_fx)/SIZE_TILE);

	lim_ini_y = int(int(lim_ini_fy)/SIZE_TILE);
	lim_fin_y = int(int(lim_fin_fy)/SIZE_TILE);

	printf("\r\nSCREEN-TILE (%d,%d) x (%d,%d)",lim_ini_x,lim_ini_y,lim_fin_x,lim_fin_y);


}


//RENDER ENVIRONMENT.
void draw_screen_with_textures(){

    float vtxcoords[12];
    float texcoords[8];

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


    //background image
    /////////////////////////////////////////////////////
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);

    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


    glPushMatrix();

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

    glPopMatrix();
    ///////////////////////////////////////////////////////////

    //LEVEL
    ///////////////////////////////////////////////////////////


    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_ALPHA);
    glAlphaFunc(GL_GREATER, GL_ZERO);
    glEnable(GL_ALPHA_TEST);

    SDL_Rect screen;

    screen.x = int(lim_ini_fx);
    screen.y = int(lim_ini_fy);
    screen.w = int(WINDOW_WIDTH);
    screen.h = int(WINDOW_HEIGHT);


    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, id_texture2);

    float data = 0.0f;

    for(int i=0; i<12; i++){
        data = 0.0f;
        for (int j=0; j<16; j++){
                    SDL_Rect tile;
                    tile.x = j*SIZE_TILE;
                    tile.y = i*SIZE_TILE;
                    tile.w = SIZE_TILE;
                    tile.h = SIZE_TILE;

                    if (collision(screen,tile)){

                        if (mapText[i][j]==1){

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

                        }
                        data = data - 1.0f;
                        glTranslatef(float(SIZE_TILE),0.0f,0.0f);

                        if (j == (lim_fin_x-1)){
                            glTranslatef(0.0f, float(SIZE_TILE),0.0f);
                        }
                    }
        }
        glTranslatef(data*float(SIZE_TILE),0.0f,0.0f);

    }

    glPopMatrix();
    ///////////////////////////////////////////////////////////

    //PLAYER
    ////////////////////////////////////////////////////////////
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, id_texture3);

    glTranslatef(movement_x-lim_ini_fx,movement_y-lim_ini_fy,0.0f);

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
    ///////////////////////////////////////////

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_ALPHA);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    glFlush();
}



//MOTOR CREACION DE UNA IMAGE A PARTIR DE UN MAPA DE TILES
/*
void draw_screen_with_textures(){

    float vtxcoords[12];
    float texcoords[8];


    //background image
    /////////////////////////////////////////////////////
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
    ///////////////////////////////////////////////////////////

    //LEVEL
    ///////////////////////////////////////////////////////////

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_ALPHA);
    glAlphaFunc(GL_GREATER, GL_ZERO);
    glEnable(GL_ALPHA_TEST);


    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, _idlevel);

    vtxcoords[0] = 0.0f;
    vtxcoords[1] = 0.0f;
    vtxcoords[2] = 0.0f;

    vtxcoords[3] = 0.0f;
    vtxcoords[4] = (float)WINDOW_HEIGHT;
    vtxcoords[5] = 0.0f;

    vtxcoords[6] = (float)WINDOW_WIDTH;
    vtxcoords[7] = (float)WINDOW_HEIGHT;
    vtxcoords[8] = 0.0f;

    vtxcoords[9] = (float)WINDOW_WIDTH;
    vtxcoords[10] = 0.0f;
    vtxcoords[11] = 0.0f;

    texcoords[0] = ((lim_ini_fx)/float(SIZE_MAP_X*SIZE_TILE));
    texcoords[1] = ((lim_ini_fy)/float(SIZE_MAP_Y*SIZE_TILE));

    texcoords[2] = ((lim_ini_fx)/float(SIZE_MAP_X*SIZE_TILE));
    texcoords[3] = ((lim_fin_fy)/float(SIZE_MAP_Y*SIZE_TILE));

    texcoords[4] = ((lim_fin_fx)/float(SIZE_MAP_X*SIZE_TILE));
    texcoords[5] = ((lim_fin_fy)/float(SIZE_MAP_Y*SIZE_TILE));

    texcoords[6] = ((lim_fin_fx)/float(SIZE_MAP_X*SIZE_TILE));
    texcoords[7] = ((lim_ini_fy)/float(SIZE_MAP_Y*SIZE_TILE));

    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glPopMatrix();
    ///////////////////////////////////////////////////////////

    //PLAYER
    ////////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_ALPHA);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    glFlush();
}
*/

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

    int screenCamera[] = {X_INF,Y_INF,X_SUP * SIZE_TILE, Y_SUP * SIZE_TILE};

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


    window=SDL_CreateWindow("Prueba XX-v2",
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
    evaluateExtensions();

    loadImage_1();
    //processCustomTileImage();

    bool DONE = false;

    long dX = SDL_GetTicks();

    while (!DONE){
         while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN:
                    SDL_Keysym *keysym = &event.key.keysym;

                    if (keysym->sym == SDLK_LEFT){
                         movement_x -= 10.0f;
                         //movement_x -= 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_RIGHT){

                        movement_x += 10.0f;
                        //movement_x += 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_UP){

                        movement_y -= 10.0f;
                        //movement_y -= 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_DOWN){

                        movement_y += 10.0f;
                        //movement_y += 0.2f * float(SIZE_TILE) * (float(SDL_GetTicks()-dX)/1000.0f);

                    }else if (keysym->sym == SDLK_ESCAPE){
                        DONE = true;

                    }else{

                    }

                    if ((keysym->sym == SDLK_LEFT) || (keysym->sym == SDLK_RIGHT) || (keysym->sym == SDLK_DOWN) || (keysym->sym == SDLK_UP)){
                       //dX = SDL_GetTicks();
                       printf("\r\nPLAYER COORDINATES (%f,%f)",movement_x,movement_y);
                       evaluateCamera_1();
                    }

                break;
            }
         }
         draw_screen_with_textures();
         SDL_GL_SwapWindow(window);
    }

    Terminate_1();
	return 0;
}
