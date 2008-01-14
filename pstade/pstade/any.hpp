#ifndef PSTADE_ANY_HPP
#define PSTADE_ANY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/none.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/as_type_erasure.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/nonvirtual.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/reset_assignment.hpp>
#include <pstade/radish/swap_reset.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/type_equal_to.hpp>
#include "./any_fwd.hpp"


namespace pstade {


    namespace any_detail {


        struct placeholder
        {
            virtual std::type_info const &typeid_() const = 0;

        protected:
            PSTADE_NONVIRTUAL ~placeholder() { }
        };


        template<class X>
        struct holder :
            placeholder
        {
            explicit holder(X x) :
                m_x(x)
            { }

            typename boost::add_reference<X>::type held()
            {
                return m_x;
            }

            std::type_info const &typeid_() const // override
            {
                typedef typename boost::remove_reference<X>::type nonref_t;
                return typeid(boost::type<nonref_t>);
            }

        private:
            X m_x;
        };


        template<class Derived>
        struct super_ :
            radish::bool_testable<Derived,
            radish::swappable    <Derived> >
        {
            explicit super_()
            { }

            template<class Holder>
            explicit super_(Holder *p) :
                m_content(p)
            { }

        // boost::any compatibles
            bool empty() const
            {
                return !m_content;
            }

            std::type_info const &type() const
            {
                return m_content ? m_content->typeid_() : typeid(void);
            }

        // bool_testable
            operator radish::safe_bool() const
            {
                return radish::make_safe_bool(m_content);
            }

        // swappable
            void swap(Derived &other)
            {
                egg::do_swap(m_content, other.m_content);
            }

        protected:
            boost::shared_ptr<placeholder> m_content;
        };


    } // namespace any_detail


    // any_ref
    //

    struct any_ref :
        any_detail::super_<any_ref>
    {
    private:
        typedef any_ref self_t;
        typedef any_detail::super_<any_ref> super_t;

    public:
    // structors
        any_ref(boost::none_t = boost::none)
        { }

        template<class X>
        any_ref(X &x, typename disable_if_copy<self_t, X>::type = 0) :
            super_t(new any_detail::holder<X &>(x))
        { }

        template<class X>
        any_ref(X const &x) :
            super_t(new any_detail::holder<X const &>(x))
        { }

        any_ref(T_as_type_erasure, self_t &x) :
            super_t(new any_detail::holder<self_t &>(x))
        { }

        any_ref(T_as_type_erasure, self_t const &x) :
            super_t(new any_detail::holder<self_t const &>(x))
        { }

    // assignments
        typedef any_ref pstade_radish_this_type;
        #include PSTADE_RADISH_SWAP_RESET()
        #include PSTADE_RADISH_RESET_ASSIGNMENT()

    // content access
        template<class X>
        bool contains() const
        {
            return type_equal_to(type(), typeid(boost::type<X>));
        }

        template<class X>
        X &content() const
        {
            // `X` must be strictly the same as holder's; for consistency.
            // Though a conversion to const type is feasible, a conversion to super type is not.
            BOOST_ASSERT(contains<X>());
            return egg::static_downcast< any_detail::holder<X &> >(*m_content).held();
        }
    };


    // any_cref
    //

    struct any_cref :
        any_detail::super_<any_cref>
    {
    private:
        typedef any_cref self_t;
        typedef any_detail::super_<any_cref> super_t;

    public:
    // structors
        any_cref(boost::none_t = boost::none)
        { }

        template<class X>
        any_cref(X const &x) :
            super_t(new any_detail::holder<X const &>(x))
        { }

        any_cref(T_as_type_erasure, self_t const &x) :
            super_t(new any_detail::holder<self_t const &>(x))
        { }

    // assignments
        typedef any_cref pstade_radish_this_type;
        #include PSTADE_RADISH_SWAP_RESET()
        #include PSTADE_RADISH_RESET_ASSIGNMENT()

    // content access
        template<class X>
        bool contains() const
        {
            return type_equal_to(type(), typeid(boost::type<X>));
        }

        template<class X>
        X &content() const
        {
            BOOST_ASSERT(contains<X>());
            return egg::static_downcast< any_detail::holder<X &> >(*m_content).held();
        }
    };


    // any_movable
    //   This is not a Movable but CopyConstructible type.

    struct any_movable :
        any_detail::super_<any_movable>
    {
    private:
        typedef any_movable self_t;
        typedef any_detail::super_<any_movable> super_t;

    public:
    // structors
        any_movable(boost::none_t = boost::none)
        { }

        template<class X>
        any_movable(X x) :
            super_t(new any_detail::holder<X>(x))
        { }

        any_movable(T_as_type_erasure, self_t x) :
            super_t(new any_detail::holder<self_t>(x))
        { }

    // assignments
        typedef any_movable pstade_radish_this_type;
        #include PSTADE_RADISH_SWAP_RESET()
        #include PSTADE_RADISH_MOVE_RESET_ASSIGNMENT()

    // content access
        template<class X>
        bool contains() const
        {
            return type_equal_to(type(), typeid(boost::type<X>));
        }

        template<class X>
        X &content() const
        {
            BOOST_ASSERT(contains<X>());
            return egg::static_downcast< any_detail::holder<X> >(*m_content).held();
        }
    };


} // namespace pstade


#endif
