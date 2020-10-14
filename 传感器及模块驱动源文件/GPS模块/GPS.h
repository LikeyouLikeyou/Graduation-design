#ifndef __GPS_H_
#define __GPS_H_

#include "stm32f10x.h"


void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);


#endif
