#ifndef _ALIEN_H_
#define _ALIEN_H_

typedef struct _S_ALIEN_OBJECT {

	int m_nFSM;
	int m_nStep;

	double m_fXpos;
	double m_fYpos;

	double m_fSpeed;

	double m_fCenterX;
	double m_fCenterY;

	_S_MAP_OBJECT *m_pBody;
	_S_BULLET_OBJECT *m_pBullet;

	void (*pfApply)(struct _S_ALIEN_OBJECT *,double);
	void (*pfDraw)(struct _S_ALIEN_OBJECT *,_S_MAP_OBJECT * );

} _S_ALIEN_OBJECT;

void alien_init(_S_ALIEN_OBJECT *pObj,_S_MAP_OBJECT *pBody,double x,double y);

#endif
