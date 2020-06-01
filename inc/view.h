#ifndef __VIEW_H__
	#define __VIEW_H__
	#include "config.h"
	
	/*Player*/
	CONTROLINT rendersMainMenu(void);
	CONTROLINT rendersGetGameMode(void);
	CONTROLINT rendersGetTotalPlayers(void);
	CONTROLINT rendersInvalidUsername(CONTROLINT attempts);
	CONTROLINT rendersGetTheme(char themesName[][MAX_SIZE_THEME_NAME],CONTROLINT totalThemes);
	CONTROLINT rendersGetAnswer(QUESTION mountedQuestion);
	void rendersInvalidPassword(CONTROLINT attempts);
	void rendersMaxAttempts(void);
	void rendersGetUsername(char * username);
	void rendersGetPassword(char * password);
	void rendersResultQuestion(QUESTION mountedQuestion, CONTROLINT choice, CONTROLINT correct);
	
	/*Register*/
	void rendersGetNameForRegister(char * name);
	void rendersGetUsernameForRegister(char * username);
	void rendersGetNickname(char * nickname);
	void rendersGetPasswordForRegister(char * password, CONTROLINT attempt);
	CONTROLINT rendersFullRegister(USER temporaryUser);
	CONTROLINT rendersPasswordsDoNotMatch(void);
	CONTROLINT rendersInvalidNickname(void);
	CONTROLINT rendersUsernameAlreadyExists(void);
	
	/*Adm*/
	
	
	
#endif
