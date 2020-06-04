#ifdef _WIN32
	#include <windows.h>
#endif

#ifdef __MAIN__
	#include "helpers.h"
	#include "boot.h"
	#include "gameLogic.h"
	#include "view.h"
	#include "shutdown.h"
	#include "register.h"
	#include "adm.h"
	#include "history.h"
	#include "top.h"
	
#endif

#ifdef __HELPERS_H__
	#include "error.h"
	#include <conio.h>
#endif

#ifdef __GAME_LOGIC_H__
	#include "helpers.h"
	#include "deckHandler.h"
	#include "login.h"
	#include "sort.h"
	#include "view.h"
	#include "history.h"
	#include "top.h"
#endif

#ifdef __SHUTDOWN_H__
	#include "crud.h"
	#include "history.h"
	#include "top.h"
#endif

#ifdef __BOOT_H__
	#include "deckHandler.h"
	#include "crud.h"
	#include "history.h"
	#include "top.h"
	#include <direct.h>
#endif

#ifdef __LOGIN_H__
	#include "helpers.h"
	#include "crud.h"
	#include "view.h"
	#include "register.h"
#endif

#ifdef __CRUD_H__
	#include "helpers.h"
#endif

#ifdef __ERROR_H__
	#include "helpers.h"
	#include "view.h"
#endif

#ifdef __SORT_H__
	#include "error.h"
#endif

#ifdef __DECK_HANDLER__
	#include "crud.h"
	#include "error.h"
#endif

#ifdef __DESIGN_H__
	#include <conio.h>
	#include "helpers.h"
#endif

#ifdef __VIEW_H__
	#include "design.h"
	#include "helpers.h"
	#include "history.h"
	#include "top.h"
#endif

#ifdef __REGISTER_H__
	#include "crud.h"
	#include "error.h"
	#include "view.h"
#endif

#ifdef __ADM_H__
	#include "view.h"
	#include "view.h"
	#include "crud.h"
#endif

#ifdef __HISTORY_H__
	#include "crud.h"
	#include "helpers.h"
	#include "sort.h" //remover se não usar a ordenação alfabética
	#include "view.h"
#endif

#ifdef __TOP_H__
	#include "crud.h"
	#include "helpers.h"
	#include "view.h"
#endif
