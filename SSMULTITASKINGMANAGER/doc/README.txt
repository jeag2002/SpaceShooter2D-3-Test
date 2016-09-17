/*

MULTITASKING

http://www.drdobbs.com/cpp/cooperative-multitasking-in-c/184408532
http://aigamedev.com/open/article/round-robin-multi-tasking/
http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/1991/9104/9104f/9104f.htm

https://libgdx.badlogicgames.com/features.html

http://www.gamedev.net/page/resources/_/technical/game-programming/enginuity-part-iv-r1973
http://www.drdobbs.com/cpp/cooperative-multitasking-in-c/184408532
http://aigamedev.com/open/article/round-robin-multi-tasking/
http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/DDJ/1991/9104/9104f/9104f.htm

https://www.codehosting.net/blog/BlogEngine/post/Lightweight-Cooperative-Multitasking-in-C.aspx

https://www.reddit.com/r/gamedev/comments/2yew3p/parallelizing_the_naughty_dog_engine_using_fibers/
https://msdn.microsoft.com/en-us/library/ms682661.aspx

http://gamedev.stackexchange.com/questions/2116/multi-threaded-game-engine-design-resources

THREADING

http://gamedev.stackexchange.com/questions/2116/multi-threaded-game-engine-design-resources
http://www.gamasutra.com/view/feature/130873/threading_3d_game_engine_basics.php

https://alexagafonov.com/2015/05/05/thread-pool-implementation-in-c-11/
http://stackoverflow.com/questions/10998780/stdthread-calling-method-of-class
http://stackoverflow.com/questions/10673585/start-thread-with-member-function

*/


1-Después de revisar el contenido tanto de Game Coding como de Advanced 2D Game Development; redefino en engine multiTasking
del sistema.

a)El sistema multitasking pasa de ser un separador de tareas (IA, Animacion, ...) a tareas elementales (elementos atómicos; componentes
dinámicos del engine (jugadores remotos, enemigos, fuentes de particulas)).  En cada task, se gestionará tres temas
(Collision, Animation, IA individual).De momento; el jugador principal queda como Tarea principal.

b)Tal y como se ha implementado en SpaceShooter; se define dos queues. Una de eventos activos (teclado/raton);otro de respuestas del
sistemas. Esta última ha de ser thread safe.

c)El jugador principal/jugadores queda como observator de los elementos de la queue (esto lo intenté implementar en su momento, pero no me salio)

d)Se define varios Threads.

d.1)Thread Time; (marca el ritmo del juego. Servirá mas adelante cuando se gestione el juego por componentes)
d.2)Thread GameEngine (+Multitasking)
d.3)Thread Garbage (Elimina por detras los elementos que han sido eliminados)
d.4)Thread IA cooperativa (Gestiona los Steering Behaviours)

(Rendering  y Sonido se gestionan aparte)

De momento; la gestión del jugador principal; los eventos del jugador principal y la lectura de los eventos dinámicos se gestionan en el thread principal.

Task scheduler; Task manager:

http://codereview.stackexchange.com/questions/28437/multithreaded-task-scheduler
http://codereview.stackexchange.com/questions/21336/c-task-scheduler

Observer pattern:

https://sourcemaking.com/design_patterns/observer/cpp/3


ThreadPool:
http://stackoverflow.com/questions/15252292/extend-the-life-of-threads-with-synchronization-c11

/*
Primera etapa.

1-Crear elementos (DynamicElements)
2-Crear Elmento Task
3-Crear Elemento Observer
3.1-->Derivar DynamicElements de Task y Observer.
4-Crear Elemento Subject.
5-Añadir Objeto Log.

Segunda etapa, definir multitasking. --> OK
Tercera etapa, crear ThreadPool. --> OK
Cuarta etapa, crear Time Task. --> OK
Quinta etapa, crear locks --> OK
*/


http://stackoverflow.com/questions/22386428/codeblocks-pthread-example-can-not-compile

http://stackoverflow.com/questions/1151582/pthread-function-from-a-class
http://www.scsc.no/blog/2010/09-03-creating-pthreads-in-c++-using-pointers-to-member-functions.html
http://codereview.stackexchange.com/questions/4589/passing-a-member-function-in-pthread-create

http://stackoverflow.com/questions/5800959/a-c-function-that-periodically-gets-called
http://disi.unitn.it/~abeni/RTOS/periodic_threads-1.c
http://courses.cs.vt.edu/~cs5565/spring2012/projects/project1/posix-timers.c
http://osdl.sourceforge.net/main/documentation/rendering/SDL-threads.html

https://alexagafonov.com/2015/05/05/thread-pool-implementation-in-c-11/
http://stackoverflow.com/questions/10998780/stdthread-calling-method-of-class
http://stackoverflow.com/questions/10673585/start-thread-with-member-function

http://stackoverflow.com/questions/11093139/pthread-input-thread-and-worker-thread-synchronization
http://www.bogotobogo.com/cplusplus/multithreading_pthread.php
http://stackoverflow.com/questions/9822829/one-producer-two-consumers-acting-on-one-queue-produced-by-producer


funcionoids: https://isocpp.org/wiki/faq/pointers-to-members
http://www.bogotobogo.com/cplusplus/C11/3_C11_Threading_Lambda_Functions.php

https://github.com/niXman/mingw-builds/blob/master/tests/time_test.c


http://www.csc.villanova.edu/~mdamian/threads/posixsem.html
http://pages.cs.wisc.edu/~travitch/pthreads_primer.html
http://stackoverflow.com/questions/13558493/c-using-semaphores-instead-of-busy-waiting
http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
https://jlmedina123.wordpress.com/2013/05/03/pthreads-with-mutex-and-semaphores/

http://pages.cs.wisc.edu/~remzi/Classes/537/Fall2008/Notes/threads-semaphores.txt
http://mingw-w64-public.narkive.com/xqvalkAn/shared-semaphores


PRODUCER-CONSUMER:
*****************************************************************************************************
http://www.dreamincode.net/forums/topic/332518-threads-multiple-producerconsumer/
http://www.gamedev.net/topic/534791-a-producerconsumer-example-using-c0x-threads/
http://codegur.com/9822829/one-producer-two-consumers-acting-on-one-queue-produced-by-producer
*****************************************************************************************************

1)Sustituir Timers por Signals.
2)Mejorar la sincronizacion.
