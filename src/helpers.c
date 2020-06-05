#include "../inc/helpers.h"

void getString(const CONTROLINT responseSize, char *answer)
{
	char inputFilter[12];
	
	clearBuffer();
	sprintf(inputFilter," \%%%hu[^\n]s",responseSize);	
	scanf(inputFilter,answer);
}

CONTROLINT getShortInteger(const char *question)
{
	CONTROLINT integer;
	
	printf(question);
	scanf(" %hu",&integer);
	clearBuffer();
	return integer;
}

CONTROLINT getChoiceMenu(void)
{
	char choice;
	CONTROLINT number;
	
	do
	{
		choice = getch();				
	}
	while(!(choice >= 48 && choice <= 57));
	
	number = (CONTROLINT) choice - '0';
	return number;
}

void clearBuffer(void)
{
	setbuf(stdin, keyboard);
	//char garbageCollector;
	//while((garbageCollector = getchar()) != '\n' && garbageCollector != EOF);	
}



CONTROLINT inRange(const int number, const int inferiorLimit, const int upperLimit, const CONTROLINT rangeType)
{	
	switch(rangeType)
	{
		case CLOSED_RANGE:
			return (number >= inferiorLimit && number <= upperLimit);
			break;							
		case OPEN_RANGE:
			return (number > inferiorLimit && number < upperLimit);		
			break;
		default:
			return FALSE;
	}
}

CONTROLINT randomNumber(const int start, int end)
{
	static CONTROLINT initialized=FALSE;
	if (start >= end)
		return FALSE;
		
    if(initialized == FALSE)
	{
        srand((unsigned int) time(NULL));
        initialized = TRUE;
    }
    end = (end - start)+1;
	
	return (start + rand() % end);
}

void swapString(char *stringA, char *stringB)
{
	char * auxiliaryString = (char *) malloc(strlen(stringA)+1);
	
	strcpy(auxiliaryString,stringA);
	strcpy(stringA,stringB);
	strcpy(stringB,auxiliaryString);
	
	free(auxiliaryString);
}

void shufflesAnswers(char array[][MAX_ANSWER_SIZE], const CONTROLINT size)
{
	CONTROLINT i;
	for(i=size-1; i>0 ; i--)
		swapString(array[i],array[randomNumber(0,i)]);
	
}

void swapQuestion(QUESTION * questionA, QUESTION * questionB)
{
	QUESTION auxiliaryQuestion;
	auxiliaryQuestion = *questionA;
	*questionA = *questionB;
	*questionB = auxiliaryQuestion;
}

void shuffleQuestions(QUESTION * listQuestion, const CONTROLINT size)
{
	CONTROLINT i, aux;
	QUESTION auxiliaryQuestion;
	for(i=size-1; i>0 ; i--)
		swapQuestion(&listQuestion[i],&listQuestion[randomNumber(0,i)]);
}

static struct tm * currentDateTime(void)
{
	time_t now;	
	time(&now);
	return localtime(&now);
}

char * formattedDateTime(void)
{
	static char formattedDate[22];
	struct tm d;
	d = *currentDateTime();
	
	sprintf(formattedDate,"%d/%2d/%d - %2d:%2d:%2d",d.tm_mday,d.tm_mon+1,d.tm_year+1900,d.tm_hour, d.tm_min,d.tm_sec);
	
	return formattedDate;
}

void * allocateMemory(const int quantity, const int dataSize)
{
	void * pointer = calloc(quantity, dataSize);
	if(pointer == NULL)
		eventsHandling(CRITICAL_FAILURE);
	return pointer;
}

void * reAllocateMemory(USER * oldPointer, const int newSize)
{
	void * pointer = realloc(oldPointer,newSize);
	if(pointer == NULL)
		eventsHandling(CRITICAL_FAILURE);
	return pointer;
}

long int roundInteger(double number)
{
	long int roundNumber;
	
	roundNumber = (int) number;
	number -= roundNumber;
	if(number > 0.5)
		roundNumber++;
	
	return roundNumber;
}

void wait(void)
{
	clearBuffer();
	getch();
}
