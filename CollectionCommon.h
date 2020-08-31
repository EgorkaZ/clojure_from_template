#pragma once

#include "Bool.h"
#include "Int.h"

namespace types {
    struct EmptyCollType;
}

template<template<class...>class CollType>
struct EmptyColl
{
    using Type = types::EmptyCollType;
    using This = EmptyColl;
    using First = void;
    using Rest = void;

    using Count = Int<0>;
    using Empty = True;
    using NotEmpty = False;

    template<class New>
    using Cons = CollType<New>;

    template<class Idx>
    using Nth = void;

    template<class, class Curr>
    using IndexOf = Curr;


    static void Print(std::string_view delimeter = "")
    {
        std::cout << delimeter;
    }
};


template <template<class...> class CollType, class...Elements> struct CreateCollAT;

template <template<class...> class CollType, class... Elements>
using CreateColl = typename CreateCollAT<CollType, Elements...>::type;


template <template<class...> class CollType, class Head, class...Tail>
struct CreateCollAT<CollType, Head, Tail...>
{
    using rest = CreateColl<CollType, Tail...>;
    using type = typename rest::template Cons<Head>;
};

template<template<class...> class CollType>
struct CreateCollAT<CollType>
{
    using type = EmptyColl<CollType>;
};