#ifndef PSTADE_OVEN_WITH_LINE_NUMBER_HPP
#define PSTADE_OVEN_WITH_LINE_NUMBER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Iterator type works as a "key"; see 'T_line_number'.
// This way seems better than zipping referent and line number.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/default_newline.hpp"
#include "./detail/line_number_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


// with_line_number
//

namespace with_line_number_detail {


    template< class Range, class Incrementable >
    struct base
    {
        typedef typename
            range_value<Range>::type
        val_t;

        typedef typename
            detail::line_number_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Incrementable>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Incrementable& n, val_t nl = detail::default_newline<val_t>::value()) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result_type(iter_t(boost::begin(rng), n, nl), iter_t(boost::end(rng), n, nl));
        }
    };


} // namespace with_line_number_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(with_line_number, (with_line_number_detail::base<_, _>))


// line_number
//

template< class Incrementable >
struct X_line_number
{
    typedef X_line_number function_type;
    typedef Incrementable result_type;

    template< class Adapted >
    Incrementable operator()(Adapted ad,
        typename enable_if< detail::has_line_number<Adapted, Incrementable> >::type = 0) const
    {
        return ad.line_number();
    }

    template< class Adapted >
    Incrementable operator()(Adapted ad,
        typename disable_if<detail::has_line_number<Adapted, Incrementable> >::type = 0) const
    {
        return (*this)(ad.base());

    }
};

template< class Incrementable, class Adapted > inline
Incrementable line_number(Adapted ad)
{
    return X_line_number<Incrementable>()(ad);
}


} } // namespace pstade::oven


#endif
