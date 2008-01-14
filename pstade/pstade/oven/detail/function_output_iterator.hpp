#ifndef PSTADE_OVEN_DETAIL_FUNCTION_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_FUNCTION_OUTPUT_ITERATOR_HPP
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


template< class UnaryFun >
struct function_output_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
    typedef UnaryFun function_type;

    explicit function_output_iterator(UnaryFun fun) :
        m_fun(fun)
    { }

    UnaryFun function() const
    {
        return m_fun;
    }

// for 'adapted_to'
    UnaryFun base() const
    {
        return m_fun;
    }

private:
    UnaryFun m_fun;

// iterator implentation
    struct output_proxy
    {
        UnaryFun& m_fun;

        // can replace 'for_each'?
        template< class Value >
        void operator=(Value& val)
        {
            m_fun(val);
        }

        template< class Value >
        void operator=(Value const& val)
        {
            m_fun(val);
        }
    };

public:
    output_proxy operator *()
    {
        output_proxy r = {m_fun};
        return r;
    }

    function_output_iterator& operator++() { return *this; }
    function_output_iterator& operator++(int) { return *this; }
};


} } } // namespace pstade::oven::detail


#endif
