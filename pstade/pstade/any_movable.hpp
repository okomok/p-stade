#ifndef PSTADE_ANY_MOVABLE_HPP
#define PSTADE_ANY_MOVABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::any' requires a held type to be CopyConstructible,
// but 'auto_ptr' etc is not. In detail, 'boost::any' takes it
// as const-reference, hence it becomes unmovable.
// you can wrap non-Copyable object with 'boost::shared_ptr';
//   'any = shared_ptr< auto_ptr<int> >(..);'
// But it is cumbersome and inefficient. So we define...


#include <typeinfo>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/specified.hpp>
#include <pstade/egg/static_downcast.hpp>


namespace pstade {


    namespace any_movable_detail {


        struct placeholder
        {
            virtual ~placeholder() { }
            virtual std::type_info const& type() const = 0;
        };


        template<class X>
        struct holder :
            placeholder
        {
            explicit holder(X& x) :
                m_x(x)
            { }

            X& held()
            {
                return m_x;
            }

            virtual std::type_info const& type() const
            {
                return typeid(X);
            }

        private:
            X m_x;
        };


    } // namespace any_movable_detail


    struct any_movable
    {
        any_movable()
        { }

        template<class X>
        any_movable(X x) :
            m_content(new any_movable_detail::holder<X>(x))
        { }

        template<class X>
        X& base() const
        {
            return egg::static_downcast< any_movable_detail::holder<X> >(*m_content).held();
        }

        bool empty() const
        {
            return !m_content;
        }

        std::type_info const& type() const
        {
            return m_content ? m_content->type() : typeid(void);
        }

    private:
        boost::shared_ptr<any_movable_detail::placeholder> m_content;
    };


    template<class X>
    struct op_any_movable_cast
    {
        typedef X& result_type;

        X& operator()(any_movable const& a) const
        {
            return a.base<X>();
        }
    };

    PSTADE_SPECIFIED1(any_movable_cast, op_any_movable_cast, 1)


} // namespace pstade


#endif
