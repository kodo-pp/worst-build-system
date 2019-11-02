struct Nil { };



template <typename Element, typename List>
struct Cons
{
    using Head = Element;
    using Tail = List;
};



template <typename List1, typename List2>
struct Cat_
{
    using Type = Cons<typename List1::Head, typename Cat_<typename List1::Tail, List2>::Type>;
};

template <typename List2>
struct Cat_<Nil, List2>
{
    using Type = List2;
};

template <typename List1, typename List2>
using Cat = typename Cat_<List1, List2>::Type;



template <typename List>
struct CatList_
{
    using Type = Cat<typename List::Head, typename CatList_<typename List::Tail>::Type>;
};

template <>
struct CatList_<Nil>
{
    using Type = Nil;
};

template <typename List>
using CatList = typename CatList_<List>::Type;


template <char c>
struct Char
{
    static constexpr char value = c;
};



template <typename Head, typename... Tail>
struct Mklist_
{
    using Type = Cons<Head, typename Mklist_<Tail...>::Type>;
};

template <typename Head>
struct Mklist_<Head>
{
    using Type = Cons<Head, Nil>;
};

template <typename... Args>
using Mklist = typename Mklist_<Args...>::Type;



template <typename T, typename U>
struct Eq
{
    static constexpr bool value = false;
};

template <typename T>
struct Eq<T, T>
{
    static constexpr bool value = true;
};

template <typename T, typename U>
constexpr bool eq = Eq<T, U>::value;



template <typename Haystack, typename Needle>
struct Startswith
{
    static constexpr bool value = eq<typename Haystack::Head, typename Needle::Head>;
};

template <typename Haystack>
struct Startswith<Haystack, Nil>
{
    static constexpr bool value = true;
};

template <typename Needle>
struct Startswith<Nil, Needle>
{
    static constexpr bool value = false;
};

template <>
struct Startswith<Nil, Nil>
{
    static constexpr bool value = true;
};

template <typename Haystack, typename Needle>
constexpr bool starts_with = Startswith<Haystack, Needle>::value;



template <typename Accum, typename List>
struct ReverseCons_
{
    using Type = typename ReverseCons_<Cons<typename List::Head, Accum>, typename List::Tail>::Type;
};

template <typename Accum>
struct ReverseCons_<Accum, Nil>
{
    using Type = Accum;
};

template <typename List>
using Reverse = typename ReverseCons_<Nil, List>::Type;



template <typename Haystack, typename Needle>
constexpr bool ends_with = starts_with<Reverse<Haystack>, Reverse<Needle>>;



template <bool cond, typename True, typename False>
struct IfElse_
{
    using Type = False;
};

template <typename True, typename False>
struct IfElse_<true, True, False>
{
    using Type = True;
};

template <bool cond, typename True, typename False>
using IfElse = typename IfElse_<cond, True, False>::Type;



template <typename Output_, typename Source_, typename Flags_>
struct Object
{
    using Output = Output_;
    using Source = Source_;
    using Flags = Cat<
        Mklist<
            Char<'-'>,
            Char<'c'>,
            Char<' '>
        >,
        Flags_
    >;
};

template <typename Output_, typename Objects_, typename Flags_>
struct Executable
{
    using Output = Output_;
    using Objects = Objects_;
    using Flags = Flags_;
};



template <typename Source>
using GetCompiler = IfElse<
    ends_with<Source, Mklist<Char<'.'>, Char<'c'>>>,
    Mklist<
        Char<'c'>,
        Char<'c'>
    >,
    Mklist<
        Char<'c'>,
        Char<'+'>,
        Char<'+'>
    >
>;



template <typename Object>
using CompileObject = CatList<
    Mklist<
        GetCompiler<typename Object::Source>,
        Mklist<
            Char<' '>,
            Char<'-'>,
            Char<'o'>,
            Char<' '>
        >,
        typename Object::Output,
        Mklist<Char<' '>>,
        typename Object::Flags,
        Mklist<Char<' '>>,
        typename Object::Source,
        Mklist<Char<'\n'>>
    >
>;



template <typename Objects>
struct CompileObjects_
{
    using Type = Cat<
        CompileObject<typename Objects::Head>,
        typename CompileObjects_<typename Objects::Tail>::Type
    >;
};

template <>
struct CompileObjects_<Nil>
{
    using Type = Nil;
};

template <typename Objects>
using CompileObjects = typename CompileObjects_<Objects>::Type;



template <typename Separator, typename Sequence>
struct Join_
{
    using Type = Cat<
        typename Sequence::Head,
        Cons<
            Separator,
            typename Join_<
                Separator,
                typename Sequence::Tail
            >::Type
        >
    >;
};

template <typename Separator>
struct Join_<Separator, Nil>
{
    using Type = Nil;
};

template <typename Separator, typename Sequence>
using Join = typename Join_<Separator, Sequence>::Type;



template <typename Objects>
struct GetOutputNames_
{
    using Type = Cons<
        typename Objects::Head::Output,
        typename GetOutputNames_<typename Objects::Tail>::Type
    >;
};

template <>
struct GetOutputNames_<Nil>
{
    using Type = Nil;
};

template <typename Objects>
using GetOutputNames = typename GetOutputNames_<Objects>::Type;



template <typename Target>
using Link = CatList<
    Mklist<
        Mklist<
            Char<'c'>,
            Char<'+'>,
            Char<'+'>,
            Char<' '>,
            Char<'-'>,
            Char<'o'>,
            Char<' '>
        >,
        typename Target::Output,
        Mklist<Char<' '>>,
        typename Target::Flags,
        Mklist<Char<' '>>,
        Join<Char<' '>, GetOutputNames<typename Target::Objects>>,
        Mklist<Char<'\n'>>
    >
>;


template <typename Target>
using Compile = Cat<CompileObjects<typename Target::Objects>, Link<Target>>;



extern "C" int putchar(int c);



template <typename List>
void print()
{
    putchar(List::Head::value);
    print<typename List::Tail>();
}

template <>
void print<Nil>()
{ }



int main()
{
    #include "wbs.build.cpp"
}
