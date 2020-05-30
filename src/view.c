#include "../inc/view.h"

CONTROLINT rendersMainMenu(void)
{
	CONTROLINT choice;
	char mainMenu[][MAX_OPTION_MENU_SIZE]={"1 - JOGAR","2 - CADASTRAR USUÁRIO", "3 - TOP 10", "4 - HISTÓRICO", "5 - MINHA CONTA", "0 - SAIR"};
	
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
	char menuGameMode[][MAX_OPTION_MENU_SIZE]={"1 - PEQUENO (4 perguntas)", "2 - MÉDIO (8 perguntas)", "3 - GRANDE (16 perguntas)"};
	
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
	instructionBox("TOTAL DE JOGADORES","O jogo suporta de 2 a 6 jogadores. Com quantos amigos gostaria de se divertir?","Pressione o número de jogadores para continuar..",STANDARD_BOX,INSTRUCTION_BOX);
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
	instructionBox("ALERTA","Você atingiu o máximo de tentativas. Não é possível continuar tentando.","Pressione qualquer tecla para retornar ao menu principal...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

CONTROLINT rendersInvalidUsername(CONTROLINT attempts)
{
	CONTROLINT choice;
	//pode colocar qual é a tentativa atual (número) na mensagem.
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("USUÁRIO INVÁLIDO","O usuário informado não foi encontrado em nossa base de dados. Você pode tentar novamente ou simplesmente se cadastrar agora.","Pressione [1] para se cadastrar ou [2] para tentar novamente.",STANDARD_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}

void rendersInvalidPassword(CONTROLINT attempts)
{
	//pode colocar qual é a tentativa atual (número) na mensagem.
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("SENHA INVÁLIDA","A senha informada não corresponde com a cadastrada. Você ainda pode tentar outra vez.","Pressione qualquer tecla para tentar novamente...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

void rendersGetUsername(char * username)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("LOGIN","Informe o seu nome de usuário.","Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USER_NAME_SIZE,username);
}

void rendersGetPassword(char * password)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("LOGIN","Informe a palavra passe do seu usuário.","Password:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	catchPassword(password,MAX_PASSWD_SIZE);
}

CONTROLINT rendersGetTheme(char themesName[][MAX_THEME_SIZE],CONTROLINT totalThemes)
{
	CONTROLINT choice;
	char listaThemes[][MAX_OPTION_MENU_SIZE]={"1 - HISTÓRIA", "2 - BIOLOGIA E GEOGRAFIA", "3 - ARTES E LETRAS", "4 - TRIVIALIDADES"};
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("TEMAS",listaThemes,totalThemes);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,4,CLOSED_RANGE));
	
	
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
	instructionBox(" "," ","Pressione o número da resposta correta.",STANDARD_BOX,INSTRUCTION_BOX);
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
