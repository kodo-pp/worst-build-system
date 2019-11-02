using cxxflags = Mklist<
    Char<'-'>,
    Char<'s'>,
    Char<'t'>,
    Char<'d'>,
    Char<'='>,
    Char<'c'>,
    Char<'+'>,
    Char<'+'>,
    Char<'1'>,
    Char<'7'>,
    Char<' '>,
    Char<'-'>,
    Char<'W'>,
    Char<'a'>,
    Char<'l'>,
    Char<'l'>,
    Char<' '>,
    Char<'-'>,
    Char<'W'>,
    Char<'e'>,
    Char<'x'>,
    Char<'t'>,
    Char<'r'>,
    Char<'a'>,
    Char<' '>,
    Char<'-'>,
    Char<'p'>,
    Char<'e'>,
    Char<'d'>,
    Char<'a'>,
    Char<'n'>,
    Char<'t'>,
    Char<'i'>,
    Char<'c'>,
    Char<' '>,
    Char<'-'>,
    Char<'I'>,
    Char<'i'>,
    Char<'n'>,
    Char<'c'>,
    Char<'l'>,
    Char<'u'>,
    Char<'d'>,
    Char<'e'>,
    Char<' '>
>;

using main_o = Object<
    Mklist<
        Char<'m'>,
        Char<'a'>,
        Char<'i'>,
        Char<'n'>,
        Char<'.'>,
        Char<'o'>
    >,
    Mklist<
        Char<'s'>,
        Char<'r'>,
        Char<'c'>,
        Char<'/'>,
        Char<'m'>,
        Char<'a'>,
        Char<'i'>,
        Char<'n'>,
        Char<'.'>,
        Char<'c'>,
        Char<'p'>,
        Char<'p'>
    >,
    cxxflags
>;

using add5_o = Object<
    Mklist<
        Char<'a'>,
        Char<'d'>,
        Char<'d'>,
        Char<'5'>,
        Char<'.'>,
        Char<'o'>
    >,
    Mklist<
        Char<'s'>,
        Char<'r'>,
        Char<'c'>,
        Char<'/'>,
        Char<'a'>,
        Char<'d'>,
        Char<'d'>,
        Char<'5'>,
        Char<'.'>,
        Char<'c'>,
        Char<'p'>,
        Char<'p'>
    >,
    cxxflags
>;

using exe = Executable<
    Mklist<
        Char<'a'>,
        Char<'d'>,
        Char<'d'>,
        Char<'5'>
    >,
    Mklist<main_o, add5_o>,
    Nil
>;

print<Compile<exe>>();
