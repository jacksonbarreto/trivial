#ifndef __LOGIN_H__
	#define __LOGIN_H__
	#include "config.h"
	
	USER * login(const CONTROLINT totLogin);
	USER registerUser(void);
	CONTROLINT isAdministrator(USER * user);
	static char * getUsername(void);
	static char * getPassword(void);
	
#endif
