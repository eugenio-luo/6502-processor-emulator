#ifndef NES_LOG_H
#define NES_LOG_H

#ifndef LOG_DIR_PATH
#define LOG_DIR_PATH   NULL
#endif

#define PATH_MAX   255

void log_init(const char *log_path);
void log_quit(void);

/*
  log_write: for normal behaviour.
  
  log_error: for system breaking errors, the emulation halts. 
 
  log_warning: for non system breaking errors or inconsistencies, 
               the emulation does NOT halt. In testing mode, the
               emulation halts.
*/

void log_write(const char *fmt, ...);
void log_error(const char *fmt, ...);
void log_warning(const char *fmt, ...);

#endif
