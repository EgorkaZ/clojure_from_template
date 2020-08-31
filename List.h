#pragma once

#include "CollectionCommon.h"

namespace types {
    struct ListType;
}

template<class, class> class List;

template<class Head, class Tail = EmptyColl<List>>
struct List
{
    using Type = types::ListType;
    using This = List<Head, Tail>;
    using First = Head;
    using Rest = Tail;

    using Count = Int<Rest::Count::value + 1>;
    using Empty = Eq<Count, Int<0>>;
    using NotEmpty = Ne<Count, Int<0>>;

    template<class New>
    using Cons = List<New, This>;

    template<class Idx>
    using Nth = IfThen<Eq<Idx, Int<0>>, First, typename Rest::template Nth<typename Idx::template Sub<Int<1>>>>;

    template<class Searched, class Curr = Int<0>>
    using IndexOf = IfThen<Eq<Searched, First>, Curr, typename Rest::template IndexOf<Searched, typename Curr::template Add<Int<1>>>>;


    static void Print(std::string_view delimeter = "")
    {
        constexpr std::string_view comma = Eq<Count, Int<1>>::value ? "" : ", ";
        First::Print(comma);
        Rest::Print(delimeter);
    }
};

template<class...Elements>
using CreateList = CreateColl<List, Elements...>;