#ifndef PSTADE_OVEN_ATL_HPP
#define PSTADE_OVEN_ATL_HPP



// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



// forward declarations
//


#include <pstade/apple/atl/base_fwd.hpp>
#include <pstade/apple/atl/coll_fwd.hpp>
#include <pstade/apple/atl/comcli_fwd.hpp>
#include <pstade/apple/atl/core_fwd.hpp>
#include <pstade/apple/atl/cstringt_fwd.hpp>
#include <pstade/apple/atl/simpcoll_fwd.hpp>
#include <pstade/apple/atl/str_fwd.hpp>



// 'boost::pointee' extensions
//

#if !defined(PSTADE_OVEN_ATL_NO_POINTEE_SPECIALIZATIONS)


#include <boost/mpl/identity.hpp>
#include <boost/pointee.hpp>


namespace boost {


    template< class E >
    struct pointee< ATL::CAutoPtr<E> > :
        mpl::identity<E>
    { };

    template< class T >
    struct pointee< ATL::CComPtr<T> > :
        mpl::identity<T>
    { };

    template< class T, const IID *piid >
    struct pointee< ATL::CComQIPtr<T, piid> > :
        mpl::identity<T>
    { };

    template< class E, class Allocator >
    struct pointee< ATL::CHeapPtr<E, Allocator> > :
        mpl::identity<E>
    { };

    template< class T >
    struct pointee< ATL::CAdapt<T> > :
        pointee<T>
    { };


} // namespace boost


#endif // !defined(PSTADE_OVEN_ATL_NO_POINTEE_SPECIALIZATIONS)



// range extensions
//


#include <boost/foreach.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/apple/atl/base.hpp> // CComBSTR
#include <pstade/apple/atl/config.hpp>
#include <pstade/apple/atl/is_ATL_string.hpp>
#include "./detail/ms_extension.hpp"
#include "./extension.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade_oven_extension {


