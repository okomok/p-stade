#ifndef PSTADE_CLONE_PTR_HPP
#define PSTADE_CLONE_PTR_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <pstade/egg/do_swap.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/reset_assignment.hpp>
#include <pstade/type_equal_to.hpp>
#include "./detail/clonable.hpp"
#include "./detail/pointer_cast.hpp"


namespace pstade {


    namespace clone_ptr_detail {


        template<class O>
        struct virtual_new
        {
            typedef O *(*type)(O *p);
        };

        template<class O, class Q>
        struct override_new
        {
            static O *call(O *p)
            {
                BOOST_ASSERT(p);

                // Hmm, this cast lets primary new_clone eats derived types.
                return detail::clonable_new(*detail::pointer_cast<Q const>(p));
            }
        };


        template<class O>
        struct virtual_delete
        {
            typedef void (*type)(O *p);
        };

        template<class O, class Q>
        struct override_delete
        {
            static void call(O *p)
            {
                BOOST_ASSERT(p);
                detail::clonable_delete(detail::pointer_cast<Q>(p));
            }
        };


        template<class O>
        struct virtual_typeid
        {
            typedef std::type_info const &(*type)(O *);
        };

        template<class O, class Q>
        struct override_typeid
        {
            static std::type_info const &call(O *)
            {
                return typeid(Q);
            }
        };

        template<class O, class Q>
        struct override_typeid_rt
        {
            static std::type_info const &call(O *p)
            {
                (void)p;
                return typeid(*p);
            }
        };


        // This must be pod for static-initialization.
        template<class O>
        struct vtable
        {
            typename virtual_new<O>::type new_;
            typename virtual_delete<O>::type delete_;
            typename virtual_typeid<O>::type typeid_;
        };


        template<class O, class Q>
        vtable<O> const *vtable_pointer()
        {
            static vtable<O> const vtbl = {
                &override_new<O, Q>::call,
                &override_delete<O, Q>::call,
                &override_typeid<O, Q>::call
            };

            return &vtbl;
        }

        template<class O> inline
        vtable<O> const *vtable_pointer_rt()
        {
            static vtable<O> const vtbl = {
                &override_new<O, O>::call,
                &override_delete<O, O>::call,
                &override_typeid_rt<O, O>::call
            };

            return &vtbl;
        }



    } // namespace clone_ptr_detail


    template<class O>
    struct clone_ptr :
        radish::bool_testable  < clone_ptr<O>,
        radish::pointable      < clone_ptr<O>, O,
        radish::swappable      < clone_ptr<O>,
        boost::totally_ordered1< clone_ptr<O> > > > >
    {
    private:
        typedef clone_ptr self_t;

    public:
    // structors
        clone_ptr(boost::none_t = boost::none) :
            m_ptr(PSTADE_NULLPTR),
            m_pvtbl(PSTADE_NULLPTR)
        { }

        ~clone_ptr()
        {
            BOOST_ASSERT(invariant());

            if (m_pvtbl)
                m_pvtbl->delete_(m_ptr);
        }

        template<class Q>
        explicit clone_ptr(Q *p) :
            m_ptr(p),
            m_pvtbl(clone_ptr_detail::vtable_pointer<O, Q>())
        { }

        clone_ptr(self_t const &other) :
            m_ptr(other ? other.m_pvtbl->new_(other.m_ptr) : PSTADE_NULLPTR),
            m_pvtbl(other.m_pvtbl)
        { }

        // O_ must be a polymorphic Clonable.
        template<class O_>
        clone_ptr(clone_ptr<O_> const &other,
            typename enable_if< is_convertible<O_ *, O *> >::type = 0
        ) :
            m_ptr(other ? detail::clonable_new(*other) : PSTADE_NULLPTR),
            m_pvtbl(other ? clone_ptr_detail::vtable_pointer_rt<O>() : PSTADE_NULLPTR)
        { }

        template<class Q>
        clone_ptr(std::auto_ptr<Q> ap,
            typename enable_if< is_convertible<Q *, O *> >::type = 0
        ) :
            m_ptr(ap.release()),
            m_pvtbl(clone_ptr_detail::vtable_pointer<O, Q>())
        { }

    // assignments
        void reset(boost::none_t = boost::none)
        {
            self_t().swap(*this);
        }

        template<class Ptr>
        void reset(Ptr p)
        {
            self_t(p).swap(*this);
        }

        self_t &operator=(self_t const &other)
        {
            self_t(other).swap(*this);
            return *this;
        }

        PSTADE_MOVE_RESET_ASSIGNMENT(clone_ptr)

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(m_ptr);
        }

    // pointable
        O *operator->() const
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(m_ptr);
            return m_ptr;
        }

        O *get() const
        {
            BOOST_ASSERT(invariant());
            return m_ptr;
        }

    // swappable
        void swap(self_t &other) // nothrow
        {
            BOOST_ASSERT(invariant());
            egg::do_swap(m_ptr, other.m_ptr);
            egg::do_swap(m_pvtbl, other.m_pvtbl);
        }

    // totally_ordered
        bool operator< (self_t const &other) const
        {
            BOOST_ASSERT(invariant());
            return m_ptr < other.m_ptr;
        }

        bool operator==(self_t const &other) const
        {
            BOOST_ASSERT(invariant());
            return m_ptr == other.m_ptr;
        }

    // release/reset
        std::auto_ptr<O> release()
        {
            BOOST_ASSERT(invariant());
            std::auto_ptr<O> ap(m_ptr);
            m_ptr = PSTADE_NULLPTR;
            m_pvtbl = PSTADE_NULLPTR;
            return ap;
        }

    // boost::any compatibles
        bool empty() const
        {
            BOOST_ASSERT(invariant());
            return !m_ptr;
        }

        std::type_info const &type() const
        {
            BOOST_ASSERT(invariant());
            return !empty() ? m_pvtbl->typeid_(m_ptr) : typeid(void);
        }

    // content access
        template<class Q>
        bool contains() const
        {
            BOOST_ASSERT(invariant());
            return type_equal_to(this->type(), typeid(Q));
        }

        template<class Q>
        Q const &content() const
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(contains<Q>());
            return *detail::pointer_cast<Q const>(m_ptr);
        }

    private:
        O *m_ptr;
        clone_ptr_detail::vtable<O> const *m_pvtbl;

        bool invariant() const
        {
            return !m_ptr == !m_pvtbl;
        }
    };


} // namespace pstade


#endif
