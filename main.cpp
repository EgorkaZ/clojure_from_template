#include <iostream>
#include <utility>
#include <string_view>

#include "Bool.h"
#include "Int.h"
#include "Operators.h"
#include "List.h"
#include "Vector.h"


template<class C, class Type>
using Isa = Bool<std::is_same_v<typename C::Type, Type>>;

// template<class Curr, long I, long Size, template<class...> class Func, class...Vectors>
// struct MapImpl {
//     using type = std::conditional_t<I < Size,
//         typename MapImpl<typename Curr::template Append<Func<typename Vectors::template Nth<Int<I>>...>>, I + 1, Size, Func, Vectors...>::type, 
//         Curr>;
// };

template<class, template<class...> class, class...> struct MapImpl;

template<long...Is, template<class...> class Func, class... Vectors>
struct MapImpl<std::index_sequence<Is...>, Func, Vectors...>
{
    template<long Idx, class...VecPack>
    using NthVector = Func<typename VecPack::template Nth<Int<Idx>>...>;
    using type = Vector<NthVector<Is, Vectors...>...>;
};

template<class...Vectors>
struct GetSize
{
    static constexpr long Size = (Vectors::Count::value, ...);
    static_assert(((Vectors::Count::value) == ...), "vectors should have equal size");
};

template<template<class...> class Func, class Vector> 
struct MapvDelegator;

template<template<class...> class Func, class...Vectors>
struct MapvDelegator<Func, Vector<Vectors...>>{
    static constexpr long Size = (Vectors::Count::value,...);
    static_assert((Vectors::Count::value == ...), "vectors should have equal sizes");
    using type = typename MapImpl<std::make_index_sequence<Size>, Func, Vectors...>::type;
};

template<template<class...> class Func, class Arg>
using Mapv = typename MapvDelegator<Func, Arg>::type;

template<template<class...> class Func, class...Args>
using Map = typename MapImpl<std::make_index_sequence<GetSize<Args...>::Size>, Func, Args...>::type;

#define EXPECT_EQ(lhs, rhs) static_assert((lhs) == (rhs))

struct S
{
    type 
};

int main() {
    using l = CreateList<Int<0>, Int<1>, Int<2>>;

    int a = parse_int("");
    using zero = Int<0>;
    using one = Int<1>;
    using two = Int<2>;
    using three = Int<3>;
    using four = Int<4>;
    using five = Int<5>;

    EXPECT_EQ(l::Count::value, 3);
    EXPECT_EQ(l::Nth<two>::value, 2);

    using l1 = l::Cons<Int<-1>>::Cons<Int<-2>>;

    EXPECT_EQ(l1::Nth<one>::value, -1);
    EXPECT_EQ(l1::IndexOf<one>::value, 3);

    l1::Print("\n");

    using v = Vector<one, two, three>;
    v::Print("\n");

    using v1 = Vector<zero, one, two>;
    using v2 = Vector<one, two, three>;
    using matrix = Vector<v1, v2>;

    Mapv<Vector, matrix>::Print();
    Map<Vector, v1, v2>::Print();

    EXPECT_EQ(v::Nth<zero>::value, 1);
    EXPECT_EQ(v::Nth<two>::value, 3);
    EXPECT_EQ((v::Append<four, five>::Peek::value), 5);

    EXPECT_EQ(v::Peek::value, 3);


    
    return 0;
}
