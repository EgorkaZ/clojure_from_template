#pragma once

#include <type_traits>

namespace types {
    struct BoolType;
}

template<bool Val>
struct Bool
{
    using Type = types::BoolType;

    constexpr static bool value = Val;
    
    using Not = Bool<!value>;
    
    template<class Other>
    using And = Bool<value && Other::value>;
    
    template<class Other>
    using Or = Bool<value || Other::value>;

    template<class Other>
    using Eq = Bool<value == Other::value>;

    template<class Other>
    using Xor = Bool<value != Other::value>;


    static void Print(std::string_view delimeter = "")
    {
        std::cout << (value ? "true" : "false") << delimeter;
    }
};

using True = Bool<true>;
using False = Bool<false>;



template<bool Val>
struct ConditionalAT
{
    using type = True;
};
template<>
struct ConditionalAT<false>
{
    using type = False;
};

template<bool Val>
using Conditional = typename ConditionalAT<Val>::type;


template<class Cond, class Then, class Else>
using IfThen = std::conditional_t<Cond::value, Then, Else>;