#include "../inc/config.h"


CONTROLINT isAdministrator(USER * user)
{
	return (user->userType == ADMIN_USER);
}

static CONTROLINT usernameExists(USER * user, const char * username)
{
		if(strcmp(user->username,username) == 0)
			return SUCCESS;	
		else
			return INVALID_USER;
}

static CONTROLINT validPassword(USER * user,  const char * password)
{
	if(strcmp(user->password,password) == 0)
		return SUCCESS;
	else
		return INVALID_PASSWORD;
}
/*
desenvolvendo
CONTROLINT userExist( const char * username, const char * password)
{
	FILE * file = openFile(USERS_FILE_NAME,BINARY_READING);
	USER user;
	fseek(file,sizeof(CONTROLINT),SEEK_SET);
	do
	{
		readData(&user,sizeof(USER),1,file);
		if(usernameExists(user,username) == SUCCESS)
		{
			if(validPassword(user,password) == SUCCESS)
				*user
		}
		else
		{
			
		}
	}
	while(feof(file));
	user = createNullUser;
	return user;
}

*/
