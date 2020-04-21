#include "../inc/config.h"


CONTROLINT isAdministrator(USER * user)
{
	return (user->userType == ADMIN_USER);
}

CONTROLINT userExists(USER * user, const char * username)
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
