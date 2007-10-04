++++++++++++++++++++++++
The Napkin Trace Library
++++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: Shunsuke Sogame
:Contact: pstade.mb@gmail.com
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.90.4



.. epigraph::

    "*But I cleaned them with my napkin.*"

    -- Dr. Nick



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------
Napkin is the simple header-only logging library which provides generic reference-like type to output devices::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\introduction.ipp

All the types, functions and objects are defined in namespace ``pstade::napkin``.



Requirements
------------
- `Boost C++ Libraries Version 1.34.0`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 1.05.3`__ or later (no compilation required)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition SP1
- Microsoft Visual C++ .NET Version 7.1 SP1
- GCC 3.4.4



Quick Start
-----------
1. Include the Napkin header::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\quick_start_0.ipp

2. Initialize `ostream`_::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\quick_start_1.ipp

3. Call ``operator<<``::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\quick_start_2.ipp



Basic Concepts
--------------


String
^^^^^^
A ``String`` is a null-terminated ``const char *``.


String Outputable
^^^^^^^^^^^^^^^^^
A ``StringOutputable`` is any ``out`` that either of the following expression is valid::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\basic_concepts_string_outputable.ipp

, where ``psz`` is a `String`_ and ``ov`` is a ``pstade::overload`` object.
It is unsurprising that many types conform to this simple concept; even ``afxDump``.


WideString
^^^^^^^^^^
A ``WideString`` is a null-terminated ``const wchar_t *``.


WideString Outputable
^^^^^^^^^^^^^^^^^^^^^
A ``WideStringOutputable`` is any ``out`` that either of the following expression is valid::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\basic_concepts_string_outputable.ipp

, where ``psz`` is a `WideString`_ and ``ov`` is a ``pstade::overload`` object.


Output Streamable
^^^^^^^^^^^^^^^^^
This concept comes from `Boost.LexicalCast`_;
an ``OutputStreamable`` is any type that
``operator<<`` is defined that takes a ``std::ostream`` or ``std::wostream`` 
object on the left hand side and an instance of the argument type on the right.
That means if you have already defined ``operator<<`` of your class,
Napkin can work with it.



Classes
-------


``ostream``
^^^^^^^^^^^
``ostream`` is the generic reference-like type to `String Outputable`_ objects.
The valid expressions are::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\classes_ostream_0.ipp

, where ``os`` is a ``ostream`` object, ``out`` is a `String Outputable`_ object and
``stm`` is a `Output Streamable`_ object.

``ostream`` conforms to also `Default Constructible`_ and `Assignable`_::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\classes_ostream_1.ipp

Its default `String Outputable`_ is `nout`_.
Note that ``ostream`` is of course a model of `String Outputable`_,
because a `String`_ is `Output Streamable`_ by definition.



``wostream``
^^^^^^^^^^^^
``wostream`` is the generic reference-like type to `WideString Outputable`_ objects.
The valid expressions are::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\classes_ostream_2.ipp

, where ``os`` is a ``ostream`` object, ``out`` is a `String Outputable`_ object and
``stm`` is a `Output Streamable`_ object.
The usage is the same as above.



``lock_ostream``
^^^^^^^^^^^^^^^^
``lock_ostream`` makes a `String Outputable`_ thread-safe::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\classes_lock_ostream_0.ipp

Except for not `Assignable`_, the valid expression and usage is same as `ostream`_.
Note that you must build `Boost.Thread`_ and include explicitly ``<pstade/napkin/lock_ostream.hpp>``.



``lock_wostream``
^^^^^^^^^^^^^^^^^
``lock_wostream`` makes a `WideString Outputable`_ thread-safe.
Except for not `Assignable`_, the valid expression and usage is same as `wostream`_.



Predefined String Outputables
-----------------------------


``nout``
^^^^^^^^
``nout`` is the object that conforms to both `String Outputable`_ and `WideString Outputable`_.
``nout`` throws out all the inputs, which is usable if you want to temporarily turn off a logging.


``dout``
^^^^^^^^
``dout`` is the object that conforms to both `String Outputable`_ and `WideString Outputable`_.
``dout`` outputs strings by using ``::OutputDebugString``.
This works only under Windows, so that you must explicitly include the header ``<pstade/napkin/dout.hpp>``.


Standard Containers
^^^^^^^^^^^^^^^^^^^
Napkin customizes the standard `Back Insertion Sequence`_\s by using the second valid expression of `String Outputable`_ or
`WideString Outputable`_ concept. If ``seq::value_type`` is convertible to ``char``, the ``seq`` is a model of `String Outputable`_, and
if ``seq::value_type`` is convertible to ``wchar_t``, the ``seq`` is a model of `WideString Outputable`_,
where ``seq`` is a type `Back Insertion Sequence`_.



Define your own String Outputable
---------------------------------
As an example, let's look into `dout`_ type definition::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\define_dout.ipp

Pretty simple.



Remove Side-effects
-------------------
Though Napkin provides `nout`_, you might want to remove all the side-effects under the release compilation.
An easy solution is maybe something like::

	E:\p-stade.sourceforge.net\pstade\libs\napkin\doc\inline\remove_side_effects.ipp

``PSTADE_IF_DEBUG`` disappears under the release compilation.
``PSTADE_UNPARENTHESIZE`` works only if the argument is a type.



Points of Interest
------------------
As mentioned above, `String Outputable`_ concept is simple.
You can chain, broadcast or add time information anyway you like.
Napkin could be a building block of your logging strategy.

Regardless of its flexibility, Napkin's implementaion is very small.
Napkin only makes use of `Boost.LexicalCast`_, which makes use of
``std::stringstream``.



References
----------
- `P-Stade`_
- `Boost C++ Libraries`_
- `Boost.LexicalCast`_
- `Boost.Log`__
- `Log for C++`__

__ http://www.torjo.com/
__ http://log4cpp.sourceforge.net/



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Initial version released.


Version 0.90.1
^^^^^^^^^^^^^^
- Supported standard `Back Insertion Sequence`_\s as `String Outputable`_.
- Extended `String Outputable`_ concept.
- Removed ``wnew``.


Version 0.90.2
^^^^^^^^^^^^^^
- Removed pointer style.


Version 0.90.3
^^^^^^^^^^^^^^
- Updated document.
- Added `lock_ostream`_ and `lock_wostream`_.

Version 0.90.4
^^^^^^^^^^^^^^
- Ported to Boost v1.34.


