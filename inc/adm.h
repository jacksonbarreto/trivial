#ifndef __ADM_H__
	#define __ADM_H__
	#include "config.h"
	
	
	/*		ADMINISTRATOR		*/
	void promoteUserToAdministrator(void);
	void recoverPassword(void);
	void changeName(USER * user);
	
	/*		INSERT QUESTION		*/
	void insertQuestion(void);
	static QUESTION getQuestion(void);
	
#endif
