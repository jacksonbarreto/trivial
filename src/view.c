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
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USERNAME_SIZE,username);
}

void rendersGetPassword(char * password)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("LOGIN","Informe a palavra passe do seu usu�rio.","Password:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	catchPassword(password,MAX_PASSWD_SIZE);
}

CONTROLINT rendersGetThemeForPlaying(char themesName[][MAX_SIZE_THEME_NAME],const CONTROLINT totalThemes, USER player, CONTROLINT gameMode)
{
	CONTROLINT i, choice;
	char listaThemes[totalThemes][MAX_OPTION_MENU_SIZE];
	
	for(i=0;i<settings.totalThemes;i++)
		sprintf(listaThemes[i],"%d - %s",i+1,themesName[i]);
	
	clearScreen();
	placarBox(player, gameMode);
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("TEMAS",listaThemes,totalThemes);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,totalThemes,CLOSED_RANGE));	
	
	return choice;
}

CONTROLINT rendersGetAnswer(QUESTION mountedQuestion, USER player, CONTROLINT gameMode)
{
	CONTROLINT choice;	
	
	clearScreen();
	placarBox(player, gameMode);
	verticalPadding(VERTICAL_PADDING_STANDARD);
	cardFrame(mountedQuestion.title,mountedQuestion.answers);
	putchar('\n');
	simpleInstructionBox("Pressione o n�mero correspondente a resposta correta.",STANDARD_BOX);
	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,4,CLOSED_RANGE) );
	
	return choice;
}

void rendersResultQuestion(QUESTION mountedQuestion, CONTROLINT choice, CONTROLINT correct, USER player, CONTROLINT gameMode)
{
	clearScreen();
	placarBox(player, gameMode);
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	cardFrameContrast(mountedQuestion.title,mountedQuestion.answers,correct,choice);
	putchar('\n');
	simpleInstructionBox("Pressione qualquer tecla para continar...",STANDARD_BOX);
	wait();	
}

void renderCongratulations(USER player){	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX,5,5,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	char nome[2][50];
	sprintf(nome[0]," |       |             %s",player.name);	
	sprintf(nome[1],"  \\     /                  Voc� ganhou o jogo!");
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_SUCCESS, BAKGROUND_SUCCESS);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, "  _______", TEXT_SUCCESS, BAKGROUND_SUCCESS);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, " |       |", TEXT_SUCCESS, BAKGROUND_SUCCESS);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, "(|  #1   |)       PARAB�NS!", TEXT_SUCCESS, BAKGROUND_SUCCESS);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, nome[0], TEXT_SUCCESS, BAKGROUND_SUCCESS);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, nome[1] , TEXT_SUCCESS, BAKGROUND_SUCCESS);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, "   `---'", TEXT_SUCCESS, BAKGROUND_SUCCESS);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, "   _|_|_", TEXT_SUCCESS, BAKGROUND_SUCCESS);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_SUCCESS, BAKGROUND_SUCCESS);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_SUCCESS, BAKGROUND_SUCCESS);
	sleep(2);
}

/*Register*/
void rendersGetNameForRegister(char * name)
{
	char message[100];
	sprintf(message,"Informe o seu nome com at� %d letras.",MAX_NAME_SIZE-1);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,1,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Nome:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,29,STANDARD_BOX);
	getString(MAX_NAME_SIZE-1,name);	
}

void rendersGetUsernameForRegister(char * username)
{
	char message[150];
	sprintf(message,"Informe o seu 'username' com at� %d letras. Ele deve ser �nico e sera usado para se logar no sistema.",MAX_USERNAME_SIZE-1);
	clearScreen();	
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,2,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USERNAME_SIZE-1,username);	
}

