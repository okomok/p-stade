#pragma once

// See:
//   Boost.Foreach or Boost.Serialization


// trigger intentional '2nd-phase ADL' into the global namespace.
struct pstade_overload_detail_adl_marker
{ };


namespace pstade {


typedef pstade_overload_detail_adl_marker overload;


} // namespace pstade
