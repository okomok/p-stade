#ifndef PSTADE_OVEN_AS_C_STR_HPP
#define PSTADE_OVEN_AS_C_STR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'taken_while(_1 != 0)' is useless if you want
// null-terminated string, because it can't return
// RandomAccessRange. Thus, 'as_c_str' kicks in.


#include <algorithm> // find
#include <cstddef>   // size_t
#include <cstring>   // strlen
#include <cwchar>    // wcslen
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
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
            is_convertible<X, char const *>,
            is_convertible<X, wchar_t const *>
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


    template< class Range >
    struct iter_const_range_of
    {
        typedef typename
            iter_range_of<Range>::type const
        type;
    };


    template< class MaybeCString >
    struct to_range :
        boost::mpl::eval_if< is_cstring<MaybeCString>,
            cstring_to_range<MaybeCString>,
            iter_const_range_of<MaybeCString>
        >
    { };


    // suppress warning: comparison between signed and unsigned integer
    template< class Range > inline
    typename range_value<Range>::type
    zero()
    {
        return 0;
    }


    struct op :
        callable<op>
    {
        template< class Myself, class MaybeCString >
        struct apply :
            to_range<MaybeCString>
        { };

        template< class Result, class Char >
        Result call(Char *psz) const
        {
            return Result(psz, psz + (length)(psz));
        }

        template< class Result, class Range >
        Result call(Range& rng,
            typename disable_if< is_cstring<Range> >::type = 0) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return Result(
                boost::begin(rng),
                std::find(boost::begin(rng), boost::end(rng), zero<Range>())
            );
        }
    };


} // namespace as_c_str_detail


PSTADE_AUXILIARY(0, as_c_str, (as_c_str_detail::op))


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
