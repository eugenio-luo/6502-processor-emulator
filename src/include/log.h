#ifndef NES_LOG_H
#define NES_LOG_H

#ifndef LOG_DIR_PATH
#define LOG_DIR_PATH   NULL
#endif

#define PATH_MAX   255

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

void log_init(const char *log_path);
void log_quit(void);

/*
  log_write: for normal behaviour.
  
  log_error: for system breaking errors, the emulation halts. 
 
  log_warning: for non system breaking errors or inconsistencies, 
               the emulation does NOT halt. In strict mode, the
               emulation halts.
*/

void log_write(const char *fmt, ...);
void log_error(const char *fmt, ...);
void log_warning(const char *fmt, ...);

#endif
