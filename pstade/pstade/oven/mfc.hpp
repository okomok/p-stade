#ifndef PSTADE_OVEN_MFC_HPP
#define PSTADE_OVEN_MFC_HPP
#include "./prelude.hpp"



// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



// forward declarations
//


template< class Type, class ArgType >
class CArray;

template< class Type, class ArgType >
class CList;

template< class Key, class ArgKey, class Mapped, class ArgMapped >
class CMap;

template< class BaseClass, class PtrType >
class CTypedPtrArray;

template< class BaseClass, class PtrType >
class CTypedPtrList;

template< class BaseClass, class KeyPtrType, class MappedPtrType >
class CTypedPtrMap;



// range extensions
//


#include <cstddef> // ptrdiff_t
#include <utility> // pair
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/apple/mfc/afx.hpp> // legacy CString
#include <pstade/apple/mfc/afxcoll.hpp> // CXXXArray, CXXXList, CMapXXXToXXX
#include <pstade/apple/mfc/config.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/const_overloaded.hpp>
#include "./atl.hpp" // seems to be allowed.
#include "./extension.hpp"
#include "./range_constant_iterator.hpp"
#include "./range_mutable_iterator.hpp"


namespace pstade_oven_extension {


    namespace ms_detail {

        // mfc_ptr_array_iterator
        //
        // 'void **' is not convertible to 'void const **',
        // so we define...
        //

        template< class ArrayT, class PtrType >
        struct mfc_ptr_array_iterator;

        template< class ArrayT, class PtrType >
        struct mfc_ptr_array_iterator_super
        {
            typedef boost::iterator_adaptor<
                mfc_ptr_array_iterator<ArrayT, PtrType>,
                std::ptrdiff_t, // Base!
                PtrType,        // Value
                boost::random_access_traversal_tag,
                boost::use_default,
                std::ptrdiff_t  // Difference
            > type;
        };

        template< class ArrayT, class PtrType >
        struct mfc_ptr_array_iterator :
            mfc_ptr_array_iterator_super<ArrayT, PtrType>::type
        {
        private:
            typedef mfc_ptr_array_iterator self_t;
            typedef typename mfc_ptr_array_iterator_super<ArrayT, PtrType>::type super_t;
            typedef typename super_t::reference ref_t;

        public:
            mfc_ptr_array_iterator()
            { }

            mfc_ptr_array_iterator(ArrayT& arr, INT_PTR index) :
                super_t(index), m_parr(boost::addressof(arr))
            { }

        template< class, class > friend struct mfc_ptr_array_iterator;
            template< class ArrayT_, class PtrType_ >
            mfc_ptr_array_iterator(
                mfc_ptr_array_iterator<ArrayT_, PtrType_> const& other,
                typename boost::enable_if_convertible<PtrType_, PtrType>::type * = 0
            ) :
                super_t(other.base()), m_parr(other.m_parr)
            { }

        private:
            ArrayT *m_parr;

        friend class boost::iterator_core_access;
            ref_t dereference() const
            {
                BOOST_ASSERT("out of range" && 0 <= this->base() && this->base() < m_parr->GetSize());
                return *( m_parr->GetData() + this->base() );
            }

            template< class Other >
            bool equal(Other const& other) const
            {
                BOOST_ASSERT("incompatible iterators" && m_parr == other.m_parr);
                return this->base() == other.base();
            }
        };

        struct mfc_ptr_array_functions
        {
            template< class Iterator, class X >
            Iterator begin(X& x)
            {
                return Iterator(x, 0);
            }

            template< class Iterator, class X >
            Iterator end(X& x)
            {
                return Iterator(x, x.GetSize());
            }
        };

    } // namespace ms_detail


    // arrays
    //

