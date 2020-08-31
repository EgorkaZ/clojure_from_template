#pragma once

#include "Bool.h"

namespace types {
    struct IntType;
}

template<long Val> 
struct Int
{
    using Type = types::IntType;

    constexpr static int value = Val;
    
    template<class Other>
    using Add = Int<value + Other::value>;
    
    template<class Other>
    using Sub = Int<value - Other::value>;
    
    template<class Other>
    using Mul = Int<value * Other::value>;
    
    template<class Other>
    using Div = Int<value / Other::value>;
    
    using Neg = Int<-value>;


    static void Print(std::string_view delimeter = "")
    {
        std::cout << value << delimeter;
    }
    
#define COMPARISON_OP(name, op) \
template<class Other> \
using name = Bool<(value op Other::value)>;

#include "comparison.inl"
};