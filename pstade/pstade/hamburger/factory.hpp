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
        void register_(ustring name, method_t m)
        {
            m_methods[name] = m;
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


    // Workaround:
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
void register_element(ustring name, factory_detail::method_t m)
{
    // Workaround:
    // Use 'impl_()' instead of 'impl' for GCC broken dynamic initialization.
    //
    factory_detail::impl_().register_(name, m);
}


template< class T > inline
void register_element(ustring name)
{
    // Workaround:
    // Without '&', VC8 sometimes misses 'new_method' at link time.
    //
    hamburger::register_element(name, &factory_detail::new_method<T>::call);
}


inline
element_node *create_element(element_node& parent, ustring name)
{
    return factory_detail::impl.create(parent, name);
}


} } // namespace pstade::hamburger


#endif
