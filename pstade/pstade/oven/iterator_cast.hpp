#ifndef PSTADE_OVEN_ITERATOR_CAST_HPP
#define PSTADE_OVEN_ITERATOR_CAST_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Supports:
//
// eVC4


#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE, BOOST_NO_MEMBER_TEMPLATES
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>


#if defined(BOOST_NO_MEMBER_TEMPLATES)
    #define PSTADE_OVEN_ITERATOR_CAST_NO_BASE_ITERATOR
#endif


namespace pstade { namespace oven {


namespace iterator_cast_detail {


    // Note:
    // eVC4 doesn't allow functions(in this case, iterator_cast) to be separated
    // as definition and declaration if it has default arguments.
    template< class BaseIter, class Iterator >
    struct dispatcher;


} // namespace iterator_cast_detail


template< class BaseIter, class Iterator > inline
BaseIter iterator_cast(Iterator const& it BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(BaseIter))
{
    typedef typename iterator_cast_detail::dispatcher<BaseIter, Iterator>::type dispatcher_t;
    return dispatcher_t::call(it);
}


namespace iterator_cast_detail {


    template< class BaseIter, class Iterator >
    struct as_is
    {
        static BaseIter call(Iterator const& it)
        {
            return it;
        }
    };


    // Workaround:
    // The same function name as type often causes name conflict under eVC4.
    template< class BaseIter, class Iterator >
    struct base_ // base
    {
        static BaseIter call(Iterator const& it)
        {
            // recursive calls
            return oven::iterator_cast<BaseIter>(it.base());
        }
    };


    template< class BaseIter, class Iterator >
    struct dispatcher :
        boost::mpl::if_< boost::is_convertible<Iterator, BaseIter>,
            as_is<BaseIter, Iterator>,
            base_<BaseIter, Iterator>
        >
    { };


} // namespace iterator_cast_detail


#if !defined(PSTADE_OVEN_ITERATOR_CAST_NO_BASE_ITERATOR)


namespace iterator_cast_detail {


    template< class Iterator >
    struct temp
    {
        explicit temp(Iterator const& it) :
            m_it(it)
        { }

        template< class BaseIter >
        operator BaseIter() const
        {
            return oven::iterator_cast<BaseIter>(m_it);
        }

    private:
        Iterator m_it;
    };


} // namespace iterator_cast_detail


template< class Iterator > inline
iterator_cast_detail::temp<Iterator> const
base_iterator(Iterator const& it)
{
    return iterator_cast_detail::temp<Iterator>(it);
}


#endif // !defined(PSTADE_OVEN_ITERATOR_CAST_NO_BASE_ITERATOR)


} } // namespace pstade::oven


#endif
