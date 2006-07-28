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
#include <cwchar>       // wcslen
#include <stdexcept>    // range_error
#include <string>
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template< class ForwardRange > inline
void null_terminate(ForwardRange& rng)
{
    BOOST_ASSERT(!boost::empty(rng));

    typedef typename range_value<ForwardRange>::type val_t;
    *boost::begin(rng) = val_t('\0');
}


template< class ForwardRange >
bool is_null_terminated(ForwardRange const& rng)
{
    detail::requires< boost::ForwardRangeConcept<ForwardRange> >();

    typedef typename boost::range_const_iterator<ForwardRange>::type iter_t;
    typedef typename range_value<ForwardRange>::type val_t;

    iter_t first = boost::begin(rng);
    iter_t last = boost::end(rng);
    iter_t it = std::find(first, last, val_t('\0'));

    return (it != last);
}


namespace null_terminate_range_detail {


    template< class ForwardRange >
    typename range_iterator<ForwardRange>::type
    begin(ForwardRange& rng)
    {
        detail::requires< boost::ForwardRangeConcept<ForwardRange> >();
        return boost::begin(rng);
    }

    template< class ForwardRange >
    typename range_iterator<ForwardRange>::type
    end(ForwardRange& rng)
    {
        detail::requires< boost::ForwardRangeConcept<ForwardRange> >();

        typedef typename range_iterator<ForwardRange>::type iter_t;
        typedef typename range_value<ForwardRange>::type val_t;

        iter_t first = boost::begin(rng);
        iter_t last = boost::end(rng);
        iter_t it = std::find(first, last, val_t('\0'));

        if (it == last) {
            std::string msg("pstade::oven - rng must be null-terminated.");
            boost::throw_exception(std::range_error(msg));
        }

        return it;
    }


    // take both array and pointer out of Boost.ForwardRange.
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
    char const *begin(const char *s)
    {
        return s;
    }

    inline
    char const *end(const char *s)
    {
        using namespace std;
        return s + strlen(s);
    }


    inline
    wchar_t *begin(wchar_t *s)
    {
        return s;
    }

    inline
    wchar_t *end(wchar_t *s)
    {
        using namespace std;
        return s + wcslen(s);
    }

    inline
    wchar_t const *begin(const wchar_t *s)
    {
        return s;
    }

    inline
    wchar_t const *end(const wchar_t *s)
    {
        using namespace std;
        return s + wcslen(s);
    }


    // meta
    //

    template< class ForwardRange >
    struct iter
    {
        typedef typename range_iterator<ForwardRange>::type type;
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


    template< class ForwardRangeOrCString >
    struct super_
    {
        typedef boost::iterator_range<
            typename iter<ForwardRangeOrCString>::type 
        > type;
    };


} // namespace null_terminate_range_detail


template< class ForwardRangeOrCString >
struct null_terminate_range :
    null_terminate_range_detail::super_<ForwardRangeOrCString>::type,
    private lightweight_proxy< null_terminate_range<ForwardRangeOrCString> >
{
private:
    typedef typename null_terminate_range_detail::super_<ForwardRangeOrCString>::type super_t;

public:
    explicit null_terminate_range(ForwardRangeOrCString& x) :
        super_t(null_terminate_range_detail::begin(x), null_terminate_range_detail::end(x))
    { }
};


namespace null_terminate_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRangeOrCString >
        struct result
        {
            typedef null_terminate_range<ForwardRangeOrCString> const type;
        };

        template< class Result, class ForwardRangeOrCString >
        Result call(ForwardRangeOrCString& x)
        {
            return Result(x);
        }
    };


} // namespace null_terminate_range_detail



PSTADE_EGG_FUNCTION(make_null_terminate_range, null_terminate_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(null_terminated, null_terminate_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
