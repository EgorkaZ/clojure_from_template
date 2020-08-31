#pragma once

#include "Bool.h"
#include "Int.h"

#define BINARY_OP(name) \
template<class Lhs, class Rhs> \
using name = typename Lhs::template name<Rhs>;

BINARY_OP(And)
BINARY_OP(Or)

BINARY_OP(Eq)
BINARY_OP(Ne)
BINARY_OP(Lt)
BINARY_OP(Gt)
BINARY_OP(Le)
BINARY_OP(Ge)

#undef BINARY_OP