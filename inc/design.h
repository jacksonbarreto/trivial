
#ifndef __DESIGN_H__
	#define __DESIGN_H__
	#include "config.h"
		
	
	#define STANDARD_SCREEN_WIDTH 120
	#define STANDARD_BOX_SIZE 80
	#define PLACAR_BOX_SIZE 120
	#define MENU_BOX_SIZE 50
	#define PADDING_TITLE 2
	#define PADDING_INTERNAL 3
	#define PADDING_NULL 0
	#define VERTICAL_PADDING_STANDARD 7
	#define STRING_COLOR_SIZE 25
	
	#define ALIGN_CENTER 1
	#define ALIGN_RIGHT 2
	#define ALIGN_LEFT 3
	
	#define BACKSPACE 8
	
	/*BOX STYLE*/
	#define ERROR_BOX 1
	#define SUCCESS_BOX 2
	#define ATTENTION_BOX 3
	#define STANDARD_BOX 4
	#define PLACAR_BOX 5
	
	/*TYPES OF BOX*/
	#define QUESTION_BOX 1
	#define INSTRUCTION_BOX 2
		
	/*COLORS*/
	
	#define RESET_COLOR "\x1B[0m"
	
	#define BAKGROUND_ERROR "\x1B[48;2;242;222;223m"   
	#define BAKGROUND_SUCCESS "\x1B[48;2;222;240;214m" 
	#define BAKGROUND_ATTENTION "\x1B[48;2;253;248;228m" 
	#define BAKGROUND_STANDARD "\x1B[48;2;217;237;246m" 
	#define BAKGROUND_COMPLETED "\x1B[48;2;39;174;96m"  
	#define BAKGROUND_NOT_COMPLETED "\x1B[48;2;189;195;199m" 
	
	#define TEXT_STANDARD "\x1B[38;2;63;100;116m" 
	#define TEXT_ERROR "\x1B[38;2;138;79;85m"  
	#define TEXT_SUCCESS "\x1B[38;2;69;103;68m" 
	#define TEXT_ATTENTION "\x1B[38;2;121;107;72m" 
	#define TEXT_RESPONSE "\x1B[38;2;142;68;173m"  
	
	
	void instructionBox(char * title, char * message, char * instruction, CONTROLINT boxStyle, CONTROLINT typeBox);
	void verticalPadding(CONTROLINT lines);
	void menuBox(char * title, char  options[][MAX_OPTION_MENU_SIZE], CONTROLINT totalOptions);
	void placarBox(char * playerNickname, CONTROLINT gameMode);
	void positionCursor(CONTROLINT linesUp, CONTROLINT movementsToRight, CONTROLINT boxStyle);
	void progressBar(const CONTROLINT lineSize, const CONTROLINT totalSteps, const CONTROLINT currentStep, char * completedStepColor, char * stepColorNotCompleted);
	void clearScreen(void);
	
	void catchPassword(char * password, const CONTROLINT passwordSize);
	
	
	void textFrame(const char limiter, const CONTROLINT internalPadding, const CONTROLINT frameWidth, const CONTROLINT internalAlignment, const CONTROLINT boxAlignment, char * text, char * textColor, char * backgroundColor);
	void alignmentPadding(const CONTROLINT lineSize, const CONTROLINT alignment);	
	void emptyLine(const char limiter, const CONTROLINT lineSize, char * textColor, char * backgroundColor);
	void bottomLine(const char limiter, const char fill, const CONTROLINT lineSize, char * textColor, char * backgroundColor);
	void lineTitle(const char limiter, const char fill, const CONTROLINT lineSize, const CONTROLINT alignment, char * text,char * textColor, char * backgroundColor);	
	void lineBuilder(const char limiter, const char fill, const char charPaddingTitle, const CONTROLINT internalPadding, const CONTROLINT paddingTitleSize, const CONTROLINT lineSize, const CONTROLINT alignment, char * text, char * textColor, char * backgroundColor);
	static CONTROLINT numberImpressions(const CONTROLINT screenWidth, const CONTROLINT lineSize, const CONTROLINT alignment);
	void applyColor(char * color);
	
	
	static void setColor(char * textColor, char * backgroundColor, CONTROLINT boxStyle);
	
#endif
