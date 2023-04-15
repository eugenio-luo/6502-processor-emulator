#ifndef NES_TEST_CHECK_H
#define NES_TEST_CHECK_H

#include <stdlib.h>

#include "log.h"
#include "test.h"

#define TEST_CHECK(N, M, CONDITION)                                     \
        if (CONDITION) {                                                \
                log_write(GREEN BOLD "[PASSED]"                         \
                          RESET " %s %d", N, M);                        \
                test_set_err(0);                                        \
        } else {                                                        \
                log_error(RED BOLD "[FAILED]"                           \
                          RESET " %s %d", N, M);                        \
                exit(1);                                                \
        }                                                               \
        
#endif
