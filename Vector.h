#include "Int.h"
#include "Bool.h"

#include <utility>
#include <iostream>
#include <string_view>

namespace types {
    struct VectorType;
}

template<long I, class E>
struct IdxElement
{
    constexpr static long Idx = I;
    using El = E;
};

template<class...> struct Vector;

template<class, class...> struct VectorImpl;

template<long...Is, class...Els>
struct VectorImpl<std::index_sequence<Is...>, Els...> : public IdxElement<Is, Els>... {
    using This = VectorImpl<std::index_sequence<Is...>, Els...>;

    using Count = Int<sizeof...(Els)>;
    using Empty = Eq<Count, Int<0>>;

    template<long Idx, class Res>
    static IdxElement<Idx, Res> NthImpl(IdxElement<Idx, Res> *);

    using MakeVector = Vector<Els...>;


    static void Print(std::string_view delimeter = "\n")
    {
        long last = Count::value - 1;
        (..., (Els::Print(Is == last ? "" : ", ")));
        std::cout << delimeter;
    }
};


template<class...Els>
struct Vector
{
    using Type = types::VectorType;
    using This = Vector<Els...>;

    using Impl = VectorImpl<std::index_sequence_for<Els...>, Els...>;
    using Count = typename Impl::Count;
    using Empty = False;
    using NotEmpty = True;

    template<class Idx, std::enable_if_t<Lt<Idx, Count>::value, int> = 0>
    using Nth = typename decltype(Impl::template NthImpl<Idx::value>(reinterpret_cast<Impl *>(0)))::El;

    template<class First, class...Others>
    using Append = Vector<Els..., First, Others...>;

    using Peek = decltype ((Els{}, ...));

    using First = Nth<Int<0>>;


    template<long I, long From, class Head, class...Tail> 
    struct FromImpl
    {
        using type = std::conditional_t<(I >= From), Vector<Head, Tail...>, FromImpl<I + 1, From, Tail...>>; 
    };

    template<long I, long From, class Last>
    struct FromImpl<I, From, Last>
    {
        using type = std::conditional_t<(I >= From), Vector<Last>, Vector<>>;
    };

    template<class Idx>
    using FromNth = typename FromImpl<0, Idx::value, Els...>::type;
    
    template<class Curr, long To, class Head, class...Tail>
    struct ToImpl
    {
        using type = std::conditional_t<Curr::Count::value < To, ToImpl<typename Curr::template Append<Head>, To, Tail...>, Curr>;
    };

    template<class Curr, long To, class Last>
    struct ToImpl<Curr, To, Last>
    {
        using type = std::conditional_t<Curr::Count::value < To, typename Curr::template Append<Last>, Curr>;
    };

    template<class Idx>
    using ToNth = ToImpl<Vector<>, Idx::value, Els...>;

    static void Print(std::string_view delimeter = "\n")
    {
        std::cout << "[ ";
        Impl::Print("");
        std::cout << " ]" << delimeter;
    }
};

template<>
struct Vector<>
{
    using Count = Int<0>;
    using Empty = True;
    using NotEmpty = False;

    template<class Idx>
    using Nth = void;
    
    using Peek = void;

    template<class First, class...Others>
    using Append = Vector<First, Others...>;

    using First = void;


    static void Print(std::string_view delimeter = "\n")
    {
        std::cout << "[ ]" << delimeter;
    }
};