#include "../inc/sort.h"

	
		

void bubbleSort(USER * list, int listSize, int sortType, int dataType)
{
	int i, j, exchangeStatus;
	int (*sortingMethod) (USER *list, int index);
	
	if(sortType == DECREASING)
	{
		if(dataType == STRING_DATA)
			sortingMethod = sortDecreasingString;
		else
			sortingMethod = sortDecreasingNumber;	
	}
	else
	{
		if(dataType == STRING_DATA)
			sortingMethod = sortIncreasingString;
		else
			sortingMethod = sortIncreasingNumber;
	}
			
	for(i=0;i<listSize-1;i++)
	{
		for(j=0;j<listSize-1-i;j++)
			exchangeStatus = (*sortingMethod)(list,j);
		if(exchangeStatus == DONTCHANGED)
			break;		
	}		
			
}

static void switchPosition(USER *list, int index)
{
	USER auxiliary;
	
	auxiliary = list[index];
	list[index] = list[index+1];
	list[index+1] = auxiliary;
}

static int sortIncreasingString(USER *list, int index)
{	
	if(strcmp(list[index].name,list[index+1].name) > 0)
	{
		switchPosition(list, index);
		return CHANGED;
	}
	return DONTCHANGED;		
}

static int sortIncreasingNumber(USER *list, int index)
{	
	if(list[index].percentageCorrect > list[index+1].percentageCorrect)
	{
		switchPosition(list, index);
		return CHANGED;
	}
	return DONTCHANGED;
}

static int sortDecreasingString(USER *list, int index)
{	
	if(strcmp(list[index].name,list[index+1].name) < 0)
	{
		switchPosition(list, index);
		return CHANGED;
	}
	return DONTCHANGED;
}

static int sortDecreasingNumber(USER *list, int index)
{	
	if(list[index].percentageCorrect < list[index+1].percentageCorrect){
		switchPosition(list, index);
		return CHANGED;
	}
	return DONTCHANGED;
}

