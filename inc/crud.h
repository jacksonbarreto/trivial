#ifndef __CRUD_H__
	#define __CRUD_H__
	#include "config.h"
	FILE * openFile(const char * fileName, const char * openingMode);
	CONTROLINT writeData(void * data, int dataSize, int quantity, FILE * file);
	CONTROLINT readData(void * destiny, int dataSize, int quantity, FILE * file);
	CONTROLINT createUserId(void);
	void reverseCreatedIDForUsers(void);
	CONTROLINT createThemeId(void);
	CONTROLINT createQuestionId(void);
	THEME createNullTheme(void);
	THEME themeExist(const CONTROLINT themeId);
	THEME themeExist(const CONTROLINT themeId);
	USER findUserByUsername(char * username);
	CONTROLINT nicknameExists(char * nickname);
	CONTROLINT usernameExists(char * username);
	USER createNullUser(void);
	USER userIdExists(const CONTROLINT id); //apagar
	void insertUser(USER user);
	void recordQuestion(QUESTION question, const CONTROLINT themeId);
	void insertTheme(THEME theme);
	void resetCurrentScore(USER * user);
	void getThemesName(char ThemesName[][MAX_SIZE_THEME_NAME]);
	
#endif
