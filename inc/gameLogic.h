#ifndef __GAME_LOGIC_H__
	#define __GAME_LOGIC_H__
	#include "config.h"
	
	CONTROLINT startGame(void);
	static CONTROLINT getGameMode(void);
	static CONTROLINT getTotalPlayers(void);
	static CONTROLINT playRound(USER * players,const CONTROLINT totalPlayers, const CONTROLINT gameMode);
	static THEME * instantiateThemes(void);
	static CONTROLINT correctOption(const QUESTION originalQuestion, const QUESTION questionChanged);
	static CONTROLINT isAnswerCorrect(const CONTROLINT choice, const CONTROLINT correctOption);
 	static void punctuatePlayer(USER * player, CONTROLINT chosenTheme);
	static CONTROLINT isEndGame(const USER * playersList, const CONTROLINT currentPlayer, const CONTROLINT gameMode);
	static CONTROLINT isEndRound(const CONTROLINT currentPlayer, const CONTROLINT totalPlayers);
	static void restartRound(CONTROLINT * currentPlayer);
	static CONTROLINT getAnswer(QUESTION mountedQuestion, USER player, CONTROLINT gameMode);
	static CONTROLINT getTheme(void);
	static void advanceRound(CONTROLINT * currentPlayer);
	static float getPercentageCorrectAnswers(const USER * player, const CONTROLINT gameMode);
	static void bootPlayer(USER * player);
	void resetCurrentScore(USER * user);
	static CONTROLINT isTop(USER player);
	static void insertTop(USER player);
	static void insertHistory(USER * playersList, const CONTROLINT totalPlayers);
	static CONTROLINT defineDeckSize(const CONTROLINT gameMode, const CONTROLINT totalPlayers, const float averageErrorAnswer, const CONTROLINT totalThemes);
	static float averageWrongAnswersRound(USER * players, const CONTROLINT totalPlayers);
	static float averageWrongAnswersGlobal(float currentGlobalAverage, float roundAverage, CONTROLINT * totalRounds);
	static void increasesGlobalRound(USER * players, const CONTROLINT totalPlayers, SETTINGS * settings);
#endif
