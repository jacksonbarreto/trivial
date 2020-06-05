#include "../inc/boot.h"

void boot(void)
{
	
	#ifdef _WIN32
		SetConsoleOutputCP(1252);
		SetConsoleCP(1252);
	#endif
	setlocale(LC_ALL,"");
	system("color");
	
	loadFileSystem();
	
	
	loadUsers();
	loadTopList();	
	loadHistoryList();	
	loadThemes();
		
	
	//última sempre
	loadSettings();
}

static void loadFileSystem(void)
{
	_mkdir(LOG_DIRECTORY);
	_mkdir(DATA_DIRECTORY);
}

static void startFileInf(FILEINF * info)
{
	info->size=0;
	info->trash=0;
	info->lastAcess= 0L;
}

static void loadUsers(void)
{
	FILEINF info;
	startFileInf(&info);
	info.size=1;
	
	USER sudo = createSUDO();
	FILE * pointer = fopen(USERS_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(USERS_FILE_NAME,BINARY_WRITING);		
		writeData(&info,sizeof(FILEINF),1,pointer);
		writeData(&sudo,sizeof(USER),1,pointer);
		settings.totalUsers=info.size;
		settings.lastIdUsedForUser=1;
	} 
	else
	{ 
		fread(&info,sizeof(FILEINF),1,pointer);
		settings.totalUsers = info.size;	
	}
	
	fclose(pointer);
}

static USER createSUDO(void)
{
	USER sudo;	
	sudo = createNullUser();
	sudo.id=1;
	sudo.userType = ADMIN_USER;
	strcpy(sudo.password,"admin");
	strcpy(sudo.username,"admin");
	strcpy(sudo.name,"SUDO");	
	
	return sudo;
}

static void loadTopList(void)
{
	FILEINF info;
	USER temporaryPlayer;
	FILE * file = fopen(TOP_LIST_FILE_NAME, BINARY_READING);
	
	startFileInf(&info);
	topPlayers = newList();
	
	if(file == NULL)
	{
		file = openFile(TOP_LIST_FILE_NAME,BINARY_WRITING);		
		writeData(&info,sizeof(FILEINF),1,file);		
		settings.topSize=info.size;
	} 
	else
	{
		fread(&info,sizeof(FILEINF),1,file);
		settings.topSize = info.size;
		
		if(info.size > 0)
		{
			do
			{
				readData(&temporaryPlayer,sizeof(USER),1,file);
				insertInOrder(topPlayers,temporaryPlayer);
			}
			while(!feof(file));
		}	
	}		
	fclose(file);
}

static void loadHistoryList(void)
{
	FILEINF info;
	USER temporaryPlayer;
	FILE * file = fopen(HISTORY_FILE_NAME, BINARY_READING);
	
	startFileInf(&info);	
	historyPlayers = newqueue();
	
	if(file == NULL)
	{
		file = openFile(HISTORY_FILE_NAME,BINARY_WRITING);		
		writeData(&info,sizeof(FILEINF),1,file);		
		settings.historySize=info.size;
	} 
	else
	{
		fread(&info,sizeof(FILEINF),1,file);		
		settings.historySize = info.size;
		
		if(info.size > 0)
		{
			do
			{
				readData(&temporaryPlayer,sizeof(USER),1,file);
				equeue(historyPlayers,temporaryPlayer);
			}
			while(!feof(file));
		}		
	}
	
	fclose(file);
}

static void createDefaultThemes(THEME theme[TOTAL_THEMES])
{
	char names[TOTAL_THEMES][MAX_SIZE_THEME_NAME] = {"HISTÓRIA", "BIOLOGIA E GEOGRAFIA", "ARTES E LETRAS", "TRIVIALIDADES"};
	CONTROLINT i;
	
	for(i=0;i<TOTAL_THEMES;i++)
	{
		theme[i] = createNullTheme();
		theme[i].id = i+1;
		strcpy(theme[i].themeName,names[i]);
	}

}


static void loadThemes(void)
{
	FILEINF info;
	startFileInf(&info);
	THEME theme[TOTAL_THEMES];
	
	FILE * pointer = fopen(THEMES_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(THEMES_FILE_NAME,BINARY_WRITING);
		info.size = TOTAL_THEMES;		
		writeData(&info,sizeof(FILEINF),1,pointer);
		createDefaultThemes(theme);
		writeData(&theme,sizeof(THEME),TOTAL_THEMES,pointer);
		settings.totalThemes = info.size;
		settings.lastIdUsedForThema = TOTAL_THEMES;
		settings.lastIdUsedForQuestion = 0;
		createQuestionFile();
	} 
	else
	{
		readData(&info,sizeof(FILEINF),1,pointer);
		settings.totalThemes = info.size;
	}
			
	fclose(pointer);
}

static void createQuestionFile(void)
{
	FILE * file;
	FILEINF info;
	CONTROLINT i;	
	char * fileName = (char *) allocateMemory(strlen(QUESTION_PREFIX)+QUESTION_SUFIX_SIZE,sizeof(char));
		
	for(i=0;i<TOTAL_THEMES;i++)
	{
		sprintf(fileName,"%s%d.dat",QUESTION_PREFIX,i+1);
		file = fopen(fileName,BINARY_WRITING);
		startFileInf(&info);
		writeData(&info,sizeof(FILEINF),1,file);
		fclose(file);
	}	
	free(fileName);
}

static void loadSettings(void)  //deve ser a última a carregar.
{
	SETTINGS setts;
	FILE * file = fopen(SETTING_FILE_NAME, BINARY_READING);
	if(file == NULL)
	{
		file = fopen(SETTING_FILE_NAME, BINARY_WRITING);	
	
		settings.totalRoundsGlobal=0;		
		settings.averageGlobalErrorAnswer=1;
		settings.defragRate=0.5;		
		writeData(&settings,sizeof(SETTINGS),1,file);
	}
	else
	{
		readData(&setts,sizeof(SETTINGS),1,file);
		settings.totalRoundsGlobal= setts.totalRoundsGlobal;		
		settings.averageGlobalErrorAnswer=setts.averageGlobalErrorAnswer;
		settings.defragRate=setts.defragRate;
		settings.lastIdUsedForUser = setts.lastIdUsedForUser;
		settings.lastIdUsedForThema = setts.lastIdUsedForThema;
		settings.lastIdUsedForQuestion = setts.lastIdUsedForQuestion;
	}
	fclose(file);
}




