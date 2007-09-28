#ifndef PSTADE_POLY_HPP
#define PSTADE_POLY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// Boost.Function
// Boost.Optional
// http://homepages.fh-regensburg.de/~mpool/mpool07/proceedings/5.pdf


// Preconditions:
//
// O and Q is CopyConstructible.
// Q is Convertible to O.
// Q is Clonable.
//   (http://www.boost.org/libs/ptr_container/doc/reference.html#the-clonable-concept)


// Note:
//
// clone_ptr vs poly
//   clone_ptr is lightweight swappable.
//   poly can be lightweight copyable.


#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/reset_assignment.hpp>


namespace pstade {


    template<class O>
    struct poly;


    namespace poly_detail {


        namespace here = poly_detail;


        template<class O> inline
        O *new_(O const &o)
        {
            return boost::heap_clone_allocator::allocate_clone(o);
        }

        template<class O> inline
        void delete_(O *ptr)
        {
            return boost::heap_clone_allocator::deallocate_clone(ptr);
        }


        template<class O>
        union buffer
        {
            O *ptr;
            char m_data[sizeof(O)*2]; // do you know better size?

            void const *data() const { return &m_data[0]; }
            void       *data()       { return &m_data[0]; }
        };


        template<class O, class Q>
        struct is_local_aux :
            boost::mpl::bool_<
                (sizeof(Q) <= sizeof(buffer<O>)) &&
                (boost::alignment_of< buffer<O> >::value % boost::alignment_of<Q>::value == 0)
            >
        { };

        template<class O, class Q>
        struct is_local :
            is_local_aux<O, typename boost::remove_cv<Q>::type>
        { };


        template<class O>
        struct vdestructor
        {
            typedef void (*type)(buffer<O> &buf);
        };

        template<class O, class Q>
        struct destructor
        {
            static void call(buffer<O> &buf)
            {
                aux(buf, typename is_local<O, Q>::type());
            }

        private:
            // local
            static void aux(buffer<O> &buf, boost::mpl::true_)
            {
                reinterpret_cast<Q *>(buf.data())->~Q();
            }

            // heap
            static void aux(buffer<O> &buf, boost::mpl::false_)
            {
                here::delete_(buf.ptr);
            }
        };


        template<class O>
        struct vcopyconstructor
        {
            typedef void (*type)(buffer<O> const &buf, buffer<O> &to);
        };

        template<class O, class Q>
        struct copyconstructor
        {
            static void call(buffer<O> const &buf, buffer<O> &to)
            {
                aux(buf, to, typename is_local<O, Q>::type());
            }

        private:
            // local
            static void aux(buffer<O> const &buf, buffer<O> &to, boost::mpl::true_)
            {
                Q const * q = reinterpret_cast<Q const *>(buf.data());
                new (to.data()) Q(*q);
            }

            // heap
            static void aux(buffer<O> const &buf, buffer<O> &to, boost::mpl::false_)
            {
                to.ptr = here::new_(*buf.ptr);
            }
        };


        template<class O>
        struct vgetter
        {
            typedef O *(*type)(buffer<O> &buf);
        };

        template<class O, class Q>
        struct getter
        {
            static O *call(buffer<O> &buf)
            {
                return aux(buf, typename is_local<O, Q>::type());
            }

        private:
            // local
            static O *aux(buffer<O> &buf, boost::mpl::true_)
            {
                return reinterpret_cast<Q *>(buf.data());
            }

            // heap
            static O *aux(buffer<O> &buf, boost::mpl::false_)
            {
                return buf.ptr;
            }
        };


        template<class O>
        struct vtable
        {
            typename vdestructor<O>::type      dtor;
            typename vcopyconstructor<O>::type copy;
            typename vgetter<O>::type          get;

            vtable() :
                dtor(PSTADE_NULLPTR),
                copy(PSTADE_NULLPTR),
                get(PSTADE_NULLPTR)
            { }

