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


#include <boost/type.hpp>
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


    struct to_type_cast_result
    {
        template< class >
        struct result;

        template< class Self, class From, class Type_To >
        struct result<Self(From, Type_To)> :
            to_type<Type_To>
        { };
    };


} // namespace pstade


#endif
