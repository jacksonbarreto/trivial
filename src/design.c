#include "../inc/design.h"


void cardFrame(char * questionTitle, char answers[MAX_RESPONSE_OPTIONS][MAX_ANSWER_SIZE])
{
	CONTROLINT i;
	char answerTemplate[] = "%i - %s";
	
	
	/*header*/
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	textFrame(' ',PADDING_INTERNAL,CARD_BOX_SIZE,ALIGN_LEFT,ALIGN_CENTER,questionTitle,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','*',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	
	/*answers*/
	for(i=0;i<MAX_RESPONSE_OPTIONS;i++)
	{
		char * mountedResponse = allocateMemory(strlen(answerTemplate)+strlen(answers[i]),sizeof(char));
		sprintf(mountedResponse,answerTemplate,i+1,answers[i]);
		textFrame(' ',PADDING_INTERNAL,CARD_BOX_SIZE,ALIGN_LEFT,ALIGN_CENTER,mountedResponse,TEXT_STANDARD,BAKGROUND_STANDARD);		
		free(mountedResponse);
	}	
	
	/*footer*/
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
}

void cardFrameContrast(char * questionTitle, char answers[MAX_RESPONSE_OPTIONS][MAX_ANSWER_SIZE], CONTROLINT correctOption, CONTROLINT choice) 
{
	CONTROLINT i;
	char answerTemplate[] = "%i - %s";
	char textColor[STRING_COLOR_SIZE], backgroundColor[STRING_COLOR_SIZE];
	
	/*header*/
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	textFrame(' ',PADDING_INTERNAL,CARD_BOX_SIZE,ALIGN_LEFT,ALIGN_CENTER,questionTitle,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','*',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	
	/*answers*/
	for(i=0;i<MAX_RESPONSE_OPTIONS;i++)
	{
		char * mountedResponse = allocateMemory(strlen(answerTemplate)+strlen(answers[i]),sizeof(char));
		sprintf(mountedResponse,answerTemplate,i+1,answers[i]);
		if(i == correctOption)
		{
			strcpy(backgroundColor,TEXT_SUCCESS);
			strcpy(textColor,BAKGROUND_SUCCESS);
		}
		else if(i == choice)
		{
			strcpy(backgroundColor,BAKGROUND_ERROR);
			strcpy(textColor,TEXT_ERROR);
		}
		else
		{
			strcpy(backgroundColor,BAKGROUND_STANDARD);
			strcpy(textColor,TEXT_STANDARD);
		}
		textFrame(' ',PADDING_INTERNAL,CARD_BOX_SIZE,ALIGN_LEFT,ALIGN_CENTER,mountedResponse,textColor,backgroundColor);		
		free(mountedResponse);
	}	
	
	/*footer*/
	alignmentPadding(CARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',CARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
}

void textFrame(const char limiter, const CONTROLINT internalPadding, const CONTROLINT frameWidth, const CONTROLINT internalAlignment, const CONTROLINT boxAlignment, char * text, char * textColor, char * backgroundColor)
{
	const char delimiter[] = " ";
	const CONTROLINT stringTerminator=1;
	const CONTROLINT limiters=2;
	const CONTROLINT whiteSpace=1;
	CONTROLINT sizeAvailableFilling = frameWidth-(internalPadding*2)-limiters;
									
	char * line = (char *) calloc(sizeAvailableFilling+stringTerminator,sizeof(char));
	char * copyText = (char *) calloc(strlen(text)+1,sizeof(char));
	char * token;
	
	strcpy(copyText,text);
	token = strtok(copyText,delimiter);
	
	while(token != NULL)
	{
		if((strlen(line)+strlen(token)+whiteSpace) < sizeAvailableFilling)
		{
			if(line[0] != '\0')
				strcat(line," ");
			strcat(line,token);
		}
		else
		{
			alignmentPadding(frameWidth,boxAlignment);
			lineBuilder(limiter,' ',' ',internalPadding,PADDING_NULL,frameWidth,internalAlignment,line, textColor, backgroundColor);
			line[0] = '\0';
			strcat(line,token);
		}			
		token = strtok(NULL,delimiter);
	}
	alignmentPadding(frameWidth,boxAlignment);
	lineBuilder(limiter,' ',' ',internalPadding,PADDING_NULL,frameWidth,internalAlignment,line, textColor, backgroundColor);
	free(copyText);
	free(line);
	applyColor(RESET_COLOR);
}

void bottomLine(const char limiter, const char fill, const CONTROLINT lineSize, char * textColor, char * backgroundColor)
{
	lineBuilder(limiter,fill,fill,PADDING_NULL,PADDING_NULL,lineSize,ALIGN_CENTER,"", textColor, backgroundColor);
}

void lineTitle(const char limiter, const char fill, const CONTROLINT lineSize, const CONTROLINT alignment, char * text, char * textColor, char * backgroundColor)
{
	lineBuilder(limiter,fill,' ',PADDING_INTERNAL, PADDING_TITLE,lineSize,alignment,text, textColor, backgroundColor);
}

void emptyLine(const char limiter, const CONTROLINT lineSize, char * textColor, char * backgroundColor)
{
	lineBuilder(limiter,' ',' ',PADDING_NULL,PADDING_NULL,lineSize,ALIGN_CENTER," ", textColor, backgroundColor);
}

void lineBuilder(const char limiter, const char fill, const char charPaddingTitle, const CONTROLINT internalPadding, 
const CONTROLINT paddingTitleSize, const CONTROLINT lineSize, const CONTROLINT alignment, char * text, char * textColor, char * backgroundColor)
{
	CONTROLINT i, totalTitleFillImpression, leftImpressions, rightImpressions, sizeAvailableFilling, textSize;
	const CONTROLINT totalLimiters=2;
	
	textSize = strlen(text)+(internalPadding*2)+(paddingTitleSize*2)+totalLimiters;

	if(textSize < lineSize)
	{
		sizeAvailableFilling = lineSize - textSize;
				
		switch(alignment)
		{
			case ALIGN_LEFT:
				leftImpressions = 0;
				break;
			case ALIGN_RIGHT:
				leftImpressions = sizeAvailableFilling;
				break;
			case ALIGN_CENTER:
			default:
				leftImpressions = sizeAvailableFilling / 2;
				if(sizeAvailableFilling % 2 != 0)
					leftImpressions++;
		}
			
		rightImpressions = sizeAvailableFilling - leftImpressions;
		applyColor(textColor);
		applyColor(backgroundColor);
		putchar(limiter);
		for(i=0;i<internalPadding;i++)
			putchar(' ');
			
		for(i=0;i<leftImpressions;i++)
			putchar(fill);
		
		for(i=0;i<paddingTitleSize;i++)
			putchar(charPaddingTitle);
		printf("%s",text);
		for(i=0;i<paddingTitleSize;i++)
			putchar(charPaddingTitle);
		
		for(i=0;i<rightImpressions;i++)
			putchar(fill);
	
		for(i=0;i<internalPadding;i++)
			putchar(' ');
		putchar(limiter);
		applyColor(RESET_COLOR);
		putchar('\n');		
	}	
}

 void alignmentPadding(const CONTROLINT lineSize, const CONTROLINT alignment)
{
	CONTROLINT i, printer = numberImpressions(STANDARD_SCREEN_WIDTH,lineSize,alignment);	
	
	for(i=0;i<printer;i++)
		putchar(' ');	
}

static CONTROLINT numberImpressions(const CONTROLINT screenWidth, const CONTROLINT lineSize, const CONTROLINT alignment)
{
	
	CONTROLINT impressions;
	
	if(lineSize>screenWidth)
		return 0;
	
	impressions = (screenWidth - lineSize) / 2;
	
	if(alignment == ALIGN_RIGHT)
		impressions *= 2;
	else if(alignment == ALIGN_LEFT)
		impressions *= 0;
		
	return impressions;		
}

void clearScreen(void)
{
	applyColor(RESET_COLOR);
	system("clear || cls");
}

void catchPassword(char * password, const CONTROLINT passwordSize)
{
	CONTROLINT i=0;
	char temporaryCharacter;
	clearBuffer();
	do
	{
		temporaryCharacter = getch();
		if(temporaryCharacter >= 33 && temporaryCharacter <= 126)
		{
			printf("*");
			password[i]=temporaryCharacter;
			i++;
		}
		else if(temporaryCharacter == BACKSPACE && i != 0)
		{
			printf("%c %c",temporaryCharacter,temporaryCharacter);
			i--;
		}		
	}
	while(i<passwordSize-1);
	password[i]='\0';	
}

void applyColor(char * color)
{
	printf("%s",color);
}

void simpleInstructionBox(char * instruction, CONTROLINT boxStyle)
{
	char textColor[STRING_COLOR_SIZE], backgroundColor[STRING_COLOR_SIZE];
	CONTROLINT alignment = ALIGN_CENTER;
	
	setColor(textColor,backgroundColor,boxStyle);
	applyColor(RESET_COLOR);
	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
		
	textFrame(' ',PADDING_INTERNAL,STANDARD_BOX_SIZE,ALIGN_CENTER,ALIGN_CENTER,instruction,textColor, backgroundColor);
	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
	
	applyColor(RESET_COLOR);	
}

void instructionBox(char * title, char * message, char * instruction, CONTROLINT boxStyle, CONTROLINT typeBox)
{
	char textColor[STRING_COLOR_SIZE], backgroundColor[STRING_COLOR_SIZE];
	CONTROLINT alignment = ALIGN_CENTER;
	
	setColor(textColor,backgroundColor,boxStyle);
	applyColor(RESET_COLOR);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,title, textColor, backgroundColor);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','*',STANDARD_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
	textFrame(' ',PADDING_INTERNAL,STANDARD_BOX_SIZE,ALIGN_LEFT,ALIGN_CENTER,message, textColor, backgroundColor);
	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);	
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);	
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
	
	if(typeBox == QUESTION_BOX)
		alignment = ALIGN_LEFT;
		
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,alignment,instruction, textColor, backgroundColor);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,textColor, backgroundColor);
	applyColor(RESET_COLOR);	
}

