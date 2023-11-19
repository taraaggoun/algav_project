#pragma once

/* -------------------------------- INCLUDES -------------------------------- */

#include <stdio.h>

#include "../include/uint128.h"

/* -------------------------------- DEFINES --------------------------------- */

#define BUF_UINT128_LEN_B16 36

#define BUF_UINT128_LEN_B10 38

#define PATHMAX 2048

/* -------------------------------- FUNCTIONS ------------------------------- */

void argument_manager(int argc, char *argv[], char *pathname);

int read_uint128(FILE *file, uint128_t *cle, char *buf);

/* -------------------------------------------------------------------------- */
