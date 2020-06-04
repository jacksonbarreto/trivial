#ifndef __HISTORY_H__
	#define __HISTORY_H__
	#include "config.h"
	
	NODE ** newqueue(void);
	void equeue(NODE ** frontQueue, USER player);
	void dqueue(NODE ** frontQueue);
	void deleteQueue(NODE ** frontQueue);
	void saveHistoryList(NODE ** historyPlayers, CONTROLINT historySize);
	void historyForPrint(NODE ** historyPlayers, USER * players, CONTROLINT historySize);
	
	USER returnsLastPlayersOneByOne(NODE ** historyPlayers); //caso não tenha ordenação alfabética
	void lastPlayers(void);
#endif
