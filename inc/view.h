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
	void rendersNotEnoughQuestions(void);
	void rendersLoggedUser(void);
	
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
	void renderSuccessCreateUser(void);
	
	/*Adm*/	
	CONTROLINT rendersAdmMenu(USER user);
	CONTROLINT rendersGetTheme(char themesName[][MAX_SIZE_THEME_NAME],const CONTROLINT totalThemes);
	void rendersGetQuestionTitle(char * title);
	void rendersGetQuestionRightAnswer(char * correctAnswer);
	void rendersGetQuestionAnswer(char * answer, CONTROLINT progressBarPosition);
	CONTROLINT rendersConfirmationQuestion(QUESTION question);
	void rendersGetUsernameForAdm(char * username);
	CONTROLINT rendersInvalidUsernameForAdm(void);
	CONTROLINT rendersFullRegisterForAdm(USER temporaryUser);
	void rendersAuccessfulAssignment(USER user);
	void rendersGetUsernameForRecoverPassword(char * username);
	void rendersRecoverPassword(USER user);
	void rendersGetNameForChangeName(char * name, USER user);
	void rendersSuccessfulNameChange(USER user);
	CONTROLINT rendersDeleteAccount(void);
	void rendersSuccessfulDeleteAccount(USER user);
	void rendersErrorDeleteAccount(void);
	
	/*History*/
	void rendersHistory(NODE ** history);
	void redersHistoryFatalError(void);
	
	/*Top 10*/
	void rendersTopPlayers(NODE ** history);
	void redersTop10FatalError(void);
	void renderCongratulationsTop(USER player);
	
	/*Ecr�s estaticos*/
	void renderOpeningScreen(void);
	void renderClosingScreen(void);	
	
#endif
