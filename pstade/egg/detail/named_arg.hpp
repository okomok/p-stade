#ifndef PSTADE_EGG_DETAIL_NAMED_ARG_HPP
#define PSTADE_EGG_DETAIL_NAMED_ARG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_reference.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class Keyword, class Arg>
    struct named_arg
    {
        typedef Keyword keyword_type;
        typedef Arg arg_type;
        Arg& m_arg;
    };


    template<class NamedArg>
    struct keyword_of
    {
        typedef typename boost::remove_reference<NamedArg>::type named_arg_t;
        typedef typename named_arg_t::keyword_type type;
    };


} } } // namespace pstade::egg::detail


#endif
