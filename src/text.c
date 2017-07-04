#include "text.h"

char *WELCOME_01      = ":irc.labiis.org NOTICE * :*** Benvenuto!\n";
char *WELCOME_02      = ":irc.labiis.org NOTICE * :*** Registrando...\n";
char *WELCOME_03      = ":irc.labiis.org NOTICE * :*** Pronto!\n";
char *WELCOME_USER_01 = ":irc.labiis.org 001 ";
char *WELCOME_USER_02 = " :Benvenuto! il tuo hostname è: ";

char *SERVER_NAME     = "irc.labiis.org";
char *SERVER_INFO     = ":Padova, IT, Europa";
char *DEFAULT_PONG    = ":irc.labiis.org PONG irc.labiis.org :";

char *ENDOFWHOIS      = " :End of /WHOIS list\n";
char *ENDOFWHO        = " :End of /WHO list\n";
char *ENDOFNAMES      = " :End of /NAMES list\n";


char *LIST_END        = " :End of /LIST\n";
char *LIST_HEADER     = " Channel :Users Name\n";

char *DCC_START       = "\001DCC ";
char *DCC_END         = "\001\n";

char *NONICKNAMEGIVEN = " :No nickname given\n";
