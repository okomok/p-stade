#ifndef PSTADE_OVEN_AS_C_STR_HPP
#define PSTADE_OVEN_AS_C_STR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <cstring> // strlen
#include <cwchar>  // wcslen
#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./iter_range.hpp"


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


    template< class CString >
    struct baby
    {
        typedef typename
            pass_by_value<CString>::type
        char_ptr_t;

        typedef
            iter_range<char_ptr_t> const
        result;

        result call(char_ptr_t psz)
        {
            return result(psz, psz + length(psz));
        }
    };


} // namespace as_c_str_detail


PSTADE_AUXILIARY0(as_c_str, (function< as_c_str_detail::baby<boost::mpl::_> >))


} } // namespace pstade::oven


#endif
