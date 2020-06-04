#ifndef __TOP_H__
	#define __TOP_H__
	#include "config.h"
	
	void listBestPlayers(void);
	NODE ** newList(void);
	void insertInOrder(NODE ** topList, USER info);
	void saveTopList(NODE ** topList, CONTROLINT topSize);
	void removeEndList(NODE ** topList);
	void deleteList(NODE ** topList);
	USER returnsTopPlayersOneByOne(NODE ** topList);
	USER returnsLastInTheList(NODE ** topList);
#endif
