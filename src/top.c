#include "../inc/top.h"



void listBestPlayers(void)
{
	
	if(topPlayers == NULL)
	{
		eventsHandling(LIST_NOT_STARTED);
		redersTop10FatalError();
	}
	else
	{
		rendersTopPlayers(topPlayers); 
	}	
}




NODE ** newList(void)
{
	return (NODE **) allocateMemory(1,sizeof(NODE));
}

void insertInOrder(NODE ** topList, USER info)
{
	if(topList == NULL) 
		eventsHandling(LIST_NOT_STARTED);
	else
	{
		NODE * newNode = (NODE *) allocateMemory(1,sizeof(NODE));
		NODE * previous, * current;	
	
		newNode->info = info;
		newNode->next = NULL;
		
		if(*topList == NULL)
			*topList = newNode;
		else
		{
			current = *topList;
			previous = NULL;
			while(current != NULL && current->info.percentageCorrect > info.percentageCorrect)
			{
				previous = current;
				current = current->next;
			}
			if(previous == NULL)
			{
				newNode->next = *topList;
				*topList = newNode;
			}
			else
			{
				if(previous->next == NULL)
				{
					previous->next = newNode;
				}
				else
				{
					newNode->next = previous->next;
					previous->next = newNode;
				}	
			}			
		}	
	}		
}

void removeEndList(NODE ** topList)
{
	if(topList == NULL) 
		eventsHandling(LIST_NOT_STARTED);
	else
	{
		NODE * aux;
		if(*topList != NULL)
		{
			aux = *topList;
			while((aux->next)->next != NULL)
				aux = aux->next;
			free(aux->next);
			aux->next = NULL;
		}
		else
			eventsHandling(LIST_QUEUE);
	}	
}

USER returnsLastInTheList(NODE ** topList)
{
	if(topList == NULL) 
		eventsHandling(LIST_NOT_STARTED);
	
	NODE * aux;
	USER temporaryPlayer;
	if(*topList != NULL)
	{
		aux = *topList;
		while(aux->next != NULL)
			aux = aux->next;
		temporaryPlayer = aux->info;
	}
	else
	{
		eventsHandling(LIST_QUEUE); // desnecessário pois gera registro no prieiro uso
		temporaryPlayer = createNullUser();
	}	
	
	return temporaryPlayer;
}

void saveTopList(NODE ** topList, CONTROLINT topSize)
{
	if(topList == NULL) 
		eventsHandling(LIST_NOT_STARTED);
		
	FILEINF info;
	NODE * current;
	FILE * file = fopen(TOP_LIST_FILE_NAME, BINARY_WRITING);
	
	info.size = topSize;

	writeData(&info,sizeof(FILEINF),1,file); 
	
	current = *topList; 
	while(current != NULL)
	{		
		writeData(&current->info,sizeof(USER),1,file);
		current = current->next;
	}
	fclose(file);
}

void deleteList(NODE ** topList)
{
	NODE * current, * next;
	
	if(topList == NULL)
		eventsHandling(LIST_NOT_STARTED);
	
	current = *topList;
	*topList = NULL;
	
	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

CONTROLINT sizeList(NODE ** topList)
{
	if(topList == NULL)
		eventsHandling(LIST_NOT_STARTED);
		
	NODE * aux = *topList;
	CONTROLINT cont = 0;
		
	while(aux != NULL)
	{
		aux = aux->next;
		cont++;
	}
	return cont;
}
void returnsTopPlayers(NODE ** topList, USER * players)
{
	if(topList == NULL) 
		eventsHandling(LIST_NOT_STARTED);
	
	NODE * aux ;
	CONTROLINT i, size= sizeList(topList);
	
	if(*topList != NULL)	
	{		
		aux = *topList;	
		for(i=0;i<size;i++)
		{
			players[i] = aux->info;
			aux = aux->next;
		}		
	}
	else
	{
		eventsHandling(LIST_QUEUE);
	}		
		
}
