#ifndef __DECK_HANDLER__
	#define __DECK_HANDLER__
	#include "config.h"
	
	void deckControl(THEME * theme,const CONTROLINT totalTheme, const CONTROLINT deckSize, const CONTROLINT gameStatus);
	static void loadDeck(CARD ** deck, const CONTROLINT themeId, long int * lastAcess, const CONTROLINT deckSize);
	CARD ** createDeck(void);
	static void killDeck(CARD ** deck);
	QUESTION popDeck(CARD ** deck);
	static void pushDeck(CARD ** deck, QUESTION question);
	static CONTROLINT deckIsEmpty(CARD ** deck);
	static void killCard(CARD ** deck);
	
	
	
#endif
