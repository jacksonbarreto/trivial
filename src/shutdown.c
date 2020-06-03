#include "../inc/shutdown.h"

void turnOff()
{
	saveSettings();
	saveTopList(topPlayers);
	quitHistoryList();
	free(topPlayers);  //conferir se é vetor ou lista
	free(historyPlayers); //conferir se é vetor ou lista
	
}

static void saveTopList(USER * topPlayers)
{
	FILE * pointer = fopen(TOP_LIST_FILE_NAME, BINARY_WRITING);
	writeData(&settings.topSize,sizeof(CONTROLINT),1,pointer); // corrigir para file info
	writeData(&topPlayers,sizeof(USER),settings.topSize,pointer);
	fclose(pointer);
}

static void quitHistoryList(void)
{	
	deleteQueue(historyPlayers);
}

static void saveSettings(void)
{
	FILE * file = openFile(SETTING_FILE_NAME,BINARY_WRITING);
	
	writeData(&settings,sizeof(SETTINGS),1,file);	
	fclose(file);
}
