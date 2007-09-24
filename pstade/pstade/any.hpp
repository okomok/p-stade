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
#include <boost/any.hpp>
#include <boost/assert.hpp>
#include <boost/none.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/automatic.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/reset_assignment.hpp>


namespace pstade {


    namespace any_detail {


        struct placeholder
        {
            virtual ~placeholder() { }
            virtual std::type_info const &typeid_() const = 0;
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

            explicit super_(placeholder *p) :
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


        template<class Result, class To, bool IsConstAny, bool IsConstTo = boost::is_const<To>::value>
        struct from_boost_any
        {
            template<class Any>
            static Result call(Any &a)
            {
                To *p = boost::any_cast<To>(&a);
                if (p)
                    return *p;
                else
                    return Result();
            }
        };

        template<class Result, class To>
        struct from_boost_any<Result, To, true, false>
        {
            template<class Any>
            static Result call(Any const &)
            {
                return Result();
            }
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

    // assignments
        template<class X>
        void reset(X &x)
        {
            self_t(x).swap(*this);
        }

        template<class X>
        void reset(X const &x)
        {
            self_t(x).swap(*this);
        }

        void reset(boost::none_t = boost::none)
        {
            self_t().swap(*this);
        }

        void reset(self_t &other)
        {
            m_content.reset(new any_detail::holder<self_t &>(other));
        }

        PSTADE_RESET_ASSIGNMENT(self_t)

        void reset(self_t const &other)
        {
            m_content.reset(new any_detail::holder<self_t const &>(other));
        }

    // base access
        template<class X>
        bool has_base() const
        {
            return make_bool(type() == typeid(boost::type<X>));
        }

        template<class X>
        X &base() const
        {
            // `X` must be strictly the same as holder's; for consistency.
            // Though a conversion to const type is feasible, a conversion to super type is not.
            BOOST_ASSERT(has_base<X>());
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

    // assignments
        template<class X>
        void reset(X const &x)
        {
            self_t(x).swap(*this);
        }

        void reset(boost::none_t = boost::none)
        {
            self_t().swap(*this);
        }

        PSTADE_RESET_ASSIGNMENT(self_t)

        void reset(self_t const &other)
        {
            m_content.reset(new any_detail::holder<self_t const &>(other));
        }

    // base access
        template<class X>
        bool has_base() const
        {
            return make_bool(type() == typeid(boost::type<X>));
        }

        template<class X>
        X &base() const
        {
            BOOST_ASSERT(has_base<X>());
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

    // assignments
        template<class X>
        void reset(X x)
        {
            self_t(x).swap(*this);
        }

        void reset(boost::none_t = boost::none)
        {
            self_t().swap(*this);
        }

        PSTADE_MOVE_RESET_ASSIGNMENT(self_t)

        void reset(self_t other)
        {
            m_content.reset(new any_detail::holder<self_t>(other));
        }

    // base access
        template<class X>
        bool has_base() const
        {
            return make_bool(type() == typeid(boost::type<X>));
        }

        template<class X>
        X &base() const
        {
            BOOST_ASSERT(has_base<X>());
            return egg::static_downcast< any_detail::holder<X> >(*m_content).held();
        }
    };


    // any_to
    //

    template<class X>
    struct xp_any_to
    {
        typedef X &result_type;

        template<class Any>
        X &operator()(Any const &a) const
        {
            return a.template base<X>();
        }

        X &operator()(boost::any &a) const
        {
            return boost::any_cast<X &>(a);
        }

        X const &operator()(boost::any const &a) const
        {
            return boost::any_cast<X const &>(a);
        }
    };

    PSTADE_EGG_SPECIFIED1(any_to, xp_any_to, (class))


    // from_any
    //

    template<class X>
    struct xp_from_any_to;

    template<class T>
    struct xp_from_any_to< boost::optional<T &> >
    {
        typedef boost::optional<T &> result_type;

        template<class Any>
        result_type operator()(Any const &a) const
        {
            if (a.template has_base<T>())
                return a.template base<T>();
            else
                return result_type();
        }

        result_type operator()(boost::any &a) const
        {
            return any_detail::from_boost_any<result_type, T, false>::call(a);
        }

        result_type operator()(boost::any const &a) const
        {
            return any_detail::from_boost_any<result_type, T, true >::call(a);
        }
    };

    typedef egg::automatic< xp_from_any_to<boost::mpl::_> >::type op_from_any;
    PSTADE_POD_CONSTANT((op_from_any), from_any) = PSTADE_EGG_AUTOMATIC;


} // namespace pstade


#endif
