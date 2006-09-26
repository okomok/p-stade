/*#include <pstade/../libs/wine/test/assignable.cpp>
*/

#include <pstade/unique_ptr.hpp>

using namespace boost;


pstade::unique_ptr<int> make_unique_ptr1()
{
    pstade::unique_ptr<int> up(new int(10));
    // return up; // error
    return pstade::move(up);
}

pstade::unique_ptr<int> make_unique_ptr2()
{
    return pstade::unique_ptr<int>(new int(10));
}

int main()
{
    pstade::unique_ptr<int> up1(new int(1));
    // pstade::unique_ptr<int> up2(up1); // error
    pstade::unique_ptr<int> up3(pstade::move(up1));
}
