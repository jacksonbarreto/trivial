#include "../inc/history.h"



void lastPlayers(void)
{
	
	if(historyPlayers == NULL)
	{
		eventsHandling(QUEUE_NOT_STARTED);
		redersHistoryFatalError();
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

void equeue(NODE ** frontQueue, USER player)
{
	if(frontQueue == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	else
	{
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
	}		
}

void dqueue(NODE ** frontQueue)
{
	NODE * aux;
	
	if(frontQueue == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	else
	{
		if( *frontQueue != NULL)
		{
			aux = *frontQueue;
			*frontQueue = (**frontQueue).next;
			free(aux);
		}
		else
			eventsHandling(EMPTY_QUEUE);		
	}	
}

void deleteQueue(NODE ** frontQueue)
{
	NODE * current, * next;
	
	if(frontQueue == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	else
	{
		current = *frontQueue;
		*frontQueue = NULL;
		
		while(current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}
	}	
}

void saveHistoryList(NODE ** history, CONTROLINT historySize)
{	
	if(history == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	
	FILEINF info;
	NODE * current;
	FILE * file = fopen(HISTORY_FILE_NAME, BINARY_WRITING);
	
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
	else
	{
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
}

USER returnsLastPlayersOneByOne(NODE ** history) //caso não tenha ordenação alfabética, usa-se essa
{
	if(history == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	
	static NODE * aux = NULL;
	USER temporaryPlayer;
	
	if(*history != NULL)	
	{
		if(aux == NULL)	
			aux = *history;
	
		temporaryPlayer = aux->info;
		aux = aux->next;			
	}
	else
	{
		eventsHandling(EMPTY_QUEUE); //acrescentar esta opção na fila vazia no manipulador de erro deste tipo
		temporaryPlayer = createNullUser(); //tratar esse retorno
	}		
	return temporaryPlayer;			
}



