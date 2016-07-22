#ifndef	__GAME_H__
#define __GAME_H__

struct timespec work_timer;
double acc_tick,last_tick;

int bLoop = 1;
int nFSM = 0;
int nStep = 0;

_S_MAP_OBJECT gScreenBuf[3];

_S_MAP_OBJECT gPlaneModel;
_S_MAP_OBJECT gAlienModel;
_S_MAP_OBJECT gAlienModel2;

_S_MAP_OBJECT gPlasmaModel;
_S_MAP_OBJECT gBulletModel;

_S_Plane gTestPlaneObject;
_S_ALIEN_OBJECT gTestAlienObject[10];
_S_BULLET_OBJECT gTestBulletObject[10];
_S_BULLET_OBJECT gTestBulletObject2[10];

void game_init()
{

	for(int i=0;i<2;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],35,30);
	}
	map_init(&gScreenBuf[1]);
	map_load(&gScreenBuf[1],"jamjam.dat");

	map_init(&gPlaneModel);
	map_load(&gPlaneModel,"plane5.dat");


	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien5.dat");

	map_init(&gPlasmaModel);
	map_load(&gPlasmaModel,"bullet5.dat");

	map_init(&gBulletModel);
	map_load(&gBulletModel,"bullet5.dat");


	Plane_init(&gTestPlaneObject,&gPlaneModel,17,25);
	

	gTestPlaneObject.m_nFSM = 1;

	double TablePosition[] = {0,3.0,6.0,9.0,12.0,15.0,18.0,21.0,24.0,27.0};

	for(int i=0;i< sizeof(gTestBulletObject)/sizeof(_S_BULLET_OBJECT); i++)
	{
		bullet_init(&gTestBulletObject[i],0,0,0,&gBulletModel);
	}
		for(int i=0;i< 10; i++)
	{
		bullet_init(&gTestBulletObject2[i],0,0,0,&gPlasmaModel);
	}
	
	
	for(int i=0;i<10;i++)
	{
		_S_ALIEN_OBJECT *pObj = &gTestAlienObject[i];
		alien_init(pObj,&gAlienModel,1,2);
		pObj->m_fXpos = TablePosition[i];
		pObj->m_fYpos = 3;
		pObj->m_nFSM = 1;
		gTestAlienObject[i].m_pBullet = &gTestBulletObject2[i];


	}

	system("clear");

	set_conio_terminal_mode();
	acc_tick=last_tick=0;

}

void game_play()
{

		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + 
			(double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;
		//실시간 입력
		if(kbhit() != 0) {
			char ch = getch();
			if(ch == 'q') {
				nFSM = 0;
				puts("bye~ \r");
			}
			if(ch == 'j') {
				for(int i=0;i<sizeof(gTestBulletObject)/sizeof(_S_BULLET_OBJECT);i++) {
					_S_BULLET_OBJECT *pObj = &gTestBulletObject[i];
					if(pObj->m_nFSM == 0) { //슬립상태라면...

						pObj->pfFire(pObj,
								gTestPlaneObject.m_fXpos,
								gTestPlaneObject.m_fYpos,5,0,-2,3);
						break;
					}

				}
			}
		
			gTestPlaneObject.pfApply(&gTestPlaneObject,delta_tick,ch);
		}
	
		






		
		for(int i=0;i<10;i++) {
			_S_ALIEN_OBJECT *pObj = &gTestAlienObject[i];
			pObj->pfApply(pObj,delta_tick);		

	
		}
		for(int i=0;i<4;i++) {

			if(gTestBulletObject2[i].m_nFSM != 0)	{
				double bullet_pos_x = gTestBulletObject2[i].m_fXpos;	 //총알 시작위치
				double bullet_pos_y = gTestBulletObject2[i].m_fYpos;	

				double target_pos_x = gTestPlaneObject.m_fXpos;
				double target_pos_y = gTestPlaneObject.m_fYpos;

				double vx = target_pos_x - bullet_pos_x;
				double vy = target_pos_y - bullet_pos_y;
	
				double dist = sqrt(vx*vx+vy*vy);


				if(dist < 2.0) {
					gTestBulletObject2[i].m_nFSM = 0;
					gTestPlaneObject.m_nFSM = 0;
					puts("-------------game over-------------");
				}
			}

		}

		for(int i=0;i<sizeof(gTestBulletObject)/sizeof(_S_BULLET_OBJECT); i++)

			if(gTestBulletObject[i].m_nFSM !=0) {
				double bullet_pos_x = gTestBulletObject[i].m_fXpos;	 //총알 시작위치
				double bullet_pos_y = gTestBulletObject[i].m_fYpos;	

				double target_pos_x = gTestAlienObject[i].m_fXpos;
				double target_pos_y = gTestAlienObject[i].m_fYpos;

				double vx = target_pos_x - bullet_pos_x;
				double vy = target_pos_y - bullet_pos_y;

				double dist = sqrt(vx*vx+vy*vy);

				if(dist < 3.0) {
					gTestBulletObject[i].m_nFSM = 0;
					gTestAlienObject[i].m_nFSM = 0;
				}
			}




		for(int i=0;i<sizeof(gTestBulletObject)/sizeof(_S_BULLET_OBJECT);i++) {
			gTestBulletObject[i].pfApply(&gTestBulletObject[i],delta_tick);
		}
		for(int i=0;i<4;i++) {
			gTestBulletObject2[i].pfApply(&gTestBulletObject2[i],delta_tick);
		}




		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.01) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
			gTestPlaneObject.pfDraw(&gTestPlaneObject,&gScreenBuf[1]);

			for(int i=0;i<sizeof(gTestBulletObject)/sizeof(_S_BULLET_OBJECT);i++) {
				_S_BULLET_OBJECT *pObj = &gTestBulletObject[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);	
			}



			for(int i=0;i<10;i++) {

				_S_ALIEN_OBJECT *pObj = &gTestAlienObject[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}
			for(int i=0;i<4;i++) {

				_S_BULLET_OBJECT *pObj = &gTestBulletObject2[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}


			map_dump(&gScreenBuf[1],Default_Tilepalete);
			acc_tick = 0;
		}


}
#endif
