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
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/radish/bool_testable.hpp>


namespace pstade {


    namespace any_detail {


        struct placeholder
        {
            virtual ~placeholder() { }
            virtual std::type_info const &type() const = 0;
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

            virtual std::type_info const &type() const
            {
                return typeid(X);
            }

        private:
            X m_x;
        };


        struct super_ :
            radish::bool_testable<super_>
        {
            explicit super_()
            { }

            explicit super_(placeholder *p) :
                m_content(p)
            { }

            void reset()
            {
                m_content.reset();
            }

            operator radish::safe_bool() const
            {
                return radish::make_safe_bool(m_content);
            }

        // boost::any compatible
            bool empty() const
            {
                return !m_content;
            }

            std::type_info const& type() const
            {
                return m_content ? m_content->type() : typeid(void);
            }

        protected:
            boost::shared_ptr<placeholder> m_content;
        };


    } // namespace any_detail


    struct any_ref :
        any_detail::super_
    {
        any_ref()
        { }

        template<class X>
        any_ref(X &x, typename disable_if_copy<any_ref, X>::type = 0) :
            any_detail::super_(new any_detail::holder<X &>(x))
        { }

        template<class X>
        any_ref(X const &x) :
            any_detail::super_(new any_detail::holder<X const &>(x))
        { }

        template<class X>
        X &base() const
        {
            return egg::static_downcast< any_detail::holder<X &> >(*m_content).held();
        }
    };


    struct any_cref :
        any_detail::super_
    {
        any_cref()
        { }

        template<class X>
        any_cref(X const &x) :
            any_detail::super_(new any_detail::holder<X const &>(x))
        { }

        template<class X>
        X const &base() const
        {
            return egg::static_downcast< any_detail::holder<X const &> >(*m_content).held();
        }
    };


    struct any_movable :
        any_detail::super_
    {
        any_movable()
        { }

        template<class X>
        any_movable(X x) :
            any_detail::super_(new any_detail::holder<X>(x))
        { }

        template<class X>
        X &base() const
        {
            return egg::static_downcast< any_detail::holder<X> >(*m_content).held();
        }
    };


    template<class X>
    struct xp_any_ref_cast
    {
        typedef X &result_type;

        X &operator()(any_ref const &a) const
        {
            return a.base<X>();
        }
    };

    PSTADE_EGG_SPECIFIED1(any_ref_cast, xp_any_ref_cast, (class))


    template<class X>
    struct xp_any_cref_cast
    {
        typedef X const &result_type;

        X const &operator()(any_cref const &a) const
        {
            return a.base<X>();
        }
    };

    PSTADE_EGG_SPECIFIED1(any_cref_cast, xp_any_cref_cast, (class))


    template<class X>
    struct xp_any_movable_cast
    {
        typedef X &result_type;

        X& operator()(any_movable const &a) const
        {
            return a.base<X>();
        }
    };

    PSTADE_EGG_SPECIFIED1(any_movable_cast, xp_any_movable_cast, (class))


} // namespace pstade


#endif
