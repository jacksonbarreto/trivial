#include "../inc/gameLogic.h"

SINT correctOption(const QUESTION originalQuestion, const QUESTION questionChanged)
{
	CONTROLINT i;
	
	for(i=0; i < MAX_RESPONSE_OPTIONS; i++)
		if(strcmp(originalQuestion.answers[CORRECT_ANSWER],questionChanged.answers[i]) == 0)
			return i;
	return NOT_FOUND; //quando usar essa funcao tratar esse evento como inconsistencia de dados, 
					//pode por errno para receber o id da pergunta, mas nao sabera o tema remover esse comentario
}	

CONTROLINT isAnswerCorrect(const CONTROLINT choice, const CONTROLINT correctOption)
{
	return (choice == correctOption);
}

void punctuatePlayer(USER * player)
{
	player->currentScore++;
}

CONTROLINT isEndGame(const USER * playersList, const CONTROLINT currentPlayer, const CONTROLINT gameMode)
{
	return (playersList[currentPlayer].currentScore == gameMode);
}

CONTROLINT isEndRound(const CONTROLINT currentPlayer, const CONTROLINT totalPlayers)
{
	return (currentPlayer == totalPlayers);
}

void restartRound(CONTROLINT * currentPlayer)
{
	*currentPlayer = START_ROUND;
}

void advanceRound(CONTROLINT * currentPlayer)
{
	(*currentPlayer)++;
}

float getPercentageCorrectAnswers(const USER * player, const CONTROLINT gameMode)
{
	return ((float) gameMode * 100) / player->totalAnswered;
}

void bootPlayer(USER * player)
{
	player->totalAnswered = START;
	player->currentScore = START;
	player->percentageCorrect = START;
}

CONTROLINT isTop(USER player)
{
	if(topPlayers == NULL)
		return SUCCESS;
	return (player.percentageCorrect > topPlayers[settings.topSize-1].percentageCorrect);
	
}

void insertTop(USER player)
{
	if(topPlayers == NULL || settings.topSize < MAX_TOP_LIST)
	{
		topPlayers = (USER *) reAllocateMemory(topPlayers,sizeof(USER)*(settings.topSize+1));
		settings.topSize++;
	} 
	
	topPlayers[settings.topSize-1] = player;	
	bubbleSort(topPlayers,settings.topSize,DECREASING,NUMBER_DATA);	
}

void insertHistory(USER player)
{
	if(historyPlayers == NULL || settings.historySize < MAX_HISTORY_LIST)
	{
		historyPlayers = (USER *) reAllocateMemory(historyPlayers,sizeof(USER)*(settings.historySize+1));
		settings.historySize++;
	} 
	
	historyPlayers[settings.historySize-1] = player;	
	bubbleSort(historyPlayers,settings.historySize,INCREASING,STRING_DATA);
}

CONTROLINT defineDeckSize(const CONTROLINT gameMode, const CONTROLINT totalPlayers, const float averageErrorAnswer, const CONTROLINT totalThemes)
{
	CONTROLINT deckSize;
	CONTROLINT averageErrorInt = (CONTROLINT) roundInteger(averageErrorAnswer);
	
	deckSize = (gameMode * totalPlayers * averageErrorInt)/totalThemes;
	
	return deckSize;
}



