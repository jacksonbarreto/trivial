#ifndef __TOP_H__
	#define __TOP_H__
	#include "config.h"
	
	void listBestPlayers(void);
	NODE ** newList(void);
	void insertInOrder(NODE ** topList, USER info);
	void saveTopList(NODE ** topList, CONTROLINT topSize);
	void removeEndList(NODE ** topList);
	void deleteList(NODE ** topList);
	CONTROLINT sizeList(NODE ** topList);
	void returnsTopPlayers(NODE ** topList, USER * players);
	USER returnsLastInTheList(NODE ** topList);
#endif
