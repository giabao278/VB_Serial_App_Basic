/* Author: DGB
 * From: my lab WiH (more infor: IUH, DHDKTD14A)
 * this is my protocol used for Measurement & Control by Computer subject
 * email: dgb0728@gmail.com
 * github: github.com/giabao278 (give a star if you like my code)
 * just research & ignore my broken english
 * 
 * command_table.h
*/

#ifndef COMMAND_TABLE_H
#define COMMAND_TABLE_H

#include <string.h>
#include <stdlib.h>
#include "led_mode.h"

/* declare enum command */
typedef enum
{
    CMD_SLE,
    CMD_SLT,
    CMD_SLS,
    CMD_SLR,
    CMD_NON,
}command_e;

/* declare entry struct for search and call function */
typedef struct
{
    const char      *Name;
    const char      *Help;
    const command_e Command;
}command_entry_t;

/* declare command table */
const command_entry_t cmd_table[] = 
{   
    {"SLE", "Set effect of led.", CMD_SLE},
    {"SLS", "Set led data but none effect.", CMD_SLS},
	{"SLT", "Set timer of led.", CMD_SLT},
    {"SLR", "Set led response.", CMD_SLR},
    {NULL, "Not found command.", CMD_NON}
};


/*------------------------Declare function------------------------*/
command_e command_search(char *pCmd);
void command_excute(char *pCmd, char *argv_1);


/*-----------------------function implement-----------------------*/

/* Search command in command table declare */
command_e command_search(char *pCmd)
{
    int cmdIndex = 0;
    while(cmd_table[cmdIndex].Command != CMD_NON)
    {
        if(strcmp(cmd_table[cmdIndex].Name,pCmd) == 0) {
            return cmd_table[cmdIndex].Command;
        }
        else {
            cmdIndex++;
        }
    }
    return CMD_NON;
}

/* excute command function call by my_protocol_decode function */
void command_excute(char *pCmd, char *argv_1)
{
    const command_e cmd_search = command_search(pCmd);
    switch (cmd_search)
    {
        case CMD_SLE:{
            int modeLED = atoi(argv_1);
            led_setMode(modeLED);
            //Serial.println(cmd_table[0].Help);
            break;
        }
        case CMD_SLS:{
            char sngLed = *argv_1;
            led_setSingle(sngLed);
            //Serial.println(cmd_table[1].Help);
            break;
        }
        case CMD_SLT:{
            int timerLED = atoi(argv_1);
            led_setTimer(timerLED);
            //Serial.println(cmd_table[2].Help);
            break;
        }
        case CMD_SLR:{
            int repState = atoi(argv_1);
            led_reps(repState);
            //Serial.println(cmd_table[3].Help);
            break;
        }
        case CMD_NON:{
            //Serial.println(cmd_table[4].Help);
            break;
        }
    }
}

#endif