#include "../inc/gameLogic.h"

CONTROLINT startGame(void)
{
	CONTROLINT gameMode, totalPlayers;
	USER * players;
	
	gameMode = getGameMode();
	totalPlayers = getTotalPlayers();
	players = login(totalPlayers);
	playRound(players,totalPlayers,gameMode);
	
	return SUCCESS;
}

static CONTROLINT getGameMode(void)
{
	CONTROLINT gameMode;
	
	gameMode = rendersGetGameMode();
	
	return gameMode;	
}

static CONTROLINT getTotalPlayers(void)
{
	CONTROLINT totalPlayers;
	
	totalPlayers = rendersGetTotalPlayers();
	
	return totalPlayers;
}

static CONTROLINT playRound(USER * players,const CONTROLINT totalPlayers, const CONTROLINT gameMode)
{
	CONTROLINT i, currentPlayer, deckSize, chosenTheme, choice, result;
	float averageRound;
	QUESTION originalQuestion, mountedQuestion;
	THEME * listThemes;
	
	listThemes = instantiateThemes();
	bubbleSort(players, totalPlayers, INCREASING, ID_DATA);
	
	for(i=0; i < totalPlayers; i++)
		bootPlayer(&players[i]);
	
	deckSize = defineDeckSize(gameMode,totalPlayers,settings.averageGlobalErrorAnswer,settings.totalThemes);
	
	currentPlayer=0;
	do
	{
		if(isEndRound(currentPlayer,totalPlayers))	
			restartRound(&currentPlayer);
		deckControl(listThemes,settings.totalThemes,deckSize,GAME_STARTED);
		
		do
		{
			chosenTheme = getTheme(listThemes); //escolha do tema
			
			originalQuestion = popDeck(listThemes[chosenTheme].deck);
			mountedQuestion = originalQuestion;
			shufflesAnswers(mountedQuestion.answers,MAX_RESPONSE_OPTIONS);
			
			choice = getAnswer(mountedQuestion);
			
			result = isAnswerCorrect(choice,correctOption(originalQuestion,mountedQuestion));
			
			rendersResultQuestion(mountedQuestion, choice, correctOption(originalQuestion,mountedQuestion));
			
			if(result)
			{
				punctuatePlayer(&players[currentPlayer],chosenTheme); //corrigir tem que mandar o tema para pontuar corretamente
				players[currentPlayer].percentageCorrect = getPercentageCorrectAnswers(&players[currentPlayer],gameMode);
				if(isEndGame(players,currentPlayer,gameMode))
				{
					if(isTop(players[currentPlayer]))
					{
						insertTop(players[currentPlayer]);
						//Imprime parabens vc é um top 10.
					}
						
					
					//insertHistory(players); corrigir a função insertHistory
					deckControl(listThemes,settings.totalThemes,deckSize,GAME_FINISHED);
					increasesGlobalRound(players,totalPlayers,&settings);
					free(listThemes);
					//imprime vítoria do jogador
					return 1; //termina tudo			
				}	
			}
		}while(result);
		advanceRound(&currentPlayer);		
	}while(REPEAT);
}

static CONTROLINT getAnswer(QUESTION mountedQuestion)
{
	CONTROLINT choice;
	
	choice = rendersGetAnswer(mountedQuestion);
	
	return choice-1; //retorna o indice do vetor onde está a resposta.
}

static CONTROLINT getTheme(THEME * themes)
{
	CONTROLINT choice;
	char themesName[4][MAX_THEME_SIZE]; //corrigir não esta sendo usada
	
	choice = rendersGetTheme(themesName,4);
	
	return choice-1; //é o índice do vetor	
}

static THEME * instantiateThemes(void)
{
	FILE * file = openFile(THEMES_FILE_NAME, BINARY_READING);
	THEME * listThemes;
	CONTROLINT i;
	
	listThemes = (THEME *) allocateMemory(settings.totalThemes, sizeof(THEME));
	for(i=0;i<settings.totalThemes;i++)
	{
		readData(&listThemes[i],sizeof(THEME),1,file);
		listThemes[i].deck = createDeck();
	}
	fclose(file);
	return listThemes;
}

static CONTROLINT correctOption(const QUESTION originalQuestion, const QUESTION questionChanged)
{
	CONTROLINT i;
	
	for(i=0; i < MAX_RESPONSE_OPTIONS; i++)
		if(strcmp(originalQuestion.answers[CORRECT_ANSWER],questionChanged.answers[i]) == 0)
			return i;
}	

