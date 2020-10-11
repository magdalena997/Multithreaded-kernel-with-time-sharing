#include"semaphor.h"
#include <iostream.h>
#include "KernelSm.h"


Semaphore::Semaphore(int init){
	myImpl=new KernelSem(init);
}

void Semaphore::signal(){

	myImpl->signal();

}

#ifndef BCC_BLOCK_IGNORE
Semaphore::~Semaphore(){
	lock
	delete myImpl;
	unlock
}



int Semaphore::wait(int toBlock){
	int i=0;
	lock
	i=myImpl->wait(toBlock);
	unlock
	return i;
}
#endif
int Semaphore::val() const{
	return myImpl->val();
}
