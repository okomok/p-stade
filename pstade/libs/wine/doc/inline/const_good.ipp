#include <pstade/const.hpp>
// ...

double d = 3;
d = d*d;
d = d/d;

// ::apply(::reset, pstade::const_(d)); error!
::apply(::resee, pstade::const_(d));