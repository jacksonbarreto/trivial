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
			chosenTheme = getTheme();
			
			originalQuestion = popDeck(listThemes[chosenTheme].deck);
			mountedQuestion = originalQuestion;
			shufflesAnswers(mountedQuestion.answers,MAX_RESPONSE_OPTIONS);
			
			choice = getAnswer(mountedQuestion);
			
			result = isAnswerCorrect(choice,correctOption(originalQuestion,mountedQuestion));
			
			rendersResultQuestion(mountedQuestion, choice, correctOption(originalQuestion,mountedQuestion));
			
			if(result)
			{
				punctuatePlayer(&players[currentPlayer],chosenTheme);
				players[currentPlayer].percentageCorrect = getPercentageCorrectAnswers(&players[currentPlayer],gameMode);
				if(isEndGame(players,currentPlayer,gameMode))
				{
					if(isTop(players[currentPlayer]))
					{
						insertTop(players[currentPlayer]);
						//Imprime parabens vc é um top 10.
					}
						
					insertHistory(players,totalPlayers);
					deckControl(listThemes,settings.totalThemes,deckSize,GAME_FINISHED);
					increasesGlobalRound(players,totalPlayers,&settings);
					free(listThemes);
					//imprime vítoria do jogador
					return SUCCESS; //termina tudo			
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

static CONTROLINT getTheme(void)
{
	CONTROLINT choice;
	char themesName[settings.totalThemes][MAX_SIZE_THEME_NAME];
	
	getThemesName(themesName);
	choice = rendersGetTheme(themesName,settings.totalThemes);
	
	return choice-1; //é o índice do vetor	
}

static THEME * instantiateThemes(void)
{
	FILE * file = openFile(THEMES_FILE_NAME, BINARY_READING);
	THEME * listThemes;
	CONTROLINT i;
	
	listThemes = (THEME *) allocateMemory(settings.totalThemes, sizeof(THEME));
	fseek(file,sizeof(FILEINF),SEEK_SET);
	readData(&listThemes,sizeof(THEME),settings.totalThemes,file);
	fclose(file);
	for(i=0;i<settings.totalThemes;i++)
		listThemes[i].deck = createDeck();
		
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
		if(playersList[currentPlayer].currentScore[i] >= gameMode)
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
	return ((float) gameMode * settings.totalThemes * 100) / player->totalAnswered;
}

static void bootPlayer(USER * player)
{
	resetCurrentScore(player);
	player->percentageCorrect = RESET;
}

static CONTROLINT isTop(USER player)
{
	USER temporaryPlayer = returnsLastInTheList(topPlayers);
	
	if(temporaryPlayer.id == 0 || player.percentageCorrect > temporaryPlayer.percentageCorrect)
		return SUCCESS;
	else
		return FAILURE;
}

static void insertTop(USER player)
{
	if(settings.topSize == MAX_TOP_LIST)
	{
		removeEndList(topPlayers);
		settings.topSize--;
	}
	insertInOrder(topPlayers,player);
	settings.topSize++;
	saveTopList(topPlayers,settings.topSize);
}

static void insertHistory(USER * playersList, const CONTROLINT totalPlayers) 
{
	CONTROLINT i;
	
	for(i=0;i<totalPlayers;i++)
	{
		if(settings.historySize == MAX_HISTORY_LIST)
		{
			dqueue(historyPlayers);
			settings.historySize--;
		}	
		equeue(historyPlayers,playersList[i]);
		settings.historySize++;
	}
	saveHistoryList(historyPlayers,settings.historySize);
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
	CONTROLINT i, j, wrongAnswers, currentScore;
	
	for(i=0,wrongAnswers=0;i<totalPlayers;i++)
	{
		for(j=0, currentScore=0;j<TOTAL_THEMES;j++)
		{
			currentScore += players[i].currentScore[j];
		}
		wrongAnswers += (players[i].totalAnswered - currentScore);
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

void resetCurrentScore(USER * user)
{
	CONTROLINT i;
	
	for(i=0;i<TOTAL_THEMES;i++)
		user->currentScore[i] = RESET;
}
