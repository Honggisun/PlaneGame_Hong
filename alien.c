#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "engine2d.h"
#include "map.h"

#include "bullet.h"
#include "alien.h"

static void Apply(_S_ALIEN_OBJECT *pObj,double deltaTick)
{
	double speed = 1.0;

	switch(pObj->m_nFSM) {

		case 0: //die
			break;
		case 1: //ready
			pObj->m_nFSM = 2;
			break;
		case 2: //move right
			pObj->m_fXpos += (deltaTick * speed);
			if(pObj->m_fXpos > 34) {
				pObj->m_fYpos +=2;
				pObj->m_nFSM = 3;
				pObj->m_nStep = 0;

				if(pObj->m_fYpos > 15) {
					pObj->m_nFSM = 0;
				}
			}
			if(pObj->m_pBullet != NULL) {
				if(pObj->m_pBullet->m_nFSM == 0) {
					pObj->m_pBullet->pfFire(pObj->m_pBullet,
							pObj->m_fXpos,pObj->m_fYpos,10.0,
							0,1.0,3.0);
				}
			}

			break;
		case 3: //move left
			pObj->m_fXpos -=(deltaTick * speed);
			if(pObj->m_fXpos <= 0 ) {
				pObj->m_fYpos +=2;
				pObj->m_nStep = 0;
				pObj->m_nFSM = 2;	
				if(pObj->m_fYpos > 15) {
					pObj->m_nFSM = 0;
				}

			}
			if(pObj->m_pBullet != NULL) {
				if(pObj->m_pBullet->m_nFSM == 0) {
					pObj->m_pBullet->pfFire(pObj->m_pBullet,
							pObj->m_fXpos,pObj->m_fYpos,10.0,
							0,1.0,3.0);
				}
			}


			break;

	}

}
static void Draw(_S_ALIEN_OBJECT *pObj, _S_MAP_OBJECT *pBuff)
{
	switch(pObj->m_nFSM) 
	{
		case 0:
			break;
		default :
			map_drawTile_trn(pObj->m_pBody,
					(int)(pObj->m_fXpos + pObj->m_fCenterX),
					(int)(pObj->m_fYpos + pObj->m_fCenterY),
					pBuff);

			break;
	}
}

void alien_init(_S_ALIEN_OBJECT *pObj,_S_MAP_OBJECT *pBody,double x,double y)
{
	pObj->m_nFSM = 0;
	pObj->m_nStep = 0;
	pObj->m_pBody = pBody;
	pObj->m_fYpos = y;
	pObj->m_fXpos = x;
	pObj->m_fSpeed = 0;

	pObj->m_fCenterX = 0 - (pBody->m_header.m_nWidth/2);
	pObj->m_fCenterY = 0 - (pBody->m_header.m_nHeight/2);
	pObj->m_pBullet = NULL;
	
	pObj->pfApply = Apply;
	pObj->pfDraw = Draw;


}


