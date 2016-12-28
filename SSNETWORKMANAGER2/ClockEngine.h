/*
CLOCKENGINE_H -> Marca el ritmo de juego. Limita el ritmo a 60fps en entornos Desktop y 30fps en entornos moviles.
http://lazyfoo.net/SDL_tutorials/lesson14/
http://gamedev.stackexchange.com/questions/6825/time-based-movement-vs-frame-rate-based-movement
*/

#ifndef CLOCKENGINE_H_INCLUDED
#define CLOCKENGINE_H_INCLUDED

#include "Stdafx.h"

#define DEFAULT_FRAME 60

class ClockEngine{

    public:
        ClockEngine(){
            startTicks = 0;
            pausedTicks = 0;
            paused = false;
            started = false;
            framerrate = DEFAULT_FRAME;
        };

        ClockEngine(int FRAMERRATE){
            startTicks = 0;
            pausedTicks = 0;
            paused = false;
            started = false;
            framerrate = FRAMERRATE;
        };


        ~ClockEngine(){
            startTicks = 0;
            pausedTicks = 0;
            paused = false;
            started = false;
            framerrate = DEFAULT_FRAME;
        };

        void start(){
            started = true;
            paused = false;
            startTicks = SDL_GetTicks();
        };

        void stop(){
            started = false;
            paused = false;
        };

        void pause(){
            if( ( started == true ) && ( paused == false ) )
            {
                paused = true;
                pausedTicks = SDL_GetTicks() - startTicks;
            }
        };

        void unpause(){
            if( paused == true )
            {
                paused = false;
                startTicks = SDL_GetTicks() - pausedTicks;
                pausedTicks = 0;
            }

        };

        void setFramerrate(int _framerrate){framerrate = _framerrate;}
        int getFrammerrate(){return framerrate;}

        int get_ticks(){
            if( started == true )
            {
                if( paused == true )
                {
                    return pausedTicks;
                }
                else
                {
                    return SDL_GetTicks() - startTicks;
                }
            }

            return 0;
        }

        bool is_started(){return started;};
        bool is_paused(){return paused;};

        void evaluateFramerrate(){
            if(( get_ticks() < 1000 / framerrate) )
            {
                SDL_Delay( ( 1000 / framerrate) - get_ticks() );
            }
        };

    private:

        int framerrate;
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;
};

#endif // CLOCKENGINE_H_INCLUDED
