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
- `P-Stade C++ Libraries Version 1.02.4`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition SP1
- Microsoft Visual C++ .NET Version 7.1 SP1
- GCC 3.4.4



``PSTADE_ADL_BARRIER``
----------------------
``PSTADE_ADL_BARRIER`` protects names from ADL invasions::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\adl_barrier.ipp

Now ``xxx::aaa`` is isolated from ``xxx::begin``, so ``::begin`` is called.

- Header: ``<pstade/adl_barrier.hpp>``
- Valid expression: ``PSTADE_ADL_BARRIER(id) { ... }``



``arg``
-------
A non-const rvalue cannot bind to the deduced non-const reference.
``arg`` works around it::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\arg.ipp

- Header: ``<pstade/arg.hpp>``
- Valid expression: ``arg(x)``



``arraya``
----------
``arraya`` is a replacement for the infamous ``alloca``.

- Header: ``<pstade/arraya.hpp>``
- Valid expression: ``arraya<t> a(sz);`` and ``a.get()``, where ``t`` is a typename.
- Semantics: ``a.get()`` returns a pointer whose type is ``t*``.



``const_``
----------
``const_`` just const-qualifies its argument.

- Header: ``<pstade/const.hpp>``
- Valid expression: ``const_(x)``



``const_overloaded``
--------------------
Pending...



``derived_cast``
----------------

``derived_cast`` is a type-safe cast from a base class to the derived class.
It just calls ``static_cast``, but the name makes codes clearer::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\derived_cast.ipp

``derived`` provides the automatic conversion.


- Header: ``<pstade/const.hpp>``
- Valid expression: ``D& d = derived(b)``
- Precondition: ``D`` is derived from the type of ``b``.


Design by Contract
------------------

Pending...

- Header: ``<pstade/contract.hpp>``


``PSTADE_PRECONDITION``
^^^^^^^^^^^^^^^^^^^^^^^

``PSTADE_PUBLIC_PRECONDITION``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``PSTADE_BLOCK_INVARIANT``
^^^^^^^^^^^^^^^^^^^^^^^^^^



``PSTADE_INSTANCE``
-------------------
C++ has the power to define objects in headers by using ``static`` keyword, but
has some pitfalls, which ``PSTADE_INSTANCE`` works around.


- Header: ``<pstade/instance.hpp>``
- Valid expression: ``PSTADE_INSTANCE(t, n, value)`` or ``PSTADE_INSTANCE(t, n, seq)``



``is_ndebug``
-------------
``is_ndebug`` is a nullary Metafunction_ that returns ``boost::mpl::true_`` if ``NDEBUG`` is defined;
otherwise, ``boost::mpl::false_``. Moreover, it is convertible to ``boost::mpl::true_`` if ``NDEBUG`` is defined;
otherwise, convertible to ``boost::mpl::false_``::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\is_ndebug.ipp


- Header: ``<pstade/is_ndebug.hpp>``
- Valid expression: ``is_ndebug<>``



``is_same``
-----------

- Header: ``<pstade/is_same.hpp>``
- Valid expression: ``is_same(x, y)``
- Returns: ``true`` if ``x`` and ``y`` are the same object; otherwise, ``false``.



``new_``
--------
Pending...



``nonassignable``
-----------------
Class ``nonassignable`` is a base class.
Derive your own class from ``nonassignable`` when you want to prohibit copy assignment.

- Header: ``<pstade/nonassignable.hpp>``
- Valid expression: ``class A : nonassignable { ... };``
- Postcondition: ``a1 = a2`` is invalid, where ``a1`` and ``a2`` are types of ``A``.



``PSTADE_NULLPTR``
------------------
It is the macro which represents the null pointer, which is defined ``0``.
Additional information is available at the proposal `A name for the null pointer: nullptr`__.

__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1601.pdf



``pause``
---------
Pending...




``PSTADE_STATEMENT``
--------------------
Pending...



``static_c``
------------
Pending...



``PSTADE_UNPARENTHESIZE``
-------------------------
Macros regard `,` as an argument separator. This makes problem when
you pass a type to macros. ``PSTADE_UNPARENTHESIZE`` works around it::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\unparenthesize.ipp

If the argument type is a dependent name, add ``typename`` before.


- Header: ``<pstade/unparenthesize.hpp>``
- Valid expression: ``PSTADE_UNPARENTHESIZE((t))``
- Precondition: ``t`` is a type name.



``unused``
----------
Though an unused variable makes the cumbersome "unused variable" warning, it sometimes helps you.
The legacy workaround shows::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\unused_bad.ipp

``unused`` is a function whose body is empty. It suppresses the warning::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\unused_good.ipp

A smart compiler easily removes such an empty function as ``unused``.
Note that ``(void)option`` could still make the warning. One of the useful cases is::

	E:\p-stade.sourceforge.net\pstade\libs\wine\doc\inline\unused_useful.ipp

The error seems conforming one, but ``unused`` can work around.



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
- Updated the document.
- Renamed ``PSTADE_COMMA_PROTECT`` to ``PSTADE_UNPARENTHESIZE``

