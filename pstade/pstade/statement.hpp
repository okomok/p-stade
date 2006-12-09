#ifndef PSTADE_STATEMENT_HPP
#define PSTADE_STATEMENT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Strictly speaking, there seems no guarantee that
// the statement is executed before 'main'...
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/7d2a6bb473c31056/


#include <boost/noncopyable.hpp>
#include <boost/preprocessor/cat.hpp>
#include <pstade/constant.hpp>


#define PSTADE_STATEMENT(Label, Statement) \
    PSTADE_STATEMENT_define_init_type(Label, Statement) \
    namespace { \
        PSTADE_STATEMENT_init_type(Label) const volatile& PSTADE_STATEMENT_init(Label) \
            = pstade::singleton< PSTADE_STATEMENT_init_type(Label) >::instance; \
    } \
/**/


#define PSTADE_STATEMENT_define_init_type(Label, Statement) \
    struct PSTADE_STATEMENT_init_type(Label) : \
        private boost::noncopyable \
    { \
        PSTADE_STATEMENT_init_type(Label)() \
        { \
            Statement \
        } \
    }; \
/**/


#define PSTADE_STATEMENT_init_type(Label) \
    BOOST_PP_CAT(pstade_statement_init_type_of_, Label) \
/**/


#define PSTADE_STATEMENT_init(Label) \
    BOOST_PP_CAT(pstade_statement_init_of_, Label) \
/**/


#endif
