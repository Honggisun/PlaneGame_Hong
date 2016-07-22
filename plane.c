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

#include "plane.h"

void Plane_Apply(_S_Plane *pObj,double deltaTick,char key_input)
{
	switch(pObj->m_nFSM) {
		case 0: //die
			break;
		case 1: //play
			
			switch(key_input)
			{
				case 'a':
					pObj->m_fXpos -= 1;
					break;
				case 'd':
					pObj->m_fXpos += 1;
					break;
				case 'w':
					pObj->m_fYpos -= 1;
					break;
				case 's':
					pObj->m_fYpos += 1;
					break;
			}

			break;
	}
}
void Plane_Draw(_S_Plane *pObj, _S_MAP_OBJECT *pBuff)
{
	switch(pObj->m_nFSM)
	{
		case 0:
			break;
		default :
			map_drawTile_trn(pObj->m_pBody,(int)(pObj->m_fXpos - pObj->m_fCenterX),(int)(pObj->m_fYpos - pObj->m_fCenterY),pBuff);

			break;

	}
}

void Plane_init(_S_Plane *pObj,_S_MAP_OBJECT *pBody,double x,double y)
{
	pObj->m_nFSM = 0;
	pObj->m_nStep = 0;
	pObj->m_pBody = pBody;
	pObj->m_fYpos = y;
	pObj->m_fXpos = x;
	pObj->m_fCenterX = 0 + (pBody->m_header.m_nWidth/2);//중심점
	pObj->m_fCenterY = 0 + (pBody->m_header.m_nHeight/2);
	
	pObj->pfApply = Plane_Apply;//
	pObj->pfDraw = Plane_Draw;//

}

