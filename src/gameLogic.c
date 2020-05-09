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
	
	//chama a fun��o design que cria tela e captura o numero
	
	return gameMode;	
}

static CONTROLINT getTotalPlayers(void)
{
	CONTROLINT totalPlayers;
	
	//chama a fun��o design que cria tela e captura o numero
	
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
			
			//fun��o de design que imprime resultado enviado
			
			if(result)
			{
				punctuatePlayer(&players[currentPlayer]);
				players[currentPlayer].percentageCorrect = getPercentageCorrectAnswers(&players[currentPlayer],gameMode);
				if(isEndGame(players,currentPlayer,gameMode))
				{
					if(isTop(players[currentPlayer]))
					{
						insertTop(players[currentPlayer]);
						//Imprime parabens vc � um top 10.
					}
						
					
					//insertHistory(players); corrigir a fun��o insertHistory
					deckControl(listThemes,settings.totalThemes,deckSize,GAME_FINISHED);
					increasesGlobalRound(players,totalPlayers,&settings);
					free(listThemes);
					//imprime v�toria do jogador
					return 1; //termina tudo			
				}	
			}
		}while(result);
		advanceRound(&currentPlayer);		
	}while(REPEAT);
}

static CONTROLINT getAnswer(const QUESTION mountedQuestion)
{
	CONTROLINT choice, status=SUCCESS;
	//chama fun��o que imprime a pergunta.
	//chama fun��o que pega a resposta.
	do
	{
		if(status == FAILURE)
		{
			//imprime tela de escolha fora do intervalo aceit�vel. systen pause
			status = SUCCESS;
		}
		
		if(!inRange(choice,1,MAX_RESPONSE_OPTIONS,CLOSED_RANGE))
			status = FAILURE;
	}while(!inRange(choice,1,MAX_RESPONSE_OPTIONS,CLOSED_RANGE));
	return choice-1; //retorna o indice do vetor onde est� a resposta.
}

static CONTROLINT getTheme(THEME * themes)
{
	CONTROLINT choice;
	
	//chama fun��o que imprime tela com os temas e retorna com a escolha que � o index do tema no vetor
	
	return choice-1; //� o �ndice do vetor	
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

void punctuatePlayer(USER * player)
{
	player->currentScore++;
}

static CONTROLINT isEndGame(const USER * playersList, const CONTROLINT currentPlayer, const CONTROLINT gameMode)
{
	return (playersList[currentPlayer].currentScore == gameMode);
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
	player->currentScore = RESET;
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
		wrongAnswers += (players[i].totalAnswered - players[i].currentScore);
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
