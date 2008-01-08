#ifndef PSTADE_EGG_TO_REF_HPP
#define PSTADE_EGG_TO_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./by_cref.hpp"
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    namespace to_ref_detail {


        struct little
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


        struct clittle
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


        struct mlittle
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


        typedef function<little,  by_perfect> op;
        typedef function<clittle, by_cref>   cop;
        typedef function<mlittle, by_cref>   mop;


    } // namespace to_ref_detail


    typedef result_of_ambi0<to_ref_detail::op>::type  T_to_ref;
    typedef result_of_ambi0<to_ref_detail::cop>::type T_to_cref;
    typedef result_of_ambi0<to_ref_detail::mop>::type T_to_mref;
    PSTADE_POD_CONSTANT((T_to_ref),  to_ref)  = PSTADE_EGG_AMBI({{}});
    PSTADE_POD_CONSTANT((T_to_cref), to_cref) = PSTADE_EGG_AMBI({{}});
    PSTADE_POD_CONSTANT((T_to_mref), to_mref) = PSTADE_EGG_AMBI({{}});


} } // namespace pstade::egg


#endif