static CONTROLINT isAnswerCorrect(const CONTROLINT choice, const CONTROLINT correctOption)
{
	return (choice == correctOption);
}

void punctuatePlayer(USER * player, CONTROLINT chosenTheme)
{
	player->currentScore[chosenTheme]++;
}

static CONTROLINT isEndGame(const USER * playersList, const CONTROLINT currentPlayer, const CONTROLINT gameMode)
{
	CONTROLINT i, status;
	
	for(i=0, status=0;i<TOTAL_THEMES;i++)
	{
		if(playersList[currentPlayer].currentScore[1] >= gameMode)
			status++;
	}
	return (status == TOTAL_THEMES);
}

static CONTROLINT isEndRound(const CONTROLINT currentPlayer, const CONTROLINT totalPlayers)
{
	return (currentPlayer == totalPlayers-1);
}

static void restartRound(CONTROLINT * currentPlayer)
{
	*currentPlayer = RESET;
}

static void advanceRound(CONTROLINT * currentPlayer)
{
	(*currentPlayer)++;
}

static float getPercentageCorrectAnswers(const USER * player, const CONTROLINT gameMode)
{
	return ((float) gameMode * 100) / player->totalAnswered;
}

static void bootPlayer(USER * player)
{
	player->totalAnswered = RESET;
	player->currentScore[0] = RESET;
	player->currentScore[1] = RESET;
	player->currentScore[2] = RESET;
	player->currentScore[3] = RESET;
	player->percentageCorrect = RESET;
}

static CONTROLINT isTop(USER player)
{
	if(topPlayers == NULL)
		return SUCCESS;
	return (player.percentageCorrect > topPlayers[settings.topSize-1].percentageCorrect);
	
}

static void insertTop(USER player)
{
	if(topPlayers == NULL || settings.topSize < MAX_TOP_LIST)
	{
		topPlayers = (USER *) reAllocateMemory(topPlayers,sizeof(USER)*(settings.topSize+1));
		settings.topSize++;
	} 
	
	topPlayers[settings.topSize-1] = player;	
	bubbleSort(topPlayers,settings.topSize,DECREASING,NUMBER_DATA);	
}

static void insertHistory(USER player) //ta errado, tem que inserir todos que jogaram
{
	if(historyPlayers == NULL || settings.historySize < MAX_HISTORY_LIST)
	{
		historyPlayers = (USER *) reAllocateMemory(historyPlayers,sizeof(USER)*(settings.historySize+1));
		settings.historySize++;
	} 
	
	historyPlayers[settings.historySize-1] = player;	
	bubbleSort(historyPlayers,settings.historySize,INCREASING,STRING_DATA);
}

static CONTROLINT defineDeckSize(const CONTROLINT gameMode, const CONTROLINT totalPlayers, const float averageErrorAnswer, const CONTROLINT totalThemes)
{
	CONTROLINT deckSize;
	CONTROLINT averageErrorInt = (CONTROLINT) roundInteger(averageErrorAnswer);
	
	deckSize = (gameMode * totalPlayers * averageErrorInt)/totalThemes;
	
	return deckSize;
}

static float averageWrongAnswersRound(USER * players, const CONTROLINT totalPlayers)
{
	float average;
	CONTROLINT i, wrongAnswers;
	
	for(i=0,wrongAnswers=0;i<totalPlayers;i++)
	{
		//wrongAnswers += (players[i].totalAnswered - players[i].currentScore); //corrigir tem que pegar o escore de cada tema
	}
	average = wrongAnswers / (float) totalPlayers;
	
	return average;
}

static float averageWrongAnswersGlobal(float currentGlobalAverage, float roundAverage, CONTROLINT * totalRounds)
{
	float newGlobalAverage;
	
	newGlobalAverage = ((currentGlobalAverage * (*totalRounds)) + roundAverage)/ ++(*totalRounds);
	
	return newGlobalAverage;
}

static void increasesGlobalRound(USER * players, const CONTROLINT totalPlayers, SETTINGS * settings)
{
	float roundAverage = averageWrongAnswersRound(players,totalPlayers);
	settings->averageGlobalErrorAnswer = averageWrongAnswersGlobal(settings->averageGlobalErrorAnswer,roundAverage,&settings->totalRoundsGlobal);
}
