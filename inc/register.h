#ifndef __REGISTER_H__
	#define __REGISTER_H__
	#include "config.h"
	
	USER registerNewUserDuringTheGame(void);
	void registerNewUser(void);
	static USER registerUser(void);
	static void getNameForRegister(char * name);
	static void getUsernameForRegister(char * username);
	static void getNickname(char * nickname);
	static void getPasswordForRegister(char * password, CONTROLINT attempt);
	
	
#endif
