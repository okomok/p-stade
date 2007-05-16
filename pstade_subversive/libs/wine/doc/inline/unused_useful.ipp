struct X; // declaration only

X& foo();

void unused_is_nice()
{
    // foo(); error C2027 under VC8
    pstade::unused(foo()); // ok
}