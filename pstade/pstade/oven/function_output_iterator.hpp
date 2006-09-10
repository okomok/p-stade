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
// This iterator must be "adaptable" for 'regularize_iterator'.


#include <iterator> // output_iterator_tag
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/void.hpp>
#include "./regularize_iterator.hpp"


namespace pstade { namespace oven {


template< class UnaryFun >
struct function_output_iterator;


namespace function_output_iterator_detail {


    template< class UnaryFun >
    struct reference_proxy
    {
        reference_proxy(UnaryFun& fun) :
            m_fun(fun)
        { }

        // can replace 'for_each'?
        template< class Value >
        reference_proxy& operator=(Value& val)
        {
            m_fun(val);
            return *this;
        }

        template< class Value >
        reference_proxy& operator=(Value const& val)
        {
            m_fun(val);
            return *this;
        }

    private:
        UnaryFun& m_fun;
    };


    template< class UnaryFun >
    struct super_
    {
        typedef boost::iterator_facade<
            function_output_iterator<UnaryFun>,
            boost::mpl::void_, // 'postfix_increment_result' dislikes 'void'.
            std::output_iterator_tag,
            reference_proxy<UnaryFun>
        > type;
    };


} // namespace function_output_iterator_detail


template< class UnaryFun >
struct function_output_iterator :
    function_output_iterator_detail::super_<UnaryFun>::type
{
private:
    typedef typename function_output_iterator_detail::super_<UnaryFun>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    explicit function_output_iterator()
    { }

    explicit function_output_iterator(UnaryFun const& fun) :
        m_fun(fun)
    { }

private:
    mutable UnaryFun m_fun;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return ref_t(m_fun);
    }

    void increment()
    { }
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
