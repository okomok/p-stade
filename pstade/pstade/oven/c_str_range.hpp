#ifndef PSTADE_OVEN_C_STR_RANGE_HPP
#define PSTADE_OVEN_C_STR_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <cstring> // strlen
#include <cwchar>  // wcslen
#include <boost/type_traits/remove_pointer.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace c_str_range_detail {


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


} // namespace c_str_range_detail


template< class Char >
struct c_str_range :
    iter_range<Char *>::type,
    private as_lightweight_proxy< c_str_range<Char> >
{
    typedef c_str_range type;

private:
    typedef typename iter_range<Char *>::type super_t;

public:
    explicit c_str_range(Char *psz) :
        super_t(psz, psz + c_str_range_detail::length(psz))
    { }
};


template< class CString >
struct deduce_to_char_ptr :
    boost::remove_pointer<typename pass_by_value<CString>::type>
{ };


PSTADE_OBJECT_GENERATOR(make_c_str_range,
    (c_str_range< deduce_to_char_ptr<_1> >) const)
PSTADE_PIPABLE(as_c_str, (op_make_c_str_range))


} } // namespace pstade::oven


#endif
