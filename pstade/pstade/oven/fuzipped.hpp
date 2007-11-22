#ifndef PSTADE_OVEN_FUZIPPED_HPP
#define PSTADE_OVEN_FUZIPPED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include "./begin_end.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/fuzip_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace fuzipped_detail {


    template< class RangeTuple >
    struct base
    {
        typedef
            boost::fusion::transform_view<RangeTuple, T_begin>
        begin_tup_t;

        typedef
            boost::fusion::transform_view<RangeTuple, T_end>
        end_tup_t;

        typedef
            detail::fuzip_iterator<
                // Remove reference(to range) in transform_view.
                typename boost::fusion::result_of::as_vector<begin_tup_t>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(RangeTuple& tup) const
        {
            begin_tup_t begin_tup(tup, begin);
            end_tup_t end_tup(tup, end);
            return result_type(
                iter_t( boost::fusion::as_vector(begin_tup) ),
                iter_t( boost::fusion::as_vector(end_tup) )
            );
        }
    };


} // namespace fuzipped_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(fuzipped, (fuzipped_detail::base<_>))


} } // namespace pstade::oven


#endif // BOOST_VERSION >= 103500


#endif
