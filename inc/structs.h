#ifndef __STRUCT_C__
	#define __STRUCT_C__
	
	typedef unsigned short int CONTROLINT;
	typedef short int SINT;
	
	typedef struct _user
	{
		CONTROLINT id;
		CONTROLINT currentScore;		
		CONTROLINT totalAnswered;
		CONTROLINT userType;
		float percentageCorrect;
		char username[MAX_USER_NAME_SIZE];
		char password[MAX_PASSWD_SIZE];
		char name[MAX_NAME_SIZE];		
	}
	USER;
	
	typedef struct _question
	{
		CONTROLINT id;
		CONTROLINT used;
		char title[MAX_TITLE_SIZE];		
		char answers[MAX_RESPONSE_OPTIONS][MAX_ANSWER_SIZE];		
	}
	QUESTION;
	
	typedef struct _theme
	{
		CONTROLINT id;
		CONTROLINT totalQuestions;
		char themeName[MAX_THEME_SIZE];		
	}
	THEME;
	
	typedef struct _listHead
	{
		CONTROLINT listSize;
		CONTROLINT listRound;
		CONTROLINT validQuestions;
		QUESTION * listQuestions;
	}
	LISTHEAD;
	
	typedef struct _listTheme
	{
		THEME theme;
		LISTHEAD * questionListHead;
	}
	LISTTHEMES;
	
	typedef struct _settings
	{
		CONTROLINT topSize;
		CONTROLINT historySize;
		CONTROLINT totalThemes;
		CONTROLINT totalUsers;
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
