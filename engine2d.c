#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>


#include "engine2d.h"

struct termios orig_termios;

void reset_terminal_mode()
{
	tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
	struct termios new_termios;

	/* take two copies - one for now, one for later */
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));

	/* register cleanup handler, and set the new terminal mode */
	atexit(reset_terminal_mode);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
	int r;
	unsigned char c;
	if ((r = read(0, &c, sizeof(c))) < 0) {
		return r;
	} else {
		return c;
	}
}

//------------------console grp---------
void setColor(int fore_color,int backg_color)
{
	printf("%c[%d;%dm",0x1b,fore_color,backg_color);
}

void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1b,y,x);

}


void drawMyBox(
		int nXpos,int nYpos,
		int nColor,int nSize)
{
	int ix,iy;

	setColor(30,nColor);
	ix=0;
	for(iy=0;iy <= nSize;iy++) {
		for(ix=0;ix <=nSize;ix++) {
			gotoxy(ix+nXpos,iy+nYpos);
			printf(" ");
		}
	}

	setColor(0,0);

}
//--------------타일멥 엔진-------------
void map_drawAll(int *pMap);
void map_printCell(int rawdata);

void map_printCell(int rawdata)
{
	switch(rawdata) {
		case 0: //공터 
			printf(" ");
			break;
		case 1: //벽
			printf("#");
			break;
		case 2: //문 
			printf("M");
			break;
		default:
			printf(" ");
			break;
	}

}

void map_drawAll(int *pMap)
{
	int ix,iy;

	for(iy=0;iy<8;iy++) {
		for(ix=0;ix<8;ix++) {
			map_printCell(pMap[ix+iy*8]);
		}
		printf("\r\n");
	}
}

void putTile(int sy,int ey,int sx,int ex,
int width,
char *ptrBuf,
char *chrTable
)

{
	int ix,iy;

	for(iy=sy;iy<ey;iy++) {
		for(ix=sx;ix<ex;ix++) {
			
			putchar(chrTable[ptrBuf[(iy*width)+ix]]);
		}
		printf("\r\n");
		//puts("");
	}
}



