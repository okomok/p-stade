#ifndef PSTADE_ENABLE_IF_HPP
#define PSTADE_ENABLE_IF_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::enable_if' using void pointer seems a mistake?
// GCC makes you write enable_if on function parameter list,
// then, void pointer that can eat any pointer would be dangerous.


namespace pstade {


    namespace enable_if_detail {

        struct klass;

    }


    typedef
        enable_if_detail::klass *
    enabler;


    template< bool B, class T = enabler >
    struct enable_if_c
    {
        typedef T type;
    };

    template< class T >
    struct enable_if_c<false, T>
    { };


    template< class Cond, class T = enabler > 
    struct enable_if :
        enable_if_c<Cond::value, T>
    { };


    template< bool B, class T >
    struct lazy_enable_if_c
    {
        typedef typename T::type type;
    };

    template< class T >
    struct lazy_enable_if_c<false, T>
    { };


    template< class Cond, class T > 
    struct lazy_enable_if :
        lazy_enable_if_c<Cond::value, T>
    { };


    template< bool B, class T = enabler >
    struct disable_if_c
    {
        typedef T type;
    };

    template< class T >
    struct disable_if_c<true, T>
    { };


    template< class Cond, class T = enabler > 
    struct disable_if :
        disable_if_c<Cond::value, T>
    { };


    template< bool B, class T >
    struct lazy_disable_if_c
    {
        typedef typename T::type type;
    };

    template< class T >
    struct lazy_disable_if_c<true, T>
    { };


    template< class Cond, class T > 
    struct lazy_disable_if :
        lazy_disable_if_c<Cond::value, T>
    { };


} // namespace pstade


#endif
