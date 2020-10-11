#ifndef _SYS_H_
#define _SYS_H_

#include <stdlib.h>
#include <dos.h>
#include "SCHEDULE.H"

enum Status{kreiran, spreman, zavrsen, running, blokirane};


#define lock asm{pushf; cli}
#define unlock asm popf;

void inic();

void restore();
typedef unsigned char IVTNo;

typedef void interrupt (*PtrToIntr)(...);

#define PREPAREENTRY(entryNumber, callOld)\
		void interrupt inter##entryNumber(...);\
		IVTEntry newEntry##entryNumber(entryNumber, inter##entryNumber, callOld);\
		void interrupt inter##entryNumber(...){newEntry##entryNumber.signal();\
		                                       if(callOld) newEntry##entryNumber.callOldRoutine();}\




#endif
