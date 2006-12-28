#ifndef PSTADE_TO_TYPE_HPP
#define PSTADE_TO_TYPE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// I love the name of 'boost::type', but she is not a metafunction!


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/type.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/lambda_sig.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    template< class Metafunction >
    struct to_type_impl :
        Metafunction
    { };

    template< class T >
    struct to_type_impl< boost::type<T> >
    {
        typedef T type;
    };


    template< class Type >
    struct to_type :
        to_type_impl<typename remove_cvr<Type>::type>
    { };


    PSTADE_ADL_BARRIER(to_type) {


        // lightweight 'callable' for cast functions
        template< class Derived >
        struct to_type_callable :
            lambda_sig
        {
            template< class Signature >
            struct result
            { };

            template< class Self, class From, class Type_To >
            struct result<Self(From, Type_To)> :
                to_type<Type_To>
            { };

            template< class From, class Type_To >
            typename to_type<Type_To>::type operator()(From& from, Type_To) const
            {
                return derived().BOOST_NESTED_TEMPLATE call<typename to_type<Type_To>::type>(from);
            }

            template< class From, class Type_To >
            typename to_type<Type_To>::type operator()(From const& from, Type_To) const
            {
                return derived().BOOST_NESTED_TEMPLATE call<typename to_type<Type_To>::type>(from);
            }

        private:
            Derived const& derived() const
            {
                return static_cast<Derived const&>(*this);
            }
        };


    } // ADL barrier


} // namespace pstade


#endif
