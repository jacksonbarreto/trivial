#include "../inc/history.h"



void lastPlayers(void)
{
	
	if(historyPlayers == NULL)
	{
		eventsHandling(QUEUE_NOT_STARTED);
		redersHistoryError();
	}
	else
	{
		rendersHistory(historyPlayers); 
	}	
}



NODE ** newqueue(void)
{
	return (NODE **) allocateMemory(1,sizeof(NODE));
}

int equeue(NODE ** frontQueue, USER player)
{
	if(frontQueue == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
		
	NODE * newNode = (NODE *) allocateMemory(1,sizeof(NODE));
	NODE * aux;

	newNode->info = player;
	newNode->next = NULL;		
	if(*frontQueue == NULL)
	{
		(*frontQueue) = newNode;		
	}
	else
	{
		aux = *frontQueue;
		while(aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = newNode;
	}
	return SUCCESS;		
}

void dqueue(NODE ** frontQueue)
{
	NODE * aux;
	
	if(frontQueue == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);

	if( *frontQueue != NULL)
	{
		aux = *frontQueue;
		*frontQueue = (**frontQueue).next;
		free(aux);
	}
	else
		eventsHandling(EMPTY_QUEUE);
	
}

void deleteQueue(NODE ** frontQueue)
{
	NODE * current, * next;
	
	if(frontQueue == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
		
	current = *frontQueue;
	*frontQueue = NULL;
	
	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void saveHistoryList(NODE ** history, CONTROLINT historySize)
{
	FILEINF info;
	NODE * current;
	FILE * file = fopen(HISTORY_FILE_NAME, BINARY_WRITING);
	
	if(history == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
		
	info.size = historySize;
	
	writeData(&info,sizeof(FILEINF),1,file); 
	
	current = *history; 
	while(current != NULL)
	{		
		writeData(&current->info,sizeof(USER),1,file);
		current = current->next;
	}
	
	fclose(file);
}

void historyForPrint(NODE ** history, USER * players, CONTROLINT historySize)
{
	if(history == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	
	CONTROLINT i;	
	NODE * aux = *history;
	
	if(historySize > 0)
	{
		for(i=0;i<historySize;i++)
		{
			players[i] = aux->info;
			aux = aux->next;
		}
		bubbleSort(players,historySize,INCREASING,STRING_DATA);
	}
	else
		eventsHandling(EMPTY_QUEUE); //acrescentar esta opção na fila vazia no manipulador de erro deste tipo
}

USER returnsLastPlayersOneByOne(NODE ** history) //caso não tenha ordenação alfabética, usa-se essa
{
	if(history == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	
	static NODE * aux = NULL;
	USER temporaryUser;
	
	if(*history != NULL)	
	{
		if(aux == NULL)	
			aux = *historyPlayers;
	
		temporaryUser = aux->info;
		aux = aux->next;			
	}
	else
	{
		eventsHandling(EMPTY_QUEUE); //acrescentar esta opção na fila vazia no manipulador de erro deste tipo
		temporaryUser = createNullUser(); 
	}
	
	return temporaryUser;	
}



