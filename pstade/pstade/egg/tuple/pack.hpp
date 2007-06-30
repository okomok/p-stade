#ifndef PSTADE_EGG_TUPLE_PACK_HPP
#define PSTADE_EGG_TUPLE_PACK_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include "../deduce.hpp"
#include "../detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "../generator.hpp"
#include "../object.hpp"


namespace pstade { namespace egg { namespace tuples {


    namespace pack_detail {


        // Boost.MPL default max arity is not enough for 'boost::tuple<..>' with PlaceholderExpression.

        struct meta_tuple
        {
        #define PSTADE_deduce(Z, N, _) \
            typename deduce<BOOST_PP_CAT(A, N), as_reference, boost::tuples::null_type>::type \
        /**/

            template<BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, class A)>
            struct apply
            {
                typedef
                    boost::tuples::tuple<
                        BOOST_PP_ENUM(PSTADE_EGG_MAX_ARITY, PSTADE_deduce, ~)
                    >
                type; // Don't add 'const' for 'operator='.
            };

        #undef  PSTADE_deduce
        };


    } // namespace pack_detail


    typedef
        generator<
            pack_detail::meta_tuple,
            boost::use_default,
            boost::tuples::tuple<>
        >::type
    op_pack;


    PSTADE_EGG_OBJECT((op_pack), pack) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } } // namespace pstade::egg::tuples


#endif
