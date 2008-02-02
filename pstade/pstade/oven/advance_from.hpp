#ifndef PSTADE_OVEN_ADVANCE_FROM_HPP
#define PSTADE_OVEN_ADVANCE_FROM_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Traversal concept version of 'std::advance'.
// This function doesn't modify the argument iterator.


// References:
//
// [1] Dave Abrahams and Daniel Walker, next and prior, Boost.Utility, 2003.
//     http://www.boost.org/libs/utility/utility.htm


#include <iterator> // advance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/polymorphic.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace oven {


namespace advance_from_detail {


    namespace here = advance_from_detail;


    template< class Iterator, class Difference > inline
    void aux(Iterator& it, Difference n, boost::random_access_traversal_tag)
    {
        it += n;
    }

    template< class Iterator, class Difference > inline
    void aux(Iterator& it, Difference n, boost::bidirectional_traversal_tag)
    {
        std::advance(it, n);
    }

    template< class Iterator, class Difference > inline
    void aux(Iterator& it, Difference n, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(0 <= n);
        std::advance(it, n);
    }


    template< class Iterator >
    struct base
    {
        typedef typename
            pass_by_value<Iterator>::type
        result_type;

        typedef typename
            boost::iterator_difference<result_type>::type
        diff_t;

        result_type operator()(result_type it, diff_t n) const
        {
            here::aux(it, n, typename boost::iterator_traversal<result_type>::type());
            return it;
        }
    };


} // namespace advance_from_detail


typedef egg::polymorphic< advance_from_detail::base<boost::mpl::_> >::type T_advance_from;
PSTADE_POD_CONSTANT((T_advance_from), advance_from) = PSTADE_EGG_POLYMORPHIC();


} } // namespace pstade::oven


#endif
