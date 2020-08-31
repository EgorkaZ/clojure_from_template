#include <iostream>

#include "Bool.h"
#include "Int.h"
#include "Operators.h"
#include "List.h"


template<class C, class Type>
using Isa = Bool<std::is_same_v<typename C::Type, Type>>;

namespace types {
    struct VectorType;
}

template<class, class> struct Vector;

template<class Last, class FirstPart = EmptyColl<Vector>>
struct Vector
{
    using Type = types::VectorType;
    using This = Vector<Last, FirstPart>;
    using Peek = Last;
    using Pop = FirstPart;

    using Count = Int<Pop::Count::value + 1>;
    using Empty = False;
    using NotEmpty = True;

    template<class New>
    using Cons = Vector<New, This>;

    template<class Idx>
    using Nth = IfThen<Eq<typename Count::template Sub<Idx>, Int<1>>, Peek, typename Pop::template Nth<Idx>>;

    template<class Searched, class Curr = Int<0>>
    using IndexOf = IfThen<Eq<Searched, Peek>, typename Pop::Count, typename Pop::template IndexOf<Searched, typename Curr::template Add<Int<1>>>>;


    static void Print(std::string_view delimeter = "")
    {
        constexpr std::string_view comma = Isa<Pop, types::EmptyCollType>::value ? "" : ", ";
        Pop::Print(comma);
        Peek::Print(delimeter);
    }
};

template<class Curr, class...Elements> struct CreateVectorAT;
template<class...Elements>
using CreateVector = typename CreateVectorAT<EmptyColl<Vector>, Elements...>::type;

template<class Curr, class Head, class...Tail>
struct CreateVectorAT<Curr, Head, Tail...>
{
    using type = typename CreateVectorAT<typename Curr::template Cons<Head>, Tail...>::type;
};

template<class Curr, class Last>
struct CreateVectorAT<Curr, Last>
{
    using type = typename Curr::template Cons<Last>;
};

#define EXPECT_EQ(lhs, rhs) static_assert((lhs) == (rhs))

int main() {
    using l = CreateList<Int<0>, Int<1>, Int<2>>;

    using zero = Int<0>;
    using one = Int<1>;
    using two = Int<2>;
    using three = Int<3>;
    using four = Int<4>;

    EXPECT_EQ(l::Count::value, 3);
    EXPECT_EQ(l::Nth<two>::value, 2);

    using l1 = l::Cons<Int<-1>>::Cons<Int<-2>>;

    EXPECT_EQ(l1::Nth<one>::value, -1);
    EXPECT_EQ(l1::IndexOf<one>::value, 3);

    l1::Print("\n");

    using v = CreateVector<zero, one, two>;
    v::Nth<zero>::Print(", ");
    v::Nth<one>::Print(", ");
    v::Nth<two>::Print("\n");

    EXPECT_EQ(v::Count::value, 3);
    EXPECT_EQ(v::Nth<two>::value, 2);

    using v1 = v::Cons<Int<3>>::Cons<Int<4>>;

    v1::Print("\n");

    EXPECT_EQ(v1::Nth<three>::value, 3);
    EXPECT_EQ(v1::IndexOf<four>::value, 4);
    
    return 0;
}
