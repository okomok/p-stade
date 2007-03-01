#ifndef PSTADE_OVEN_AS_C_STR_HPP
#define PSTADE_OVEN_AS_C_STR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find
#include <cstddef>   // size_t
#include <cstring>   // strlen
#include <cwchar>    // wcslen
#include <boost/mpl/or.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace as_c_str_detail {


    inline
    std::size_t length(char const *psz)
    {
        using namespace std;
        return strlen(psz);
    }

    inline
    std::size_t length(wchar_t const *psz)
    {
        using namespace std;
        return wcslen(psz);
    }


    template< class X >
    struct is_cstring :
       boost::mpl::or_<
            is_convertible_in_enable_if<X, char const *>,
            is_convertible_in_enable_if<X, wchar_t const *>
        >
    { };

    template< class CString >
    struct cstring_to_range
    {
        typedef typename
            pass_by_value<CString>::type
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };


    // suppress warning: comparison between signed and unsigned integer
    template< class Range > inline
    typename range_value<Range>::type
    zero()
    {
        return 0;
    }


    template< class Range, class = enabler >
    struct baby
    {
        typedef typename
            iter_range_of<Range>::type const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return result_type(
                boost::begin(rng),
                std::find(boost::begin(rng), boost::end(rng), zero<Range>())
            );
        }
    };

    template< class CString >
    struct baby<CString, typename enable_if< is_cstring<CString> >::type>
    {
        typedef typename
            cstring_to_range<CString>::type
        result_type;

        template< class Char >
        result_type operator()(Char *psz) const
        {
            return result_type(psz, psz + length(psz));
        }
    };

    PSTADE_FUNCTION(normal, (baby<_>))


} // namespace as_c_str_detail


PSTADE_AUXILIARY(0, as_c_str, (as_c_str_detail::op_normal))


struct op_contains_zero
{
    typedef bool result_type;

    template< class Range >
    bool operator()(Range const& rng) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        return boost::end(rng) !=
            std::find(boost::begin(rng), boost::end(rng), as_c_str_detail::zero<Range>());
    }
};

PSTADE_CONSTANT(contains_zero, (op_contains_zero))


} } // namespace pstade::oven


#endif
