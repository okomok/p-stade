#ifndef PSTADE_RADISH_ACCESS_HPP
#define PSTADE_RADISH_ACCESS_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace radish {


class access
{
public:
    template< class T, class OStream > static
    void detail_output(T const& x, OStream& os)
    {
        x.pstade_radish_output(os);
    }

    template< class Element, class T > static
    Element *detail_pointer(T const& x)
    {
        return x.pstade_radish_pointer();
    }

    template< class T > static
    void detail_swap(T& x, T& y)
    {
        x.pstade_radish_swap(y);
    }
};


} } // namespace pstade::radish


#endif
