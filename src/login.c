#include "../inc/login.h"

USER * login(const CONTROLINT totLogin)
{
	CONTROLINT i, choice, attempts;
	USER * players;
	USER temporaryUser;
	
	players = (USER *) allocateMemory(totLogin,sizeof(USER));
	
	for(i=0; i < totLogin; i++)
	{
		attempts = 0;		
		do
		{
			choice = 0;
			attempts++;
			if(attempts > MAXIMUM_LOGIN_ATTEMPTS)
			{
				//ALERTA: Atingiu o límite de tentativas. pressione qualquer tecla para retornar ao menu principal
				free(players);
				return NULL;
			}
				
			temporaryUser =	findUserByUsername(getUsername());
			
			if(temporaryUser.id == 0)
			{
				//Mensagem de erro: Username inválido.
				//Tentativa X de MAXIMUM_LOGIN_ATTEMPTS
				//Deseja se cadastrar ou tentar novamente - menu que retorna int
				if(choice == REGISTER_USER)
					temporaryUser = registerUser();  // registerUser é o módulo de cadastro e deve retornar um USER
				
			}
			
		}while(temporaryUser.id == 0);
		
		if(choice == REGISTER_USER)
		{
			//Inclui o usuário no players sem pedir senha	
			players[i] = temporaryUser;
			choice = 0;
			continue;			
		}
		
		attempts = 0;
		do
		{
			attempts++;
			if(attempts > MAXIMUM_LOGIN_ATTEMPTS)
			{
				//ALERTA: Atingiu o límite de tentativas. pressione qualquer tecla para retornar ao menu principal
				free(players);
				return NULL;
			}
			if(attempts > 1)
				;//exibe mensagem: Senha inválida tente novamente.  Tentativa X de MAXIMUM_LOGIN_ATTEMPTS
		}while(! strcmp(temporaryUser.password,getPassword()) );
	
		players[i] = temporaryUser;	
	}
	
	return players;
}

USER registerUser(void)
{
	
}

static char * getUsername(void)
{
	
	//chama tela para capturar o username, retorna uma string com o username
}

static char * getPassword(void)
{
	//chama tela para capturar a pssword, retorna uma string com a password
}



CONTROLINT isAdministrator(USER * user)
{
	return (user->userType == ADMIN_USER);
}



