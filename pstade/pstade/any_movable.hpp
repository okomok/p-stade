#ifndef PSTADE_ANY_MOVABLE_HPP
#define PSTADE_ANY_MOVABLE_HPP


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
// as const-reference, hence it becomes unmovable. So we define...


#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/shared_ptr.hpp>


namespace pstade {


    namespace any_movable_detail {


        struct placeholder
        {
            virtual ~placeholder()
            { }
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

        private:
            X m_x;
        };


        template<class To, class From> inline
        To& downcast(From& from)
        {
            return *boost::polymorphic_downcast<To *>(&from);
        }


    } // namespace any_movable_detail


    struct any_movable
    {
        explicit any_movable()
        { }

        template<class X>
        explicit any_movable(X x) :
            m_px(new any_movable_detail::holder<X>(x))
        { }

        template<class X>
        void reset(X x)
        {
            m_px.reset(new any_movable_detail::holder<X>(x));
        }

        template<class X>
        X& base() const
        {
            return any_movable_detail::downcast<
                any_movable_detail::holder<X>
            >(*m_px).held();
        }

    private:
        boost::shared_ptr<any_movable_detail::placeholder> m_px;
    };


} // namespace pstade


#endif
