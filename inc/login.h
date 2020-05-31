#ifndef __LOGIN_H__
	#define __LOGIN_H__
	#include "config.h"
	
	USER * login(const CONTROLINT totLogin);
	CONTROLINT isAdministrator(USER * user);
	static void getUsername(char * username);
	static void getPassword(char * password);
	
#endif
