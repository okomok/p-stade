#ifndef PSTADE_TIE_HPP
#define PSTADE_TIE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Supports rvalue and const-reference.


#include <boost/tuple/tuple.hpp>
#include <pstade/constant.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>


namespace pstade {


    namespace tie_detail {


        // Workaround:
        // Boost.MPL default max arity is not enough for Boost.Tuple.
        // So, avoid PlaceholderExpression.


#define PSTADE_deduce(Z, N, _) typename deduce_by_reference< BOOST_PP_CAT(A, N), boost::tuples::null_type >::type

        struct expr
        {
            template< BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, class A) >
            struct apply
            {
                typedef boost::tuples::tuple<
                    BOOST_PP_ENUM(PSTADE_CALLABLE_MAX_ARITY, PSTADE_deduce, ~)
                > type;
            };
        };

#undef PSTADE_deduce


    } // namespace tie_detail


    typedef object_generator< tie_detail::expr, boost::tuples::tuple<> > op_tie;
    PSTADE_CONSTANT(tie, op_tie)
    PSTADE_PIPABLE(tied, op_tie)


} // namespace pstade


#endif
