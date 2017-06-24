#include "text.h"

char *WELCOME_01      = ":irc.labiis.org NOTICE * :*** Benvenuto!\n";
char *WELCOME_02      = ":irc.labiis.org NOTICE * :*** Registrando...\n";
char *WELCOME_03      = ":irc.labiis.org NOTICE * :*** Pronto!\n";
char *WELCOME_USER_01 = ":irc.progredes.org 001 ";
char *WELCOME_USER_02 = " :Benvenuto! il tuo hostname è: ";

char *DUMMY_USER      = "unnamed_user";
char *DUMMY_CHANNEL   = "*";
char *DUMMY_HOST      = "unknown_host";

char *SERVER_NAME     = "irc.labiis.org";
char *SERVER_INFO     = ":Padova, IT, Europa";
char *DEFAULT_PONG    = ":irc.labiis.org PONG irc.labiis.org :";

char *ENDOFWHOIS      = " :End of /WHOIS list\n";
char *ENDOFWHO        = " :End of /WHO list\n";
char *ENDOFNAMES      = " :End of /NAMES list\n";

char *CHANNELS[]      = {"WhiteHat",
                         " :No script kiddies allowed.\n",
                         "1337h4x0rz",
                         " ::(){ :|: & };:\n"};

char *LIST_END        = " :End of /LIST\n";
char *LIST_HEADER     = " Channel :Users Name\n";

char *DCC_START       = "\001DCC ";
char *DCC_END         = "\001\n";

char *NONICKNAMEGIVEN = " :No nickname given\n";
