#ifndef PSTADE_PIZZA_ACCESS_HPP
#define PSTADE_PIZZA_ACCESS_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/nonconstructible.hpp>


namespace pstade { namespace pizza {


class access :
    private nonconstructible
{
public:
    template< class Profile > static
    void detail_initialize(Profile& pr, const TCHAR *pszName)
    {
        pr.pstade_pizza_initialize(pszName);
    }

    template< class Profile > static
    void detail_set_string(Profile& pr, const TCHAR *pszValueName, const TCHAR *pszValue)
    {
        pr.pstade_pizza_set_string(pszValueName, pszValue);
    }

    template< class Profile > static
    bool detail_query_string(Profile& pr, const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast)
    {
        return pr.pstade_pizza_query_string(pszValueName, pFirst, pLast);
    }

    template< class Profile > static
    void detail_delete(Profile& pr, const TCHAR *pszValueName)
    {
        pr.pstade_pizza_delete(pszValueName);
    }
};


} } // namespace pstade::pizza


#endif
