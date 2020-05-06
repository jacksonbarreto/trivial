#ifndef __CRUD_H__
	#define __CRUD_H__
	#include "config.h"
	FILE * openFile(const char * fileName, const char * openingMode);
	CONTROLINT writeData(void * data, int dataSize, int quantity, FILE * file);
	CONTROLINT readData(void * destiny, int dataSize, int quantity, FILE * file);
	CONTROLINT createUserId(void);
	CONTROLINT createThemeId(void);
	THEME createNullTheme(void);
	THEME themeExist(const CONTROLINT themeId);
	THEME themeExist(const CONTROLINT themeId);
	USER createNullUser(void);
	USER userIdExists(const CONTROLINT id);
	void insertUser(USER user);
	void insertQuestion(QUESTION question, const CONTROLINT themeId);
	void insertTheme(THEME theme);
	
#endif
