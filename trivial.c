#define __MAIN__
#include "inc/config.h"

int main(void) 
{	
	CONTROLINT choice;
	
	boot();
	
	do
	{
		choice = rendersMainMenu();
		switch(choice)
		{
			case PLAY:
				startGame();
				break;
			case NEW_USER:
				registerNewUser();
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
	
	
	turnOff();
		
	return EXIT_SUCCESS;
}
