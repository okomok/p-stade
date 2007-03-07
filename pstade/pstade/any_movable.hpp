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


#include <typeinfo>
#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/radish/swappable.hpp>


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


        template<class To, class From> inline
        To& downcast(From& from)
        {
            return *boost::polymorphic_downcast<To *>(&from);
        }


    } // namespace any_movable_detail


    struct any_movable :
        private radish::swappable<any_movable>
    {
    private:
        typedef any_movable self_t;

    public:
        any_movable()
        { }

        template<class X>
        any_movable(X x) :
            m_px(new any_movable_detail::holder<X>(x))
        { }

        template< class X >
        self_t& operator=(X x)
        {
            self_t(x).swap(*this);
            return *this;
        }

        template<class X>
        X& base() const
        {
            return any_movable_detail::downcast<
                any_movable_detail::holder<X>
            >(*m_px).held();
        }

        bool empty() const
        {
            return !m_px;
        }

        std::type_info const& type() const
        {
            return m_px ? m_px->type() : typeid(void);
        }

        void swap(self_t& other)
        {
            m_px.swap(other.m_px);
        }

    private:
        boost::shared_ptr<any_movable_detail::placeholder> m_px;
    };


    template<class X>
    struct op_any_movable_cast
    {
        typedef X& result_type;

        result_type operator()(any_movable const& a) const
        {
            return a.base<X>();
        }
    };

    template<class X> inline
    typename boost::result_of<op_any_movable_cast<X>(any_movable const&)>::type
    any_movable_cast(any_movable const& a)
    {
        return op_any_movable_cast<X>()(a);
    }


} // namespace pstade


#endif
