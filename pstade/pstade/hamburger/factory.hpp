#ifndef PSTADE_HAMBURGER_FACTORY_HPP
#define PSTADE_HAMBURGER_FACTORY_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <map>
#include <boost/assert.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/cat.hpp>
#include <pstade/instance.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include "./element.hpp"
#include "./unknown.hpp"


namespace pstade { namespace hamburger {


namespace factory_detail {


    typedef boost::function<element_node *(element_node&)>
    method_t;


    struct impl_t :
        boost::noncopyable
    {
    private:
        typedef std::map<ustring, method_t> map_t;
        typedef map_t::iterator iter_t;

    public:
        const int& register_(ustring name, method_t m)
        {
            m_methods[name] = m;

            static const int dummy;
            return dummy;
        }

        element_node *create(element_node& parent, ustring childName)
        {
            iter_t it = m_methods.find(childName);
            if (it == m_methods.end()) {
                return new unknown();
            }

            return it->second(parent);
        }

    private:
        map_t m_methods;
    };


    PSTADE_INSTANCE(impl_t, impl, value);


    // VC7.1/8 seems still broken with function template with explicit argument.
    // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE can't work with Boost.Function.
    // So, the good old technique is here.
    //
    template< class T >
    struct new_method
    {
        static
        element_node *call(element_node& parent)
        {
            pstade::unused(parent);
            return new T();
        }
    };


} // namespace factory_detail


inline
const int& register_node(ustring name, factory_detail::method_t m)
{
    return factory_detail::impl.register_(name, m);
}


template< class T > inline
const int& register_node(ustring name)
{
    // Without '&', VC8 sometimes misses 'new_method' at link time. 
    return hamburger::register_node(name, &factory_detail::new_method<T>::call);
}


inline
element_node *create_node(element_node& parent, ustring name)
{
    return factory_detail::impl.create(parent, name);
}


typedef const int&
entry_type; // syntax sugar


} } // namespace pstade::hamburger


#endif
