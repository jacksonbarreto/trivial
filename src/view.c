#include "../inc/view.h"

	/*Player*/
CONTROLINT rendersMainMenu(void)
{
	CONTROLINT choice;
	char mainMenu[][MAX_OPTION_MENU_SIZE]={"1 - JOGAR","2 - CADASTRAR USU�RIO", "3 - TOP 10", "4 - HIST�RICO", "5 - MINHA CONTA", "0 - SAIR"};
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("MENU PRINCIPAL",mainMenu,TOTAL_OPTION_MAIN_MENU);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,0,5,CLOSED_RANGE));
	
	
	return choice;
}


CONTROLINT rendersGetGameMode(void)
{
	CONTROLINT choice;
	char menuGameMode[][MAX_OPTION_MENU_SIZE]={"1 - PEQUENO (4 perguntas)", "2 - M�DIO (8 perguntas)", "3 - GRANDE (16 perguntas)"};
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("MODO DE JOGO",menuGameMode,3);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,3,CLOSED_RANGE));
	
	return choice;
}

CONTROLINT rendersGetTotalPlayers(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("TOTAL DE JOGADORES","O jogo suporta de 2 a 6 jogadores. Com quantos amigos gostaria de se divertir?","Pressione o n�mero de jogadores para continuar..",STANDARD_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,2,6,CLOSED_RANGE));
	
	return choice;
}

void rendersMaxAttempts(void)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("ALERTA","Voc� atingiu o m�ximo de tentativas. N�o � poss�vel continuar tentando.","Pressione qualquer tecla para retornar ao menu principal...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

CONTROLINT rendersInvalidUsername(CONTROLINT attempts)
{
	CONTROLINT choice;
	//pode colocar qual � a tentativa atual (n�mero) na mensagem.
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("USU�RIO INV�LIDO","O usu�rio informado n�o foi encontrado em nossa base de dados. Voc� pode tentar novamente ou simplesmente se cadastrar agora.","Pressione [1] para se cadastrar ou [2] para tentar novamente.",STANDARD_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}

void rendersInvalidPassword(CONTROLINT attempts)
{
	//pode colocar qual � a tentativa atual (n�mero) na mensagem.
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("SENHA INV�LIDA","A senha informada n�o corresponde com a cadastrada. Voc� ainda pode tentar outra vez.","Pressione qualquer tecla para tentar novamente...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

void rendersGetUsername(char * username)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("LOGIN","Informe o seu nome de usu�rio.","Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,28,STANDARD_BOX);
	getString(MAX_USER_NAME_SIZE,username);
}

void rendersGetPassword(char * password)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("LOGIN","Informe a palavra passe do seu usu�rio.","Password:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	catchPassword(password,MAX_PASSWD_SIZE);
}

CONTROLINT rendersGetTheme(char themesName[][MAX_SIZE_THEME_NAME],CONTROLINT totalThemes)
{
	CONTROLINT i, choice;
	char listaThemes[totalThemes][MAX_OPTION_MENU_SIZE];
	
	for(i=0;i<settings.totalThemes;i++)
		sprintf(listaThemes[i],"%d - %s",i+1,themesName[i]);
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("TEMAS",listaThemes,totalThemes);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,totalThemes,CLOSED_RANGE));
	
	
	return choice;
}

CONTROLINT rendersGetAnswer(QUESTION mountedQuestion)
{
	CONTROLINT choice;	
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox(mountedQuestion.title,mountedQuestion.answers,MAX_RESPONSE_OPTIONS);
	putchar('\n');
	//emptyLine(' ',MENU_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	instructionBox(" "," ","Pressione o n�mero da resposta correta.",STANDARD_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,4,CLOSED_RANGE) );

	
	return choice;
}

void rendersResultQuestion(QUESTION mountedQuestion, CONTROLINT choice, CONTROLINT correct)
{
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox(mountedQuestion.title,mountedQuestion.answers,MAX_RESPONSE_OPTIONS);
	putchar('\n');
	instructionBox(" ","Falta exibir a correta e a escolhida","Pressione qualquer tecla para continar..",STANDARD_BOX,INSTRUCTION_BOX);
	wait();
	
}

/*Register*/
void rendersGetNameForRegister(char * name)
{
	char message[100];
	sprintf(message,"Informe o seu nome com at� %d letras.",MAX_NAME_SIZE);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,1,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Nome:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,29,STANDARD_BOX);
	getString(MAX_NAME_SIZE,name);	
}

void rendersGetUsernameForRegister(char * username)
{
	char message[150];
	sprintf(message,"Informe o seu 'username' com at� %d letras. Ele deve ser �nico e sera usado para se logar no sistema.",MAX_USER_NAME_SIZE);
	clearScreen();	
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,2,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USER_NAME_SIZE,username);	
}

