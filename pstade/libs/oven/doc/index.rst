++++++++++++++++++++++
The Oven Range Library
++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: MB
:Contact: mb2act@yahoo.co.jp 
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.90.0



.. epigraph::

	"*Oh Paulie!*"
	
	-- Adrian



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------
The next `Boost.Range`_ library is under construction.
Oven provides some ranges and `Range Adaptors`_ for those who cannot wait for the official.
All the types and functions are defined in ``namespace pstade::oven``.



Requirements
------------
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 0.98.5`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1
- GCC 3.4.4



Ranges
------


array_range
^^^^^^^^^^^
- Valid expression: ``array_range<T> rng(sz);``
- Returns: ``[&arr, &arr+sz)``, where ``arr`` is initialized by the expression ``boost::scoped_array<T> arr(new T[sz]);``.


counting_range
^^^^^^^^^^^^^^
- Valid expression: ``counting_range<I> rng(n, m);``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::counting_iterator``.


empty_range
^^^^^^^^^^^
- Valid expression: ``empty_range<T> rng;``
- Returns: ``[static_cast<T *>(0), static_cast<T *>(0))``.


file_range
^^^^^^^^^^
- Valid expression: ``file_range<> rng;``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::file_iterator``.


single_range
^^^^^^^^^^^^
- Valid expression: ``single_range<T> rng(v);``
- Precondition: The type of ``v`` is ``T``.
- Returns: ``[&v, &v+1)``.



Range Adaptors
--------------


appended
^^^^^^^^
- Valid expression: ``rng|appended(v)``
- Precondition: ``v *`` is convertible to the ``iterator`` type of ``rng``.
- Returns: ``rng|jointed(make_single_range(v))``.


array_protected
^^^^^^^^^^^^^^^
- Valid expression: ``arr|array_protected``
- Precondition: ``arr`` is an array.
- Returns: ``[boost::begin(arr), boost::begin(arr)+sz)``, where ``sz`` is the size of ``arr``.


filtered
^^^^^^^^
- See: `Range Adaptors`_.



indirected
^^^^^^^^^^
- See: `Range Adaptors`_.


jointed
^^^^^^^
- Valid expression: ``rng1|jointed(rng2)``
- Precondition: The ``iterator`` type of ``rng2`` is convertible to ``rng1``\'s.
- Returns: A range that joints ``[boost::begin(rng1), boost::end(rng1))`` and ``[boost::begin(rng2), boost::end(rng2))``.


multi_passed
^^^^^^^^^^^^
- Valid expression: ``rng|multi_passed``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::multi_pass``.


null_terminated
^^^^^^^^^^^^^^^
- Valid expression: ``rng|null_terminated``
- Precondition: For all the value ``v`` in the ``rng``, the expression ``v == 0`` must be valid, and some ``v`` that the expression is ``true`` exists in the ``rng``.
- Returns: ``[boost::begin(rng), y)``, where for all the value ``v`` in the range ``v != 0`` is ``true``, and ``*y == 0`` is ``true``.


pointed
^^^^^^^
- Valid expression: ``vec|pointed``
- Precondition: ``vec`` is the template instantiation of ``std::vector``.
- Returns: ``[&*boost::begin(vec), &*boost::begin(vec)+boost::size(vec))``.


prepended
^^^^^^^^^
- Valid expression: ``rng|prepended(v)``
- Precondition: The ``iterator`` type of ``rng`` is convertible to ``v *``.
- Returns: ``make_single_range(v)|jointed(rng)``.


repeated
^^^^^^^^
- Valid expression: ``rng|repeated(i)``
- Returns: A `Single Pass Range`_ that repeats ``[boost::begin(rng), boost::end(rng))`` ``i`` times.


reversed
^^^^^^^^
- See: `Range Adaptors`_.


transformed
^^^^^^^^^^^
- See: `Range Adaptors`_.


utf8_decoded
^^^^^^^^^^^^
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::u8_to_u32_iterator``.



References
----------
- `P-Stade`_
- `Boost C++ Libraries`_
- `Boost.Range`_
- `Range Library Proposal`_



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Initial version released.



