#ifndef PSTADE_EGG_UNWRAP_REF_HPP
#define PSTADE_EGG_UNWRAP_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/boost/reference_wrapper_fwd.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    namespace unwrap_ref_detail {


        struct little
        {
            template<class Me, class A>
            struct apply
            {
                typedef A& type;
            };

            template<class Me, class T>
            struct apply< Me, boost::reference_wrapper<T> >
            {
                typedef T& type;
            };

            template<class Me, class T>
            struct apply< Me, boost::reference_wrapper<T> const >
            {
                typedef T& type;
            };

            template<class Re, class A>
            Re call(A& a) const
            {
                return a;
            }
        };


    } // namespace unwrap_ref_detail


    typedef function<unwrap_ref_detail::little, by_perfect> T_unwrap_ref;
    PSTADE_POD_CONSTANT((T_unwrap_ref), unwrap_ref) = {{}};


} } // namespace pstade::egg


#endif
