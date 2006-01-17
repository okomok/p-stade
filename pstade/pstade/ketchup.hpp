#pragma once

#ifndef __ATLAPP_H__
	#error ketchup.hpp requires atlapp.h to be included first
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// inline aggressively
#pragma inline_recursion(on) // turn on inline recursion
#pragma inline_depth(255) // max inline depth


///////////////////////////////////////////////////////////////////////////////
// PStade.Ketchup
//
#include "./ketchup/cmd_ui.hpp"
#include "./ketchup/core.hpp"
#include "./ketchup/id.hpp"
#include "./ketchup/idset.hpp"
