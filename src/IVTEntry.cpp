#include"IVTEntry.h"

IVTEntry* IVTEntry::IVT[256];
#ifndef BCC_BLOCK_IGNORE

IVTEntry::IVTEntry(IVTNo num, PtrToIntr newInterrupt, int old){
	lock
	entry=num;
	callOld=old;
	oldInterrupt=getvect(num);
	setvect(num, newInterrupt);
	event=0;
	IVT[num]=this;
	unlock
}

void IVTEntry::callOldRoutine(){
	oldInterrupt();
}

IVTEntry::~IVTEntry(){
	lock
	setvect(entry, oldInterrupt);
	event=0;
	IVT[entry]=0;
	oldInterrupt();
	unlock
}
#endif

void IVTEntry::signal(){
	if(callOld) oldInterrupt();
	if(event!=0) event->signal();
}


IVTEntry* IVTEntry::getIVTentry(IVTNo n){
	return IVT[n];
}
