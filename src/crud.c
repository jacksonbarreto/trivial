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
		eventsHandling(INCOMPLETE_READING);
	return SUCCESS;
}

CONTROLINT createUserId(void)
{
	settings.lastIdUsedForUser++;
	return settings.lastIdUsedForUser;
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
	
	fseek(file,sizeof(THEMEFILEINF),SEEK_SET);
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
	
	theme.id = 0;
	theme.totalQuestions = 0;
	theme.lastAcess = 0L;
	strcpy(theme.themeName,"NULL");
	
	return theme;
}
/*
USER userIdExists(const CONTROLINT id)
{
	FILE * file = openFile(USERS_FILE_NAME,BINARY_READING);
	USER user;
	fseek(file,sizeof(CONTROLINT),SEEK_SET);
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
		printf("\nrecebido: %s", username);
		printf("\nnome: %s",user.username);
		system("pause");
		if(user.id != 0 && strcmp(user.username,username) == 0)
			return user;
	}
	while(!feof(file));
	user = createNullUser();
	fclose(file);
	return user;
}

USER createNullUser(void)
{
	USER user;
	
	user.id = 0;
	user.currentScore[0] = 0;
	user.currentScore[1] = 0;
	user.currentScore[2] = 0;
	user.currentScore[3] = 0; //gambiarra corrigir
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
	FILE * file = openFile(USERS_FILE_NAME,BINARY_APPEND);
	settings.totalUsers++;
	rewind(file);
	writeData(&settings.totalUsers,sizeof(CONTROLINT),1,file);
	fseek(file,0L,SEEK_END);
	writeData(&user,sizeof(USER),1,file);
	fclose(file);
}

void insertQuestion(QUESTION question, const CONTROLINT themeId)
{
	FILE * file;
	char * fileName = (char *) allocateMemory(strlen(QUESTION_PREFIX)+QUESTION_SUFIX_SIZE,sizeof(char));
	
	sprintf(fileName,"%s%d.dat",QUESTION_PREFIX,themeId);
	file = openFile(fileName,BINARY_APPEND);
	writeData(&question,sizeof(QUESTION),1,file);	
	fclose(file);
	free(fileName);
}
void insertTheme( THEME theme)
{
	FILE * file = openFile(THEMES_FILE_NAME,BINARY_APPEND);
	settings.totalThemes++;
	rewind(file);
	writeData(&settings.totalThemes,sizeof(CONTROLINT),1,file);
	fseek(file,0L,SEEK_END);
	writeData(&theme,sizeof(THEME),1,file);
	fclose(file);
}


