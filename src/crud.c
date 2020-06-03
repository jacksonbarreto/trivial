#include "../inc/crud.h"


FILE * openFile(const char * fileName, const char * openingMode)
{
	FILE * pointer = fopen(fileName, openingMode);
	if(pointer == NULL)
		eventsHandling(CRITICAL_FAILURE);
	return pointer;
}

CONTROLINT writeData(void * data, int dataSize, int quantity, FILE * file)
{	
	if( fwrite(data,dataSize,quantity,file) != quantity)
		eventsHandling(INCOMPLETE_RECORD);
	return SUCCESS;
}

CONTROLINT readData(void * destiny, int dataSize, int quantity, FILE * file)
{	
	if(fread(destiny,dataSize,quantity,file) != quantity)
		//eventsHandling(INCOMPLETE_READING); // não tem sentido pois quando é para ler quem não existe da erro
		//usar o fread diretamente onde existe possibilidade de nao encontrar o que deve ler
	return SUCCESS;
}

CONTROLINT createUserId(void)
{
	settings.lastIdUsedForUser++;
	return settings.lastIdUsedForUser;
}

void reverseCreatedIDForUsers(void)
{
	settings.lastIdUsedForUser--;
}

CONTROLINT createThemeId(void)
{
	settings.lastIdUsedForThema++;
	return settings.lastIdUsedForThema;
}

CONTROLINT createQuestionId(void)
{
	settings.lastIdUsedForQuestion++;
	return settings.lastIdUsedForQuestion;
}

THEME themeExist(const CONTROLINT themeId)
{
	THEME theme;
	FILE * file;
	char * fileName = (char *) allocateMemory(strlen(QUESTION_PREFIX)+QUESTION_SUFIX_SIZE,sizeof(char));
	
	sprintf(fileName,"%s%d.dat",QUESTION_PREFIX,themeId);
	file = openFile(fileName,BINARY_READING);
	
	fseek(file,sizeof(FILEINF),SEEK_SET); // verificar a logica aqui
	do
	{
		readData(&theme,sizeof(THEME),1,file);
		if(theme.id == themeId);
			return theme;
	}
	while(!feof(file));
	theme = createNullTheme();
	free(fileName);
	fclose(file);
	return theme;
}

THEME createNullTheme(void)
{
	THEME theme;
	
	theme.deck = NULL;
	theme.id = RESET;
	theme.totalQuestions = RESET;
	theme.lastAcess = 0L;
	strcpy(theme.themeName,"NULL");
	
		
	return theme;
}
/*
USER userIdExists(const CONTROLINT id)
{
	FILE * file = openFile(USERS_FILE_NAME,BINARY_READING);
	USER user;
	fseek(file,sizeof(FILEINF),SEEK_SET);
	do
	{
		readData(&user,sizeof(USER),1,file);
		if(user.id == id)
			return user;
	}
	while(!feof(file));
	user = createNullUser();
	return user;
}
*/
USER findUserByUsername(const char * username)
{
	FILE * file = openFile(USERS_FILE_NAME,BINARY_READING);
	USER user;
	fseek(file,sizeof(FILEINF),SEEK_SET);
	do
	{
		readData(&user,sizeof(USER),1,file);
		if(user.id != 0 && strcmp(user.username,username) == 0)
			return user;
	}
	while(!feof(file));
	user = createNullUser();
	fclose(file);
	return user;
}

CONTROLINT nicknameExists(char * nickname)
{
	FILE * file = openFile(USERS_FILE_NAME,BINARY_READING);
	USER user;
	
	fseek(file,sizeof(FILEINF),SEEK_SET);
	do
	{
		readData(&user,sizeof(USER),1,file);
		if(user.id != 0 && strcmp(user.nickname,nickname) == 0)
		{
			fclose(file);
			return SUCCESS;
		}
	}
	while(!feof(file));
	
	fclose(file);
	return FAILURE;
}

CONTROLINT usernameExists(char * username)
{
	FILE * file = openFile(USERS_FILE_NAME,BINARY_READING);
	USER user;
	
	fseek(file,sizeof(FILEINF),SEEK_SET);
	do
	{
		readData(&user,sizeof(USER),1,file);
		if(user.id != 0 && strcmp(user.username,username) == 0)
		{
			fclose(file);
			return SUCCESS;
		}
	}
	while(!feof(file));
	
	fclose(file);
	return FAILURE;
}

USER createNullUser(void)
{
	USER user;
	
	user.id = 0;
	resetCurrentScore(&user);
	user.percentageCorrect = 0.0;
	user.totalAnswered = 0;
	user.userType = PLAYER_USER;
	strcpy(user.name,"NULL");
	strcpy(user.password,"");
	strcpy(user.username,"NULL");
	
	return user;
}

void insertUser(USER user)
{
	FILEINF info;
	FILE * file = openFile(USERS_FILE_NAME,BINARY_READING_PLUS);
	fseek(file,0L,SEEK_END);
	writeData(&user,sizeof(USER),1,file);
	rewind(file);
	readData(&info,sizeof(FILEINF),1,file);
	info.size++;
	rewind(file);
	writeData(&info,sizeof(FILEINF),1,file);
	settings.totalUsers++;
	fclose(file);
}


void recordQuestion(QUESTION question, const CONTROLINT themeId)
{
	FILE * file;
	FILEINF info;
	char * fileName = (char *) allocateMemory(strlen(QUESTION_PREFIX)+QUESTION_SUFIX_SIZE,sizeof(char));
	
	sprintf(fileName,"%s%d.dat",QUESTION_PREFIX,themeId);

	file = openFile(fileName,BINARY_READING_PLUS);	
	fseek(file,0L,SEEK_END);
	
	if(writeData(&question,sizeof(QUESTION),1,file) == SUCCESS)
	{
		rewind(file);
		readData(&info,sizeof(FILEINF),1,file);
		info.size++;
		rewind(file);
		writeData(&info,sizeof(FILEINF),1,file);
	}	
	fclose(file);
	free(fileName);
}

void getThemesName(char ThemesName[][MAX_SIZE_THEME_NAME])
{
	CONTROLINT i;
	THEME temporaryTheme[settings.totalThemes];
	FILE * file = openFile(THEMES_FILE_NAME,BINARY_READING);
	
	fseek(file,sizeof(FILEINF),SEEK_SET);
	readData(temporaryTheme,sizeof(THEME),settings.totalThemes,file);
	for(i=0;i<settings.totalThemes;i++)
		strcpy(ThemesName[i],temporaryTheme[i].themeName);
		
	fclose(file);
}

/*
Não vai mais inserir tema 
*/
void insertTheme(THEME theme)
{
	FILE * file = openFile(THEMES_FILE_NAME,BINARY_READING_PLUS);
	FILEINF info;
	settings.totalThemes++;
	readData(&info,sizeof(FILEINF),1,file);
	info.size++;
	rewind(file);
	writeData(&info,sizeof(FILEINF),1,file);
	fseek(file,0L,SEEK_END);
	writeData(&theme,sizeof(THEME),1,file);
	fclose(file);
}




