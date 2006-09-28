#ifndef PSTADE_OVEN_AS_C_STR_HPP
#define PSTADE_OVEN_AS_C_STR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <cstring> // strlen
#include <cwchar>  // wcslen
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>


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


    struct baby
    {
        template< class Unused, class CString >
        struct apply
        {
            typedef typename pass_by_value<CString>::type ptr_t;
            typedef boost::iterator_range<ptr_t> const type;
        };

        template< class Result, class CString >
        Result call(CString psz)
        {
            return Result(psz, psz + length(psz));
        }
    };


} // namespace as_c_str_detail


PSTADE_EGG_PIPABLE(as_c_str, as_c_str_detail::baby)


} } // namespace pstade::oven


#endif
