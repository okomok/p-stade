#ifndef PSTADE_EGG_TUPLE_PACK_HPP
#define PSTADE_EGG_TUPLE_PACK_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/pod_constant.hpp>
#include "./deduce.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./generator.hpp"


namespace pstade { namespace egg {


    namespace tuple_pack_detail {


        // Boost.MPL default max arity is not enough for 'boost::tuple<..>' with PlaceholderExpression.

        struct klass
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


    } // namespace tuple_pack_detail


    typedef
        generator<
            tuple_pack_detail::klass,
            boost::use_default,
            boost::tuples::tuple<>
        >::type
    op_tuple_pack;


    PSTADE_POD_CONSTANT((op_tuple_pack), tuple_pack) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::egg


#endif
