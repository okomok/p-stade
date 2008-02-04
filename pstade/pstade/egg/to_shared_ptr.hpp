#ifndef PSTADE_EGG_TO_SHARED_PTR_HPP
#define PSTADE_EGG_TO_SHARED_PTR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes 'shared_ptr' from a pointer.
// "make_shared_ptr" is reserved for the same function as 'shared_new'.


#include <boost/mpl/bool.hpp>
#include <boost/pointee.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/apple/auto_ptr_fwd.hpp>
#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/use_default.hpp>
#include "./by_value.hpp"


namespace pstade { namespace egg {


    namespace to_shared_ptr_detail {


        template<class Element>
        struct little
        {
            template<class Me, class Ptr>
            struct apply
            {
                typedef typename
                    eval_if_use_default< Element, boost::pointee<Ptr> >::type
                elem_t;

                typedef
                    boost::shared_ptr<elem_t>
                type;
            };

            template<class Re, class Ptr>
            Re call(Ptr p) const
            {
                return Re(p);
            }
        };


    } // namespace to_shared_ptr_detail


    template<class Element = boost::use_default>
    struct X_to_shared_ptr : derived_from<
        function<to_shared_ptr_detail::little<Element>, by_value>
    >
    { };


    typedef X_to_shared_ptr<>::base_class T_to_shared_ptr;
    PSTADE_POD_CONSTANT((T_to_shared_ptr), to_shared_ptr) = {{}};


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