    template< >
    struct Range< ::CByteArray > :
        range_noncopyable,
        ms_detail::array_functions
    {
        template< class X >
        struct associate
        {
            typedef BYTE val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< >
    struct Range< ::CDWordArray > :
        range_noncopyable,
        ms_detail::array_functions
    {
        template< class X >
        struct associate
        {
            typedef DWORD val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< >
    struct Range< ::CObArray > :
        range_noncopyable,
        ms_detail::mfc_ptr_array_functions
    {
        template< class X >
        struct associate
        {
            typedef ms_detail::mfc_ptr_array_iterator<X, CObject *> mutable_iterator;
            typedef ms_detail::mfc_ptr_array_iterator<X const, CObject const *> constant_iterator;
        };
    };


    template< >
    struct Range< ::CPtrArray > :
        range_noncopyable,
        ms_detail::mfc_ptr_array_functions
    {
        template< class X >
        struct associate
        {
            typedef ms_detail::mfc_ptr_array_iterator<X, void *> mutable_iterator;
            typedef ms_detail::mfc_ptr_array_iterator<X const, void const *> constant_iterator;
        };
    };


    template< >
    struct Range< ::CStringArray > :
        range_noncopyable,
        ms_detail::array_functions
    {
        template< class X >
        struct associate
        {
            typedef ::CString val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< >
    struct Range< ::CUIntArray > :
        range_noncopyable,
        ms_detail::array_functions
    {
        template< class X >
        struct associate
        {
            typedef UINT val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< >
    struct Range< ::CWordArray > :
        range_noncopyable,
        ms_detail::array_functions
    {
        template< class X >
        struct associate
        {
            typedef WORD val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    // lists
    //

    template< >
    struct Range< ::CObList > :
        range_noncopyable,
        ms_detail::list_functions
    {
        template< class X >
        struct associate
        {
            typedef ms_detail::list_iterator<X, ::CObject *> mutable_iterator;
    #if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef ms_detail::list_iterator<X const, ::CObject const *> constant_iterator;
    #else
            typedef ms_detail::list_iterator<X const, ::CObject const * const, ::CObject const * const> constant_iterator;
    #endif
        };
    };


    template< >
    struct Range< ::CPtrList > :
        range_noncopyable,
        ms_detail::list_functions
    {
        template< class X >
        struct associate
        {
            typedef ms_detail::list_iterator<X, void *> mutable_iterator;
    #if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef ms_detail::list_iterator<X const, void const *> constant_iterator;
    #else
            typedef ms_detail::list_iterator<X const, void const * const, void const * const> constant_iterator;
    #endif
        };
    };


    template< >
    struct Range< ::CStringList > :
        range_noncopyable,
        ms_detail::list_functions
    {
        template< class X >
        struct associate
        {
            typedef ::CString val_t;

            typedef ms_detail::list_iterator<X, val_t> mutable_iterator;
    #if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef ms_detail::list_iterator<X const, val_t const> constant_iterator;
    #else
            typedef ms_detail::list_iterator<X const, val_t const, val_t const> constant_iterator;
    #endif
        };
    };


    namespace ms_detail {

        // mfc_map_iterator
        //

        template< class MapT, class KeyT, class MappedT >
        struct mfc_map_iterator;

        template< class MapT, class KeyT, class MappedT >
        struct mfc_map_iterator_super
        {
            typedef boost::iterator_facade<
                mfc_map_iterator<MapT, KeyT, MappedT>,
                std::pair<KeyT, MappedT>,
                boost::forward_traversal_tag,
                std::pair<KeyT, MappedT> const
            > type;
        };

        template< class MapT, class KeyT, class MappedT >
        struct mfc_map_iterator :
            mfc_map_iterator_super<MapT, KeyT, MappedT>::type
        {
        private:
            typedef mfc_map_iterator self_t;
            typedef typename mfc_map_iterator_super<MapT, KeyT, MappedT>::type super_t;
            typedef typename super_t::reference ref_t;

        public:
            explicit mfc_map_iterator()
            { }

            explicit mfc_map_iterator(MapT const& map, POSITION pos) :
                m_pmap(boost::addressof(map)), m_posNext(pos)
            {
                increment();
            }

            explicit mfc_map_iterator(MapT const& map) :
                m_pmap(&map), m_pos(0) // end iterator
            { }

        private:
            MapT const *m_pmap;
            POSITION m_pos, m_posNext;
            KeyT m_key; MappedT m_mapped;

        friend class boost::iterator_core_access;
            ref_t dereference() const
            {
                BOOST_ASSERT("out of range" && m_pos != 0);
                return std::make_pair(m_key, m_mapped);
            }

            void increment()
            {
                BOOST_ASSERT("out of range" && m_pos != 0);

                if (m_posNext == 0) {
                    m_pos = 0;
                    return;
                }

                m_pos = m_posNext;
                m_pmap->GetNextAssoc(m_posNext, m_key, m_mapped);
            }

            bool equal(self_t const& other) const
            {
                BOOST_ASSERT("incompatible iterators" && m_pmap == other.m_pmap);
                return m_pos == other.m_pos;
            }
        };

        struct mfc_map_functions
        {
            template< class Iterator, class X >
            Iterator begin(X& x)
            {
                return Iterator(x, x.GetStartPosition());
            }

            template< class Iterator, class X >
            Iterator end(X& x)
            {
                return Iterator(x);
            }
        };


    #if !defined(PSTADE_APPLE_MFC_NO_CPAIR)


        // mfc_cpair_map_iterator
        //
        // used by ::CMap and ::CMapStringToString
        //

        template< class MapT, class PairT >
        struct mfc_cpair_map_iterator;

        template< class MapT, class PairT >
        struct mfc_pget_map_iterator_super
        {
            typedef boost::iterator_facade<
                mfc_cpair_map_iterator<MapT, PairT>,
                PairT,
                boost::forward_traversal_tag
            > type;
        };

        template< class MapT, class PairT >
        struct mfc_cpair_map_iterator :
            mfc_pget_map_iterator_super<MapT, PairT>::type
        {
        private:
            typedef mfc_cpair_map_iterator self_t;
            typedef typename mfc_pget_map_iterator_super<MapT, PairT>::type super_t;
            typedef typename super_t::reference ref_t;

        public:
            mfc_cpair_map_iterator()
            { }

            mfc_cpair_map_iterator(MapT& map, PairT *pp) :
                m_pmap(boost::addressof(map)), m_pp(pp)
            { }

        template< class, class > friend struct mfc_cpair_map_iterator;
            template< class MapT_, class PairT_>
            mfc_cpair_map_iterator(
                mfc_cpair_map_iterator<MapT_, PairT_> const& other,
                typename boost::enable_if_convertible<PairT_ *, PairT *>::type * = 0
            ) :
                m_pmap(other.m_pmap), m_pp(other.m_pp)
            { }

        private:
            MapT  *m_pmap;
            PairT *m_pp;

        friend class boost::iterator_core_access;
            ref_t dereference() const
            {
                BOOST_ASSERT("out of range" && m_pp != 0);
                return *m_pp;
            }

            void increment()
            {
                BOOST_ASSERT("out of range" && m_pp != 0);
                m_pp = m_pmap->PGetNextAssoc(m_pp);
            }

            template< class Other >
            bool equal(Other const& other) const
            {
                BOOST_ASSERT("incompatible iterators" && m_pmap == other.m_pmap);
                return m_pp == other.m_pp;
            }
        };

        struct mfc_cpair_map_functions
        {
            template< class Iterator, class X >
            Iterator begin(X& x)
            {
                // Workaround:
                // Assertion fails if empty.
                // MFC document is wrong.
        #if !defined(NDEBUG)
                if (x.GetCount() == 0) 
                    return Iterator(x, 0);
        #endif

                return Iterator(x, x.PGetFirstAssoc());
            }

            template< class Iterator, class X >
            Iterator end(X& x)
            {
                return Iterator(x, 0);
            }
        };

#endif // !defined(PSTADE_APPLE_MFC_NO_CPAIR)

    } // namespace ms_detail


    // maps
    //

    template< >
    struct Range< ::CMapPtrToWord > :
        range_noncopyable,
        ms_detail::mfc_map_functions
    {
        template< class X >
        struct associate
        {
            typedef void *key_t;
            typedef WORD mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };
    };


    template< >
    struct Range< ::CMapPtrToPtr > :
        range_noncopyable,
        ms_detail::mfc_map_functions
    {
        template< class X >
        struct associate
        {
            typedef void *key_t;
            typedef void *mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };
    };


    template< >
    struct Range< ::CMapStringToOb > :
        range_noncopyable,
        ms_detail::mfc_map_functions
    {
        template< class X >
        struct associate
        {
            typedef ::CString key_t;
            typedef ::CObject *mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };
    };


    template< >
    struct Range< ::CMapStringToPtr > :
        range_noncopyable,
        ms_detail::mfc_map_functions
    {
        template< class X >
        struct associate
        {
            typedef ::CString key_t;
            typedef void *mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };
    };


    template< >
    struct Range< ::CMapStringToString > :
        range_noncopyable,
    #if !defined(PSTADE_APPLE_MFC_NO_CPAIR)
        ms_detail::mfc_cpair_map_functions
    #else
        ms_detail::mfc_map_functions
    #endif
    {
        template< class X >
        struct associate
        {
    #if !defined(PSTADE_APPLE_MFC_NO_CPAIR)
            typedef typename X::CPair pair_t;

            typedef ms_detail::mfc_cpair_map_iterator<X, pair_t> mutable_iterator;
            typedef ms_detail::mfc_cpair_map_iterator<X const, pair_t const> constant_iterator;
    #else
            typedef ::CString key_t;
            typedef ::CString mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
    #endif
        };
    };


    template< >
    struct Range< ::CMapWordToOb > :
        range_noncopyable,
        ms_detail::mfc_map_functions
    {
        template< class X >
        struct associate
        {
            typedef WORD key_t;
            typedef ::CObject *mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };
    };


    template< >
    struct Range< ::CMapWordToPtr > :
        range_noncopyable,
        ms_detail::mfc_map_functions
    {
        template< class X >
        struct associate
        {
            typedef WORD key_t;
            typedef void *mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };
    };


    // templates
    //

    template< class Type, class ArgType >
    struct Range< ::CArray<Type, ArgType> > :
        range_noncopyable,
        ms_detail::array_functions
    {
        template< class X >
        struct associate
        {
            typedef Type val_t;

            typedef val_t *mutable_iterator;
            typedef val_t const *constant_iterator;
        };
    };


    template< class Type, class ArgType >
    struct Range< ::CList<Type, ArgType> > :
        range_noncopyable,
        ms_detail::list_functions
    {
        template< class X >
        struct associate
        {
            typedef Type val_t;

            typedef ms_detail::list_iterator<X, val_t> mutable_iterator;
    #if !defined(PSTADE_APPLE_MFC_CONST_COL_RETURNS_NON_REF)
            typedef ms_detail::list_iterator<X const, val_t const> constant_iterator;
    #else
            typedef ms_detail::list_iterator<X const, val_t const, val_t const> constant_iterator;
    #endif
        };
    };


    template< class Key, class ArgKey, class Mapped, class ArgMapped >
    struct Range< ::CMap<Key, ArgKey, Mapped, ArgMapped> > :
        range_noncopyable,
    #if !defined(PSTADE_APPLE_MFC_NO_CPAIR)
        ms_detail::mfc_cpair_map_functions
    #else
        ms_detail::mfc_map_functions
    #endif
    {
        template< class X >
        struct associate
        {
    #if !defined(PSTADE_APPLE_MFC_NO_CPAIR)
            typedef typename X::CPair pair_t;

            typedef ms_detail::mfc_cpair_map_iterator<X, pair_t> mutable_iterator;
            typedef ms_detail::mfc_cpair_map_iterator<X const, pair_t const> constant_iterator;
    #else
            typedef Key key_t;
            typedef Mapped mapped_t;

            typedef ms_detail::mfc_map_iterator<X, key_t, mapped_t> mutable_iterator;
            typedef mutable_iterator constant_iterator;
    #endif            
        };
    };


    template< class BaseClass, class PtrType >
    struct Range< ::CTypedPtrArray<BaseClass, PtrType> > :
        range_noncopyable
    {
        template< class X >
        struct fun
        {
            typedef typename boost::remove_pointer<PtrType>::type val_t;

            typedef typename boost::mpl::if_< boost::is_const<X>,
                val_t const,
                val_t
            >::type val_t_;

            typedef val_t_ * const result_type;

            template< class PtrType_ >
            result_type operator()(PtrType_ p) const
            {
                return static_cast<result_type>(p);
            }

            // for Interoperatable
            fun()
            { }

            fun(fun<typename boost::remove_const<X>::type> const& other)
            { }
        };

        template< class X >
        struct associate
        {
            typedef typename pstade::oven::range_mutable_iterator<BaseClass>::type miter_t;
            typedef typename pstade::oven::range_constant_iterator<BaseClass>::type citer_t;

            typedef boost::transform_iterator<fun<X>, miter_t> mutable_iterator;
            typedef boost::transform_iterator<fun<X const>, citer_t> constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(boost::begin<BaseClass>(x), fun<X>());
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(boost::end<BaseClass>(x), fun<X>());
        }
    };


    template< class BaseClass, class PtrType >
    struct Range< ::CTypedPtrList<BaseClass, PtrType> > :
        range_noncopyable,
        ms_detail::list_functions
    {
        template< class X >
        struct associate
        {
            typedef typename boost::remove_pointer<PtrType>::type val_t;

            // not l-value
            typedef ms_detail::list_iterator<X, val_t * const, val_t * const> mutable_iterator;
            typedef ms_detail::list_iterator<X const, val_t const * const, val_t const * const> constant_iterator;
        };
    };


    template< class BaseClass, class KeyPtrType, class MappedPtrType >
    struct Range< ::CTypedPtrMap<BaseClass, KeyPtrType, MappedPtrType> > :
        range_noncopyable,
        ms_detail::mfc_map_functions
    {
        template< class X >
        struct associate
        {
            typedef ms_detail::mfc_map_iterator<X, KeyPtrType, MappedPtrType> mutable_iterator;
            typedef mutable_iterator constant_iterator;
        };
    };


    // strings
    //

#if defined(PSTADE_APPLE_MFC_HAS_LEGACY_STRING)

    template< >
    struct Range< ::CString >
    {
        template< class X >
        struct associate
        {
            // LPTSTR/LPCTSTR is not always defined in <tchar.h>.
            typedef TCHAR *mutable_iterator;
            typedef TCHAR const *constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x PSTADE_CONST_OVERLOADED(X))
        {
            return x.GetBuffer(0);
        }

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x;
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
            BOOST_FOREACH (TCHAR ch, rng) {
                x += ch;
            }

            return x;
        }
    };

#endif // defined(PSTADE_APPLE_MFC_HAS_LEGACY_STRING)


} // namespace pstade_oven_extension



// arrays
PSTADE_OVEN_EXTENSION_OF_TYPE((CByteArray))
PSTADE_OVEN_EXTENSION_OF_TYPE((CDWordArray))
PSTADE_OVEN_EXTENSION_OF_TYPE((CStringArray))
PSTADE_OVEN_EXTENSION_OF_TYPE((CUIntArray))
PSTADE_OVEN_EXTENSION_OF_TYPE((CWordArray))
PSTADE_OVEN_EXTENSION_OF_TYPE((CObList))
PSTADE_OVEN_EXTENSION_OF_TYPE((CPtrList))
PSTADE_OVEN_EXTENSION_OF_TYPE((CStringList))
PSTADE_OVEN_EXTENSION_OF_TYPE((CObArray))
PSTADE_OVEN_EXTENSION_OF_TYPE((CPtrArray))

// maps
PSTADE_OVEN_EXTENSION_OF_TYPE((CMapPtrToWord))
PSTADE_OVEN_EXTENSION_OF_TYPE((CMapPtrToPtr))
PSTADE_OVEN_EXTENSION_OF_TYPE((CMapStringToOb))
PSTADE_OVEN_EXTENSION_OF_TYPE((CMapStringToPtr))
PSTADE_OVEN_EXTENSION_OF_TYPE((CMapStringToString))
PSTADE_OVEN_EXTENSION_OF_TYPE((CMapWordToOb))
PSTADE_OVEN_EXTENSION_OF_TYPE((CMapWordToPtr))

// templates
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((CArray), 2)
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((CList), 2)
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((CMap), 4)
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((CTypedPtrArray), 2)
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((CTypedPtrList), 2)
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((CTypedPtrMap), 3)

// strings
#if defined(PSTADE_APPLE_MFC_HAS_LEGACY_STRING)
    PSTADE_OVEN_EXTENSION_OF_TYPE((CString))
#endif



#endif
