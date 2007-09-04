#ifndef PSTADE_EGG_TO_REF_HPP
#define PSTADE_EGG_TO_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/pod_constant.hpp>
#include "./auxiliary.hpp"
#include "./function.hpp"
#include "./by_cref.hpp"


namespace pstade { namespace egg {


    namespace to_ref_detail {


        struct baby
        {
            template<class Myself, class X>
            struct apply
            {
                typedef X& type;
            };

            template<class Result, class X>
            Result call(X& x) const
            {
                return x;
            }
        };


        struct cbaby
        {
            template<class Myself, class X>
            struct apply
            {
                typedef X& type;
            };

            template<class Result, class X>
            Result call(X& x) const
            {
                return x;
            }
        };


        struct mbaby
        {
            template<class Myself, class X>
            struct apply
            {
                typedef typename boost::remove_cv<X>::type& type;
            };

            template<class Result, class X>
            Result call(X const& x) const
            {
                return const_cast<X&>(x);
            }
        };


        typedef function<baby>  op;
        typedef function<cbaby, by_cref> cop;
        typedef function<mbaby, by_cref> mop;


    } // namespace to_ref_detail


    typedef result_of_auxiliary0<to_ref_detail::op>::type  op_to_ref;
    typedef result_of_auxiliary0<to_ref_detail::cop>::type op_to_cref;
    typedef result_of_auxiliary0<to_ref_detail::mop>::type op_to_mref;
    PSTADE_POD_CONSTANT((op_to_ref),  to_ref)  = PSTADE_EGG_AUXILIARY_L {{}} PSTADE_EGG_AUXILIARY_R;
    PSTADE_POD_CONSTANT((op_to_cref), to_cref) = PSTADE_EGG_AUXILIARY_L {{}} PSTADE_EGG_AUXILIARY_R;
    PSTADE_POD_CONSTANT((op_to_mref), to_mref) = PSTADE_EGG_AUXILIARY_L {{}} PSTADE_EGG_AUXILIARY_R;


} } // namespace pstade::egg


#endif
