#ifndef PSTADE_TO_SHARED_PTR_HPP
#define PSTADE_TO_SHARED_PTR_HPP
#include "./detail/prefix.hpp"


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
#include <pstade/callable_by_value.hpp>
#include <pstade/constant.hpp>
#include <pstade/use_default.hpp>


namespace pstade {


    template<class Element = boost::use_default>
    struct op_to_shared_ptr :
        callable_by_value< op_to_shared_ptr<Element> >
    {
        template<class Myself, class Ptr>
        struct apply
        {
            typedef typename
                eval_if_use_default< Element, boost::pointee<Ptr> >::type
            elem_t;

            typedef
                boost::shared_ptr<elem_t>
            type;

            // Topic:
            // If 'result_of' returns const-qualified type,
            // 'remove_const' is often cumbersome especially if the result type has value-semantics.
            // Actually pstade higher-order functions don't return const-qualified functors.
        };

        template<class Result, class Ptr>
        Result call(Ptr p) const
        {
            return Result(p);
        }
    };


    PSTADE_CONSTANT(to_shared_ptr, (op_to_shared_ptr<>))


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