void positionCursor(CONTROLINT linesUp, CONTROLINT movementsToRight, CONTROLINT boxStyle)
{
	char textColor[STRING_COLOR_SIZE], backgroundColor[STRING_COLOR_SIZE];
	
	setColor(textColor,backgroundColor,boxStyle);
	strcpy(textColor,TEXT_RESPONSE);
	printf("\x1B[%dA\x1B[%dC",linesUp,movementsToRight);
	applyColor(textColor);
	applyColor(backgroundColor);
}

static void setColor(char * textColor, char * backgroundColor, CONTROLINT boxStyle)
{
	switch(boxStyle)
	{
		case ERROR_BOX:
			strcpy(textColor,TEXT_ERROR);
			strcpy(backgroundColor,BAKGROUND_ERROR);
			break;
		case SUCCESS_BOX:
			strcpy(textColor,TEXT_SUCCESS);
			strcpy(backgroundColor,BAKGROUND_SUCCESS);
			break;
		case ATTENTION_BOX:
			strcpy(textColor,TEXT_ATTENTION);
			strcpy(backgroundColor,BAKGROUND_ATTENTION);
			break;
		case PLACAR_BOX:
			strcpy(textColor,TEXT_STANDARD);
			strcpy(backgroundColor,BAKGROUND_STANDARD);
			break;
		case STANDARD_BOX:
		default:
			strcpy(textColor,TEXT_STANDARD);
			strcpy(backgroundColor,BAKGROUND_STANDARD);		
	}
}

