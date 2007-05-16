#ifndef PSTADE_OVEN_PASSER_HPP
#define PSTADE_OVEN_PASSER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Replaces 'boost::function_output_iterator',
// which is not adaptable using 'iterator_adaptor',
// and has no way to access its functor.
// Note that OutputIterator cannot always be implemented by using
// 'iterator_facade'; because of the postfix-increment implementation.


#include <iterator> // output_iterator_tag
#include <boost/mpl/void.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


namespace passer_detail {


    template< class UnaryFun >
    struct function_output_iterator
    {
        typedef UnaryFun function_type;

        explicit function_output_iterator(UnaryFun fun) :
            m_fun(fun)
        { }

        UnaryFun function() const
        {
            return m_fun;
        }

        // as "adaptor"; 'adapted_to' kicks in!
        UnaryFun base() const
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

        reference operator *() const { return reference(m_fun); } // 'const' for adaptors.
        function_output_iterator& operator++() { return *this; }
        function_output_iterator& operator++(int) { return *this; } // must return reference.
    };


} // namespace passer_detail


PSTADE_OBJECT_GENERATOR(passer,
    (passer_detail::function_output_iterator< deduce<_1, as_value> >) const)


} } // namespace pstade::oven


#endif
