#include "../inc/view.h"

	/*Player*/
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

/*Register*/
void rendersGetNameForRegister(char * name)
{
	char message[100];
	sprintf(message,"Informe o seu nome com até %d letras.",MAX_NAME_SIZE);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,1,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USUÁRIO",message,"Nome:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,29,STANDARD_BOX);
	getString(MAX_NAME_SIZE,name);	
}

void rendersGetUsernameForRegister(char * username)
{
	char message[150];
	sprintf(message,"Informe o seu 'username' com até %d letras. Ele deve ser único e sera usado para se logar no sistema.",MAX_USER_NAME_SIZE);
	clearScreen();	
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,2,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USUÁRIO",message,"Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USER_NAME_SIZE,username);	
}

void rendersGetNickname(char * nickname)
{
	char message[150];
	sprintf(message,"Informe o seu 'nickname' com até %d letras. Ele deve ser único. É através dele que você será reconhecido por todos.",MAX_NICKNAME_SIZE);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,3,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USUÁRIO",message,"Nickname:",STANDARD_BOX,QUESTION_BOX);
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
		sprintf(message,"Informe a sua 'password'. Ela deve ter exatamente %d caracteres. São aceitos letras, números e caracteres especiais.",MAX_PASSWD_SIZE-1);		
	}
	else
	{
		strcpy(message,"Digite novamente a sua 'password' para que possamos ter a certeza que a digitou corretamente.");		
	}
	instructionBox("CADASTRO DE USUÁRIO",message,"Password:",STANDARD_BOX,QUESTION_BOX);
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
	//Imprime os dados do usuário
	instructionBox("CADASTRO DE USUÁRIO","Verifique se todos os dados estão corretos.","Pressione [1] para reiniciar o cadastro ou [2] para confirmar.",STANDARD_BOX,INSTRUCTION_BOX);	
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
	instructionBox("PASSWORD NÃO COINCIDE","As passwords informadas não são iguais. Você pode tentar redigitá-las ou simplesmente desistir do seu cadastro.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
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
	instructionBox("NICKNAME NÃO DISPONÍVEL","O 'nickname' informado já está sendo utilizado por outro usuário. Escolha outro apelido para lhe representar.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
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
	instructionBox("USERNAME NÃO DISPONÍVEL","O 'username' informado já está sendo utilizado por outro usuário. Escolha outro nome de acesso ao sistema.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
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
	instructionBox("CADASTRO DE PERGUNTA","Informe o título da pergunta, ou seja, a pergunta propriamente dita.","Título:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,32,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,title);	
}

void rendersGetQuestionRightAnswer(char * correctAnswer)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,2,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe a resposta CORRETA para a questão anteriormente inserida.","Resposta CORRETA:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,42,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,correctAnswer);	
}

void rendersGetQuestionAnswer(char * answer, CONTROLINT progressBarPosition)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,progressBarPosition,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe outra opção de resposta para a questão anteriormente inserida.","Resposta:",STANDARD_BOX,QUESTION_BOX);
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
	instructionBox("CADASTRO DE PERGUNTA","Verifique se todos os dados estão corretos.","Pressione [1] para reiniciar o cadastro ou [2] para confirmar.",STANDARD_BOX,INSTRUCTION_BOX);	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,RECORD_QUESTION,CLOSED_RANGE) );
	
	return choice;
}



/*History*/

void rendersHistory(NODE ** history)
{
	char messageEmptyList[] = "Infelizmente nenhum jogador ainda se aventurou no fantástico mundo do TRIVIAL. Que tal você começar esta proeza!?";
	char * userLine = (char * ) allocateMemory(MAX_NICKNAME_SIZE+10,sizeof(char));
	USER temporaryUser; //apagar casou use o vetor de users
	//USER * playerList = (USER *) allocateMemory(settings.historySize,sizeof(USER));
	CONTROLINT i;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	/*header*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"HISTÓRICO",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"| Listagem dos últimos 15 jogadores |",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	
	/*content*/
	if(settings.historySize > 0)
	{
		
		for(i=0;i<settings.historySize;i++)
		{
			/*
			historyForPrint(historyPlayers,playerList,settings.historySize);
			sprintf(userLine,"%d - %s",i+1,playerList[i].nickname);	
			*/
			temporaryUser = returnsLastPlayersOneByOne(history);	
			sprintf(userLine,"%d - %s",i+1,temporaryUser.nickname);				
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
	getch();
}

void redersHistoryFatalError(void)

{
	char message[] = "Algo terrível aconteceu durante o carregamento do programa que impediu a inicialização do histórico de jogadores. Tente reinstalar o jogo, caso isto não funcione contate o suporte. O TRIVIAL precisa ser encerrado, lamentamos este inconveniente.";
	char instruction[] = "Pressione qualquer tecla para finalizar o programa.";
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("FALHA AO CARREGAR HISTÓRICO",message,instruction,ERROR_BOX,INSTRUCTION_BOX);
	getch();
}

/*Top 10*/
	
void redersTop10FatalError(void)
{
	char message[] = "Algo terrível aconteceu durante o carregamento do programa que impediu a inicialização da lista dos 10 melhores jogadores. Tente reinstalar o jogo, caso isto não funcione contate o suporte. O TRIVIAL precisa ser encerrado, lamentamos este inconveniente.";
	char instruction[] = "Pressione qualquer tecla para finalizar o programa.";
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("FALHA AO CARREGAR HISTÓRICO",message,instruction,ERROR_BOX,INSTRUCTION_BOX);
	getch();
	
}

void rendersTopPlayers(NODE ** bestPlayers)
{
	char messageEmptyList[] = "Infelizmente nenhum jogador ainda se aventurou no fantástico mundo do TRIVIAL. Que tal você começar esta proeza!?";
	char templates[] = "%dº - %s  com %2f \% de acertos";
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
		
		for(i=0;i<settings.historySize;i++)
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
	getch();
}
