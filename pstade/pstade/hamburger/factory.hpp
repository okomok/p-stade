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
#include <pstade/lime/ustring.hpp>
#include <pstade/unused.hpp>
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
        typedef std::map<lime::ustring, method_t> map_t;
        typedef map_t::iterator iter_t;

    public:
        const int& register_(lime::ustring name, method_t m)
        {
            m_methods[name] = m;

            static const int dummy;
            return dummy;
        }

        element_node *create(element_node& parent, lime::ustring childName)
        {
            iter_t it = m_methods.find(childName);
            if (it == m_methods.end()) {
				//std::string s = oven::sequence(childName);
                //BOOST_ASSERT(false);
                return new unknown();
            }

            return it->second(parent);
        }

    private:
        map_t m_methods;
    };


    PSTADE_INSTANCE(impl_t, impl, value);


    template< class T > inline
    element_node *new_method(element_node& parent)
    {
        pstade::unused(parent);
        return new T();
    }


} // namespace factory_detail


inline
const int& register_node(lime::ustring name, factory_detail::method_t m)
{
    return factory_detail::impl.register_(name, m);
}


template< class T > inline
const int& register_node(lime::ustring name)
{
    // Without '&', VC8 misses 'new_method' at link time. 
    return hamburger::register_node(name, &factory_detail::new_method<T>);
}


inline
element_node *create_node(element_node& parent, lime::ustring name)
{
    return factory_detail::impl.create(parent, name);
}


typedef const int&
entry_type; // syntax sugar


} } // namespace pstade::hamburger


#endif
