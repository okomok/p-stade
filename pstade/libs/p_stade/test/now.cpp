

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/concept_check.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/noncopyable.hpp>


struct my// :
    //boost::noncopyable
{ };


template< class Iterator >
void foo(Iterator)
{
    boost::function_requires< boost_concepts::ReadableIteratorConcept<Iterator> >();
}


int main()
{
    boost::ptr_vector<my> vec;
    ::foo(vec.begin());
}
