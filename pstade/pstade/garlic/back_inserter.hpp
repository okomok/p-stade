#ifndef PSTADE_GARLIC_BACK_INSERTER_HPP
#define PSTADE_GARLIC_BACK_INSERTER_HPP


// PStade.Garlic
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // iterator, output_iterator_tag
#include <boost/assert.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/value_type.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/if_debug.hpp>
#include <pstade/nullptr.hpp>
#include "./push_back.hpp"


namespace pstade { namespace garlic {


template< class BackInsertable >
struct back_insert_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
    explicit back_insert_iterator()
        PSTADE_IF_DEBUG (
            : m_pbi(PSTADE_NULLPTR)
        )
    { }

    explicit back_insert_iterator(BackInsertable& bi) :
        m_pbi(boost::addressof(bi))
    { }

    template< class ValueT > // template is legal
    const back_insert_iterator& operator=(const ValueT& val) const
    {
        PSTADE_IF_DEBUG (
            BOOST_ASSERT(m_pbi != PSTADE_NULLPTR);
        )

        garlic::push_back(*m_pbi, val);
        return *this;
    }

    const back_insert_iterator& operator*() const { return *this; }
    const back_insert_iterator& operator++() const { return *this; }
    const back_insert_iterator operator++(int) const { return *this; }

private:
    BackInsertable *m_pbi; // for DefaultConstructible
};


template< class BackInsertable > inline const
back_insert_iterator<BackInsertable> back_inserter(BackInsertable& bi)
{
    return back_insert_iterator<BackInsertable>(bi);
}


} } // namespace pstade::garlic


#endif
