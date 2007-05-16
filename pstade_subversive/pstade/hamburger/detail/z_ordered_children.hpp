#ifndef PSTADE_HAMBURGER_DETAIL_Z_ORDERED_CHILDREN_HPP
#define PSTADE_HAMBURGER_DETAIL_Z_ORDERED_CHILDREN_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> //sort
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/direct_range.hpp>
#include <pstade/oven/indirect_range.hpp>
#include "../element.hpp"


namespace pstade { namespace hamburger { namespace detail {


struct z_ordering
{
    bool operator()(element_node::iterator it1, element_node::iterator it2) const
    {
        int zIndex1 = pstade::lexical(it1->att(Name_zIndex));
        int zIndex2 = pstade::lexical(it2->att(Name_zIndex));
        return zIndex1 < zIndex2;
    }
};


struct z_ordered_children_base
{
    explicit z_ordered_children_base(element_node& parent)
    {
        oven::copy(parent|oven::directed, garlic::back_inserter(m_pchildren));
        std::sort(boost::begin(m_pchildren), boost::end(m_pchildren), z_ordering());
    }

protected:
    std::vector<element_node::iterator> m_pchildren;
};


template< class = void >
struct z_ordered_children_super
{
    typedef oven::indirect_range<
        std::vector<element_node::iterator>
    > type;
};


struct z_ordered_children :
    z_ordered_children_base,
    z_ordered_children_super<>::type
{
private:
    typedef z_ordered_children_base base_t;
    typedef z_ordered_children_super<>::type super_t;

public:
    explicit z_ordered_children(element_node& parent) :
        base_t(parent),
        super_t(base_t::m_pchildren)
    { }
};


} } } // namespace pstade::hamburger::detail


#endif
