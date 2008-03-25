#ifndef BOOST_EGG_TO_SHARED_PTR_HPP
#define BOOST_EGG_TO_SHARED_PTR_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
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
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/std_auto_ptr_fwd.hpp>


namespace boost { namespace egg {


    namespace to_shared_ptr_detail {


        template<class Element>
        struct little
        {
            template<class Me, class Ptr, class D = void, class A = void>
            struct apply
            {
                typedef typename
                    details::eval_if_use_default< Element, pointee<Ptr> >::type
                elem_t;

                typedef
                    shared_ptr<elem_t>
                type;
            };

            template<class Re, class Ptr>
            Re call(Ptr p) const
            {
                return Re(p);
            }

            template<class Re, class Ptr, class D>
            Re call(Ptr p, D d) const
            {
                return Re(p, d);
            }

            template<class Re, class Ptr, class D, class A>
            Re call(Ptr p, D d, A a) const
            {
                return Re(p, d, a);
            }
        };


    } // namespace to_shared_ptr_detail


    template<class Element = use_default>
    struct X_to_shared_ptr : details::derived_from<
        function<to_shared_ptr_detail::little<Element>, by_value> >
    { };

    typedef X_to_shared_ptr<>::base_class T_to_shared_ptr;
    BOOST_EGG_CONST((T_to_shared_ptr), to_shared_ptr) = {{}};


    template<class X, class Ptr>
    struct is_to_shared_ptr_param :
        mpl::false_
    { };

    template<class X>
    struct is_to_shared_ptr_param< X, X * > :
        mpl::true_
    { };

    template<class X>
    struct is_to_shared_ptr_param< X, shared_ptr<X> > :
        mpl::true_
    { };

    template<class X>
    struct is_to_shared_ptr_param< X, std::auto_ptr<X> > :
        mpl::true_
    { };


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
