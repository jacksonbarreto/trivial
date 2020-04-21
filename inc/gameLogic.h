#ifndef __GAME_LOGIC_H__
	#define __GAME_LOGIC_H__
	#include "config.h"

	SINT correctOption(const QUESTION originalQuestion, const QUESTION questionChanged);
	CONTROLINT isAnswerCorrect(const CONTROLINT choice, const CONTROLINT correctOption);
	void punctuatePlayer(USER * player);
	CONTROLINT isEndGame(const USER * playersList, const CONTROLINT currentPlayer, const CONTROLINT gameMode);
	CONTROLINT isEndRound(const CONTROLINT currentPlayer, const CONTROLINT totalPlayers);
	void restartRound(CONTROLINT * currentPlayer);
	void advanceRound(CONTROLINT * currentPlayer);
	float getPercentageCorrectAnswers(const USER * player, const CONTROLINT gameMode);
	void bootPlayer(USER * player);
	void insertTop(USER player);
	void insertHistory(USER player);
	
#endif
