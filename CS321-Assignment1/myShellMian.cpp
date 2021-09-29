//Hello lads
// Afternoon gamer
int main() {

    …

        build_command();       /* read in the commands into a table or hash table */

    user_login();                /* Authenticate the user */

    while (i < N) { /* repeat maximum N times, used to avoid the infinite loop */

        type_prompt();       /* display prompt */

        n = read_command(command, parameters)            /* input from terminal */

            if (n > 0) { /* valid command */

                if (pid = fork() > 0) { /* Parent code */

                    pid = wait(&status); /* wait for child to exit */

                    if (status == LOGOUTCODE) exit(0); /* status must be a hex number */

                                   /* For example: LOGOUTCODE is 0x0500 is child terminated with the command exit(5) */

                }
                else { /* Child code */

                    exec_command(command, parameters);    /* execute command */

                    exit(0);

                } /* end of child code */

            }
            else { cout << “Invalid command, try again\n”; }

        i++;

    }

    return (1);

}