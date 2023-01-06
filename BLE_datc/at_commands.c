#include "at_commands.h"

/*! \brief    Custom Command Handler. */
static uint8_t appNameCommandHandler(uint32_t argc, char **argv);
static uint8_t setPeerDeviceNameHandler(uint32_t argc, char **argv);
static uint8_t setPrintScanResultsHandler(uint32_t argc, char **argv);

/*! \brief    command list */
terminalCommand_t appTerminalCustomCommandList[] = {

    { NULL, "name", "name <First> <Last>", appNameCommandHandler },
    { NULL, "set-pn", "peer name <peer adv. name>", setPeerDeviceNameHandler },
    { NULL, "set-psr", "print scan results < 1 | 0 >", setPrintScanResultsHandler },
    { NULL, NULL, NULL, NULL }, // used as delimter for end of list

};

/*************************************************************************************************/
/*!
 *  \brief  Handler for a custom terminal command.
 *
 *  \param  argc      The number of arguments passed to the command.
 *  \param  argv      The array of arguments; the 0th argument is the command.
 *
 *  \return Error code.
 */
/*************************************************************************************************/
static uint8_t appNameCommandHandler(uint32_t argc, char **argv)
{
    if (argc < 3) {
        return TERMINAL_ERROR_TOO_FEW_ARGUMENTS;
    } else if (argc == 3) {
        TerminalTxPrint("Hello %s %s\r\n", argv[1], argv[2]);

    } else {
        return TERMINAL_ERROR_TOO_MANY_ARGUMENTS;
    }

    return TERMINAL_ERROR_OK;
}

/*************************************************************************************************/
/*!
 *  \brief  Handler for a custom terminal command.
 *
 *  \param  argc      The number of arguments passed to the command.
 *  \param  argv      The array of arguments; the 0th argument is the command.
 *
 *  \return Error code.
 */
/*************************************************************************************************/
extern uint8_t peer_name_len;
extern uint8_t peer_name;
extern bool name_set;
static uint8_t setPeerDeviceNameHandler(uint32_t argc, char **argv)
{
    if (argc < 2) {
        return TERMINAL_ERROR_TOO_FEW_ARGUMENTS;
    } else {
        //reset variables
        peer_name_len = 0;
        memset(&peer_name, 0x00, 20);
        for (int i = 1; i < argc; i++) {
            peer_name_len += strlen(argv[i]);

            if (i > 1) {
                // add a space before the new string if more than 2 arguments were passed
                strcat(&peer_name, " ");
                peer_name_len++;
            }
            strcat(&peer_name, argv[i]);
        }
        name_set = true;
    }
    return TERMINAL_ERROR_OK;
}

extern bool printScan;
static uint8_t setPrintScanResultsHandler(uint32_t argc, char **argv)
{
    if (argc < 2) {
        return TERMINAL_ERROR_TOO_FEW_ARGUMENTS;
    } else if (argc == 2) {
        uint8_t val = atoi(argv[1]);
        if (val) {
            TerminalTxPrint("on\r\n");
            printScan = true;
        } else {
            TerminalTxPrint("off\r\n");
            printScan = false;
        }
    }
    return TERMINAL_ERROR_OK;
}

void register_at_Commands(void)
{
    uint8_t index = 0;
    while (appTerminalCustomCommandList[index].pName != NULL) {
        TerminalRegisterCommand(&appTerminalCustomCommandList[index]);
        index++;
    }
}
