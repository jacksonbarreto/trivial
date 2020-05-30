#ifndef __STRUCT_C__
	#define __STRUCT_C__
	
	typedef unsigned short int CONTROLINT;
	typedef short int SINT;
	
	typedef struct _user
	{
		CONTROLINT id;
		CONTROLINT currentScore[TOTAL_THEMES];		
		CONTROLINT totalAnswered;
		CONTROLINT userType;
		float percentageCorrect;
		char username[MAX_USER_NAME_SIZE];
		char password[MAX_PASSWD_SIZE];
		char name[MAX_NAME_SIZE];
		char nickname[MAX_NICKNAME_SIZE];
	}
	USER;
	
	typedef struct _question
	{
		CONTROLINT id;
		//CONTROLINT used; //apagar
		char title[MAX_TITLE_SIZE];		
		char answers[MAX_RESPONSE_OPTIONS][MAX_ANSWER_SIZE];		
	}
	QUESTION;
	
	typedef struct _card
	{
		QUESTION question;
		struct _card * next;
	}
	CARD;
	
	typedef struct _theme
	{
		CONTROLINT id;
		CONTROLINT totalQuestions;
		long int lastAcess;
		char themeName[MAX_THEME_SIZE];
		CARD ** deck;	
	}
	THEME;
	
	typedef struct _themefileinf
	{
		CONTROLINT size;
		CONTROLINT trash;
		long int lastAcess;
	}
	THEMEFILEINF;
	
	typedef struct _fileinf
	{
		CONTROLINT size;
		CONTROLINT trash;
	}
	FILEINF;
	/*
	typedef struct _listTheme
	{
		THEME theme;
		CARD ** deck;
	}
	LISTTHEMES;
	*/
	typedef struct _settings
	{
		CONTROLINT topSize;
		CONTROLINT historySize;
		CONTROLINT totalThemes;
		CONTROLINT totalUsers;
		CONTROLINT totalRoundsGlobal;
		CONTROLINT lastIdUsedForUser;
		CONTROLINT lastIdUsedForThema;
		CONTROLINT lastIdUsedForQuestion;
		float averageGlobalErrorAnswer;
		float defragRate;
	}
	SETTINGS;

	typedef struct _gameplayer
	{
		CONTROLINT currentPlayer;	
		CONTROLINT gameMode;
		CONTROLINT totalPlayers;
	}
	GAMEPLAY;
	
#endif
