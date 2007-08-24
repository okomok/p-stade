#ifndef PSTADE_EGG_SCOPE_GUARD_HPP
#define PSTADE_EGG_SCOPE_GUARD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/multi_index/detail/scope_guard.hpp>


#include <pstade/pod_constant.hpp>
#include "./generator.hpp"


namespace pstade { namespace egg {


    struct scope_guard
    {
    private:
        typedef boost::function<void()> guard_type;

        explicit scope_guard(guard_type fun) :
            m_fun(fun), m_dismissed(false)
        { }

        ~scope_guard()
        {
            if (!m_dismissed)
                m_fun();
        }

        void dismiss()
        {
            m_dismiss = true;
        }

    private:
        guard_type m_fun;
        bool m_dismissed;
    };


    namespace scope_guard_detail {


        struct impl_base
        {
            impl_base() :
                m_dismissed(false)
            { }

            void dismiss() const
            {
                m_dismissed = true;
            }

        protected:
            mutable bool m_dismissed;

        private:
            impl_base& operator=(impl_base const&);
        };


        template<class Function>
        struct impl :
            impl_base
        {
            explicit impl(Function fun) :
                m_fun(fun)
            { }

            ~impl()
            {
                if (!m_dismissed)
                    m_fun();
            }

        private:
            Function m_fun;
        };


    } // namespace scope_guard_detail

    
    typedef
        scope_guard_detail::impl_base const&
    scope_guard;


    typedef
        generator<
            scope_guard_detail::impl< deduce<boost::mpl::_1, as_value> >
        >::type
    op_make_scope_guard;

    PSTADE_POD_CONSTANT((op_make_scope_guard), make_scope_guard) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
