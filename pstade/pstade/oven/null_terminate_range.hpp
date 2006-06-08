#ifndef PSTADE_OVEN_NULL_TERMINATE_RANGE_HPP
#define PSTADE_OVEN_NULL_TERMINATE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Is cstring_range/cstringized a better name ?


#include <algorithm>    // find
#include <cstddef>      // size_t
#include <cstring>      // strlen
#include <stdexcept>    // range_error
#include <string>
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


template< class Range > inline
void null_terminate(Range& rng)
{
    BOOST_ASSERT(!boost::empty(rng));

    typedef typename boost::range_value<Range>::type value_t;
    *boost::begin(rng) = value_t('\0');
}


template< class Range >
bool is_null_terminated(const Range& rng)
{
    typedef typename boost::range_const_iterator<Range>::type iter_t;
    typedef typename boost::range_value<Range>::type value_t;

    iter_t first = boost::begin(rng);
    iter_t last = boost::end(rng);
    iter_t it = std::find(first, last, value_t('\0'));

    return (it != last);
}


namespace null_terminate_range_detail {


    template< class Range >
    typename boost::range_result_iterator<Range>::type
    begin(Range& rng)
    {
        return boost::begin(rng);
    }

    template< class Range >
    typename boost::range_result_iterator<Range>::type
    end(Range& rng)
    {
        typedef typename boost::range_result_iterator<Range>::type iter_t;
        typedef typename boost::range_value<Range>::type value_t;

        iter_t first = boost::begin(rng);
        iter_t last = boost::end(rng);
        iter_t it = std::find(first, last, value_t('\0'));

        if (it == last) {
            std::string msg("pstade::oven - rng must be null-terminated.");
            boost::throw_exception(std::range_error(msg));
        }

        return it;
    }


    // take both array and pointer out of Boost.Range.
    //

    template< class T > inline
    T *begin(T *s)
    {
        return s;
    }

    template< class T > inline
    T *end(T *s)
    {
        while (*s != '\0')
            ++s;

        return s;
    }

    // 'char' loves strlen.
    inline
    char *begin(char *s)
    {
        return s;
    }

    inline
    char *end(char *s)
    {
        using namespace std;
        return s + strlen(s);
    }

    inline
    const char *begin(const char *s)
    {
        return s;
    }

    inline
    const char *end(const char *s)
    {
        using namespace std;
        return s + strlen(s);
    }


    // meta
    //
    
    template< class Range >
    struct iter
    {
        typedef typename boost::range_result_iterator<Range>::type type;
    };

    template< class T >
    struct iter<T *>
    {
        typedef T *type;
    };

    template< class T, std::size_t sz >
    struct iter<T [sz]>
    {
        typedef T *type;
    };


    template< class RangeOrCString >
    struct super_
    {
        typedef boost::iterator_range<
            typename iter<RangeOrCString>::type 
        > type;
    };


} // namespace null_terminate_range_detail


template< class RangeOrCString >
struct null_terminate_range :
    null_terminate_range_detail::super_<RangeOrCString>::type
{
private:
    typedef typename null_terminate_range_detail::super_<RangeOrCString>::type super_t;

public:
    explicit null_terminate_range(RangeOrCString& x) :
        super_t(null_terminate_range_detail::begin(x), null_terminate_range_detail::end(x))
    { }
};


namespace null_terminate_range_detail {


    struct baby_generator
    {
        template< class RangeOrCString >
        struct result
        {
            typedef const null_terminate_range<RangeOrCString> type;
        };

        template< class Result, class RangeOrCString >
        Result call(RangeOrCString& x)
        {
            return Result(x);
        }
    };


} // namespace null_terminate_range_detail



PSTADE_EGG_FUNCTION(make_null_terminate_range, null_terminate_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(null_terminated, null_terminate_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::null_terminate_range, 1)


#endif
