#include "../inc/login.h"

USER * login(const CONTROLINT totLogin)
{
	CONTROLINT i, j, choice, attempts;
	USER * players;
	USER temporaryUser;
	char username[MAX_USERNAME_SIZE];
	char password[MAX_PASSWD_SIZE];
	
	players = (USER *) allocateMemory(totLogin,sizeof(USER));
	
	for(i=0; i < totLogin; i++)
	{
		attempts = 0;		
		do
		{
			choice = 0;
			attempts++;
			if(attempts > MAXIMUM_LOGIN_ATTEMPTS)
			{
				rendersMaxAttempts();
				free(players);
				return NULL;
			}
			getUsername(username);
			temporaryUser =	findUserByUsername(username);
			
			if(temporaryUser.id == 0)
			{
				choice = rendersInvalidUsername(attempts);
				if(choice == REGISTER_USER)
					temporaryUser = registerNewUserDuringTheGame();
				else
					rendersDesistRegistering();
			}
			else if(i>0 && totLogin > 1)
			{
				for(j=0;j<i;j++)
				{
					if(players[j].id == temporaryUser.id)
					{
						rendersLoggedUser();
						temporaryUser.id = 0;
					}
				}
			}
		}while(temporaryUser.id == 0);
		
		if(choice != REGISTER_USER) 
		{
			attempts = 0;
			do
			{
				attempts++;
				if(attempts > MAXIMUM_LOGIN_ATTEMPTS)
				{
					rendersMaxAttempts();
					free(players);
					return NULL;
				}
				if(attempts > 1)
					rendersInvalidPassword(attempts);
					
				getPassword(password);
			}
			while(strcmp(temporaryUser.password,password) != 0);
				
		}		
		players[i] = temporaryUser;	
	}
	
	return players;
}


static void getUsername(char * username)
{
	
	rendersGetUsername(username);
}

static void getPassword(char * password)
{
	rendersGetPassword(password);
}



CONTROLINT isAdministrator(USER * user)
{
	return (user->userType == ADMIN_USER);
}