void rendersGetNickname(char * nickname)
{
	char message[150];
	sprintf(message,"Informe o seu 'nickname' com at� %d letras. Ele deve ser �nico. � atrav�s dele que voc� ser� reconhecido por todos.",MAX_NICKNAME_SIZE-1);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,3,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Nickname:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_NICKNAME_SIZE-1,nickname);	
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
	char listaTempUser[3][100];
	char title[100] = "Valide a informa��o do cadastro.";
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX,5,5,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);	
	
	sprintf(listaTempUser[0],"Nome: %s",temporaryUser.name);
	sprintf(listaTempUser[1],"Username: %s",temporaryUser.username);
	sprintf(listaTempUser[2],"Nickname: %s",temporaryUser.nickname);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"DADOS DO CADASTRO", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','*',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);	
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, listaTempUser[0], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT,listaTempUser[1], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT,listaTempUser[2], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	putchar('\n');	

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


void rendersDesistRegistering(void)
{	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("ALERTA","Voc� desistiu do seu registro de usu�rio. Dever� tentar se logar outra vez.","Pressione qualquer tecla para tentar logar novamente...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

/* ADM */

CONTROLINT rendersAdmMenu(USER user)
{
	CONTROLINT choice;
	char userMenu[][MAX_OPTION_MENU_SIZE]={"1 - EDITAR NOME","2 - DELETAR CONTA", "0 - VOLTAR"};
	char fullMenu[][MAX_OPTION_MENU_SIZE]={"1 - EDITAR NOME","2 - DELETAR CONTA", "3 - INSERIR PERGUNTA", "4 - ATRIBUIR PODERES DE ADMINISTRADOR", "5 - RECUPERAR SENHA DE JOGADORES", "0 - VOLTAR"};
	
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	if(user.userType == PLAYER_USER)
	{
		menuBox("MINHA CONTA",userMenu,3);
		do
		{
			choice = getChoiceMenu();
		}
		while(!inRange(choice,0,2,CLOSED_RANGE));
	}		
	else
	{
		menuBox("MENU ADIMINISTRATIVO",fullMenu,6);
		do
		{
			choice = getChoiceMenu();
		}
		while(!inRange(choice,0,5,CLOSED_RANGE));
	}	
	return choice;
}

CONTROLINT rendersGetTheme(char themesName[][MAX_SIZE_THEME_NAME],const CONTROLINT totalThemes)
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
	CONTROLINT choice;	
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	cardFrame(question.title,question.answers);
	putchar('\n');
	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,6,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);	
	
	instructionBox("CADASTRO DE PERGUNTA","Verifique se todos os dados est�o corretos.","Pressione [1] para reiniciar o cadastro ou [2] para confirmar.",STANDARD_BOX,INSTRUCTION_BOX);	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,RECORD_QUESTION,CLOSED_RANGE) );
	
	return choice;
}

