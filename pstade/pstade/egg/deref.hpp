#ifndef PSTADE_EGG_DEREF_HPP
#define PSTADE_EGG_DEREF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./deferred.hpp"
#include "./extension.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct result_of_deref
    {
        typedef typename
            pstade_egg_extension::Dereferenceable<X>::reference
        type;
    };


    namespace deref_detail {


        template<class X>
        struct base
        {
            typedef typename
                result_of_deref<X>::type
            result_type;

            result_type operator()(X& x) const
            {
                return *x;
            }
        };


    } // namespace deref_detail


    typedef PSTADE_EGG_DEFER((deref_detail::base<boost::mpl::_>)) T_deref;
    PSTADE_POD_CONSTANT((T_deref), deref) = PSTADE_EGG_DEFERRED;


} } // namespace pstade::egg


#endif
