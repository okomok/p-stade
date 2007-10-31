#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range.hpp>

using namespace boost;

int main()
{
    function_requires<ForwardRangeConcept<iterator_range<int*> > >();
}
