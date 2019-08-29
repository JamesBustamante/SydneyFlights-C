/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: James Bustamante
 * Student ID: 12900926
 * Date of submission:
 * A brief statement on what you could achieve (less than 50 words):
 * I was able to implement every feature outlined in the assignment
 * specification including date_time & flight structs, add flight,
 * display flights, save flights and load files from database.
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * There was nothing that I wasn't able to successfully achieve. Though
 * perhaps some of my algorthims could of had some reduced complexity
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdio.h>  /* printf, scanf */
#include <string.h> /* strcpy, strcmp, strlen, strcat */
#include <stdlib.h> /* malloc */

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"
typedef int bool; /*type defines bool to perform the same actions as they */
#define true 1    /*would in another programming language*/
#define false 0

/*******************************************************************************
 * Listed structs:
 *  - date_time
 *  - flght
*******************************************************************************/

struct date_time
{
    int month;
    int day;
    int hour;
    int minute;
};
typedef struct date_time date_time_t;

struct flight
{
    char flightcode[MAX_FLIGHTCODE_LEN + 1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN + 1];
    date_time_t arrival_dt;
};
typedef struct flight flight_t;

/*******************************************************************************
 * Function prototypes
*******************************************************************************/
void selectionUse(int counter, flight_t flights[]); /*select choice from menu*/
void print_menu(void);                              /*prints menu to the user*/
void addFlight(int *counter, flight_t flights[]);
void displayFlights(int *counter, flight_t flights[]);
void saveFlights(int *counter, flight_t flights[]);
void loadFlights(int *counter, flight_t flights[]);
bool isValidFlightCode(char flightcode[]); /*Checks if syntax is correct*/
bool isValidCityCode(char arrival_city[]); /*Checks if syntax is correct*/

/*******************************************************************************
 * Main: defines an array of flights to type flight_T. defines and sets the
 *       initial counter. calls function selectionUse to print menu and 
 *       allow the program to fully function.
*******************************************************************************/
int main(void)
{
    flight_t flights[MAX_NUM_FLIGHTS];
    int counter = 0;
    /*will be used as a pointer adjust amount of flights currently stored*/
    /*This allows for the changing of counter in functions  without
    returning its value (see below) */
    selectionUse(counter, flights);
    return 0;
}

