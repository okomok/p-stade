#ifndef PSTADE_OVEN_TROTTER_DECODE_RANGE_HPP
#define PSTADE_OVEN_TROTTER_DECODE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <trotter/conversion/converter.hpp> // encoder
#include <trotter/conversion/input_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/is_lightweight_proxy.hpp>
#include <pstade/oven/range_adaptor.hpp>


namespace pstade { namespace oven {


namespace trotter_decode_range_detail {


    template< class Range, class Customer >
    struct super_
    {
        typedef typename boost::range_value<Range>::type val_t;
        typedef typename trotter::conversion::encoder<val_t, Customer> coder_t;

        typedef boost::iterator_range<
            trotter::conversion::convert_input_iterator<
                coder_t,
                typename boost::range_result_iterator<Range>::type
            >
        > type;
    };


} // namespace trotter_decode_range_detail


template< class Range, class Customer >
struct trotter_decode_range :
    trotter_decode_range_detail::super_<Range, Customer>::type
{
private:
    typedef typename trotter_decode_range_detail::super_<Range, Customer>::type super_t;
    typedef typename trotter_decode_range_detail::super_<Range, Customer>::coder_t coder_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class CvtExprOrObject >
    explicit trotter_decode_range(Range& rng, CvtExprOrObject const& expr) :
        super_t(
            iter_t(coder_t(expr), boost::begin(rng), boost::end(rng)),
            iter_t(coder_t(expr), boost::end(rng), boost::end(rng))
        )
    { }
};


namespace trotter_decode_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class CvtExprOrObject, class Customer >
        struct result
        {
            typedef typename boost::remove_cv<Customer>::type cst_t;
            typedef trotter_decode_range<Range, cst_t> const type;
        };

        template< class Result, class Range, class CvtExprOrObject, class Customer  >
        Result call(Range& rng, CvtExprOrObject const& expr, Customer )
        {
            return Result(rng, expr);
        }
    };


} // namespace trotter_decode_range_detail


PSTADE_EGG_FUNCTION(make_trotter_decode_range, trotter_decode_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(trotter_decoded, trotter_decode_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::trotter_decode_range, 2)


#endif
