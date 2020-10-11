#include "Idle.h"
#include "Thread.h"
#include<conio.h>
Idle::Idle():Thread(defaultStackSize,1) {}



void Idle::run(){
	while(1){ //cprintf("idle");
	}

}
