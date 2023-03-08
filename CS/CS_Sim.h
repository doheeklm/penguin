/* CS_Sim.h */
#ifndef _CS_SIM_H_
#define _CS_SIM_H_

void SIM_SetBodyLen( unsigned char *pucBuf, int unBodyLen );
void SIM_Login( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Create( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Search( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Delete( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Logout( unsigned char *pucHeader, unsigned char *pucBody );

int SIM_SetDetailInfo( unsigned char *pucBuf, int nLen, int cnt, int card_id, char *name, char *company, char *team, char position, char title, char *mobile, char *tel, char *email );
int SIM_SetSimpleInfo( unsigned char *pucBuf, int nLen, int cnt, int card_id, char *name, char *company, char *mobile );

#endif /* _CS_SIM_H_ */