#if !defined(PSTADE_APPLE_ATL_NO_COLLECTIONS)


    // arrays
    //

    namespace ms_detail {

        struct atl_array_functions :
            array_functions
        {
            template< class Iterator, class X >
            Iterator end(X& x) // redefine
            {
                return x.GetData() + x.GetCount(); // no 'GetSize()'
            }
        };

    } // namespace ms_detail


    template< class E, class ETraits >
    struct Range< ATL::CAtlArray<E, ETraits> > :
        range_noncopyable,
        ms_detail::atl_array_functions
    {
        template< class X >
        struct associate
        {
            typedef E val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< class E >
    struct Range< ATL::CAutoPtrArray<E> > :
        range_noncopyable,
        ms_detail::atl_array_functions
    {
        template< class X >
        struct associate
        {
            // ATL::CAutoPtr/CHeapPtr is no assignable.
            typedef ATL::CAutoPtr<E> val_t;
            typedef val_t *miter_t;
            typedef val_t const *citer_t;

            typedef boost::indirect_iterator<miter_t> mutable_iterator;
            typedef boost::indirect_iterator<citer_t> constant_iterator;
        };
    };


    template< class I, const IID *piid >
    struct Range< ATL::CInterfaceArray<I, piid> > :
        range_noncopyable,
        ms_detail::atl_array_functions
    {
        template< class X >
        struct associate
        {
            typedef ATL::CComQIPtr<I, piid> val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< class E, class ETraits >
    struct Range< ATL::CAtlList<E, ETraits> > :
        range_noncopyable,
        ms_detail::list_functions
    {
        template< class X >
        struct associate
        {
            typedef E val_t;

            typedef ms_detail::list_iterator<X, val_t> mutable_iterator;
            typedef ms_detail::list_iterator<X const, val_t const> constant_iterator;
        };
    };


    namespace ms_detail {

        struct indirected_list_functions
        {
            template< class Iterator, class X >
            Iterator begin(X& x)
            {
                typedef typename Iterator::base_type base_t; // == ms_detail::list_iterator
                return Iterator(base_t(x, x.GetHeadPosition()));
            }

            template< class Iterator, class X >
            Iterator end(X& x)
            {
                typedef typename Iterator::base_type base_t;
                return Iterator(base_t(x, POSITION(0)));
            }
        };

    } // namespace ms_detail


    template< class E >
    struct Range< ATL::CAutoPtrList<E> > :
        range_noncopyable,
        ms_detail::indirected_list_functions
    {
        template< class X >
        struct associate
        {
            typedef ATL::CAutoPtr<E> val_t;
            typedef ms_detail::list_iterator<X, val_t> miter_t;
            typedef ms_detail::list_iterator<X const, val_t const> citer_t;

            typedef boost::indirect_iterator<miter_t> mutable_iterator;
            typedef boost::indirect_iterator<citer_t> constant_iterator;
        };

    };


    template< class E, class Allocator >
    struct Range< ATL::CHeapPtrList<E, Allocator> > :
        range_noncopyable,
        ms_detail::indirected_list_functions
    {
        template< class X >
        struct associate
        {
            typedef ATL::CHeapPtr<E, Allocator> val_t;
            typedef ms_detail::list_iterator<X, val_t> miter_t;
            typedef ms_detail::list_iterator<X const, val_t const> citer_t;

            typedef boost::indirect_iterator<miter_t> mutable_iterator;
            typedef boost::indirect_iterator<citer_t> constant_iterator;
        };
    };


    template< class I, const IID *piid >
    struct Range< ATL::CInterfaceList<I, piid> > :
        range_noncopyable,
        ms_detail::list_functions
    {
        template< class X >
        struct associate
        {
            typedef ATL::CComQIPtr<I, piid> val_t;

            typedef ms_detail::list_iterator<X, val_t> mutable_iterator;
            typedef ms_detail::list_iterator<X const, val_t const> constant_iterator;
        };
    };


    // maps
    //

    namespace ms_detail {

        struct indirected_GetAt
        {
            template< class Reference, class List >
            static Reference call(List& lst, POSITION pos)
            {
                // 'CRBTree::GetAt' returns pointer, so indirect it!
                return *lst.GetAt(pos);
            }
        };

        struct rb_tree_range :
            range_noncopyable,
            ms_detail::list_functions
        {
            template< class X >
            struct associate
            {
                typedef typename X::CPair val_t;

                typedef ms_detail::list_iterator<X, val_t,
                    boost::use_default, boost::use_default, indirected_GetAt> mutable_iterator;
                typedef ms_detail::list_iterator<X const, val_t const,
                    boost::use_default, boost::use_default, indirected_GetAt> constant_iterator;
            };
        };

    } // namespace ms_detail


    template< class K, class V, class KTraits, class VTraits >
    struct Range< ATL::CRBTree<K, V, KTraits, VTraits > > :
        ms_detail::rb_tree_range
    { };

    template< class K, class V, class KTraits, class VTraits >
    struct Range< ATL::CRBMap<K, V, KTraits, VTraits > > :
        ms_detail::rb_tree_range
    { };

    template< class K, class V, class KTraits, class VTraits >
    struct Range< ATL::CRBMultiMap<K, V, KTraits, VTraits > > :
        ms_detail::rb_tree_range
    { };

    template< class K, class V, class KTraits, class VTraits >
    struct Range< ATL::CAtlMap<K, V, KTraits, VTraits> > :
        ms_detail::rb_tree_range
    {
        template< class Iterator, class X >
        Iterator begin(X& x) // redefine; CAtlMap has no 'GetHeadPosition'.
        {
            return Iterator(x, x.GetStartPosition());
        }
    };


    // strings
    //

    template< class T >
    struct Range< T,
        typename where_< pstade::apple::is_ATL_string<T> >::type >
    {
        template< class X >
        struct associate
        {
            typedef typename X::PXSTR mutable_iterator;
            typedef typename X::PCXSTR constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x,
            typename const_overloaded<X>::type = 0)
        {
            return x.GetBuffer(0);
        }

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x.GetString();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.GetLength();
        }

        template< class X, class From >
        X copy(From& rng)
        {
            X x;

            typedef typename pstade::oven::
                range_reference<From>::type ref_t;

            BOOST_FOREACH (ref_t r, rng) {
                x.AppendChar(r);
            }

            return x;
        }
    };


    template< class BaseType, const int t_nSize >
    struct Range< ATL::CStaticString<BaseType, t_nSize> > :
        range_noncopyable
    {
        template< class X >
        struct associate
        {
            typedef BaseType const *mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x;
        }

        template< class Iterator, class X >
        Iterator end(X const& x)
        {
            return begin<Iterator>(x) + X::GetLength();
        }
    };


#endif // !defined(PSTADE_APPLE_ATL_NO_COLLECTIONS)


    template< >
    struct Range< ATL::CComBSTR >
    {
        template< class X >
        struct associate
        {
            typedef OLECHAR *mutable_iterator;
            typedef OLECHAR const *constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.operator BSTR();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.Length();
        }

        template< class X, class From >
        X copy(From& rng)
        {
            X x;
            BOOST_FOREACH (OLECHAR ch, rng) {
                x.Append(&ch, 1);
            }

            return x;
        }
    };


    // simples
    //

    namespace ms_detail {

        struct copyable_using_Add
        {
            template< class X, class From >
            X copy(From& rng)
            {
                typedef typename pstade::oven::
                    range_reference<From>::type ref_t;

                X x;
                BOOST_FOREACH (ref_t r, rng) {
                    x.Add(r);
                }

                return x;
            }
        };

    } // namespace ms_detail


    template< PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
    struct Range< ATL::CSimpleArray< PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > > :
        ms_detail::array_functions,
    #if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)
        ms_detail::copyable_using_Add
    #else
        range_noncopyable
    #endif
    {
        template< class X >
        struct associate
        {
            typedef T val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


#if defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)

    template< class T >
    struct Range< ATL::CSimpleValArray<T> > :
        range_noncopyable,
        ms_detail::array_functions
    {
        template< class X >
        struct associate
        {
            typedef T val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };

#endif // defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)


    template< PSTADE_APPLE_ATL_CSIMPLEMAP_TEMPLATE_PARAMS >
    struct Range< ATL::CSimpleMap< PSTADE_APPLE_ATL_CSIMPLEMAP_TEMPLATE_ARGS > > :
        range_noncopyable // how to copy?
    {
        template< class X >
        struct associate
        {
            typedef TKey k_val_t;
            typedef k_val_t *k_miter_t;
            typedef k_val_t const *k_citer_t;

            typedef TVal v_val_t;
            typedef v_val_t *v_miter_t;
            typedef v_val_t const *v_citer_t;

            // Topic:
            // 'std::pair' can't contain references
            // because of reference to reference problem.

            typedef boost::zip_iterator< boost::tuple<k_miter_t, v_miter_t> > mutable_iterator;
            typedef boost::zip_iterator< boost::tuple<k_citer_t, v_citer_t> > constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(boost::make_tuple(x.m_aKey, x.m_aVal));
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(boost::make_tuple(x.m_aKey + x.GetSize(), x.m_aVal + x.GetSize()));
        }
    };


} // namespace pstade_oven_extension



#if !defined(PSTADE_APPLE_ATL_NO_COLLECTIONS)

    // arrays
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CAtlArray), 2)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CAutoPtrArray), 1)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CInterfaceArray), (class)(const IID *))

    // lists
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CAtlList), 2)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CAutoPtrList), 1)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CHeapPtrList), 2)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CInterfaceList), (class)(const IID *))

    // maps
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CAtlMap), 4)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CRBTree), 4)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CRBMap), 4)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CRBMultiMap), 4)

    // strings
    #if !defined(BOOST_RANGE_ATL_HAS_OLD_CSIMPLESTRING)
        PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CSimpleStringT), (class)(bool))
    #else
        PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CSimpleStringT), 1)
    #endif
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CStringT), 2)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CFixedStringT), (class)(int))
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CStaticString), (class)(const int))

#endif // !defined(PSTADE_APPLE_ATL_NO_COLLECTIONS)

PSTADE_OVEN_EXTENSION_TYPE((ATL)(CComBSTR))

// simples
#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CSimpleArray), 2)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CSimpleMap), 3)
#else
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CSimpleArray), 1)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CSimpleMap), 2)
    PSTADE_OVEN_EXTENSION_TEMPLATE((ATL)(CSimpleValArray), 1)
#endif



// make_CAdapt
//


#include <pstade/apple/atl/comcli_fwd.hpp> // CAdapt
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>


namespace pstade { namespace oven {


    struct op_make_CAdapt :
        callable<op_make_CAdapt>
    {
        template< class Myself, class T >
        struct apply
        {
            typedef ATL::CAdapt<typename pass_by_value<T>::type> type;
        };

        template< class Result, class T >
        Result call(T& src) const
        {
            return Result(src);
        }
    };

    PSTADE_CONSTANT(make_CAdapt, (op_make_CAdapt))


} } // namespae pstade::oven



#endif
