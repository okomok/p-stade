#ifndef PSTADE_OVEN_FUNCTION_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_FUNCTION_OUTPUT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not: 'boost::function_output_iterator'
//
// 'make_function_output_iterator' cannot take a function type,
// because a const-qualified function type is illegal.
// Also, Boost.Lambda functors are not assignable,
// then 'regularize_iterator' can help.
// But it wants 'difference_type' not to be 'void'
// which makes the declaration of 'operator[]' illegal.


// Note:
//
// This iterator seems underestimated.
// It could replace 'back_inserter' etc with lambda.


#include <iterator> // output_iterator_tag
#include "./regularize_iterator.hpp"


namespace pstade { namespace oven {


template< class UnaryFun >
struct function_output_iterator
{
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void pointer;
    typedef int  difference_type; 

    struct reference
    {
        reference(UnaryFun const& fun) :
            m_fun(fun)
        { }

        template< class Value >
        reference& operator=(Value const& val)
        {
            m_fun(val);
            return *this;
        }

    private:
        UnaryFun m_fun;
    };

    reference operator *() const { return reference(m_fun); }
    function_output_iterator& operator++() { return *this; }
    function_output_iterator operator++(int) { return *this; }

    explicit function_output_iterator()
    { }

    explicit function_output_iterator(UnaryFun const& fun) :
        m_fun(fun)
    { }

    UnaryFun functor() const
    {
        return m_fun;
    }

private:
    UnaryFun m_fun;
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
