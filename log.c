#include "log.h"

/**
 * @brief Gets the current time
 * 
 * @return Returns a Struct timeval
*/
struct timeval gettingTime() {
    struct timeval time;
    gettimeofday(&time,NULL);
    return time;
}

/**
 * @brief Outputs the command log to the Register File
 * 
 * @param regFile Pointer to a file to be written with the logs
 *        start Start time of execution
 *        cmd Command given by the user
 * 
 * @return Returns 0 upon success, non-zero otherwise
*/
int gettingRegFileCommand(FILE *regFile, struct timeval start, char *cmd)
{
    char act[256] = "COMMAND ";
    strcat(act, cmd);

    //Adding register to the log file
    if (addLog(start, gettingTime(), act, regFile))
    {
        printf("Failed printing to log file in gettingRegFileCommand\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Outputs the SIGNAL USR1 log to the Register File
 * 
 * @param regFile Pointer to a file to be written with the logs
 *        start Start time of execution
 * 
 * @return Returns 0 upon success, non-zero otherwise
*/
int gettingRegFileSignalOne(FILE *regFile, struct timeval start)
{
    // Setting up char array act
    char act[256] = "SIGNAL USR1";

    //Adding register to the log file
    if (addLog(start, gettingTime(), act, regFile))
    {
        printf("Failed printing to log file in gettingRegFileSignalOne\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Outputs the SIGNAL USR2 log to the Register File
 * 
 * @param regFile Pointer to a file to be written with the logs
 *        start Start time of execution
 * 
 * @return Returns 0 upon success, non-zero otherwise
*/
int gettingRegFileSignalTwo(FILE *regFile, struct timeval start)
{
    //Setting up char array act
    char act[256] = "SIGNAL USR2";

    //Adding register to the log file
    if (addLog(start, gettingTime(), act, regFile))
    {
        printf("Failed printing to log file in gettingRegFileSignalTwo\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Outputs the ANALIZED FILE log to the Register File
 * 
 * @param regFile Pointer to a file to be written with the logs
 *        start Start time of execution
 * 
 * @return Returns 0 upon success, non-zero otherwise
*/
int gettingRegFileAnalized(char *file, FILE *regFile, struct timeval start)
{
    //Setting up char array act
    char act[256] = "ANALIZED ";
    strcat(act, file);

    //Adding register to the log file
    if (addLog(start, gettingTime(), act, regFile))
    {
        printf("Failed printing to log file in gettingRegFileAnalized\n");
        return 1;
    }

    return 0;
}

/**
 * @brief Outputs the FINISHED PROCESS EXECUTION  log to the Register File
 * 
 * @param regFile Pointer to a file to be written with the logs
 *        start Start time of execution
 * 
 * @return Returns 0 upon success, non-zero otherwise
*/
int gettingRegFileFinished(FILE *regFile, struct timeval start)
{
    //Setting up char array act
    char act[256] = "Finished process execution";

    //Adding register to the log file
    if (addLog(start, gettingTime(), act, regFile))
    {
        printf("Failed printing to log file in gettingRegFileFinished\n");
        return 1;
    }

    return 0;
}

/**
* @brief Adds a log at the end of a file
*
* @param start  Initial instant
*        end    Final instant
*        act    Description
*        output Output file's name
*
* @return Return zero upon sucess, non-zero otherwise
*/
int addLog(struct timeval start, struct timeval end, char act[], FILE *file_output)
{
    double inst = (double) (end.tv_usec - start.tv_usec) / 1000000 + (double)(end.tv_sec - start.tv_sec);
    char output[256];

    sprintf(output, "%-8.2f", inst*1000);

    strcat(output, " - ");

    char tmp[256];
    sprintf(tmp, "%d", getpid());
    strcat(output, tmp);
    strcat(output, " - ");

    strcat(output, act);
    strcat(output, "\n");

    fflush(file_output);
    fprintf(file_output, "%s", output);
    fflush(file_output);
    
    return 0;
}