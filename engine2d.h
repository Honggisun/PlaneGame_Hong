#ifndef __ENGIINE_2D__

#define __ENGIINE_2D__

//----------async key--------------
void reset_terminal_mode();
void set_conio_terminal_mode();
int kbhit();
int getch();
void setColor(int fore_color,int backg_color);
void gotoxy(int x,int y);


#endif
