#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "log.h"

#ifdef TEST

#include "test.h"

#endif

static FILE *log_file = NULL;

void
log_init(const char *log_dir_path)
{
        char *log_file_path = malloc(PATH_MAX);
        time_t now = time(NULL);
        snprintf(log_file_path, PATH_MAX, "%slog - %.24s.log", log_dir_path, ctime(&now));
        
        log_file = fopen(log_file_path, "w");
        
        /* if the log file fails to open, the emulator will continue but
           it isn't going to log anything */
        if (!log_file)
                log_warning("[log.c: log_init] failed to open log file: %s\n",
                            strerror(errno));
        
        free(log_file_path);
}

void
log_quit(void)
{
        fclose(log_file);
}

static void 
log_vfprintf(FILE *stream, const char *initial, const char *fmt, va_list args)
{
        if (initial)
                fprintf(stream, "%s", initial);

        vfprintf(stream, fmt, args);
}

void
log_write(const char *fmt, ...)
{
        va_list args, copy;
        va_start(args, fmt);
        va_copy(copy, args);

        log_vfprintf(stdout, NULL, fmt, args);
        if (log_file)
                log_vfprintf(log_file, NULL, fmt, copy);
       
        va_end(args);
        va_end(copy);
}

/* some tests are made deliberately to cause an error, so they shouldn't make the emulator 
   halts, instead the system should continue execution, a hard reset is advisable after an 
   error test as the emulation state isn't reliable anymore */
void
log_error(const char *fmt, ...)
{
        (void) fmt;
        va_list args, copy;
        va_start(args, fmt);
        va_copy(copy, args);

#ifdef TEST

        test_set_err(1);
        const char *initial = NULL;

#else

        const char *initial = RED BOLD "[ERROR]" RESET;

#endif
        
        log_vfprintf(stderr, initial, fmt, args);
        if (log_file)
                log_vfprintf(log_file, initial, fmt, copy);
        va_end(args);
        va_end(copy);

#ifndef TEST

        exit(1);

#endif
}

/* when the system is in strict mode it's important that the warnings are treated
   as errors, while when the system is in normal mode if it isn't a system breaking error
   it should be logged only so the system can continue to run instead of halting */
void
log_warning(const char *fmt, ...)
{
        va_list args;
        va_start(args, fmt);

#ifdef STRICT

        log_error(fmt, args);

#else
        
        va_list copy;
        va_copy(copy, args);

        log_vfprintf(stderr, YELLOW BOLD "[WARNING]" RESET, fmt, args);
        if (log_file)
                log_vfprintf(log_file, YELLOW BOLD "[WARNING]" RESET, fmt, copy);

        va_end(args);
        va_end(copy);

#endif
}
