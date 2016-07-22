#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>

#include "engine2d.h"
#include "map.h"

#include "plane.h"
#include "bullet.h"
#include "alien.h"
#include "game.h"


int main()
{

	while(bLoop) {
		if(nFSM == 0)
		{
			switch(nStep) {
				case 0:
					game_init();
					map_dump(&gScreenBuf[1],Default_Tilepalete);

					puts("press key");
					
					nStep = 1;
					break;
case 1:
					if(kbhit() !=0) {
						if(nStep == 1) {
							system("clear");
						}
						char ch = getch();
						nFSM = 1;
						nStep = 0;
						if(ch == 'q') {
							nFSM = 0;
							bLoop = 0;
							puts("good bye");
						}
					}
					break;

			}

		}
		else if(nFSM == 1)
		{
			game_play();
		}



	}

	return 0;

}
