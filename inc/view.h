#ifndef __VIEW_H__
	#define __VIEW_H__
	#include "config.h"
	
	
	CONTROLINT rendersMainMenu(void);
	CONTROLINT rendersGetGameMode(void);
	CONTROLINT rendersGetTotalPlayers(void);
	CONTROLINT rendersInvalidUsername(CONTROLINT attempts);
	CONTROLINT rendersGetTheme(char themesName[][MAX_THEME_SIZE],CONTROLINT totalThemes);
	CONTROLINT rendersGetAnswer(QUESTION mountedQuestion);
	void rendersInvalidPassword(CONTROLINT attempts);
	void rendersMaxAttempts(void);
	void rendersGetUsername(char * username);
	void rendersGetPassword(char * password);
	void rendersResultQuestion(QUESTION mountedQuestion, CONTROLINT choice, CONTROLINT correct);
	
	
#endif
