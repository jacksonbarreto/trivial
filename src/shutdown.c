#include "../inc/shutdown.h"

void turnOff()
{
	saveTopList(topPlayers);
	saveHistoryList(historyPlayers);
	free(topPlayers);
	free(historyPlayers);
	
}

static void saveTopList(USER * topPlayers)
{
	FILE * pointer = fopen(TOP_LIST_FILE_NAME, BINARY_WRITING);
	writeData(&settings.topSize,sizeof(CONTROLINT),pointer);
	writeData(&topPlayers,sizeof(USER),settings.topSize,pointer);
	fclose(pointer);
}

static void saveHistoryList(USER * historyPlayers)
{
	FILE * pointer = fopen(HISTORY_FILE_NAME, BINARY_WRITING);
	writeData(&settings.historySize,sizeof(CONTROLINT),pointer);
	writeData(&historyPlayers,sizeof(USER),settings.historySize,pointer);
	fclose(pointer);
}
