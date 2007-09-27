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
// http://homepages.fh-regensburg.de/~mpool/mpool07/proceedings/5.pdf


// Preconditions:
//
// T and U is CopyConstructible.
// U is Convertible to T.


// Not tested yet.


#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/reset_assignment.hpp>


namespace pstade {


    template<class T>
    struct poly;


    namespace poly_detail {


        namespace here = poly_detail;


        template<class T> inline
        T *new_(T const &x)
        {
            return boost::heap_clone_allocator::allocate_clone(x);
        }
     
        template<class T> inline
        void delete_(T *ptr)
        {
            return boost::heap_clone_allocator::deallocate_clone(ptr);
        }


        template<class T>
        union buffer
        {
            T *ptr;
            char data[sizeof(T)*2];
        };


        template<class T, class U>
        struct is_local_aux :
            boost::mpl::bool_<
                (sizeof(U) <= sizeof(buffer<T>)) &&
                (boost::alignment_of< buffer<T> >::value % boost::alignment_of<U>::value == 0)
            >
        { };

        template<class T, class U>
        struct is_local :
            is_local_aux<T, typename boost::remove_cv<U>::type>
        { };


        template<class T>
        struct vdestructor
        {
            typedef void (*type)(buffer<T> &buf);
        };

        template<class T, class U>
        struct destructor
        {
            static void impl(buffer<T> &buf)
            {
                aux(buf, typename is_local<T, U>::type());
            }

        private:
            // local
            static void aux(buffer<T> &buf, boost::mpl::true_)
            {
                reinterpret_cast<U *>(&buf.data)->~U();
            }

            // heap
            static void aux(buffer<T> &buf, boost::mpl::false_)
            {
                here::delete_(buf.ptr);
            }
        };


        template<class T>
        struct vcopyconstructor
        {
            typedef void (*type)(buffer<T> const &buf, buffer<T> &to);
        };

        template<class T, class U>
        struct copyconstructor
        {
            static void impl(buffer<T> const &buf, buffer<T> &to)
            {
                aux(buf, to, typename is_local<T, U>::type());
            }

        private:
            // local
            static void aux(buffer<T> const &buf, buffer<T> &to, boost::mpl::true_)
            {
                U const * u = reinterpret_cast<U const *>(&buf.data);
                new ((void *)&to.data) U(*u);
            }

            // heap
            static void aux(buffer<T> const &buf, buffer<T> &to, boost::mpl::false_)
            {
                to.ptr = here::new_(*buf.ptr);
            }
        };


        template<class T>
        struct vgetter
        {
            typedef T *(*type)(buffer<T> &buf);
        };

        template<class T, class U>
        struct getter
        {
            static T *impl(buffer<T> &buf)
            {
                return aux(buf, typename is_local<T, U>::type());
            }

        private:
            // local
            static T *aux(buffer<T> &buf, boost::mpl::true_)
            {
                return reinterpret_cast<U *>(&buf.data);
            }

            // heap
            static T *aux(buffer<T> &buf, boost::mpl::false_)
            {
                return buf.ptr;
            }
        };


        template<class T>
        struct vtable
        {
            typename vdestructor<T>::type      dtor;
            typename vcopyconstructor<T>::type copy;
            typename vgetter<T>::type          get;

            vtable() :
                dtor(PSTADE_NULLPTR),
                copy(PSTADE_NULLPTR),
                get(PSTADE_NULLPTR)
            { }

            template<class U>
            void reset(U const &)
            {
                dtor = &destructor<T, U>::impl;
                copy = &copyconstructor<T, U>::impl;
                get  = &getter<T, U>::impl;
            }

            void reset()
            {
                dtor = PSTADE_NULLPTR;
                copy = PSTADE_NULLPTR;
                get  = PSTADE_NULLPTR;
            }
        };


        template<class T, class U>
        void construct(buffer<T> &buf, U const &u, typename enable_if< is_local<T, U> >::type = 0)
        {
            new ((void *)&buf.data) U(u);
        }

        template<class T, class U>
        void construct(buffer<T> &buf, U const &u, typename disable_if<is_local<T, U> >::type = 0)
        {
            buf.ptr = here::new_(u);
        }


        template<class T, class Injector>
        struct storage
        {
        private:
            typedef storage self_t;

        public:
        // structors
            storage()
            { }

            template<class U>
            explicit storage(U const &u)
            {
                m_vtbl.reset(u);
                construct(m_buff, u);
            }

            storage(storage const &other)
            {
                if (!other.empty()) {
                    m_vtbl = other.m_vtbl;
                    other.m_vtbl.copy(other.m_buff, m_buff);
                }
            }

            ~storage()
            {
                if (!empty())
                    m_vtbl.dtor(m_buff);
            }

        // assignments
            storage &operator=(storage const &other)
            {
                if (&other == this)
                    return *this;

                m_vtbl.dtor(m_buff);
                m_vtbl = other.m_vtbl;

                try {
                    other.m_vtbl.copy(other.m_buff, m_buff);
                }
                catch (...) {
                    m_vtbl.reset();
                    throw;
                }

                return *this;
            }

            template<class U>
            void reset(U const &u)
            {
                m_vtbl.dtor(m_buff);
                m_vtbl.reset(u);

                try {
                    construct(m_buff, u);
                }
                catch (...) {
                    m_vtbl.reset();
                    throw;
                }
            }

            void reset(boost::none_t = boost::none)
            {
                m_vtbl.dtor(m_buff);
                m_vtbl.reset();
            }

        // access
            bool empty() const
            {
                return !m_vtbl.dtor;
            }

        protected:
            T *get_() const
            {
                return !empty() ? m_vtbl.get(m_buff) : PSTADE_NULLPTR;
            }

        private:
            vtable<T> m_vtbl;
            buffer<T> m_buff;
        };


        template<class T>
        struct super_
        {
            typedef
                storage<T,
                    radish::bool_testable  < poly<T>,
                    radish::pointable      < poly<T>, T,
                    boost::totally_ordered1< poly<T> > > >
                >
            type;
        };

            
    } // namespace poly_detail


    template<class T>
    struct poly :
        poly_detail::super_<T>::type
    {
    private:
        typedef poly self_t;
        typedef typename poly_detail::super_<T>::type super_t;

    public:
    // structors
        poly()
        { }

        template<class U>
        poly(U const &u, typename enable_if< is_convertible<U, T> >::type = 0) :
            super_t(u)
        { }

    // assignments
        PSTADE_MOVE_RESET_ASSIGNMENT(self_t)

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(!this->empty());
        }

    // pointable
        T *operator->() const
        {
            BOOST_ASSERT(this->get_());
            return this->get_();
        }

        T *get() const
        {
            return this->get_();
        }

    // totally_ordered (todo)
        bool operator< (self_t const& other) const
        {
            return get() < other.get();
        }

        bool operator==(self_t const& other) const
        {
            return get() == other.get();
        }
    };


} // namespace pstade


#endif
