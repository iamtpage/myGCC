#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int i; //counter for loops
    int valid = 1; //flag to determine if parameter is valid
    int filefound = 0; //flag to see if they included a .c file

    //loop for as long as we have parameters
    for(i = 1; i < argc; i++)
    {
        //check for -lm or -ll first, since it shouldn't be used until last
        if(strpbrk(argv[i], "-l") != NULL && strspn(argv[i],"-l") > 1)
        {
            //only evaluate if the next parameter is NULL.  No more parameters means it is last in the list
            if(argv[i+1] == NULL)
            {
                //check to see if it is -lm or -ll
                if (strspn(argv[i], "-lm") == 3)
                {
                    printf("%s The math library will be linked.\n", argv[i]);
                }
                if (strspn(argv[i], "-ll") == 3)
                {
                    printf("%s The lex library will be linked.\n", argv[i]);
                }
            }

            //there are more parameters after -l, which means it isn't last
            else
            {
                printf("Error, -l needs to be used last.\n");
            }
        }

        //check for -o
        if(strpbrk(argv[i],"-o") != NULL && strspn(argv[i],"-o") > 1)
        {
            //format is -o "name", so -o is argv[i], and "name" is argv[i+1]
            printf("-o The output will be named %s.\n", argv[i+1]);
            //we don't need to check to see if the output name is a parameter, so skip it.
            i = i + 1;
        }

        //check for -g flag
        if(strpbrk(argv[i], "-g") != NULL && strspn(argv[i],"-g") > 1)
        {
            printf("-g The program will be compiled with additional gdb information.\n");
        }

        //check for -c flag
        if(strpbrk(argv[i], "-c") != NULL && strspn(argv[i],"-c") > 1)
        {
            printf("-c The object file will be built, but not linked.\n");
        }

        // -E
        if(strpbrk(argv[i], "-E") != NULL && strspn(argv[i],"-E") > 1)
        {
            printf("-E No compiling will occur, just the C preprocessor output.\n");
        }

        // -S
        if(strpbrk(argv[i], "-S") != NULL && strspn(argv[i],"-S") > 1)
        {
            printf("-S The assembly language file will be built, but not linked.\n");
        }

        //-O
        if(strpbrk(argv[i], "-O") != NULL && strspn(argv[i],"-O") > 1)
        {
            //format is -O#, argv[i] = -O#, argv[i] + 2 trims the -O and we are left with the number
            if(atoi(argv[i] + 2) < 5 && atoi(argv[i] + 2) > 0 )
            {
                printf("%s The program will be compiled at an optimization level of %s.\n", argv[i], argv[i] + 2);
            }

            else
            {
                printf("%s is not a valid optimization level.\nAborting...\n", argv[i]);
            }
        }

        //-D, this was the hardest one.
        if(strpbrk(argv[i], "-D") != NULL && strspn(argv[i],"-D") > 1)
        {
            //check for -Dname=value
            if(strpbrk(argv[i], "=") != NULL)
            {
                char macroname[128];
                char valuename[128];
                int value;

                //this trims the string from "-D name=value" to "name"

                strncpy(macroname, argv[i] + 2, strlen(argv[i]) - 4);

                //get the length of the name so I can use it to trim down to the value
                if(strlen(macroname) <= sizeof(valuename))
                {
                    value = strlen(macroname);

                    strncpy(valuename, argv[i] + value + 3, 3);

                    //argv[i] = "-D name=value"
                    //macroname = "name"
                    //argv[i] + value + 4 = trim the string based on the macroname length, then trim it to just the value
                    printf("%s Compilation macro %s  defined to the value of %s.\n", argv[i], macroname, valuename);
                }

                else
                {
                    printf("The name of the macro is too long.\n");
                }
            }

            //if there isn't an =, as in the variable isn't defined
            if(strpbrk(argv[i], "=") == NULL)
            {
                //argv[i] = -D name, argv[i] = name.  So just print argv[i+1]
                printf("%s Compilation macro %s is defined.\n", argv[i], argv[i+1]);

                //skip the variable name, as it isn't a valid parameter
                i = i + 1;
            }
        }

        //check for a file to actually compile
        if(strstr(argv[i], ".c") != NULL)
        {
            printf("Compiling %s\n", argv[i]);

            //they gave us a .c file to compile
            filefound = 1;
        }

        //if its the last parameter and they haven't given us a .c file to compile
        if(argv[i+1] == NULL && filefound == 0)
        {
            printf("Error! No file given to compile.\nAborting...\n");
            break;
        }

        else
        {
            valid = 0;
        }

        if(!valid)
        {
            printf("Error! Unrecognized parameter: %s\n Aborting...\n", argv[i]);
            break;
        }
    }
    printf("\n");
    return 0;
}