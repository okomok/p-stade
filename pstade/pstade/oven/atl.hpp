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

#if !defined(PSTADE_OVEN_ATL_NO_POINTEE_EXTENSIONS)


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


#endif // !defined(PSTADE_OVEN_ATL_NO_POINTEE_EXTENSIONS)



// range extensions
//


#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/apple/atl/base.hpp> // CComBSTR
#include <pstade/apple/atl/config.hpp>
#include <pstade/apple/atl/is_ATL_string.hpp>
#include <pstade/const_overloaded.hpp>
#include "./detail/ms_extension.hpp"
#include "./extension.hpp"


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
    struct range< ATL::CAtlArray<E, ETraits> > :
        ms_detail::atl_array_functions
    {
        template< class X >
        struct meta
        {
            typedef E val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< class E >
    struct range< ATL::CAutoPtrArray<E> > :
        ms_detail::atl_array_functions
    {
        template< class X >
        struct meta
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
    struct range< ATL::CInterfaceArray<I, piid> > :
        ms_detail::atl_array_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CComQIPtr<I, piid> val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< class E, class ETraits >
    struct range< ATL::CAtlList<E, ETraits> > :
        ms_detail::list_functions
    {
        template< class X >
        struct meta
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
    struct range< ATL::CAutoPtrList<E> > :
        ms_detail::indirected_list_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CAutoPtr<E> val_t;
            typedef ms_detail::list_iterator<X, val_t> miter_t;
            typedef ms_detail::list_iterator<X const, val_t const> citer_t;

            typedef boost::indirect_iterator<miter_t> mutable_iterator;
            typedef boost::indirect_iterator<citer_t> constant_iterator;
        };
    };


    template< class E, class Allocator >
    struct range< ATL::CHeapPtrList<E, Allocator> > :
        ms_detail::indirected_list_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CHeapPtr<E, Allocator> val_t;
            typedef ms_detail::list_iterator<X, val_t> miter_t;
            typedef ms_detail::list_iterator<X const, val_t const> citer_t;

            typedef boost::indirect_iterator<miter_t> mutable_iterator;
            typedef boost::indirect_iterator<citer_t> constant_iterator;
        };
    };


    template< class I, const IID *piid >
    struct range< ATL::CInterfaceList<I, piid> > :
        ms_detail::list_functions
    {
        template< class X >
        struct meta
        {
            typedef ATL::CComQIPtr<I, piid> val_t;

            typedef ms_detail::list_iterator<X, val_t> mutable_iterator;
            typedef ms_detail::list_iterator<X const, val_t const> constant_iterator;
        };
    };


    // maps
    //

    namespace ms_detail {

        struct rb_tree_range :
            ms_detail::indirected_list_functions
        {
            template< class X >
            struct meta
            {
                typedef typename X::CPair val_t;

                typedef ms_detail::list_iterator<X, val_t *, val_t *> miter_t;
                typedef ms_detail::list_iterator<X const, val_t const *, val_t const *> citer_t;
                
                typedef boost::indirect_iterator<miter_t> mutable_iterator;
                typedef boost::indirect_iterator<citer_t> constant_iterator;
            };
        };

    } // namespace ms_detail


    template< class K, class V, class KTraits, class VTraits >
    struct range< ATL::CRBTree<K, V, KTraits, VTraits > > :
        ms_detail::rb_tree_range
    { };

    template< class K, class V, class KTraits, class VTraits >
    struct range< ATL::CRBMap<K, V, KTraits, VTraits > > :
        ms_detail::rb_tree_range
    { };

    template< class K, class V, class KTraits, class VTraits >
    struct range< ATL::CRBMultiMap<K, V, KTraits, VTraits > > :
        ms_detail::rb_tree_range
    { };

    template< class K, class V, class KTraits, class VTraits >
    struct range< ATL::CAtlMap<K, V, KTraits, VTraits> > :
        ms_detail::rb_tree_range
    {
        template< class Iterator, class X >
        Iterator begin(X& x) // redefine
        {
            typedef typename Iterator::base_type base_t; // == ms_detail::list_iterator
            return Iterator(base_t(x, x.GetStartPosition())); // no 'GetHeadPosition'
        }
    };


    // strings
    //

    template< class T >
    struct range< T, typename boost::enable_if< pstade::apple::is_ATL_string<T> >::type >
    {
        template< class X >
        struct meta
        {
            typedef typename X::PXSTR mutable_iterator;
            typedef typename X::PCXSTR constant_iterator;
        };

        template< class Iterator, class X >
        typename pstade::const_overloaded<Iterator, X>::type begin(X& x)
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
    };


    template< class BaseType, const int t_nSize >
    struct range< ATL::CStaticString<BaseType, t_nSize> >
    {
        template< class X >
        struct meta
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
    struct range< ATL::CComBSTR >
    {
        template< class X >
        struct meta
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
    };


    // simples
    //

    template< PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
    struct range< ATL::CSimpleArray< PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > > :
        ms_detail::array_functions
    {
        template< class X >
        struct meta
        {
            typedef T val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


#if defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)

    template< class T >
    struct range< ATL::CSimpleValArray<T> > :
        ms_detail::array_functions
    {
        template< class X >
        struct meta
        {
            typedef T val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };

#endif // defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLECOLL)


    template< PSTADE_APPLE_ATL_CSIMPLEMAP_TEMPLATE_PARAMS >
    struct range< ATL::CSimpleMap< PSTADE_APPLE_ATL_CSIMPLEMAP_TEMPLATE_ARGS > >
    {
        template< class X >
        struct meta
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



#endif