void verticalPadding(CONTROLINT lines)
{
	CONTROLINT i;
	for(i=0;i<lines;i++)
		putchar('\n');
}

void menuBox(char * title, char options[][MAX_OPTION_MENU_SIZE], CONTROLINT totalOptions)
{
	CONTROLINT i;
	char textColor[STRING_COLOR_SIZE], backgroundColor[STRING_COLOR_SIZE];
	setColor(textColor,backgroundColor,STANDARD_BOX);
	
	alignmentPadding(MENU_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',MENU_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(MENU_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',MENU_BOX_SIZE,ALIGN_CENTER,title, textColor, backgroundColor);	
	alignmentPadding(MENU_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',MENU_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(MENU_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','*',MENU_BOX_SIZE,textColor, backgroundColor);
	alignmentPadding(MENU_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',MENU_BOX_SIZE,textColor, backgroundColor);
	
	for(i=0;i<totalOptions;i++)
	{		
		alignmentPadding(MENU_BOX_SIZE,ALIGN_CENTER);
		lineTitle(' ',' ',MENU_BOX_SIZE,ALIGN_LEFT,options[i], textColor, backgroundColor);		
	}
	
	alignmentPadding(MENU_BOX_SIZE,ALIGN_CENTER);	
	emptyLine(' ',MENU_BOX_SIZE,textColor, backgroundColor);	
}

void placarBox(USER player, CONTROLINT gameMode)
{
	char textColor[STRING_COLOR_SIZE], backgroundColor[STRING_COLOR_SIZE];
	char line1[]="JOGADOR                  HISTÓRIA        BIOLOGIA E GEOGRAFIA        ARTES E LETRAS        TRIVIALIDADES";
	char line2[130];
	char * name;
	CONTROLINT i,j, difSize;
	
	difSize = MAX_NICKNAME_SIZE - 1 - strlen(player.nickname);
	name = (char *) allocateMemory(MAX_NICKNAME_SIZE,sizeof(char));
	strcpy(name,player.nickname);
	if(difSize != 0)
	{		
		for(i=0,j=strlen(player.nickname);i<difSize;i++,j++)
			name[j] = ' ';
		name[j] = '\0';
	}
	
	sprintf(line2," %s                     %d/%d                   %d/%d                      %d/%d                   %d/%d",name,player.currentScore[0],gameMode,player.currentScore[1],gameMode,player.currentScore[2],gameMode,player.currentScore[3],gameMode);
	setColor(textColor,backgroundColor,PLACAR_BOX);	
		
	alignmentPadding(PLACAR_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',PLACAR_BOX_SIZE,textColor, backgroundColor);
	
	alignmentPadding(PLACAR_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',PLACAR_BOX_SIZE,ALIGN_LEFT, line1, textColor, backgroundColor);
	alignmentPadding(PLACAR_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',PLACAR_BOX_SIZE,ALIGN_LEFT, line2, TEXT_RESPONSE, backgroundColor);
	
	alignmentPadding(PLACAR_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',PLACAR_BOX_SIZE,textColor, backgroundColor);
}

void progressBar(const CONTROLINT lineSize, const CONTROLINT totalSteps, const CONTROLINT currentStep, char * completedStepColor, char * stepColorNotCompleted)
{
	CONTROLINT i,j, k, printings = lineSize/totalSteps;
	
	if(currentStep<=totalSteps)
	{
		for(i=1;i<=totalSteps;i++)
		{
			if(i<=currentStep)
				printf(completedStepColor);
			else
				printf(stepColorNotCompleted);
			for(j=0;j<printings;j++)
				putchar(' ');		
		}
		applyColor(RESET_COLOR);
		putchar('\n');
	}	
}
