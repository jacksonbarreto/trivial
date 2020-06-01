#define __MAIN__
#include "inc/config.h"

void testReadQuestion()
{
	const int tot = 2;
	FILE * file = openFile("db/themeQuestions1.dat","rb");
	QUESTION question[tot];
	FILEINF info;
	int i;
	
	readData(&info,sizeof(FILEINF),1,file);
	//fseek(file,sizeof(FILEINF),SEEK_SET);
	readData(&question,sizeof(QUESTION),2,file);
	
	fclose(file);
	
	for(i=0;i<tot;i++)
		menuBox(question[i].title,question[i].answers,MAX_RESPONSE_OPTIONS);
	printf("\n\nsize: %d  ! Trash: %d  | lastAcss: %hu\n",info.size,info.trash,info.lastAcess);
	system("pause");
}

int main(void) 
{	
	CONTROLINT choice;
	
	boot();
	//testReadQuestion();
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
				break;
			case LATEST_PLAYERS:
				break;
			case MY_ACCOUNT:
				insertQuestion();
				break;
		}
	}
	while(choice != EXIT);
	
	
	turnOff();
		
	return EXIT_SUCCESS;
}
