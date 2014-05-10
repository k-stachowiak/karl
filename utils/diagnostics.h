#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <cstdio>
#include <cassert>

#define DIAG_TRACE std::fprintf(stderr, "In function [%s] %s:%d\n", __func__, __FILE__, __LINE__)

#define DIAG_MESSAGE(...) std::fprintf(stderr, __VA_ARGS__)

#define DIAG_ERROR_EXIT(...)\
	do {\
		std::fprintf(stderr, __VA_ARGS__);\
		exit(1);\
	} while(0)

#define DIAG_ASSERT(macro_arg_condition) std::assert(macro_arg_condition)

#endif
