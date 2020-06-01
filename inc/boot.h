#ifndef __BOOT_H__
	 #define __BOOT_H__
	 #include "config.h"
	 
	 void boot(void);	 
	 static void loadUsers(void);
	 static USER createSUDO(void);
	 static void loadTopList(void);
	 static void loadHistoryList(void);
	 static void loadThemes(void);
	 static void startFileInf(FILEINF info);
	 static void loadSettings(void);
	 static void loadFileSystem(void);
#endif
