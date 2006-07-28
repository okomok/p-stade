+++++++++++++++++++++++++
The Wine Utility Library
+++++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: MB
:Contact: mb2act@yahoo.co.jp 
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.90.4



.. epigraph::

	"*Language is wine upon the lips.*"
	
	-- Virginia Woolf



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------
Wine provides primitive functions and classes which are somehow missing from C++.
All the names belong to ``namespace pstade``.



Requirements
------------
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 1.00.2`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1
- GCC 3.4.4



``PSTADE_ADL_BARRIER``
----------------------



``arg``
-------
Pending...



``PSTADE_COMMA_PROTECT``
------------------------
Macros regards `,` as argument separator. This makes problem when
you pass a type to macros. ``PSTADE_COMMA_PROTECT`` works around it.



``const_``
----------
Pending...



``derived``
-----------

``pstade::derived_cast`` is a type-safe cast from a base class to the derived class.
It just calls ``static_cast``, but the name makes codes clearer::

	D:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\derived_cast.ipp

``pstade::derived`` provides the automatic conversion.



``new_``
--------



``PSTADE_INSTANCE``
-------------------
C++ has the power to define objects in headers by using 'static' keyword, but
has some pitfalls, which ``PSTADE_INSTANCE`` works around::



``is_debug``
------------
``is_debug`` is a nullary Metafunction_ that returns ``boost::mpl::true_`` if ``NDEBUG`` is not defined; otherwise ``boost::mpl::false_``::

	D:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\is_debug_eg.ipp

Macros and Metafunction_\s are on different layers. You might reject this fusion.
On the other hand, you must be against macros if "possible".



``PSTADE_NULLPTR``
------------------
It is the macro which represents the null pointer, which is defined ``0``.
Additional information is available at the proposal `A name for the null pointer: nullptr`__.

__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1601.pdf



``pause``
--------
todo




``PSTADE_STATEMENT``
--------------------
Pending...



``unused``
----------
Though an unused variable makes the cumbersome "unused variable" warning, it sometimes helps you.
The legacy workaround shows::

	D:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\unused_bad.ipp

``pstade::unused`` is a function whose body is empty. It suppresses the warning::

	D:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\unused_good.ipp

A smart compiler easily removes such an empty function as ``pstade::unused``.
Note that ``(void)option`` could still make the warning. One of the useful cases is::

	D:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\unused_useful.ipp

The error seems conforming one, but ``pstade::unused`` can work around.



Acknowledgments
---------------
- `P-Stade`_
- `C++ Template Metaprogramming`_
- `C++ Templates - The Complete Guide`_
- `Boost C++ Libraries`_
- `Boost.MPL`_
- `A Proposal to Improve const_iterator Use from C++0X Containers`__
- `A name for the null pointer: nullptr`__
- `Cast to void`__

__ http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2004/n1674.pdf
__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1601.pdf
__ http://gcc.gnu.org/ml/gcc-bugs/1999-06n/msg00493.html



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Released initial version.

Version 0.90.1
^^^^^^^^^^^^^^
- Updated the document.

Version 0.90.2
^^^^^^^^^^^^^^
- Removed ``const_``, which was the same as ``boost:lambda::make_const``.
- Changed ``nullptr_`` to the macro.

Version 0.90.3
^^^^^^^^^^^^^^
- ``const_`` came back.
- Renamed ``crtp_cast`` to ``derived_cast``.

Version 0.90.4
^^^^^^^^^^^^^^^

