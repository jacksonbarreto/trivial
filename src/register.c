#include "../inc/register.h"

USER registerNewUserDuringTheGame(void)
{
	USER temporaryUser;
	temporaryUser = registerUser();
	insertUser(temporaryUser);
	renderSuccessCreateUser();
	return 	temporaryUser;
}

void registerNewUser(void)
{
	USER temporaryUser;
	temporaryUser = registerUser();
	insertUser(temporaryUser);
	renderSuccessCreateUser();
}

static USER registerUser(void)
{
	USER temporaryUser;
	CONTROLINT choice, status;
	char name[MAX_NAME_SIZE];
	char username[MAX_USERNAME_SIZE];
	char nickname[MAX_NICKNAME_SIZE];
	char password[MAX_PASSWD_SIZE];
	char temporaryPassword[MAX_PASSWD_SIZE];
	
	do
	{
		temporaryUser = createNullUser();
		getNameForRegister(name);
		strcpy(temporaryUser.name,name);
		
		do
		{		
			getUsernameForRegister(username);
					
			if(usernameExists(username) != SUCCESS)
			{
				strcpy(temporaryUser.username,username);
				temporaryUser.id =	createUserId();
				status = SUCCESS;
			}
			else
			{
				status = FAILURE;
				choice = rendersUsernameAlreadyExists(); 	
				if(choice != REGISTER_USER)
				{
					temporaryUser = createNullUser();
					return temporaryUser;
				}				 
			}
		}
		while(status != SUCCESS);
		
		do
		{
			getNickname(nickname);
			
			if(nicknameExists(nickname) != SUCCESS)
			{
				strcpy(temporaryUser.nickname,nickname);
				status = SUCCESS;			
			}
			else
			{
				status = FAILURE;
				choice = rendersInvalidNickname(); 
				if(choice != REGISTER_USER)
				{
					temporaryUser = createNullUser();
					reverseCreatedIDForUsers();
					return temporaryUser;
				}				 
			}
		}
		while(status != SUCCESS);	
		
		do
		{
			getPasswordForRegister(password,GET_PASSWORD);
			getPasswordForRegister(temporaryPassword,PASSWORD_CONFIRMATION);
			
			if(strcmp(password,temporaryPassword) == 0)
			{
				status = SUCCESS;
				strcpy(temporaryUser.password,password);
			}
			else
			{
				status = FAILURE;
				choice = rendersPasswordsDoNotMatch(); 
				if(choice != REGISTER_USER)
				{
					temporaryUser = createNullUser();
					reverseCreatedIDForUsers();
					return temporaryUser;
				}	
			}
		}
		while(status != SUCCESS);
		
		choice = rendersFullRegister(temporaryUser);
		if(choice != REGISTER_USER)
		{
			status = SUCCESS;			
		}
		else
		{
			status = FAILURE;
			reverseCreatedIDForUsers();
		}	
	}
	while(status != SUCCESS);
	
	return temporaryUser;
}

static void getNameForRegister(char * name)
{
	rendersGetNameForRegister(name);
}

static void getUsernameForRegister(char * username)
{
	rendersGetUsernameForRegister(username);
}

static void getNickname(char * nickname)
{
	rendersGetNickname(nickname);
}

static void getPasswordForRegister(char * password, CONTROLINT attempt)
{
	rendersGetPasswordForRegister(password, attempt);
}