/*******************************************************************************
 * SelectionUse Function: while input is invaild the menu will be printed and
 * user will be asked to make a selection (1-5)
 * inputs:
 * - counter: amount of flights stored in flights[] so far
 * - flights[]: array of flights of type flight_t
 * outputs:
 * - none
*******************************************************************************/
void selectionUse(int counter, flight_t flights[])
{
    char *selection = malloc(10);

    while (1) /*condition is true*/
    {
        print_menu();
        scanf(" %s", selection);
        switch (*selection)
        {
        case '1':
            addFlight(&counter, flights);
            break;
        case '2':
            displayFlights(&counter, flights);
            break;
        case '3':
            saveFlights(&counter, flights);
            break;
        case '4':
            loadFlights(&counter, flights);
            break;
        case '5':
            exit(0); /*terminates the program*/
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

void print_menu(void)
{
    printf("\n"
           "1. add a flight\n"
           "2. display all flights to a destination\n"
           "3. save the flights to the database file\n"
           "4. load the flights from the database file\n"
           "5. exit the program\n"
           "Enter choice (number between 1-5)>\n");
}

/*******************************************************************************
 * isValidFlightCode Function: checks whether the flight code is valid in
 * accordance to the rules defined by PLATE 
 * inputs:
 * - flightcode[]: char array of struct flight flightcode
 * outputs:
 * - boolean whether code is valid or not (true/false)
*******************************************************************************/

bool isValidFlightCode(char flightcode[])
{
    int i = 0;
    for (i = 0; i < strlen(flightcode); i++) /*code can't contain spaces*/
    {
        if (flightcode[i] == ' ')
            return false;
    }

    i = 0;
    if (!(strlen(flightcode) > 6)) /*code can't be longer than 6 chars*/
    {
        if ((flightcode[0] >= 'A' && flightcode[0] <= 'Z') &&
            (flightcode[1] >= 'A' && flightcode[1] <= 'Z'))
        { /*First 2 chars must be upper case*/
            for (i = 2; i < strlen(flightcode); i++)
            { /*Every char afterwards is a numeral*/
                if (flightcode[i] >= '0' && flightcode[i] <= '9')
                {
                    if (i == strlen(flightcode) - 1)
                    {
                        return true; /*if all chars is valid*/
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}

/*******************************************************************************
 * addFlight Function: Adds a new flight to flights[] including flightcode, 
 * arrival/departure dates and citycode. 
 * inputs:
 * - counter: amount of flights stored in flights[] so far as a pointer
 * - flights[]: array of flights of type flight_t
 * outputs:
 * - none
*******************************************************************************/

void addFlight(int *counter, flight_t flights[])
{
    bool valid = true;    /*used for input validation. Assumed true*/
    bool read = false;    /*checks whether fgets has read userinput yet*/
    bool correct = false; /*extra input validation*/
    if (*counter < 5)     /*checks that there's less than 5 flights stored*/
    {
        int i = *counter;                 /*deference counter and store in i*/
        strcpy(flights[i].flightcode, "www"); /*dummy assignment*/
        while (!correct)
        {
            char *code = malloc(2000); /*allocate memory for variable*/
            /* size is large to account for unexpected large inputs */

            /* Ask user for code. */
            if (read == true)
            {
                printf("Enter flight code>\n");
            }
            /* Get the code restricted in size*/
            fgets(code, 2000, stdin);

            /* Remove trailing line if present. */
            if ((strlen(code) > 0) && (code[strlen(code) - 1] == '\n'))
                code[strlen(code) - 1] = '\0';

            if (isValidFlightCode(code)) /*calls function and passes code*/
            {
                correct = true;                      /*validates code*/
                strcpy(flights[i].flightcode, code); /*adds code to array*/
                flights[i].flightcode[strlen(flights[i].flightcode)] = '\0';
            }

            free(code); /*free memory*/
            if (!(isValidFlightCode(flights[i].flightcode)) && correct == false)
            { /*if invalid user will have to re-enter code*/
                if (read == true)
                {
                    printf("Invalid input\n");
                }
            }
            read = true;
        }
        valid = false;
        printf("Enter departure info for the flight leaving SYD.\n");
        while (valid == false) /*asks to enter dates/time until input is considered valid*/
        {
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &flights[i].departure_dt.month,
                  &flights[i].departure_dt.day, &flights[i].departure_dt.hour,
                  &flights[i].departure_dt.minute);
            valid = true;
            if (flights[i].departure_dt.month <= 0 ||
                flights[i].departure_dt.month > 12 ||
                flights[i].departure_dt.day <= 0 ||
                flights[i].departure_dt.day > 31 ||
                flights[i].departure_dt.hour < 0 ||
                flights[i].departure_dt.hour > 23 ||
                flights[i].departure_dt.minute < 0 ||
                flights[i].departure_dt.minute > 59)
            { /*checks that input conforms with defined rules*/
                valid = false;
                printf("Invalid input\n");
            }
        }

        read = false;
        valid = false;
        while (valid == false)
        {
            char *arrival_cityTEMP = malloc(2000); /*allocate memory for variable*/

            /*if (read == true)*/
            printf("Enter arrival city code>\n");

            scanf("%s", arrival_cityTEMP);

            /*fgets(arrival_cityTEMP, 2000, stdin);*/
            /*if (read == true)*/
            valid = true;
            /* Remove trailing newline, if there is. */
            if ((strlen(arrival_cityTEMP) > 0) &&
                (arrival_cityTEMP[strlen(arrival_cityTEMP) - 1] == '\n'))
                arrival_cityTEMP[strlen(arrival_cityTEMP) - 1] = '\0';

            if (strlen(arrival_cityTEMP) > 3 && valid == true)
            { /*adjust if strlen is greater than 3*/

                int k = 0;
                for (k = 0; k < 3; k++)
                {
                    flights[i].arrival_city[k] = arrival_cityTEMP[k];
                }
                flights[i].arrival_city[3] = '\0';
            }
            else
            {
                strcpy(flights[i].arrival_city, arrival_cityTEMP);
                flights[i].arrival_city[strlen(flights[i].arrival_city)] = '\0';
            }
            free(arrival_cityTEMP); /*free memory*/
            read = true;
        }
        valid = false;
        printf("Enter arrival info.\n");
        while (valid == false) /*asks to enter dates/time until input is considered valid*/
        {

            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &flights[i].arrival_dt.month,
                  &flights[i].arrival_dt.day, &flights[i].arrival_dt.hour,
                  &flights[i].arrival_dt.minute);
            valid = true;
            if (flights[i].arrival_dt.month <= 0 ||
                flights[i].arrival_dt.month > 12 ||
                flights[i].arrival_dt.day <= 0 ||
                flights[i].arrival_dt.day > 31 ||
                flights[i].arrival_dt.hour < 0 ||
                flights[i].arrival_dt.hour > 23 ||
                flights[i].arrival_dt.minute < 0 ||
                flights[i].arrival_dt.minute > 59)
            { /*checks that input conforms with defined rules*/
                valid = false;
                printf("Invalid input\n");
            }
        }
        i++; /*increments counter and sets it to the pointer*/
        *counter = i;
    }
    else
    {
        printf("Cannot add more flights - memory full\n");
        /*if counter is greater than 5*/
    }
}

/*******************************************************************************
 * displayFlights Function: displays all flights details based upon user input
 * inputs:
 * - counter: amount of flights stored in flights[] so far as a pointer
 * - flights[]: array of flights of type flight_t
 * outputs:
 * - none
*******************************************************************************/

void displayFlights(int *counter, flight_t flights[])
{
    char codeSelection[MAX_CITYCODE_LEN + 1]; /*char array for userinput */
    int i = 0;
    printf("Enter arrival city code or enter * to show all destinations>\n");
    scanf("%s", codeSelection);
    /*displays all flights for * input */
    if (codeSelection[0] == '*' && *counter > 0)
    {
        printf("Flight Origin          Destination\n");
        printf("------ --------------- ---------------\n");
        while (i <= *counter - 1)
        { /*prints all flights incrementing i*/
            printf("%-6s %s %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n",
                   flights[i].flightcode, "SYD", flights[i].departure_dt.month,
                   flights[i].departure_dt.day, flights[i].departure_dt.hour,
                   flights[i].departure_dt.minute, flights[i].arrival_city,
                   flights[i].arrival_dt.month, flights[i].arrival_dt.day,
                   flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
            i++;
        }
    }
    else if (*counter > 0) /*else that user inputs anything besides * */
    {
        bool alreadyFound = false; /*checks whether header has been printed*/
        for (i = 0; i <= *counter - 1; i++)
        { /*for each flight stored check if code matches iteratively*/
            if (strcmp(flights[i].arrival_city, codeSelection) == 0)
            {
                if (alreadyFound == false)
                { /*prints header if it hasn't been printed yet*/
                    printf("Flight Origin          Destination\n");
                    printf("------ --------------- ---------------\n");
                    alreadyFound = true;
                }
                /*prints flights that match the codeSelection*/
                printf("%-6s %s %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n",
                       flights[i].flightcode, "SYD", flights[i].departure_dt.month,
                       flights[i].departure_dt.day, flights[i].departure_dt.hour,
                       flights[i].departure_dt.minute, flights[i].arrival_city,
                       flights[i].arrival_dt.month, flights[i].arrival_dt.day,
                       flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
            }
        }
        if (alreadyFound == false) /*no flights found if this flag isn't true*/
        {
            printf("No flights\n");
        }
    }
    else
    {
        printf("No flights\n");
    }
}

/*******************************************************************************
 * saveFlights Function: saves all flights currently stored in flights[]
 * into a database file
 * inputs:
 * - counter: amount of flights stored in flights[] so far as a pointer
 * - flights[]: array of flights of type flight_t
 * outputs:
 * - none
*******************************************************************************/

void saveFlights(int *counter, flight_t flights[])
{

    FILE *fp;
    fp = fopen(DB_NAME, "w"); /*open the database for writing*/
    if (fp != NULL)           /*checks whether file can be read or not*/
    {
        int i = 0;
        while (i <= *counter - 1)
        /*for each flight currently stored in flights[]*/
        {
            fprintf(fp, "%s %d %d %d %d %s %d %d %d %d\n", flights[i].flightcode,
                    flights[i].departure_dt.month, flights[i].departure_dt.day,
                    flights[i].departure_dt.hour, flights[i].departure_dt.minute,
                    flights[i].arrival_city, flights[i].arrival_dt.month,
                    flights[i].arrival_dt.day, flights[i].arrival_dt.hour,
                    flights[i].arrival_dt.minute);
            i++;
            /*write flight to database file as text and increment counter*/
        }
        fclose(fp); /*close the file*/
    }
}

/*******************************************************************************
 * loadFlights Function: load all flights currently stored in database
 * and overwrite and store into flights[] array/structs
 * inputs:
 * - counter: amount of flights stored in flights[] so far as a pointer
 * - flights[]: array of flights of type flight_t
 * outputs:
 * - none
*******************************************************************************/

void loadFlights(int *counter, flight_t flights[])
{
    FILE *fp;
    fp = fopen(DB_NAME, "r"); /*open file for reading*/

    if (fp == NULL)
    {
        printf("Read error\n"); /*checks that file can be read*/
    }
    else
    {
        *counter = 0;      /*resets the counter to 0 as flights[] is being overridden*/
        int lineCount = 0; /*number of lines that have been read*/
        int i = 0;         /*temp variable for *counter (same functionality)*/
        /*line count ensures it doesn't read more than 5 flights loop*/
        while (MAX_NUM_FLIGHTS > i && lineCount < MAX_NUM_FLIGHTS)
        {
            if (fscanf(fp, "%s %d %d %d %d %s %d %d %d %d\n", flights[i].flightcode,
                       &flights[i].departure_dt.month, &flights[i].departure_dt.day,
                       &flights[i].departure_dt.hour, &flights[i].departure_dt.minute, flights[i].arrival_city,
                       &flights[i].arrival_dt.month, &flights[i].arrival_dt.day, &flights[i].arrival_dt.hour,
                       &flights[i].arrival_dt.minute) == 10)
            /*checks that all items have been read by fscanf*/
            {
                i++; /*increment counter*/
            }
            lineCount++; /*increment the line counter*/
        }
        *counter = i; /*assign counter to i*/
        fclose(fp);   /*close the file*/
    }
}