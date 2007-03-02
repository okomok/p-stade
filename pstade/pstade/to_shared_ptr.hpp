#ifndef PSTADE_TO_SHARED_PTR_HPP
#define PSTADE_TO_SHARED_PTR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Passes a pointer to 'shared_ptr' constructor.
// Boost1.34 will make this deprecated.


#include <memory> // auto_ptr
#include <boost/mpl/bool.hpp>
#include <boost/pointee.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>


namespace pstade {


    // Avoid to use 'callable/function', which adds
    // const-qualifier to 'auto_ptr', then it becomes non-movable. 


    struct op_to_shared_ptr
    {
        template<class FunCall>
        struct result;

        template<class Fun, class Ptr>
        struct result<Fun(Ptr)> :
            result<Fun(typename pass_by_value<Ptr>::type)>
        { };

        template<class Fun, class X>
        struct result<Fun(X *)>
        {
            typedef X *type;
        };

        template<class Fun, class X>
        struct result<Fun(boost::shared_ptr<X>)>
        {
            typedef boost::shared_ptr<X> type;
        };

        template<class Fun, class X>
        struct result<Fun(std::auto_ptr<X>)>
        {
            typedef X *type;
        };

        template<class Ptr>
        typename result<void(Ptr)>::type
        operator()(Ptr p) const
        {
            return p;
        }

        template<class X>
        typename result<void(std::auto_ptr<X>)>::type
        operator()(std::auto_ptr<X> ap) const
        {
            return ap.release();
        }
    };


    PSTADE_CONSTANT(to_shared_ptr, (op_to_shared_ptr))


    template<class X, class Ptr>
    struct is_shared_ptr_constructible :
        boost::mpl::false_
    { };

    template<class X>
    struct is_shared_ptr_constructible< X, X * > :
        boost::mpl::true_
    { };

    template<class X>
    struct is_shared_ptr_constructible< X, boost::shared_ptr<X> > :
        boost::mpl::true_
    { };

    template<class X>
    struct is_shared_ptr_constructible< X, std::auto_ptr<X> > :
        boost::mpl::true_
    { };


    template<class X>
    struct shared_pointee :
        boost::pointee<
            typename pass_by_value<X>::type
        >
    { };


} // namespace pstade


#endif
