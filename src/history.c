#include "../inc/history.h"

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

void saveHistoryList(NODE ** historyPlayers, CONTROLINT historySize)
{
	FILEINF info;
	NODE * current;
	FILE * file = fopen(HISTORY_FILE_NAME, BINARY_WRITING);
	
	if(historyPlayers == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
		
	info.size = historySize;
	
	writeData(&info,sizeof(FILEINF),1,file); 
	
	current = *historyPlayers; 
	while(current != NULL)
	{		
		writeData(&current->info,sizeof(USER),1,file);
		current = current->next;
	}
	
	fclose(file);
}

void historyForPrint(NODE ** historyPlayers, USER * players, CONTROLINT historySize)
{
	if(historyPlayers == NULL) 
		eventsHandling(QUEUE_NOT_STARTED);
	
	CONTROLINT i;	
	NODE * aux = *historyPlayers;
	
	for(i=0;i<historySize;i++)
	{
		players[i] = aux->info;
		aux = aux->next;
	}
	bubbleSort(players,historySize,INCREASING,STRING_DATA);
}
