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
#include <sstream>

#define N 10 //You may increase N later for the final testing
#define LOGOUTCODE 5

using namespace std;

void build_command();
void user_login();
void type_prompt();
int read_command(string command, string* parameters);
void exec_command(int opcode, string* parameters);

string commands[7];
string currUser;

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
    commandFile.open("MSHcommands.txt");
    
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

    // make it so that it compares to the text file
    ifstream loginFile;
    loginFile.open("users.txt");

    string line;
    while (getline(loginFile, line))
    {
        istringstream iss(line);
        while (true)
        {
            if (line.find(username))
            {
                if (line.find(en_passwd))
                {
                    loginFile.close();
                    currUser = username;
                    break;
                }
            }
            cout << "Login invalid\n";
        }
    }
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
    string commandstring;
    getline(cin, commandstring);
    istringstream cmdStream(commandstring);
    cmdStream >> command;

    // store parameters
    
    /* search the table to return the opcode */
    if (command.compare("MSHlogout") == 0) opcode = LOGOUTCODE;
    return opcode;
    // check whether it's a valid command
}

void exec_command(int opcode, string* parameters)
{
    cout << "Child: Execute command function: 1" + (string)"\n";
    /* Using the case statement to run the simple shell commands */
    /* Write your code here  */
    switch (opcode)
    {
    case 1: 
    {
        //MSHpwd code
        string newPass;
        cout << "New password: ";
        cin >> newPass;

        string editPass = crypt(newPass.c_str(), "22");

        ifstream loginfile;
        loginfile.open("users.txt");

        string line;
        while (getline(loginfile, line))
        {
            istringstream iss(line);
            while (true)
            {
                if (line.find(currUser))
                {
                    // insert changing current password to editPass

                }
            }
        }
        break;
    }
    case 2: 
        //MSHcopy code
        //const char* file1 = parameters[0].c_str();
        //const char* file2 = parameters[1].c_str();
       

        //if third parameter isn't input. fileName portions of string need to be replaced with input files
        if (parameters[2] == "")
        {
            string input = "cp " + parameters[0] + " " + parameters[1];
            const char* command = input.c_str();
            system(command);
        }
        else //if third parameter is input. filename portions of string need to be replaced with input files
        {
            string input1 = "cp " + parameters[0] + " " + parameters[2];
            string input2 = "cp " + parameters[1] + " " + parameters[2];
            const char* command1 = input1.c_str();
            const char* command2 = input2.c_str();

            system(command1);
            system(command2);
        }
        break;
    case 3: 
    {
        //MSHps [loginName] code
        if (parameters->length() == 0)
        {
            string input = "ps -ef | grep " + parameters[0];
            const char* command = input.c_str();
            system(command);
        }
        else
        {
            system("ps -ef");
        }
        break;
    }
    case 4: 
    {
        //MSHdf [filesystem] code
        if (parameters->length() == 0)
        {
            string input = "df -k | grep " + parameters[0];
            const char* command = input.c_str();
            system(command);
        }
        else
        {
            system("df -k");
        }
        break;
    }
    case 5: 
    {
        //MSHsearch word fileName code
        string input = "grep " + parameters[0];
        const char* command = input.c_str();
        system(command);
    }
        break;
    case 6:
    {
        //MSHhistory code
        for (list<string>::iterator i = history.begin(); i != history.end(); i++)
        {
            cout << *i << endl;
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