#ifndef PSTADE_PACK_HPP
#define PSTADE_PACK_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Yet another 'make_tuple' to support rvalue and const-reference.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/callable.hpp> // MAX_ARITY
#include <pstade/constant.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


    namespace pack_detail {


        // Workaround:
        // Boost.MPL default max arity is not enough for 'boost::tuple<..>' with PlaceholderExpression.

        struct klass
        {
        #define PSTADE_deduce(Z, N, _) \
            typename deduce<BOOST_PP_CAT(A, N), deducers::to_reference, boost::tuples::null_type>::type \
        /**/

            template<BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, class A)>
            struct apply
            {
                typedef
                    boost::tuples::tuple<
                        BOOST_PP_ENUM(PSTADE_CALLABLE_MAX_ARITY, PSTADE_deduce, ~)
                    >
                type; // Don't add 'const' for 'operator='.
            };

        #undef  PSTADE_deduce
        };


    } // namespace pack_detail


    typedef object_generator<pack_detail::klass> op_pack;
    PSTADE_CONSTANT(pack, (op_pack))
    PSTADE_PIPABLE(packed, (op_pack))


} // namespace pstade


#endif
