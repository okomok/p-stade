#ifndef PSTADE_GARLIC_ACCESS_HPP
#define PSTADE_GARLIC_ACCESS_HPP


// PStade.Garlic
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace garlic {


class access
{
public:
    template< class T, class ValueT > static
    void detail_push_back(T& x, const ValueT& val)
    {
        x.pstade_garlic_push_back(x);
    }
};


} } // namespace pstade::garlic


#endif
