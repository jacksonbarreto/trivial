#ifndef __CONFIG_H__
	#define __CONFIG_H__
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <locale.h>
	#include <time.h>
	#include <errno.h>	
	
	/*size and limit settings*/
	#define MAX_NAME_SIZE 50+1
	#define MAX_OPTION_MENU_SIZE 50
	#define TOTAL_OPTION_MAIN_MENU 6
	#define MAX_USER_NAME_SIZE 25+1
	#define MAX_PASSWD_SIZE 5+1
	#define MAX_TITLE_SIZE 120+1
	#define MAX_ANSWER_SIZE 80+1
	#define MAX_SIZE_THEME_NAME 25+1
	#define MAX_NICKNAME_SIZE 5+1
	#define MAX_TOP_LIST 10
	#define MAX_HISTORY_LIST 15
	#define TOTAL_THEMES 4
	
	/*definition of controllers*/
	#define SUCCESS 1
	#define FAILURE 0
	#define TRUE 1
	#define FALSE 0
	#define EXIT 0
	#define NOT_FOUND -1
	#define OPEN_RANGE 0
	#define CLOSED_RANGE 1
	
	/*Adm settings*/
	#define RECORD_QUESTION 2
	
	/*login settings*/
	#define INVALID_PASSWORD 1
	#define INVALID_USER 0
	#define MINIMUM_ID 2
	#define MAXIMUM_LOGIN_ATTEMPTS 3
	#define REGISTER_USER 1
	
	/*register settings*/
	#define GET_PASSWORD 1
	#define PASSWORD_CONFIRMATION 2
	
	/*user type definition*/
	#define ADMIN_USER 1
	#define PLAYER_USER 2
	
	/*CRUD settings*/
	#define BINARY_READING "rb"
	#define BINARY_WRITING "wb"
	#define BINARY_APPEND "ab"
	#define BINARY_READING_PLUS "r+b"
	#define USER_DATA 1
	#define QUESTION_DATA 2
	#define LOG_DIRECTORY "logs"
	#define DATA_DIRECTORY "db"
	#define LOG_FILE_NAME "logs/logs.txt"
	#define SETTING_FILE_NAME "db/settings.dat"
	#define USERS_FILE_NAME "db/users.dat"
	#define THEMES_FILE_NAME "db/themes.dat"
	#define QUESTION_PREFIX "db/themeQuestions"
	#define QUESTION_SUFIX_SIZE 12
	#define TOP_LIST_FILE_NAME "db/top.dat"
	#define HISTORY_FILE_NAME "db/history.dat"
	
	/*event and error settings*/
	#define STANDARD_EVENT 1
	#define CRITICAL_FAILURE 2
	#define INCOMPLETE_RECORD 3
	#define INCOMPLETE_READING 4
	#define REMOVAL_STACK_EMPTY 5
	#define GAME_STATUS_UNIDENTIFIED 6
	#define DATA_TYPE_UNIDENTIFIED 7
	#define EMPTY_QUEUE 8
	#define QUEUE_NOT_STARTED 9
	#define LIST_NOT_STARTED 10
	#define LIST_QUEUE 11
	
	
	
	/*color setting*/
	#define RED "\033[1;91m"
	#define RESET_COLORS "\033[0;0m"
	
	/*game logic*/
	#define CORRECT_ANSWER 0
	#define SMALL_MODE_QUESTIONS 4
	#define MEDIUM_MODE_QUESTIONS 8
	#define LARGE_MODE_QUESTIONS 16
	#define REPEAT 1
	#define GAME_STARTED 1
	#define GAME_FINISHED 2
	#define RESET 0
	#define MAX_PLAYERS 6
	#define MIN_PLAYERS 2
	#define MAX_RESPONSE_OPTIONS 4
	
		
	/*setting menus*/
		/*main menu*/
		#define PLAY 1
		#define NEW_USER 2
		#define TOP_10 3
		#define LATEST_PLAYERS 4
		#define MY_ACCOUNT 5
		
		/*game mode*/
		#define SMALL_MODE 1
		#define MEDIUM_MODE 2
		#define LARGE_MODE 3
	
	#include "structs.h"
	
	/*global variables*/
		
		/*configuration variables*/
		SETTINGS settings;
		
		char keyboard[BUFSIZ];
		NODE ** topPlayers;
		NODE ** historyPlayers;
	
#endif

#include "dependency.h"
