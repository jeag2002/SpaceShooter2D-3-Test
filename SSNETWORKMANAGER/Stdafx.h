#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED


#include "Constants.h"
#include <windows.h>

extern "C"
{
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
}

#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <SDL_net.h>
#include <SDL.h>
#undef main

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include <time.h>
#include <algorithm>
#include <functional>

#include <semaphore.h>


#endif // STDAFX_H_INCLUDED
