#ifndef PSTADE_OVEN_FUNCTION_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_FUNCTION_OUTPUT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Replaces 'boost::function_output_iterator'.
// 'regularize_iterator' for Boost.Lambda functors
// requires this iterator be *adaptable*.
// That is, the nested typedef's may not be 'void'.
// Note that this iterator cannot be implemented by using
// 'iterator_facade', because of the postfix-increment implementation.


#include <boost/mpl/void.hpp>
#include <iterator> // output_iterator_tag
#include "./regularize_iterator.hpp"


namespace pstade { namespace oven {


template< class UnaryFun >
struct function_output_iterator
{
    explicit function_output_iterator()
    { }

    explicit function_output_iterator(UnaryFun const& fun) :
        m_fun(fun)
    { }

// as "adaptor", 'oven::to_base' can kick in!
    typedef UnaryFun base_type;

    UnaryFun const& base() const
    {
        return m_fun;
    }

private:
    mutable UnaryFun m_fun;

public:
    typedef std::output_iterator_tag iterator_category;
    typedef boost::mpl::void_ value_type; // for 'postfix_increment_result'
    typedef boost::mpl::void_ pointer;    // for a rainy day
    typedef int difference_type;          // for 'iterator_facade::operator[]'

    struct reference                      // for adaptors
    {
        explicit reference(UnaryFun& fun) :
            m_fun(fun)
        { }

        // can replace 'for_each'?
        template< class Value >
        reference& operator=(Value& val)
        {
            m_fun(val);
            return *this;
        }

        template< class Value >
        reference& operator=(Value const& val)
        {
            m_fun(val);
            return *this;
        }

    private:
        UnaryFun& m_fun;
    };

    reference operator *() const { return reference(m_fun); }   // 'const' for adaptors.
    function_output_iterator& operator++() { return *this; }
    function_output_iterator& operator++(int) { return *this; } // must return reference.
};


template< class UnaryFun > inline
function_output_iterator<UnaryFun> const
to_function(UnaryFun fun = UnaryFun())
{
    return function_output_iterator<UnaryFun>(fun);
}


template< class UnaryFun > inline
regularize_iterator< function_output_iterator<UnaryFun> > const
to_regularized_function(UnaryFun fun = UnaryFun())
{
    return oven::make_regularize_iterator(oven::to_function(fun));
}


} } // namespace pstade::oven


#endif
