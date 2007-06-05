#ifndef PSTADE_OVEN_FUZIPPED_HPP
#define PSTADE_OVEN_FUZIPPED_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/sequence/view/transform_view.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/polymorphic.hpp>
#include "./begin_end.hpp"
#include "./detail/fuzip_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace fuzipped_detail {


    template< class RangeTuple >
    struct baby
    {
        // Prefer a view to 'transform', keeping the mutability of elements.
        typedef
            boost::fusion::transform_view<
                RangeTuple,
                typename boost::result_of<op_polymorphic(op_begin const&)>::type
            >
        begin_tup_t;

        typedef
            boost::fusion::transform_view<
                RangeTuple,
                typename boost::result_of<op_polymorphic(op_end const&)>::type
            >
        end_tup_t;

        typedef
            detail::fuzip_iterator<
                // Copy the iterators by 'as_vector', following 'boost::zip_iterator'.
                typename boost::fusion::result_of::as_vector<begin_tup_t>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(RangeTuple& tup) const
        {
            begin_tup_t begin_tup(tup, polymorphic(begin));
            end_tup_t end_tup(tup, polymorphic(end));
            return result_type(
                iter_t( boost::fusion::as_vector(begin_tup) ),
                iter_t( boost::fusion::as_vector(end_tup) )
            );
        }
    };


} // namespace fuzipped_detail


PSTADE_FUNCTION(make_fuzipped, (fuzipped_detail::baby<_>))
PSTADE_PIPABLE(fuzipped, (op_make_fuzipped))


} } // namespace pstade::oven


#endif // #if BOOST_VERSION >= 103500


#endif
