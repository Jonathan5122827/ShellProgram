/*
 * Created by: Henry Iraheta
 * exit() command
 *
 *
 */
#include "major2.h"

//Takes the command line and checks for the exit Operations

//If we hit exit we wait to exit until everything is done

//After all commands are done executing we exit the shell

int exit(argv) {

    command = agrv[0];

    exit = false;

    commands = ??(command, ??)

    for command in commands {

        if command == "exit" {

            exit = true;

            continue;
        }
        
        command.main();
    }
    if exit {

        exit(??);

    }
    return 0;
}
