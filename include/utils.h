#pragma once

/* -------------------------------- INCLUDES -------------------------------- */

#include "binary_tree.h"

#include <stdbool.h>

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Renvoie si v1 inf a v2
**/
bool is_inf(tree_value v1, tree_value v2, type t);

/**
 * Renvoie si v1 est egale a v2
 **/
bool is_eg(tree_value v1, tree_value v2, type t);

/* -------------------------------------------------------------------------- */