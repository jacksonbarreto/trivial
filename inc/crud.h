#ifndef __CRUD_H__
	#define __CRUD_H__
	#include "config.h"
	FILE * openFile(const char * fileName, const char * openingMode);
	CONTROLINT writeData(const void * data, const int dataSize, const int quantity, const FILE * file);
	CONTROLINT readData(const void * destiny, const int dataSize, const int quantity, const FILE * file);
	CONTROLINT createUserId();
	CONTROLINT createThemeId();
	void insertUser(USER user);
	void insertQuestion(const QUESTION question, const CONTROLINT themeId);
	void insertTheme(const THEME theme);
	
#endif