void rendersGetNickname(char * nickname)
{
	char message[150];
	sprintf(message,"Informe o seu 'nickname' com at� %d letras. Ele deve ser �nico. � atrav�s dele que voc� ser� reconhecido por todos.",MAX_NICKNAME_SIZE);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,3,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Nickname:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_NICKNAME_SIZE,nickname);	
}

void rendersGetPasswordForRegister(char * password, CONTROLINT attempt)
{
	char message[150];

	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,4,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	if(attempt == GET_PASSWORD)
	{
		sprintf(message,"Informe a sua 'password'. Ela deve ter exatamente %d caracteres. S�o aceitos letras, n�meros e caracteres especiais.",MAX_PASSWD_SIZE-1);		
	}
	else
	{
		strcpy(message,"Digite novamente a sua 'password' para que possamos ter a certeza que a digitou corretamente.");		
	}
	instructionBox("CADASTRO DE USU�RIO",message,"Password:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	catchPassword(password,MAX_PASSWD_SIZE);
}

CONTROLINT rendersFullRegister(USER temporaryUser)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX,5,5,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	//Imprime os dados do usu�rio
	instructionBox("CADASTRO DE USU�RIO","Verifique se todos os dados est�o corretos.","Pressione [1] para reiniciar o cadastro ou [2] para confirmar.",STANDARD_BOX,INSTRUCTION_BOX);	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,2,CLOSED_RANGE) );
	
	return choice;
}

CONTROLINT rendersPasswordsDoNotMatch(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("PASSWORD N�O COINCIDE","As passwords informadas n�o s�o iguais. Voc� pode tentar redigit�-las ou simplesmente desistir do seu cadastro.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;	
}

CONTROLINT rendersInvalidNickname(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("NICKNAME N�O DISPON�VEL","O 'nickname' informado j� est� sendo utilizado por outro usu�rio. Escolha outro apelido para lhe representar.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}

CONTROLINT rendersUsernameAlreadyExists(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("USERNAME N�O DISPON�VEL","O 'username' informado j� est� sendo utilizado por outro usu�rio. Escolha outro nome de acesso ao sistema.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}


/* ADM */

void rendersGetQuestionTitle(char * title)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,1,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe o t�tulo da pergunta, ou seja, a pergunta propriamente dita.","T�tulo:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,32,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,title);	
}

void rendersGetQuestionRightAnswer(char * correctAnswer)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,2,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe a resposta CORRETA para a quest�o anteriormente inserida.","Resposta CORRETA:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,42,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,correctAnswer);	
}

void rendersGetQuestionAnswer(char * answer, CONTROLINT progressBarPosition)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,progressBarPosition,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe outra op��o de resposta para a quest�o anteriormente inserida.","Resposta:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,answer);	
}

CONTROLINT rendersConfirmationQuestion(QUESTION question)
{
	CONTROLINT i, choice;
	
	char listaQuestion[MAX_RESPONSE_OPTIONS][MAX_ANSWER_SIZE];
	
	for(i=0;i<MAX_RESPONSE_OPTIONS;i++)
		sprintf(listaQuestion[i],"%d - %s",i+1,question.answers[i]);
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX,6,6,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	menuBox(question.title,listaQuestion,MAX_RESPONSE_OPTIONS);
	putchar('\n');
	instructionBox("CADASTRO DE PERGUNTA","Verifique se todos os dados est�o corretos.","Pressione [1] para reiniciar o cadastro ou [2] para confirmar.",STANDARD_BOX,INSTRUCTION_BOX);	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,RECORD_QUESTION,CLOSED_RANGE) );
	
	return choice;
}
