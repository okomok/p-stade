#ifndef PSTADE_OVEN_DETAIL_FILTER_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_FILTER_OUTPUT_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator>


namespace pstade { namespace oven { namespace detail {


template< class OutIter, class Predicate >
struct filter_output_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
    typedef OutIter base_type;
    typedef Predicate predicate_type;

    filter_output_iterator(OutIter it, Predicate fun) :
         m_it(it), m_pred(fun)
    { }

    OutIter base() const
    {
        return m_it;
    }

    Predicate predicate() const
    {
        return m_pred;
    }

private:
    OutIter m_it;
    Predicate m_pred;

// iterator implentation
    struct output_proxy
    {
        OutIter& m_it;
        Predicate& m_pred;

        // can replace 'for_each'?
        template< class Value >
        void operator=(Value& val)
        {
            if (m_pred(val))
                *m_it = val;
        }

        template< class Value >
        void operator=(Value const& val)
        {
            if (m_pred(val))
                *m_it = val;
        }
    };

public:
    output_proxy operator *()
    {
        output_proxy r = {m_it, m_pred};
        return r;
    }

    filter_output_iterator& operator++() { return *this; }
    filter_output_iterator& operator++(int) { return *this; }
};


} } } // namespace pstade::oven::detail


#endif
