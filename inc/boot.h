#ifndef __BOOT_H__
	 #define __BOOT_H__
	 #include "config.h"
	 
	 void boot();
	 static void loadUsers();
	 static USER createSUDO();
	 static void loadTopList();
	 static void loadHistoryList();
	 static void loadThemes();
#endif
