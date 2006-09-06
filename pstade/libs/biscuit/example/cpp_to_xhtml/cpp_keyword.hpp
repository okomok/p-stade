#ifndef PSTADE_LIB_BISCUIT_EXAMPLE_CPP_KEYWORD_HPP
#define PSTADE_LIB_BISCUIT_EXAMPLE_CPP_KEYWORD_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>


namespace {
    
    using namespace pstade;
    using namespace biscuit;

    struct cpp_keyword0 :
        or_<
            chseq<'a','n','d'>,
            chseq<'a','n','d','_','e','q'>,
            chseq<'b','i','t','a','n','d'>,
            chseq<'b','i','t','o','r'>,
            chseq<'c','o','m','p','l'>,
            chseq<'n','o','t'>,
            chseq<'o','r'>,
            chseq<'n','o','t','_','e','q'>,
            chseq<'c','a','s','e'>,
            chseq<'d','e','f','a','u','l','t'>
        >
    { };

    struct cpp_keyword1 :
        or_<
            chseq<'i','f'>,
            chseq<'e','l','s','e'>,
            chseq<'s','w','i','t','c','h'>,
            chseq<'c','h','a','r'>,
            chseq<'w','c','h','a','r','_','t'>,
            chseq<'b','o','o','l'>,
            chseq<'s','h','o','r','t'>,
            chseq<'i','n','t'>,
            chseq<'l','o','n','g'>,
            chseq<'s','i','g','n','e','d'>
        >
    { };

    struct cpp_keyword2 :
        or_<
            chseq<'u','n','s','i','g','n','e','d'>,
            chseq<'c','l','a','s','s'>,
            chseq<'s','t','r','u','c','t'>,
            chseq<'u','n','i','o','n'>,
            chseq<'p','r','i','v','a','t','e'>,
            chseq<'p','r','o','t','e','c','t','e','d'>,
            chseq<'p','u','b','l','i','c'>,
            chseq<'o','p','e','r','a','t','o','r'>,
            chseq<'e','n','u','m'>,
            chseq<'n','a','m','e','s','p','a','c','e'>
        >
    { };

    struct cpp_keyword3 :
        or_<
            chseq<'u','s','i','n','g'>,
            chseq<'a','s','m'>,
            chseq<'c','o','n','s','t'>,
            chseq<'v','o','l','a','t','i','l','e'>,
            chseq<'e','x','p','o','r','t'>,
            chseq<'t','e','m','p','l','a','t','e'>,
            chseq<'f','a','l','s','e'>,
            chseq<'t','r','u','e'>,
            chseq<'f','r','i','e','n','d'>,
            chseq<'t','y','p','e','d','e','f'>
        >
    { };
    
    struct cpp_keyword4 :
        or_<
            chseq<'a','u','t','o'>,
            chseq<'r','e','g','i','s','t','e','r'>,
            chseq<'s','t','a','t','i','c'>,
            chseq<'e','x','t','e','r','n'>,
            chseq<'m','u','t','a','b','l','e'>,
            chseq<'i','n','l','i','n','e'>,
            chseq<'t','h','i','s'>,
            seq< chseq<'d','y','n','a','m','i','c','_','c','a'>, chseq<'s','t'> >,
            seq< chseq<'s','t','a','t','i','c','_','c','a','s'>, chseq<'t'> >,
            seq< chseq<'r','e','i','n','t','e','r','p','r','e'>, chseq<'t','_','c','a','s','t'> >
        >
    { };
    
    struct cpp_keyword5 :
        or_<
            chseq<'c','o','n','s','t','_','c','a','s','t'>,
            chseq<'t','r','y'>,
            chseq<'c','a','t','c','h'>,
            chseq<'t','h','r','o','w'>,
            chseq<'t','y','p','e','i','d'>,
            chseq<'t','y','p','e','n','a','m','e'>,
            chseq<'s','i','z','e','o','f'>,
            chseq<'n','e','w'>,
            chseq<'d','e','l','e','t','e'>,
            chseq<'u','n','s','i','g','n','e','d'>
        >
    { };
    
    struct cpp_keyword6 :
        or_<
            chseq<'f','l','o','a','t'>,
            chseq<'d','o','u','b','l','e'>,
            chseq<'v','o','i','d'>,
            chseq<'v','i','r','t','u','a','l'>,
            chseq<'e','x','p','l','i','c','i','t'>,
            chseq<'w','h','i','l','e'>,
            chseq<'d','o'>,
            chseq<'f','o','r'>,
            chseq<'b','r','e','a','k'>,
            chseq<'c','o','n','t','i','n','u','e'>
        >
    { };

    struct cpp_keyword7 :
        or_<
            chseq<'r','e','t','u','r','n'>,
            chseq<'g','o','t','o'>,
            chseq<'x','o','r'>,
            chseq<'o','r','_','e','q'>,
            chseq<'x','o','r','_','e','q'>  
        >
    { };

    struct cpp_keyword :
        or_<
            cpp_keyword0,
            cpp_keyword1,
            cpp_keyword2,
            cpp_keyword3,
            cpp_keyword4,
            cpp_keyword5,
            cpp_keyword6,
            cpp_keyword7
        >
    { };

}


#endif
