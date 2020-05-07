#include "../inc/boot.h"

void boot()
{
	
	#ifdef _WIN32
		SetConsoleOutputCP(1252);
		SetConsoleCP(1252);
	#endif
	setlocale(LC_ALL,"");
	system("color");
	
	loadUsers();
	loadTopList();
	loadHistoryList();
	loadThemes();
}

static void loadUsers()
{
	CONTROLINT total=1;
	USER sudo = createSUDO();
	FILE * pointer = fopen(USERS_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(USERS_FILE_NAME,BINARY_WRITING);		
		writeData(&total,sizeof(CONTROLINT),1,pointer);
		writeData(&sudo,sizeof(USER),1,pointer);
		settings.totalUsers=total;
	} 
	else
	{ 
		fread(&settings.totalUsers,sizeof(CONTROLINT),1,pointer);
	}
	
	fclose(pointer);
}

static USER createSUDO()
{
	USER sudo;	
	
	sudo.id=1;
	sudo.currentScore=0;
	sudo.percentageCorrect = 0.0;
	sudo.userType = ADMIN_USER;
	sudo.totalAnswered = 0;
	strcpy(sudo.password,"admin");
	strcpy(sudo.username,"admin");
	strcpy(sudo.name,"SUDO");	
	
	return sudo;
}

static void loadTopList()
{
	CONTROLINT total=0;
	
	FILE * pointer = fopen(TOP_LIST_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(TOP_LIST_FILE_NAME,BINARY_WRITING);		
		writeData(&total,sizeof(CONTROLINT),1,pointer);		
		settings.topSize=total;
	} 
	else
	{
		fread(&settings.topSize,sizeof(CONTROLINT),1,pointer);		
	}
	if(settings.topSize != 0)
		topPlayers = (USER *) allocateMemory(settings.topSize,sizeof(USER));
	else
		topPlayers = NULL;
		
	fclose(pointer);
}

static void loadHistoryList()
{
	CONTROLINT total=0;
	
	FILE * pointer = fopen(HISTORY_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(HISTORY_FILE_NAME,BINARY_WRITING);		
		writeData(&total,sizeof(CONTROLINT),1,pointer);		
		settings.historySize=total;
	} 
	else
	{
		fread(&settings.historySize,sizeof(CONTROLINT),1,pointer);		
	}
	if(settings.historySize != 0)
		historyPlayers = (USER *) allocateMemory(settings.historySize,sizeof(USER));
	else
		historyPlayers = NULL;
		
	fclose(pointer);
}

static void loadThemes()
{
	CONTROLINT i, total=0;
	
	FILE * pointer = fopen(THEMES_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(THEMES_FILE_NAME,BINARY_WRITING);		
		writeData(&total,sizeof(CONTROLINT),1,pointer);		
		settings.totalThemes=total;
	} 
	else
	{
		readData(&settings.totalThemes,sizeof(CONTROLINT),1,pointer);		
	}
	if(settings.totalThemes != 0)
	{
		//cortar isso aqui depois, os temas vão ser instanciado dentro do módulo jogando
		listTheme = (THEME *) allocateMemory(settings.totalThemes, sizeof(THEME));
		for(i=0;i<settings.totalThemes;i++)
		{
			readData(&listTheme[i],sizeof(THEME),1,pointer);
			listTheme[i].deck = createDeck();
		}
	}
	else
		listTheme = NULL;
		
	fclose(pointer);
}
