#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <crypt.h>
#include <list>

// include c++ header files
#include <string>
#include <iostream>
#include <fstream>

#define N 10 //You may increase N later for the final testing
#define LOGOUTCODE 5

using namespace std;

void build_command();
void user_login();
void type_prompt();
int read_command(string command, string* parameters);
void exec_command(int opcode, string* parameters);

string commands[7];

list<string> history;

int main() 
{
    int i = 0, opcode = 0;
    int pid = 0, status = 0;
    string command, parameters[3];

    

    build_command(); /* read in the commands into a table or hash table */

    user_login(); /* Authenticate the user */

    while (i < N) { /* repeat maximum N times, used to avoid the infinite loop */

        type_prompt(); /* display prompt */

        opcode = read_command(command, parameters); /* input from terminal */

            if (opcode > 0) /* valid command */
            { 
                history.push_back(commands[opcode - 1]);
                if (pid = fork() != 0) { /* Parent code */

                    pid = wait(&status); /* wait for child to exit */
                    cout << "Parent: returned Child PID = " << pid << "\n";
                    cout << "Parent: returned Child Status = " << status << "\n";

                    if (status == LOGOUTCODE) exit(0); /* status must be a hex number */

                    /* For example: LOGOUTCODE is 0x0500 is child terminated with the command exit(5) */
                }
                else /* Child code */
                { 
                    exec_command(opcode, parameters); /* execute command */

                    exit(0);
                } 
                /* end of child code */
            }
            else 
            { 
                cout << "Invalid command, try again\n"; 
            }

        i++;
    }
    return (1);
}

void build_command()
{
    cout << "Build command function: \n";
    ifstream commandFile;
    commandFile.open("shellcommands.txt");
    
    for (int i = 0; i <= 6; i++)
    {
        commandFile >> commands[i];
    }
    commandFile.close();
}

void user_login()
{
    cout << "User login function: \n";
    /* Write your code here  */
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;
    cout << username << "'s password: ";
    cin >> password;

    string en_passwd = crypt(password.c_str(), "22");
}

void type_prompt()
{
    cout << "MSH> ";
}

int read_command(string command, string* parameter)
{
    int opcode = 0;
    cin >> command;
    /* read and parsing the input strings using the strtok() and others */
    /* Write your code here  */
    string commandstring;
    getline(cin, commandstring);
    istringstream cmdStream(commandstring);
    cmdStream >> command;
    /* search the table to return the opcode */
    if (command.compare("MSHlogout") == 0) opcode = LOGOUTCODE;
    return opcode;
}

void exec_command(int opcode, string* parameters)
{
    cout << "Child: Execute command function: 1" + (string)"\n";
    /* Using the case statement to run the simple shell commands */
    /* Write your code here  */
    switch (opcode)
    {
    case 1: 
        //MSHpwd code

        break;
    case 2: 
        //MSHcopy code
        
        //if third parameter isn't input. fileName portions of string need to be replaced with input files
        system("cat fileName1 fileName2"); 

        //if third parameter is input. filename portions of string need to be replaced with input files
        system("cat fileName1 fileHame3");
        system("cat filename2 fileName3");

        break;
    case 3: 
    {
        //MSHps [loginName] code
        string input = "ps -ef | grep " + parameters[0];
        const char* command = input.c_str();
        system(command);
        break;
    }
    case 4: 
    {
        //MSHdf [filesystem] code
        string input = "ps -ef | grep " + parameters[0];
        const char* command = input.c_str();
        system(command);
        break;
    }
    case 5: 
        //MSHsearch word fileName code


        break;
    case 6:
    {
        //MSHhistory code
        for (list<string>::iterator i = history.begin(); i != history.end(); i++)
        {
            cout << *i << "\n";
        }
        break;
    }
    case 7: 
        //MSHlogout code
        cout << "Child: exit with status = LOGOUTCODE\n";
        exit(LOGOUTCODE);
        break;
    default:
        cout << "Invalid command\n";
        break;
    }

    //system("cp " + file1 + " " + file2);

    if (opcode == LOGOUTCODE) {
        cout << "Child: exit with status = LOGOUTCODE\n";
        exit(LOGOUTCODE);
    }
    return;
}