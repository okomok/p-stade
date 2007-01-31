#ifndef PSTADE_OVEN_AS_SINGLE_HPP
#define PSTADE_OVEN_AS_SINGLE_HPP


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


#include <vector>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include "./iter_range.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


namespace as_single_detail {


    template< class X >
    struct baby
    {
        typedef
            iter_range<X *> const
        result;

        result call(X& x)
        {
            return result(boost::addressof(x), boost::addressof(x) + 1);
        }
    };


} // namespace as_single_detail


PSTADE_AUXILIARY0(as_single, (function< as_single_detail::baby<boost::mpl::_> >))


namespace as_shared_single_detail {


    template< class X >
    struct baby
    {
        typedef typename
            affect<
                X,
                std::vector<typename boost::remove_cv<X>::type>
            >::type
        rng_t;

        typedef typename
            boost::result_of<
                op_make_shared(rng_t *)
            >::type
        result;

        result call(X& x)
        {
            return make_shared(
                new rng_t(boost::addressof(x), boost::addressof(x) + 1)
            );
        }
    };


} // namespace as_shard_single_detail


PSTADE_AUXILIARY0(as_shared_single, (function< as_shared_single_detail::baby<boost::mpl::_> >))


} } // namespace pstade::oven


#endif
