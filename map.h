#ifndef __MAP_H__
#define __MAP_H__

typedef struct {
	int m_nSkima;
	int m_nWidth;
	int m_nHeight;
}_S_MAP_HEADER;

typedef struct _S_MAP_OBJECT{
	_S_MAP_HEADER m_header;
	char *m_pBuf;
//멤버함수 정의..////////////////////////////////////////////////////////////////////
	int (*fpLoad)(struct _S_MAP_OBJECT *,char *);
	int (*fpSave)(struct _S_MAP_OBJECT *,char *);
	void (*fpDump)(struct _S_MAP_OBJECT *,char *);
	void (*fpNew)(struct _S_MAP_OBJECT *,int,int);
	void (*fpPutTile)(struct _S_MAP_OBJECT *,int,int,int);
	void (*fpDrawTile)(struct _S_MAP_OBJECT *,int,int,struct _S_MAP_OBJECT *);
	void (*fpDrawTile_mirror_v)(struct _S_MAP_OBJECT *,int,int,struct _S_MAP_OBJECT *);
	void (*fpDrawTile_mirror_h)(struct _S_MAP_OBJECT *,int,int,struct _S_MAP_OBJECT *);
	void (*fpDrawTile_trn)(struct _S_MAP_OBJECT *,int,int,struct _S_MAP_OBJECT *);
////////////////////////////////////////////////////////////////////////////////////
}_S_MAP_OBJECT;

extern char Default_Tilepalete[];

void map_init(_S_MAP_OBJECT *pObj);
int map_load(_S_MAP_OBJECT *pObj,char *filename);
int map_save(_S_MAP_OBJECT *pObj,char *filename);

void map_dump(_S_MAP_OBJECT *pObj,char *pTile_pal);
void map_new(_S_MAP_OBJECT *pObj,int nWidth,int nHeight);
void map_PutTile(_S_MAP_OBJECT *pObj, int x,int y,int nTileIndex);

void map_drawTile(_S_MAP_OBJECT *pObj,int posx,int posy,_S_MAP_OBJECT *pTarget);
void map_drawTile_mirror_v(_S_MAP_OBJECT *pObj,int posx,int posy,_S_MAP_OBJECT *pTarget);
void map_drawTile_mirror_h(_S_MAP_OBJECT *pObj,int posx,int posy,_S_MAP_OBJECT *pTarget);
void map_drawTile_trn(_S_MAP_OBJECT *pObj,int posx,int posy,_S_MAP_OBJECT *pTarget);

#endif
