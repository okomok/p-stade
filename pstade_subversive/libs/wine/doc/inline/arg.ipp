template< class T >
void foo(T&)
{ }


void test()
{
    ::foo(pstade::arg(1));
}