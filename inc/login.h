#ifndef __LOGIN_H__
	#define __LOGIN_H__
	#include "config.h"
	
	CONTROLINT isAdministrator(USER * user);
	CONTROLINT usernameExists(USER * user, const char * username);
	static CONTROLINT validPassword(USER * user,  const char * password);
	
#endif
