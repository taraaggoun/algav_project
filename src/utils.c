/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/utils.h"

#include "../include/uint128.h"

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

bool is_inf(tree_value v1, tree_value v2, type t) {
	if (t == uint128) {
		return inf(v1.u128, v2.u128);
	}
	// pas implementé pour l'instant
	return true;
}

bool is_eg(tree_value v1, tree_value v2, type t) {
	if (t == uint128) {
		return eg(v1.u128, v2.u128);
	}
	// pas implementé pour l'instant
	return true;
}

/* -------------------------------------------------------------------------- */