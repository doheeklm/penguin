/* CS_Sim.h */
#ifndef _CS_SIM_H_
#define _CS_SIM_H_

void SIM_Login( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Create( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Search( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Delete( unsigned char *pucHeader, unsigned char *pucBody );
void SIM_Logout( unsigned char *pucHeader, unsigned char *pucBody );

#endif /* _CS_SIM_H_ */
