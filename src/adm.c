#include "../inc/adm.h"


void insertQuestion(void)
{
	char themesName[settings.totalThemes][MAX_SIZE_THEME_NAME];
	CONTROLINT chosenTheme;
	QUESTION question;
	
	getThemesName(themesName);	
	chosenTheme = rendersGetTheme(themesName,settings.totalThemes);	
	question = getQuestion();
	
	recordQuestion(question,chosenTheme);
}

static QUESTION getQuestion(void)
{
	QUESTION question;
	CONTROLINT i,progressBarPosition, choice;
	
	do
	{
		rendersGetQuestionTitle(question.title);
		rendersGetQuestionRightAnswer(question.answers[0]);
		for(i=1,progressBarPosition=3;i<MAX_RESPONSE_OPTIONS;i++,progressBarPosition++)
			rendersGetQuestionAnswer(question.answers[i],progressBarPosition);
		
		choice = rendersConfirmationQuestion(question);
	}
	while(choice != RECORD_QUESTION);
	
	return question;
}
