#ifndef __VIEW_H__
	#define __VIEW_H__
	#include "config.h"
	
	/*Player*/
	CONTROLINT rendersMainMenu(void);
	CONTROLINT rendersGetGameMode(void);
	CONTROLINT rendersGetTotalPlayers(void);
	CONTROLINT rendersInvalidUsername(CONTROLINT attempts);
	CONTROLINT rendersGetThemeForPlaying(char themesName[][MAX_SIZE_THEME_NAME],const CONTROLINT totalThemes, USER player, CONTROLINT gameMode);
	CONTROLINT rendersGetAnswer(QUESTION mountedQuestion, USER player, CONTROLINT gameMode);
	void rendersInvalidPassword(CONTROLINT attempts);
	void rendersMaxAttempts(void);
	void rendersGetUsername(char * username);
	void rendersGetPassword(char * password);
	void rendersResultQuestion(QUESTION mountedQuestion, CONTROLINT choice, CONTROLINT correct, USER player, CONTROLINT gameMode);
	void renderCongratulations(USER player);
		
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
	CONTROLINT rendersGetTheme(char themesName[][MAX_SIZE_THEME_NAME],const CONTROLINT totalThemes);
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
	void renderCongratulationsTop(USER player);
	
	/*Ecrãs estaticos*/
	void renderInicio(void);
	void renderCreditos(void);	
	
#endif
