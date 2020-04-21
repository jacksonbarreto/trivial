#include "../inc/crud.h"


FILE * openFile(const char * fileName, const char * openingMode)
{
	FILE * pointer = fopen(fileName, openingMode);
	if(pointer == NULL)
		eventsHandling(CRITICAL_FAILURE);
	return pointer;
}

CONTROLINT writeData(const void * data, const int dataSize, const int quantity, const FILE * file)
{	
	if(fwrite(data,dataSize,quantity,file) != quantity)
		eventsHandling(INCOMPLETE_RECORD);
	return SUCCESS;
}

CONTROLINT readData(const void * destiny, const int dataSize, const int quantity, const FILE * file)
{	
	if(fread(destiny,dataSize,quantity,file) != quantity)
		eventsHandling(INCOMPLETE_READING);
	return SUCCESS;
}

CONTROLINT createUserId()
{
	return settings.totalUsers+1;
}

CONTROLINT createThemeId()
{
	return settings.totalThemes+1;
}

void insertUser(const USER user)
{
	FILE * file = openFile(USERS_FILE_NAME,BINARY_APPEND);
	settings.totalUsers++;
	rewind(file);
	writeData(&settings.totalUsers,sizeof(CONTROLINT),1,file);
	fseek(file,0L,SEEK_END);
	writeData(&user,sizeof(USER),1,file);
	fclose(file);
}

void insertQuestion(const QUESTION question, const CONTROLINT themeId)
{
	FILE * file;
	char * fileName = (char *) allocateMemory(strlen(QUESTION_PREFIX)+8,sizeof(char));
	
	sprintf(fileName,"%s%d.dat",QUESTION_PREFIX,themeId);
	file = openFile(fileName,BINARY_APPEND);
	writeData(&question,sizeof(QUESTION),1,file);	
	fclose(file);
}
void insertTheme(const THEME theme)
{
	FILE * file = openFile(THEMES_FILE_NAME,BINARY_APPEND);
	settings.totalThemes++;
	rewind(file);
	writeData(&settings.totalThemes,sizeof(CONTROLINT),1,file);
	fseek(file,0L,SEEK_END);
	writeData(&theme,sizeof(THEME),1,file);
	fclose(file);
}
