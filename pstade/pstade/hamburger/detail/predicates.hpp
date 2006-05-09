#ifndef PSTADE_HAMBURGER_DETAIL_PREDICATES_HPP
#define PSTADE_HAMBURGER_DETAIL_PREDICATES_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include "../element.hpp"
#include "../point.hpp"


namespace pstade { namespace hamburger { namespace detail {


struct in_rectangle
{
    explicit in_rectangle(point pt) :
        m_pt(pt)
    { }

    typedef bool result_type;

    bool operator()(const element_node& nd) const
    {
        return tomato::boolean(nd.get_bounds().PtInRect(m_pt));
    }

private:
    point m_pt;
};


struct is_windowless_function
{
    typedef bool result_type;

    bool operator()(const element_node& nd) const
    {
        return nd.is_windowless();
    }
};


PSTADE_INSTANCE(const is_windowless_function, is_windowless, value);


struct z_order_function
{
    typedef bool result_type;

    template< class Node >
    bool operator()(Node& nd1, Node& nd2) const
    {
        int zIndex1 = pstade::lexical(nd1.att(Name_zIndex));
        int zIndex2 = pstade::lexical(nd2.att(Name_zIndex));
        return zIndex1 < zIndex2;
    }
};


PSTADE_INSTANCE(const z_order_function, z_order, value);


} } } // namespace pstade::hamburger::detail


#endif
