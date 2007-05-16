
#include <boost/concept/where.hpp> 
#include <boost/concept_check.hpp> // Convertible
#include <boost/mpl/identity.hpp>


// See:
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2081.pdf


template< class U, class T >
BOOST_CONCEPT_WHERE(
    ((boost::Convertible<T, U>))
    ((boost::Convertible<T, U>)),
(U)) convert(T const& x);


template< class U, class T >
typename boost::where_<
    boost::Convertible<T, U>,
    boost::where_<
        boost::Convertible<T, U>,
        boost::mpl::identity<U>
    >
>::type convert_(T const& x);


int main()
{
    ::convert<float>(17);
    // ::convert<int *>(17.0); // error
    ::convert_<float>(17);
    // ::convert_<int *>(17.0); // error
}
