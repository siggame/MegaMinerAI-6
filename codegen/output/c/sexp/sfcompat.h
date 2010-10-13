#ifndef SFCOMPAT_H
#define SFCOMPAT_H

#include "sexp.h"

typedef Sexp sexp_t;

void destroy_sexp(Sexp*);

Sexp* extract_sexpr(char*);

int sexp_list_length(Sexp*);

#endif