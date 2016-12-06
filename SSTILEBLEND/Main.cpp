#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "GLES/gl.h"
#include "GLES/egl.h"
#include "GLES/glext.h"
#include "GLES/glplatform.h"

#include "SDL.h"
#include "SDL_opengles.h"
#include "SDL_image.h"
#undef main


#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define WINDOW_BPP     16
#define SIZE_TILE      64

#define SIZE_MAP_X 16
#define SIZE_MAP_Y 12

#define X_INF 0
#define X_SUP 9
#define Y_INF 0
#define Y_SUP 7

/*
BUMPMAPPING
GLOOM
*/



SDL_DisplayMode mode;
SDL_Window *window;
SDL_GLContext context;

GLuint id_texture1;
GLuint id_texture2;
GLuint id_texture3;
GLuint id_texture4;

float size_world_x = 0;
float size_world_y = 0;

int lim_ini_x = 0; //OJO x = j; y = i
int lim_ini_y = 0;
int lim_fin_x = 9;
int lim_fin_y = 7;

GLfloat LightAmbient[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

bool isBlend = false;
bool isLight = false;
int texture = 0;


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

void InitGL_2(){
}

void InitGL_1(){
	glShadeModel( GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClearDepthf(1.0f);
	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void resizeWindow_2(int width, int height){
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrthof(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );
    glEnable( GL_LIGHT1 );
    glColor4f( 1.0f, 1.0f, 1.0f, 0.5f);

    glLoadIdentity();
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


void loadImage_1(){

    SDL_Surface *surface = SDL_LoadBMP("./data/background.bmp");

    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }

    surface = ConvertToRGBA_1(surface);

    glGenTextures(1, &id_texture1);
    glBindTexture(GL_TEXTURE_2D, id_texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);


    surface = SDL_LoadBMP("./data/glass.bmp");

    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }

    surface = ConvertToRGBA_1(surface);

    glGenTextures(1, &id_texture2);
    glBindTexture(GL_TEXTURE_2D, id_texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);


    surface = SDL_LoadBMP("./data/glass.bmp");

    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }

    surface = ConvertToRGBA_1(surface);

    glGenTextures(1, &id_texture3);
    glBindTexture(GL_TEXTURE_2D, id_texture3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("./data/glass.bmp");

    if (!surface){
        printf("Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }

    surface = ConvertToRGBA_1(surface);

    glGenTextures(1, &id_texture4);
    glBindTexture(GL_TEXTURE_2D, id_texture4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);
}


void draw_screen_with_textures(){

    float vtxcoords[12];
    float texcoords[8];

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glLoadIdentity();

    if(isLight){
        glEnable(GL_LIGHTING);
    }else{
        glDisable(GL_LIGHTING);
    }


    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, id_texture1);

    vtxcoords[0] = 0.0f;
    vtxcoords[1] = 0.0f;
    vtxcoords[2] = 0.0f;

    vtxcoords[3] = float(WINDOW_WIDTH);
    vtxcoords[4] = 0.0f;
    vtxcoords[5] = 0.0f;

    vtxcoords[6] = 0.0f;
    vtxcoords[7] = float(WINDOW_HEIGHT);
    vtxcoords[8] = 0.0f;

    vtxcoords[9] = float(WINDOW_WIDTH);
    vtxcoords[10] = float(WINDOW_HEIGHT);
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


    glPushMatrix();

    if (texture == 0){
        glBindTexture(GL_TEXTURE_2D, id_texture2);
    }else if (texture == 1){
        glBindTexture(GL_TEXTURE_2D, id_texture3);
    }else{
        glBindTexture(GL_TEXTURE_2D, id_texture4);
    }

    if (isBlend){
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glDisable( GL_DEPTH_TEST );
    }else{
        glDisable( GL_DEPTH_TEST );
    }

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

    texcoords[2] = 1.0f;
    texcoords[3] = 0.0f;

    texcoords[4] = 1.0f;
    texcoords[5] = 1.0f;

    texcoords[6] = 0.0f;
    texcoords[7] = 1.0f;

    glVertexPointer(3, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    if (isBlend){
        glDisable( GL_BLEND );
        glEnable( GL_DEPTH_TEST );
    }else{
        glEnable( GL_DEPTH_TEST );
    }

    glPopMatrix();


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    glFlush();

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


    window=SDL_CreateWindow("Prueba Multitexturing, Blending, Bumpmapping",
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
    char* extensionList = (char*)glGetString(GL_EXTENSIONS);    printf("GLExtensions --> [%s]\r\n",extensionList);

    loadImage_1();
    bool DONE = false;

    while (!DONE){

        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_KEYDOWN:
                    SDL_Keysym *keysym = &event.key.keysym;
                    if (keysym->sym == SDLK_ESCAPE){
                        DONE = true;
                    }
                    else if (keysym->sym == SDLK_b){
                        isBlend = !isBlend;
                    }
                    else if (keysym->sym == SDLK_l){
                        isLight = !isLight;
                    }
                    else if (keysym->sym == SDLK_t){
                        texture = (texture++)%3;
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