void rendersGetUsernameForAdm(char * username)
{
	char message[] = "Informe o 'username' do usu�rio ao qual deseja atribuir poderes de administrador.";
	
	clearScreen();	
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("ATRIBUI��O DE SUPER PODERES",message,"Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USERNAME_SIZE-1,username);	
}

void rendersGetUsernameForRecoverPassword(char * username)
{
	char message[] = "Informe o 'username' do usu�rio ao qual deseja recuperar a senha. Lembre-se da responsabilidade e princ�pios �ticos inerente a ser um administrador.";
	
	clearScreen();	
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("RECUPERA��O DE SENHA",message,"Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USERNAME_SIZE-1,username);	
}

CONTROLINT rendersInvalidUsernameForAdm(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("USERNAME N�O ENCONTRADO","O 'username' informado n�o existe. Porvavelmente cometeu um erro de digita��o ou o usu�rio n�o est� cadastrado.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}


CONTROLINT rendersFullRegisterForAdm(USER temporaryUser)
{
	CONTROLINT choice;
	char listaTempUser[3][100];
	char title[100] = "Valide a informa��o do cadastro.";
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	
	sprintf(listaTempUser[0],"Nome: %s",temporaryUser.name);
	sprintf(listaTempUser[1],"Username: %s",temporaryUser.username);
	sprintf(listaTempUser[2],"Nickname: %s",temporaryUser.nickname);
	
	/*header*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"INFORMA��ES DO USU�RIO", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','*',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);	
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	
	/*user information*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, listaTempUser[0], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT,listaTempUser[1], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT,listaTempUser[2], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	putchar('\n');	

	
	instructionBox("ATRIBUI��O DE SUPER PODERES","Tem certeza que deseja atribuir super poderes a este usu�rio?  Esta a��o n�o pode ser desfeita!","Pressione [1] para CONFIRMAR ou [2] para DESISTIR.",ATTENTION_BOX,INSTRUCTION_BOX);	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,2,CLOSED_RANGE) );
	
	return choice;
}

void rendersAuccessfulAssignment(USER user)
{
	char preMessage[] = "Atibui��o realizada com sucesso! Agora o usu�rio de nome %s - [username: %s] - � um ADMINISTRADOR.";
	char * message = allocateMemory(strlen(preMessage)+MAX_NAME_SIZE+MAX_USERNAME_SIZE,sizeof(char));
	sprintf(message,preMessage, user.name,user.username);
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("ATRIBUI��O DE SUPER PODERES",message,"Pressione qualquer tecla para continuar...",SUCCESS_BOX,INSTRUCTION_BOX);
	wait();	
}

void rendersRecoverPassword(USER user)
{
	char preMessage[] = "O usu�rio de nome %s - [username: %s] - tem a SENHA: |%s|.";
	char * message = allocateMemory(strlen(preMessage)+MAX_NAME_SIZE+MAX_USERNAME_SIZE,sizeof(char));
	sprintf(message,preMessage, user.name,user.username,user.password);
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("RECUPERA��O DE SENHA",message,"Pressione qualquer tecla para continuar.",ATTENTION_BOX,INSTRUCTION_BOX);
	wait();
}

void rendersGetNameForChangeName(char * name, USER user)
{
	
	
	char instruction[100];	
	char preMessage[] = "O seu nome atual �: |%s|.";
	char * message = allocateMemory(strlen(preMessage)+MAX_NAME_SIZE+MAX_USERNAME_SIZE,sizeof(char));
	
	sprintf(message,preMessage, user.name,user.username,user.password);
	
	sprintf(instruction,"Informe o seu NOVO nome com at� %d letras.",MAX_NAME_SIZE-1);
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	//instructionBox("ALTERA��O DE NOME",message,"Pressione qualquer tecla para continuar.",ATTENTION_BOX,INSTRUCTION_BOX);
	simpleInstructionBox(message,ATTENTION_BOX);
	
	instructionBox("ALTERA��O DE NOME",instruction,"Nome:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,29,STANDARD_BOX);
	getString(MAX_NAME_SIZE-1,name);	
}

void rendersSuccessfulNameChange(USER user)
{
	char preMessage[] = "A altera��o de nome foi realizada com sucesso! Agora o seu nome �:  %s - [username: %s].";
	char * message = allocateMemory(strlen(preMessage)+MAX_NAME_SIZE+MAX_USERNAME_SIZE,sizeof(char));
	sprintf(message,preMessage, user.name,user.username);
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("ALTERA��O DE NOME",message,"Pressione qualquer tecla para continuar...",SUCCESS_BOX,INSTRUCTION_BOX);
	wait();	
}

/*History*/

void rendersHistory(NODE ** history)
{
	char messageEmptyList[] = "Infelizmente nenhum jogador ainda se aventurou no fant�stico mundo do TRIVIAL. Que tal voc� come�ar esta proeza!?";
	char * userLine = (char * ) allocateMemory(MAX_NICKNAME_SIZE+10,sizeof(char));
	//USER temporaryUser; //apagar casou use o vetor de users
	USER * playerList = (USER *) allocateMemory(settings.historySize,sizeof(USER)); //para listagem n�o ordenada
	CONTROLINT i;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	/*header*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"HIST�RICO",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"| Listagem dos �ltimos 15 jogadores |",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	
	/*content*/
	if(settings.historySize > 0)
	{
		
		for(i=0;i<settings.historySize;i++)
		{
			
			historyForPrint(historyPlayers,playerList,settings.historySize);
			sprintf(userLine,"%d - %s",i+1,playerList[i].nickname);	
			/*
			temporaryUser = returnsLastPlayersOneByOne(history);	
			sprintf(userLine,"%d - %s",i+1,temporaryUser.nickname);				
			alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
			lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_LEFT,userLine,TEXT_STANDARD,BAKGROUND_STANDARD);
			*/
		}		
	}
	else
	{
		alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
		emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
		textFrame(' ',PADDING_INTERNAL,STANDARD_BOX_SIZE,ALIGN_CENTER,ALIGN_CENTER, messageEmptyList,TEXT_STANDARD,BAKGROUND_STANDARD);
	}
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
			
	/*footer*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"Pressione qualquer tecla para retornar ao menu principal...",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	wait();
}



void redersHistoryFatalError(void)

{
	char message[] = "Algo terr�vel aconteceu durante o carregamento do programa que impediu a inicializa��o do hist�rico de jogadores. Tente reinstalar o jogo, caso isto n�o funcione contate o suporte. O TRIVIAL precisa ser encerrado, lamentamos este inconveniente.";
	char instruction[] = "Pressione qualquer tecla para finalizar o programa.";
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("FALHA AO CARREGAR HIST�RICO",message,instruction,ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

/*Top 10*/
	
void redersTop10FatalError(void)
{
	char message[] = "Algo terr�vel aconteceu durante o carregamento do programa que impediu a inicializa��o da lista dos 10 melhores jogadores. Tente reinstalar o jogo, caso isto n�o funcione contate o suporte. O TRIVIAL precisa ser encerrado, lamentamos este inconveniente.";
	char instruction[] = "Pressione qualquer tecla para finalizar o programa.";
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("FALHA AO CARREGAR HIST�RICO",message,instruction,ERROR_BOX,INSTRUCTION_BOX);
	wait();
	
}

void rendersTopPlayers(NODE ** bestPlayers)
{
	char messageEmptyList[] = "Infelizmente nenhum jogador ainda se aventurou no fant�stico mundo do TRIVIAL. Que tal voc� come�ar esta proeza!?";
	char templates[] = "%d� - %s  com %2.f %% de acertos";
	char * userLine = (char * ) allocateMemory(MAX_NICKNAME_SIZE+strlen(templates)+2,sizeof(char));
	USER temporaryUser;
	CONTROLINT i;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	/*header*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"MELHORES JOGADORES",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"| Listagem dos 10 melhores jogadores de todos os tempos |",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	
	/*content*/
	if(settings.topSize > 0)
	{
		
		for(i=0;i<settings.topSize;i++)
		{
			temporaryUser = returnsTopPlayersOneByOne(bestPlayers);	
			sprintf(userLine,templates,i+1,temporaryUser.nickname,temporaryUser.percentageCorrect);				
			alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
			lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_LEFT,userLine,TEXT_STANDARD,BAKGROUND_STANDARD);
		}		
	}
	else
	{
		alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
		emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
		textFrame(' ',PADDING_INTERNAL,STANDARD_BOX_SIZE,ALIGN_CENTER,ALIGN_CENTER, messageEmptyList,TEXT_STANDARD,BAKGROUND_STANDARD);
	}
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
			
	/*footer*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"Pressione qualquer tecla para retornar ao menu principal...",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	wait();
}

void renderCongratulationsTop(USER player){
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	char dados[1][50];	
	sprintf(dados[0],"%s",player.name);	
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_SUCCESS, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER,"                                    .''.             ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "       .''.      .        *''*    :_\\/_:     .    ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "     :_\\/_:   _\\(/_  .:.*_\\/_*   : /\\ :  .'.:.'.", TEXT_ERROR, BAKGROUND_STANDARD);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, " .''.: /\\ :   ./)\\   ':'* /\\ * :  '..'.  -=:o:=- ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ":_\\/_:'.:::.    ' *''*    * '.\\'/.' _\\(/_'.':'.' ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ": /\\ : :::::     *_\\/_*     -= o =-  /)\\    '  * ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "  '..'  ':::'     * /\\ *     .'/.\\'.   '           ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "     *              *..*         :                   ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "       *                                            ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "       *                                            ", TEXT_ERROR, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, dados[0] , TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER,"Voc� entrou no Top 10.", TEXT_STANDARD, BAKGROUND_STANDARD);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER,"PARAB�NS!", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	sleep(2);
}

/*Ecr�s estaticos*/
void renderCreditos(void){
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	
	char ta[8][100];
	sprintf(ta[0],"Alunos:");
	sprintf(ta[1],"Jackson Barreto n� 24031");
	sprintf(ta[2],"Leonardo Lopez n� 18278");
	sprintf(ta[3],"Professores:");
	sprintf(ta[4],"Pedro Coutinho");
	sprintf(ta[5],"Estrela Cruz");
	sprintf(ta[6],"Programa��o 1 - Jogo do Trivia (Adaptado)");
	sprintf(ta[7],"2019-2020");
    int jumpControlAtBottom = 0;
    const int someDelay = 500000;
    int shifControl = 0;
    for (jumpControlAtBottom = 0; jumpControlAtBottom < 30; ++jumpControlAtBottom)
    {
        printf("\n");
    }    
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);	
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);	
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, ta[0], TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ta[1], TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ta[2], TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);	
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, ta[3], TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ta[4], TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ta[5], TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ta[6], TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, ta[7], TEXT_STANDARD,BAKGROUND_STANDARD);	
	usleep(someDelay);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	usleep(someDelay);
	for (shifControl = 0; shifControl < 30; ++shifControl)
    {               
        printf("\n");
        usleep(someDelay);
    }	
}
void renderInicio(void){
/***
 *     ______                                          ___      
 *    /\__  _\          __              __            /\_ \     
 *    \/_/\ \/   _ __  /\_\    __  __  /\_\      __   \//\ \    
 *       \ \ \  /\`'__\\/\ \  /\ \/\ \ \/\ \   /'__`\   \ \ \   
 *        \ \ \ \ \ \/  \ \ \ \ \ \_/ | \ \ \ /\ \_\.\   \_\ \_ .
 *         \ \_\ \ \_\   \ \_\ \ \___/   \ \_\\ \__/.\_\ /\____\.
 *          \/_/  \/_/    \/_/  \/__/     \/_/ \/__/\/_/ \/____/
 *                                                                
 *                                                                
 */
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "     ______                                          ___      ", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "    /\\__  _\\          __              __            /\\_ \\     ", TEXT_STANDARD, BAKGROUND_STANDARD);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "    \\/_/\\ \\/   _ __  /\\_\\    __  __  /\\_\\      __   \\//\\ \\    ", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "      \\ \\ \\  /\\`'__\\\\/\\ \\  /\\ \\/\\ \\ \\/\\ \\   /'__`\\   \\ \\ \\   ", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "        \\ \\ \\ \\ \\ \\/  \\ \\ \\ \\ \\ \\_/ | \\ \\ \\ /\\ \\_\\.\\   \\_\\ \\_ ", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "         \\ \\_\\ \\ \\_\\   \\ \\_\\ \\ \\___/   \\ \\_\\\\ \\__/.\\_\\ /\\____\\ ", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_CENTER, "          \\/_/  \\/_/    \\/_/  \\/__/     \\/_/ \\/__/\\/_/ \\/____/", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);	
	sleep(2);
	
}
