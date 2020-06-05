#define __MAIN__
#include "inc/config.h"

int main(void) 
{	
	CONTROLINT choice;
	
	boot();
	renderInicio();
	
	/*
	QUESTION question;
	
	FILE * file = openFile("db/themeQuestions1.dat",BINARY_READING);
	
	fseek(file,sizeof(FILEINF),SEEK_SET);
	do
	{
		readData(&question,sizeof(QUESTION),1,file);
		cardFrame(question.title,question.answers); 
		system("pause");
	}
	while(!feof(file));
	*/
	
	do
	{
		choice = rendersMainMenu();
		switch(choice)
		{
			case PLAY:
				startGame();
				break;
			case NEW_USER:
				registerNewUser();
				break;
			case TOP_10:
				listBestPlayers();
				break;
			case LATEST_PLAYERS:
				lastPlayers();
				break;
			case MY_ACCOUNT:
				insertQuestion();
				break;
		}
	}
	while(choice != EXIT);
	
	
	turnOff();
	renderCreditos();	
	return EXIT_SUCCESS;
}
