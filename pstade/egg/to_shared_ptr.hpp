#ifndef PSTADE_EGG_TO_SHARED_PTR_HPP
#define PSTADE_EGG_TO_SHARED_PTR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes 'shared_ptr' from a pointer.
// "make_shared_ptr" is reserved for the same function as 'new_shared'.


#include <boost/mpl/bool.hpp>
#include <boost/pointee.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/apple/auto_ptr_fwd.hpp>
#include <pstade/use_default.hpp>
#include "./function_by_value.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    namespace to_shared_ptr_detail {


        template<class Element>
        struct baby
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
            };

            template<class Result, class Ptr>
            Result call(Ptr p) const
            {
                return Result(p);
            }
        };


    } // namespace to_shared_ptr_detail


    template<class Element = boost::use_default>
    struct tp_to_shared_ptr
    {
        typedef
            function_by_value< to_shared_ptr_detail::baby<Element> >
        type;
    };


    template<class Element = boost::use_default>
    struct xp_to_shared_ptr :
        tp_to_shared_ptr<Element>::type
    { };


    typedef tp_to_shared_ptr<>::type op_to_shared_ptr;
    PSTADE_EGG_OBJECT((op_to_shared_ptr), to_shared_ptr) = { {} };


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


} } // namespace pstade::egg


#endif
