#ifndef PSTADE_OVEN_ADVANCE_HPP
#define PSTADE_OVEN_ADVANCE_HPP


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


#include <iterator> // advance
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>


namespace pstade { namespace oven {


namespace advance_detail {


    template< class Iterator, class >
    struct baby
    {
        typedef typename
            pass_by_value<Iterator>::type
        result_type;

        typedef typename
            boost::iterator_difference<result_type>::type
        diff_t;

        result_type operator()(result_type it, diff_t const& d) const
        {
            aux(it, d, typename boost::iterator_traversal<result_type>::type());
            return it;
        }

        void aux(result_type& it, diff_t const& d, boost::random_access_traversal_tag) const
        {
            it += d;
        }

        void aux(result_type& it, diff_t const& d, boost::single_pass_traversal_tag) const
        {
            std::advance(it, d);
        }
    };


} // namespace advance_detail


PSTADE_FUNCTION(advance, (advance_detail::baby<_, _>))


} } // namespace pstade::oven


#endif
