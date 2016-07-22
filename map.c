#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "engine2d.h"

char Default_Tilepalete[] = {
	'.',//0
	'#',//1
	'@',//2
	'/',//3
	92,//4
	'+',//5
	'=',//6
	'^',//7
	'>',//8
	'<',//9
	'|',//10
	'-',//11
	'*'//12
 };

void map_init(_S_MAP_OBJECT *pObj)
{
	pObj->m_pBuf = NULL;
	pObj->fpLoad = map_load;
	pObj->fpSave = map_save;
	pObj->fpDump = map_dump;
	pObj->fpNew = map_new;
	pObj->fpPutTile = map_PutTile;
	pObj->fpDrawTile = map_drawTile;
	pObj->fpDrawTile_trn = map_drawTile_trn;
	pObj->fpDrawTile_mirror_v = map_drawTile_mirror_v;
	pObj->fpDrawTile_mirror_h = map_drawTile_mirror_h;
}

void map_dump(_S_MAP_OBJECT *pObj,char *pTile_pal)
{
	/*putTile(
			0,pObj->m_header.m_nHeight,
			0,pObj->m_header.m_nWidth,
			pObj->m_header.m_nWidth,
			pObj->m_pBuf,
			pTile_pal	
		   );
	*/
	for(int iy=0;iy < pObj->m_header.m_nHeight;iy++) {
		for(int ix=0;ix < pObj->m_header.m_nWidth;ix++) {
			putchar(pTile_pal[ pObj->m_pBuf[iy* pObj->m_header.m_nWidth + ix]]);
		}
		printf("\r\n");
	}
}


void map_new(_S_MAP_OBJECT *pObj,int nWidth,int nHeight)
{
	int nSize = nWidth*nHeight; 
	
	if(pObj->m_pBuf !=NULL) {free(pObj->m_pBuf); }
	pObj->m_header.m_nWidth =  nWidth;// atoi(strtok(NULL," "));
	pObj->m_header.m_nHeight = nHeight;//atoi(strtok(NULL," "));
	//printf("%d \r\n",nSize);
	pObj->m_pBuf = malloc( nSize);

	for(int i=0;i< nSize ;i++) {
		pObj->m_pBuf[i] = 0;
		//printf("%d",pObj->m_pBuf[i]);
	}
	

}

void map_PutTile(_S_MAP_OBJECT *pObj, int x,int y,int nTileIndex)
{
	//클리핑 처리 
	if(x >= 0 && y >=0) {
		if(x < pObj->m_header.m_nWidth && y < pObj->m_header.m_nHeight) {
			pObj->m_pBuf[ pObj->m_header.m_nWidth * y + x  ] = nTileIndex;
		}
	}
}

//0 : 성공
//1 : 실패 
int map_save(_S_MAP_OBJECT *pObj,char *filename)
{
	FILE *pf = fopen(filename,"wb");
	fwrite( &( pObj->m_header),sizeof(pObj->m_header),1,pf);
	int nSize = pObj->m_header.m_nWidth * pObj->m_header.m_nHeight;
	fwrite(pObj->m_pBuf,nSize,1,pf);

	fclose(pf);
	return 0;

}
//0: success
//1 : error
int map_load(_S_MAP_OBJECT *pObj,char *filename)
{
	FILE *pf = fopen(filename,"rb");
	fread( &(pObj->m_header),sizeof(_S_MAP_HEADER),1,pf);

	if(pObj->m_pBuf) {
		free(pObj->m_pBuf);
	}
	int nSize = pObj->m_header.m_nWidth * pObj->m_header.m_nHeight;
	pObj->m_pBuf = malloc( nSize);

	fread(pObj->m_pBuf,nSize,1,pf);

	for(int i=0;i<nSize;i++) {
		printf("%d,",pObj->m_pBuf[i]);
	}

	return 0;
}

void map_drawTile(_S_MAP_OBJECT *pObj,int posx,int posy,_S_MAP_OBJECT *pTarget)
{
//	_S_MAP_OBJECT *pObj = &humanObj;
//	_S_MAP_OBJECT *pTarget = &screenBuf;
//	int posx = 5;
//	int posy = 5;

	for(int iy=0;iy < pObj->m_header.m_nHeight;iy++) {
		for(int ix = 0; ix < pObj->m_header.m_nWidth;ix++) {
			map_PutTile(pTarget,ix + posx,iy + posy,
					pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix]);
		}
	}

}

void map_drawTile_mirror_h(_S_MAP_OBJECT *pObj,int posx,int posy,_S_MAP_OBJECT *pTarget) 
{	
	for(int iy=0;iy < pObj->m_header.m_nHeight;iy++) {
		for(int ix = 0; ix < pObj->m_header.m_nWidth;ix++) {
			map_PutTile(pTarget, posx - ix,iy + posy,
					pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix]);
		}
	}

}


void map_drawTile_mirror_v(_S_MAP_OBJECT *pObj,int posx,int posy,_S_MAP_OBJECT *pTarget) 
{	
	for(int iy=0;iy < pObj->m_header.m_nHeight;iy++) {
		for(int ix = 0; ix < pObj->m_header.m_nWidth;ix++) {
			map_PutTile(pTarget,ix + posx, posy -iy,
					pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix]);
		}
	}

}

void map_drawTile_trn(_S_MAP_OBJECT *pObj, int posx,int posy,_S_MAP_OBJECT *pTarget) 
{
	for(int iy=0;iy < pObj->m_header.m_nHeight;iy++) {
		for(int ix = 0; ix < pObj->m_header.m_nWidth;ix++) {
			int nPixel = pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix];
			if(nPixel != 0) {
				map_PutTile(pTarget,ix + posx,iy + posy,
						pObj->m_pBuf[iy*pObj->m_header.m_nWidth + ix]);
			}
		}
	}

}






