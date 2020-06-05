#ifndef __VIEW_H__
	#define __VIEW_H__
	#include "config.h"
	
	/*Player*/
	CONTROLINT rendersMainMenu(void);
	CONTROLINT rendersGetGameMode(void);
	CONTROLINT rendersGetTotalPlayers(void);
	CONTROLINT rendersInvalidUsername(CONTROLINT attempts);
	CONTROLINT rendersGetTheme(char themesName[][MAX_SIZE_THEME_NAME],const CONTROLINT totalThemes);
	CONTROLINT rendersGetAnswer(QUESTION mountedQuestion, USER player, CONTROLINT gameMode);
	void rendersInvalidPassword(CONTROLINT attempts);
	void rendersMaxAttempts(void);
	void rendersGetUsername(char * username);
	void rendersGetPassword(char * password);
	void rendersResultQuestion(QUESTION mountedQuestion, CONTROLINT choice, CONTROLINT correct);
	void renderParabens(USER player);
		
	/*Register*/
	void rendersGetNameForRegister(char * name);
	void rendersGetUsernameForRegister(char * username);
	void rendersGetNickname(char * nickname);
	void rendersGetPasswordForRegister(char * password, CONTROLINT attempt);
	CONTROLINT rendersFullRegister(USER temporaryUser);
	CONTROLINT rendersPasswordsDoNotMatch(void);
	CONTROLINT rendersInvalidNickname(void);
	CONTROLINT rendersUsernameAlreadyExists(void);
	void rendersDesistRegistering(void);
	
	/*Adm*/	
	void rendersGetQuestionTitle(char * title);
	void rendersGetQuestionRightAnswer(char * correctAnswer);
	void rendersGetQuestionAnswer(char * answer, CONTROLINT progressBarPosition);
	CONTROLINT rendersConfirmationQuestion(QUESTION question);
	
	/*History*/
	void rendersHistory(NODE ** history);
	void redersHistoryFatalError(void);
	
	/*Top 10*/
	void rendersTopPlayers(NODE ** history);
	void redersTop10FatalError(void);
	void renderParabensTop(USER player);
	
	/*Ecrãs estaticos*/
	void renderInicio(void);
	void renderCreditos(void);	
	
#endif
