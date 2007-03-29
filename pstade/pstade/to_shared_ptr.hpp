#ifndef PSTADE_TO_SHARED_PTR_HPP
#define PSTADE_TO_SHARED_PTR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes 'shared_ptr' from a pointer.
// "make_shared_ptr" is reserved for the same function as 'pstade::new_shared'.


#include <memory> // auto_ptr
#include <boost/mpl/bool.hpp>
#include <boost/pointee.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/provide_sig.hpp>


namespace pstade {


    // Avoid to use 'callable/function', which adds
    // const-qualifier to 'auto_ptr', then it becomes non-movable. 


    struct op_to_shared_ptr :
        provide_sig
    {
        template<class FunCall>
        struct result
        { };

        template<class Fun, class Ptr>
        struct result<Fun(Ptr)>
        {
            typedef
                boost::shared_ptr<
                    typename boost::pointee<
                        typename pass_by_value<Ptr>::type
                    >::type
                >
            type;

            // Topic:
            // If 'result_of' returns const-qualified type,
            // 'remove_cv' is often cumbersome especially if the result type has value-semantics.
            // Actually pstade higher-order functions don't return const-qualified functors.
        };

        template<class Ptr>
        typename result<void(Ptr)>::type
        operator()(Ptr p) const
        {
            return typename result<void(Ptr)>::type(p);
        }
    };


    PSTADE_CONSTANT(to_shared_ptr, (op_to_shared_ptr))


    template<class X, class Ptr>
    struct is_to_shared_ptr_param :
        boost::mpl::false_
    { };

    template<class X>
    struct is_to_shared_ptr_param< X, X * > :
        boost::mpl::true_
    { };

    template<class X>
    struct is_to_shared_ptr_param< X, boost::shared_ptr<X> > :
        boost::mpl::true_
    { };

    template<class X>
    struct is_to_shared_ptr_param< X, std::auto_ptr<X> > :
        boost::mpl::true_
    { };



} // namespace pstade


#endif
