#include "../inc/error.h"

void eventsHandling(CONTROLINT event)
{
	FILE * logs = fopen(LOG_FILE_NAME,"a");
	
	if(logs == NULL)
	{	
		fprintf(stderr,RED"\nOCORREU UM ERRO\nNão foi possível abrir o arquivo de log.\nErro cod. %d : %s\n"RESET_COLORS,errno,strerror(errno));		
		system("pause");
	}
	
	switch(event)
	{
		case STANDARD_EVENT:
			fprintf(logs,"%s - Erro cod %d : %s\n", formattedDateTime(), errno, strerror(errno));
			break;
		case CRITICAL_FAILURE:
			fprintf(logs,"%s - Erro cod %d : %s\n", formattedDateTime(), errno, strerror(errno));
			exit(EXIT_FAILURE);
			break;
		case INCOMPLETE_RECORD:
			fprintf(logs,"%s - Falha em [writeData()]. Nem todos os registros foram gravados.\n", formattedDateTime());
			break;
		case INCOMPLETE_READING:
			fprintf(logs,"%s - Falha em [readData()]. Nem todos os registros foram lidos.\n", formattedDateTime());
			break;
		case REMOVAL_STACK_EMPTY:
			fprintf(logs,"%s - Falha em [removeCard()]. Tentativa de remoção em pilha vazia.\n", formattedDateTime());
			break;
		case GAME_STATUS_UNIDENTIFIED:
			fprintf(logs,"%s - Falha em [deckControl()]. Status do jogo não identificado.\n", formattedDateTime());
			break;
		case DATA_TYPE_UNIDENTIFIED:
			fprintf(logs,"%s - Falha em [bubbleSort()]. DataType não suportado, não ocorreu ordenação.\n", formattedDateTime());
			break;
		case EMPTY_QUEUE	:
			fprintf(logs,"%s - Falha em [dqueue()]. Tentativa de remoção em FILA vazia.\n", formattedDateTime());
			break;
		case QUEUE_NOT_STARTED:
			fprintf(logs,"%s - Falha em [history.h]. Tentativa de uso de FILA não inicializada.\n", formattedDateTime());
			redersHistoryFatalError();
			exit(EXIT_FAILURE);
			break;
		case LIST_NOT_STARTED:
			fprintf(logs,"%s - Falha em [top.h]. Tentativa de uso de LISTA não inicializada.\n", formattedDateTime());
			redersTop10FatalError();
			exit(EXIT_FAILURE);
			break;
		case LIST_QUEUE:
			fprintf(logs,"%s - Falha em [top.h]. Tentativa de uso de LISTA vazia.\n", formattedDateTime());
			break;
		default:
			fprintf(logs,"%s - Evento desconhecido\n", formattedDateTime());
	}
	fclose(logs);
}
