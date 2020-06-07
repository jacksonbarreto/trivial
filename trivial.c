#define __MAIN__
#include "inc/config.h"

int main(void) 
{	
	CONTROLINT choice;
	USER * user;
	
	boot();
	renderOpeningScreen();
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
				listBestPlayers();
			break;
			case LATEST_PLAYERS:
				lastPlayers();
			break;
			case MY_ACCOUNT:
				user = login(1);
				if(user->id != 0)
				{
					do
					{
						choice = rendersAdmMenu(*user);
						switch(choice)
						{
							case EDIT_ACCOUNT:
								changeName(user);
								break;
							case DELETE_ACCOUNT:
								choice = deleteAccount(*user);
								break;
							case INSERT_QUESTION:
								insertQuestion();
								break;
							case CREATE_ADMINISTRATOR:
								promoteUserToAdministrator();
								break;
							case RECOVER_PASSWORD:
								recoverPassword();
								break;
							case EXIT:
								choice = BACK_TO_MAIN_MENU;
						}
					}
					while(choice != BACK_TO_MAIN_MENU);					
				}
				free(user);
			break;
		}
	}
	while(choice != EXIT);
	
	
	turnOff();
	renderClosingScreen();	
	return EXIT_SUCCESS;
}
