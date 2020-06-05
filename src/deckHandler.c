#include "../inc/deckHandler.h"


void deckControl(THEME * theme,const CONTROLINT totalTheme, const CONTROLINT deckSize, const CONTROLINT gameStatus)
{
	CONTROLINT i;
	
	switch(gameStatus)
	{
		case GAME_STARTED:
			for(i=0;i<totalTheme;i++)
				if(deckIsEmpty(theme[i].deck))
					loadDeck(theme[i].deck, theme[i].id,&theme[i].lastAcess, deckSize);			
			break;
		case GAME_FINISHED:
			for(i=0;i<totalTheme;i++)
				killDeck(theme[i].deck);
			break;
		default:
			eventsHandling(GAME_STATUS_UNIDENTIFIED);
	}	
	
}

static void loadDeck(CARD ** deck, const CONTROLINT themeId, long int * lastAcess, const CONTROLINT deckSize)
{	
	FILE * file;
	CONTROLINT i;
	//QUESTION question;
	QUESTION * areaShuffles = (QUESTION *) allocateMemory(deckSize,sizeof(QUESTION));
	char * fileName = (char *) allocateMemory(strlen(QUESTION_PREFIX)+QUESTION_SUFIX_SIZE,sizeof(char));
		
	sprintf(fileName,"%s%d.dat",QUESTION_PREFIX,themeId);	
	file = openFile(fileName,BINARY_READING);
	
	fseek(file,*lastAcess,SEEK_SET);	
	for(i=0;i<deckSize;i++)
	{	
		do
		{
			readData(&areaShuffles[i],sizeof(QUESTION),1,file);
			//areaShuffles[i] = question;
			if (feof(file))
				fseek(file,sizeof(FILEINF),SEEK_SET);
		}
		while(areaShuffles[i].id == 0);			
	}
	*lastAcess = ftell(file);		
	fclose(file);
	
	//shuffleQuestions(areaShuffles,deckSize);
	for(i=0;i<deckSize;i++)
		pushDeck(deck,areaShuffles[i]);	
	
	free(fileName);
	free(areaShuffles);
}

CARD ** createDeck(void)
{
	CARD ** deck = (CARD **) allocateMemory(1,sizeof(CARD));
	
	*deck = NULL;
	return deck;
}

static void killDeck(CARD ** deck)
{
	CARD * aux;
	while(!deckIsEmpty(deck))
		killCard(deck);
	
	free(deck);
}

QUESTION popDeck(CARD ** deck)
{
	QUESTION question = (**deck).question;
	killCard(deck);
	
	return question;
}

static void pushDeck(CARD ** deck, QUESTION question)
{
	CARD * newCard = (CARD *) allocateMemory(1,sizeof(CARD));
	newCard->question = question;
	newCard->next = (*deck);
	*deck = newCard;	
}

static CONTROLINT deckIsEmpty(CARD ** deck)
{
	return (*deck == NULL);
}

static void killCard(CARD ** deck)
{
	CARD * aux;
	if(deckIsEmpty(deck))
		eventsHandling(REMOVAL_STACK_EMPTY);
	else
	{
		aux = *deck;
		*deck = (**deck).next;
		free(aux);
	}		
}


