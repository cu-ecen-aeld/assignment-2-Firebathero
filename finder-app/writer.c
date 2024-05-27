#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <string>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *writestr = argv[2];

    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    int fd = creat(filename, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Error opening file '%s': %s", filename, strerror(errno));
        closelog();
        return 1;
    }

    ssize_t bytes_written = write(fd, writestr, strlen(writestr));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Error writing to file '%s': %s", filename, strerror(errno));
        close(fd);
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing '%s' to '%s'", writestr, filename);

    if (close(fd) == -1) {
        syslog(LOG_ERR, "Error closing file '%s': %s", filename, strerror(errno));
        closelog();
        return 1;
    }

    closelog();

    return 0;
}


/* Params
 *
 * 1) full path to a file (including filename) writefile
 * 2) the text string which will be written to the file
    
    Exits with value 1 error and print statements if any of the arguments above were not specified

*   You can assume the directory is created by the caller.

    Core Functionality:
    -------------------
    Creates a new file with name and path writefile with content writestr, 
    overwrites existing file and creates the path if it doesn’t exist. 

    Exits with value 1 and error print statement if the file could not be created.
*   
*   Logging
*   -------
*   DEBUG LOG "Writing <string> to <file> "
*   ERROR LOG any unexpected errors
*
*/
