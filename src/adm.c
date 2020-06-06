#include "../inc/adm.h"

/*		 ADMINISTRATOR		*/

void promoteUserToAdministrator(void)
{
	char username[MAX_USERNAME_SIZE];
	USER temporaryUser;
	CONTROLINT choice;	
	
	do
	{
		rendersGetUsernameForAdm(username);
		if(usernameExists(username) == SUCCESS)
		{
			temporaryUser = findUserByUsername(username);
			choice = rendersFullRegisterForAdm(temporaryUser);
			if(choice == ALLOCATED_POWERS);
			{
				temporaryUser.userType = ADMIN_USER;
				updateUser(temporaryUser);
				rendersAuccessfulAssignment(temporaryUser);
			}
				//se nao volta para menur anterior
		}
		else
		{
			choice = rendersInvalidUsernameForAdm();
		}
		
	}	
	while(choice == TRY_AGAIN);
	//volta para o menu anterior
		
}

void recoverPassword(void)
{
	char username[MAX_USERNAME_SIZE];
	USER temporaryUser;	
	CONTROLINT choice;
	
	do
	{
		rendersGetUsernameForRecoverPassword(username);
		if(usernameExists(username) == SUCCESS)
		{
			temporaryUser = findUserByUsername(username);			
			rendersRecoverPassword(temporaryUser);
			break;			
		}
		else
			choice = rendersInvalidUsernameForAdm();	
	}	
	while(choice == TRY_AGAIN);	
}

void changeName(USER * user)
{
	char name[MAX_NAME_SIZE];
	rendersGetNameForChangeName(name,*user);
	strcpy(user->name,name);
	updateUser(*user);
	rendersSuccessfulNameChange;	
}

CONTROLINT deleteAccount(USER user)
{
	CONTROLINT choice;
	
	choice = rendersDeleteAccount();
	if(choice == CONFIRM_DELETE_ACCOUNT)
	{
		if(user.id == 1)
		{
			rendersErrorDeleteAccount();
		}
		else
		{
			user.id = RESET;
			updateUser(user);
			rendersSuccessfulDeleteAccount(user);
		}		
		return BACK_TO_MAIN_MENU;
	}
	else
		return COME_BACK;	
}

/*		INSERT QUESTION		*/

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
