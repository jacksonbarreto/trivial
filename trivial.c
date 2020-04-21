#define __MAIN__
#include "inc/config.h"

int main(void) 
{	
	CONTROLINT choice;
	
	boot();
	
	do
	{
		switch(choice)
		{
			case PLAY:
				break;
			case NEW_USER:
				break;
			case TOP_10:
				break;
			case LATEST_PLAYERS:
				break;
			case MY_ACCOUNT:
				break;
		}
	}
	while(choice != EXIT);
	
	
	
	system("pause");	
	return EXIT_SUCCESS;
}