            template<class Q>
            void reset(Q const &)
            {
                dtor = &destructor<O, Q>::call;
                copy = &copyconstructor<O, Q>::call;
                get  = &getter<O, Q>::call;
            }

            void reset()
            {
                dtor = PSTADE_NULLPTR;
                copy = PSTADE_NULLPTR;
                get  = PSTADE_NULLPTR;
            }
        };


        template<class O, class Q>
        void construct(buffer<O> &buf, Q const &q, typename enable_if< is_local<O, Q> >::type = 0)
        {
            new (buf.data()) Q(q);
        }

        template<class O, class Q>
        void construct(buffer<O> &buf, Q const &q, typename disable_if<is_local<O, Q> >::type = 0)
        {
            buf.ptr = new Q(q);
        }


        template<class O, class Injector>
        struct impl :
            Injector
        {
        private:
            typedef impl self_t;

        public:
        // structors
            impl()
            { }

            template<class Q>
            explicit impl(Q const &q)
            {
                m_vtbl.reset(q);
                construct(m_buff, q);
            }

            impl(impl const &other)
            {
                if (!other.empty()) {
                    m_vtbl = other.m_vtbl;
                    other.m_vtbl.copy(other.m_buff, m_buff);
                }
            }

            ~impl()
            {
                destruct_();
            }

        // assignments
            impl &operator=(impl const &other)
            {
                if (&other == this)
                    return *this;

                destruct_(); // nothrow
                m_vtbl = other.m_vtbl; // nothrow

                try {
                    other.m_vtbl.copy(other.m_buff, m_buff);
                }
                catch (...) {
                    m_vtbl.reset();
                    throw;
                }

                return *this;
            }

            template<class Q>
            void reset(Q const &q)
            {
                destruct_(); // nothrow
                m_vtbl.reset(q); // nothrow

                try {
                    construct(m_buff, q);
                }
                catch (...) {
                    m_vtbl.reset();
                    throw;
                }
            }

            void reset(boost::none_t = boost::none)
            {
                destruct_(); // nothrow
                m_vtbl.reset(); // nothrow
            }

        // access
            bool empty() const
            {
                return !m_vtbl.dtor;
            }

        protected:
            O *get_() const
            {
                return !empty() ? m_vtbl.get(m_buff) : PSTADE_NULLPTR;
            }

        private:
            vtable<O> m_vtbl;
            mutable buffer<O> m_buff;

            void destruct_() // nothrow
            {
                if (!empty())
                    m_vtbl.dtor(m_buff);
            }
        };


        template<class O>
        struct super_
        {
            typedef
                impl<O,
                    radish::bool_testable  < poly<O>,
                    boost::totally_ordered1< poly<O> > >
                >
            type;
        };

            
    } // namespace poly_detail


    template<class O>
    struct poly :
        poly_detail::super_<O>::type
    {
    private:
        typedef poly self_t;
        typedef typename poly_detail::super_<O>::type super_t;

    public:
    // structors
        poly()
        { }

        template<class Q>
        poly(Q const &q, typename enable_if< is_convertible<Q const &, O const &> >::type = 0) :
            super_t(q)
        { }

    // assignments
        PSTADE_MOVE_RESET_ASSIGNMENT(self_t)

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(!this->empty());
        }

    // pointer-like (const affects.)
        O *operator->()
        {
            BOOST_ASSERT(this->get_());
            return this->get_();
        }

        O const *operator->() const
        {
            BOOST_ASSERT(this->get_());
            return this->get_();
        }

        O &operator *()
        {
            BOOST_ASSERT(this->get_());
            return *this->get_();
        }

        O const &operator *() const
        {
            BOOST_ASSERT(this->get_());
            return *this->get_();
        }

    // totally_ordered (todo)
        bool operator< (self_t const& other) const
        {
            return this->get_() < other.get_();
        }

        bool operator==(self_t const& other) const
        {
            return this->get_() == other.get_();
        }

    // workaround
        PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(poly, super_t)
    };


} // namespace pstade


#endif
