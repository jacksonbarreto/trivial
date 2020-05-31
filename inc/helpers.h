#ifndef __HELPERS_H__
	#define __HELPERS_H__
	#include "config.h"
	
	void getString(const CONTROLINT responseSize, char *answer);
	CONTROLINT getShortInteger(const char *question);
	void clearBuffer(void);

	CONTROLINT inRange(const int number, const int inferiorLimit, const int upperLimit, const CONTROLINT rangeType);
	CONTROLINT randomNumber(const int start, int end);
	void swapString(char *stringA, char *stringB);
	void shufflesAnswers(char array[][MAX_ANSWER_SIZE], const CONTROLINT size);
	static struct tm * currentDateTime(void);
	char * formattedDateTime(void);
	void * allocateMemory(const int quantity, const int dataSize);
	void * reAllocateMemory(USER * oldPointer, const int newSize);
	long int roundInteger(double number);
	void shuffleQuestions(QUESTION * listQuestion, const CONTROLINT size);
	void swapQuestion(QUESTION * questionA, QUESTION * questionB);
	void wait(void);
	CONTROLINT getChoiceMenu(void);
#endif
