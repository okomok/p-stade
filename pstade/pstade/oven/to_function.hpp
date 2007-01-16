#ifndef PSTADE_OVEN_TO_FUNCTION_HPP
#define PSTADE_OVEN_TO_FUNCTION_HPP


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
// Also, 'boost::function_output_iterator' doesn't provide a way
// to access its functor.
// Note that OutputIterator cannot always be implemented by using
// 'iterator_facade', because of the postfix-increment implementation.


#include <boost/mpl/void.hpp>
#include <boost/utility/result_of.hpp>
#include <iterator> // output_iterator_tag
#include <pstade/function.hpp>
#include <pstade/object_generator.hpp>
#include "./regularize_iterator.hpp"


namespace pstade { namespace oven {


namespace to_function_detail {


    template< class UnaryFun >
    struct output_iterator
    {
        typedef UnaryFun function_type;

        explicit output_iterator()
        { }

        explicit output_iterator(UnaryFun const& fun) :
            m_fun(fun)
        { }

        UnaryFun const& function() const
        {
            return m_fun;
        }

    // as "adaptor", 'oven::adapted_to' kicks in!
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
        output_iterator& operator++() { return *this; }
        output_iterator& operator++(int) { return *this; } // must return reference.
    };


} // namespace to_function_detail


PSTADE_OBJECT_GENERATOR(to_function, (to_function_detail::output_iterator< deduce<_1, to_value> >) const)


namespace to_regularized_function_detail {


    template< class UnaryFun >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_regularize_iterator(typename boost::result_of<op_to_function(UnaryFun&)>::type)
            >::type
        result;

        result call(UnaryFun& fun)
        {
            return make_regularize_iterator(to_function(fun));
        }
    };


} // namespace to_regularized_function_detail


PSTADE_FUNCTION(to_regularized_function, (to_regularized_function_detail::baby<_>))


} } // namespace pstade::oven


#endif
