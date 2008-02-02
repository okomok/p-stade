#ifndef PSTADE_OVEN_SINGLE_HPP
#define PSTADE_OVEN_SINGLE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The constant-iterator is the same as the mutable-iterator.
// Const-ness of this range must be independent from const-ness of the 'X'.


#include <boost/utility/addressof.hpp>
#include <pstade/egg/polymorphic.hpp>
#include <pstade/pod_constant.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace single_detail {


    template< class X >
    struct base
    {
        typedef
            iter_range<X *> const
        result_type;

        result_type operator()(X& x) const
        {
            return result_type(boost::addressof(x), boost::addressof(x) + 1);
        }
    };


} // namespace single_detail


typedef egg::polymorphic< single_detail::base<boost::mpl::_> >::type T_single;
PSTADE_POD_CONSTANT((T_single), single) = PSTADE_EGG_POLYMORPHIC();


} } // namespace pstade::oven


#endif
