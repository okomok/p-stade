#ifndef PSTADE_OVEN_DETAIL_ADAPTOR_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_ADAPTOR_OUTPUT_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator>


namespace pstade { namespace oven { namespace detail {


template< class OutIter, class BinaryFun >
struct adaptor_output_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
    typedef OutIter base_type;
    typedef BinaryFun adaptor_type;

    adaptor_output_iterator(OutIter it, BinaryFun fun) :
        m_it(it), m_fun(fun)
    { }

    OutIter base() const
    {
        return m_it;
    }

    BinaryFun function() const
    {
        return m_fun;
    }

private:
    OutIter m_it;
    BinaryFun m_fun;

// iterator implentation
    struct output_proxy
    {
        OutIter& m_it;
        BinaryFun& m_fun;

        template< class Value >
        void operator=(Value& val)
        {
            m_fun(m_it, val);
        }

        template< class Value >
        void operator=(Value const& val)
        {
            m_fun(m_it, val);
        }
    };

public:
    output_proxy operator *()
    {
        output_proxy r = {m_it, m_fun};
        return r;
    }

    adaptor_output_iterator& operator++() { return *this; }
    adaptor_output_iterator& operator++(int) { return *this; }
};


} } } // namespace pstade::oven::detail


#endif
