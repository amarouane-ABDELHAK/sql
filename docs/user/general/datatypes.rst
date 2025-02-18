==========
Data Types
==========

.. rubric:: Table of contents

.. contents::
   :local:
   :depth: 2


Overview
========

OpenSearch SQL Data Types
-------------------------

The OpenSearch SQL Engine support the following data types.

+---------------------+
| OpenSearch SQL Type |
+=====================+
| boolean             |
+---------------------+
| byte                |
+---------------------+
| short               |
+---------------------+
| integer             |
+---------------------+
| long                |
+---------------------+
| float               |
+---------------------+
| double              |
+---------------------+
| string              |
+---------------------+
| text                |
+---------------------+
| timestamp           |
+---------------------+
| datetime            |
+---------------------+
| date                |
+---------------------+
| time                |
+---------------------+
| interval            |
+---------------------+
| ip                  |
+---------------------+
| geo_point           |
+---------------------+
| binary              |
+---------------------+
| struct              |
+---------------------+
| array               |
+---------------------+

Data Types Mapping
------------------

The table below list the mapping between OpenSearch Data Type, OpenSearch SQL Data Type and SQL Type.

+-----------------+---------------------+-----------+
| OpenSearch Type | OpenSearch SQL Type | SQL Type  |
+=================+=====================+===========+
| boolean         | boolean             | BOOLEAN   |
+-----------------+---------------------+-----------+
| byte            | byte                | TINYINT   |
+-----------------+---------------------+-----------+
| short           | byte                | SMALLINT  |
+-----------------+---------------------+-----------+
| integer         | integer             | INTEGER   |
+-----------------+---------------------+-----------+
| long            | long                | BIGINT    |
+-----------------+---------------------+-----------+
| float           | float               | REAL      |
+-----------------+---------------------+-----------+
| half_float      | float               | FLOAT     |
+-----------------+---------------------+-----------+
| scaled_float    | float               | DOUBLE    |
+-----------------+---------------------+-----------+
| double          | double              | DOUBLE    |
+-----------------+---------------------+-----------+
| keyword         | string              | VARCHAR   |
+-----------------+---------------------+-----------+
| text            | text                | VARCHAR   |
+-----------------+---------------------+-----------+
| date            | timestamp           | TIMESTAMP |
+-----------------+---------------------+-----------+
| ip              | ip                  | VARCHAR   |
+-----------------+---------------------+-----------+
| date            | timestamp           | TIMESTAMP |
+-----------------+---------------------+-----------+
| binary          | binary              | VARBINARY |
+-----------------+---------------------+-----------+
| object          | struct              | STRUCT    |
+-----------------+---------------------+-----------+
| nested          | array               | STRUCT    |
+-----------------+---------------------+-----------+

Notes: Not all the OpenSearch SQL Type has correspond OpenSearch Type. e.g. data and time. To use function which required such data type, user should explicitly convert the data type.

Data Type Conversion
====================

A data type can be converted to another, implicitly or explicitly or impossibly, according to type precedence defined and whether the conversion is supported by query engine.

The general rules and design tenets for data type conversion include:

1. Implicit conversion is defined by type precedence which is represented by the type hierarchy tree. See `Data Type Conversion in SQL/PPL </docs/dev/TypeConversion.md>`_ for more details.
2. Explicit conversion defines the complete set of conversion allowed. If no explicit conversion defined, implicit conversion should be impossible too.
3. On the other hand, if implicit conversion can occur between 2 types, then explicit conversion should be allowed too.
4. Conversion within a data type family is considered as conversion between different data representation and should be supported as much as possible.
5. Conversion across two data type families is considered as data reinterpretation and should be enabled with strong motivation.

Type Conversion Matrix
----------------------

The following matrix illustrates the conversions allowed by our query engine for all the built-in data types as well as types provided by OpenSearch storage engine.

+--------------+------------------------------------------------+---------+------------------------------+-----------------------------------------------+--------------------------+---------------------+
|  Data Types  |               Numeric Type Family              | BOOLEAN |      String Type Family      |              Datetime Type Family             |  OpenSearch Type Family  | Complex Type Family |
|              +------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|              | BYTE | SHORT | INTEGER | LONG | FLOAT | DOUBLE | BOOLEAN | TEXT_KEYWORD | TEXT | STRING | TIMESTAMP | DATE | TIME | DATETIME | INTERVAL | GEO_POINT |  IP | BINARY |   STRUCT  |  ARRAY  |
+==============+======+=======+=========+======+=======+========+=========+==============+======+========+===========+======+======+==========+==========+===========+=====+========+===========+=========+
|   UNDEFINED  |  IE  |   IE  |    IE   |  IE  |   IE  |   IE   |    IE   |      IE      |  IE  |   IE   |     IE    |  IE  |  IE  |    IE    |    IE    |     IE    |  IE |   IE   |     IE    |    IE   |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     BYTE     |  N/A |   IE  |    IE   |  IE  |   IE  |   IE   |    X    |       X      |   X  |    E   |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     SHORT    |   E  |  N/A  |    IE   |  IE  |   IE  |   IE   |    X    |       X      |   X  |    E   |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|    INTEGER   |   E  |   E   |   N/A   |  IE  |   IE  |   IE   |    X    |       X      |   X  |    E   |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     LONG     |   E  |   E   |    E    |  N/A |   IE  |   IE   |    X    |       X      |   X  |    E   |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     FLOAT    |   E  |   E   |    E    |   E  |  N/A  |   IE   |    X    |       X      |   X  |    E   |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|    DOUBLE    |   E  |   E   |    E    |   E  |   E   |   N/A  |    X    |       X      |   X  |    E   |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|    BOOLEAN   |   E  |   E   |    E    |   E  |   E   |    E   |   N/A   |       X      |   X  |    E   |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
| TEXT_KEYWORD |      |       |         |      |       |        |         |      N/A     |      |   IE   |           |      |      |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     TEXT     |      |       |         |      |       |        |         |              |  N/A |   IE   |           |      |      |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|    STRING    |   E  |   E   |    E    |   E  |   E   |    E   |    IE   |       X      |   X  |   N/A  |     IE    |   IE |   IE |     IE   |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|   TIMESTAMP  |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |    E   |    N/A    |      |      |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     DATE     |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |    E   |           |  N/A |      |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     TIME     |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |    E   |           |      |  N/A |     X    |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|   DATETIME   |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |    E   |           |      |      |    N/A   |     X    |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|   INTERVAL   |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |    E   |           |      |      |     X    |    N/A   |     X     |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|   GEO_POINT  |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |        |     X     |   X  |   X  |     X    |     X    |    N/A    |  X  |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|      IP      |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |        |     X     |   X  |   X  |     X    |     X    |     X     | N/A |    X   |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|    BINARY    |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |        |     X     |   X  |   X  |     X    |     X    |     X     |  X  |   N/A  |     X     |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|    STRUCT    |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |        |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |    N/A    |    X    |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+
|     ARRAY    |   X  |   X   |    X    |   X  |   X   |    X   |    X    |       X      |   X  |        |     X     |   X  |   X  |     X    |     X    |     X     |  X  |    X   |     X     |   N/A   |
+--------------+------+-------+---------+------+-------+--------+---------+--------------+------+--------+-----------+------+------+----------+----------+-----------+-----+--------+-----------+---------+

Note that:

1. ``I`` means if implicit conversion will occur automatically. ``E`` stands for explicit conversion by ``CAST`` function. ``X`` for impossible to convert. Empty means not clear and need more test.
2. There is no ``UNDEFINED`` column because it's only for ``NULL`` literal at runtime and should not be present in function signature definition.
3. OpenSearch and complex types are not supported by ``CAST`` function, so it's impossible to convert a type to it for now.

Examples
--------

Here are a few examples for implicit type conversion::

    os> SELECT
    ...  1 = 1.0,
    ...  'True' = true,
    ...  DATE('2021-06-10') < '2021-06-11';
    fetched rows / total rows = 1/1
    +-----------+-----------------+-------------------------------------+
    | 1 = 1.0   | 'True' = true   | DATE('2021-06-10') < '2021-06-11'   |
    |-----------+-----------------+-------------------------------------|
    | True      | True            | True                                |
    +-----------+-----------------+-------------------------------------+

Here are a few examples for explicit type conversion::

    os> SELECT
    ...  CAST(true AS INT),
    ...  CAST(1.2 AS STRING),
    ...  CAST('2021-06-10 00:00:00' AS TIMESTAMP);
    fetched rows / total rows = 1/1
    +---------------------+-----------------------+--------------------------------------------+
    | CAST(true AS INT)   | CAST(1.2 AS STRING)   | CAST('2021-06-10 00:00:00' AS TIMESTAMP)   |
    |---------------------+-----------------------+--------------------------------------------|
    | 1                   | 1.2                   | 2021-06-10 00:00:00                        |
    +---------------------+-----------------------+--------------------------------------------+

Undefined Data Type
===================

The type of a null literal is special and different from any existing one. In this case, an ``UNDEFINED`` type is in use when the type cannot be inferred at "compile time" (during query parsing and analyzing). The corresponding SQL type is NULL according to JDBC specification. Because this undefined type is compatible with any other type by design, a null literal can be accepted as a valid operand or function argument.

Here are examples for NULL literal and expressions with NULL literal involved::

    os> SELECT NULL, NULL = NULL, 1 + NULL, LENGTH(NULL);
    fetched rows / total rows = 1/1
    +--------+---------------+------------+----------------+
    | NULL   | NULL = NULL   | 1 + NULL   | LENGTH(NULL)   |
    |--------+---------------+------------+----------------|
    | null   | null          | null       | null           |
    +--------+---------------+------------+----------------+


Numeric Data Types
==================

Numeric values ranged from -2147483648 to +2147483647 are recognized as integer with type name ``INTEGER``. For others outside the range, ``LONG`` integer will be the data type after parsed.


Date and Time Data Types
========================

The date and time data types are the types that represent temporal values and SQL plugin supports types including DATE, TIME, DATETIME, TIMESTAMP and INTERVAL. By default, the OpenSearch DSL uses date type as the only date and time related type, which has contained all information about an absolute time point. To integrate with SQL language, each of the types other than timestamp is holding part of temporal or timezone information, and the usage to explicitly clarify the date and time types is reflected in the datetime functions (see `Functions <functions.rst>`_ for details), where some functions might have restrictions in the input argument type.


Date
----

Date represents the calendar date regardless of the time zone. A given date value represents a 24-hour period, or say a day, but this period varies in different timezones and might have flexible hours during Daylight Savings Time programs. Besides, the date type does not contain time information as well. The supported range is '1000-01-01' to '9999-12-31'.

+------+--------------+------------------------------+
| Type | Syntax       | Range                        |
+======+==============+==============================+
| Date | 'yyyy-MM-dd' | '0001-01-01' to '9999-12-31' |
+------+--------------+------------------------------+


Time
----

Time represents the time on the clock or watch with no regard for which timezone it might be related with. Time type data does not have date information.

+------+-----------------------+----------------------------------------+
| Type | Syntax                | Range                                  |
+======+=======================+========================================+
| Time | 'hh:mm:ss[.fraction]' | '00:00:00.000000' to '23:59:59.999999' |
+------+-----------------------+----------------------------------------+


Datetime
--------

Datetime type is the combination of date and time. The conversion rule of date or time to datetime is described in `Conversion between date and time types`_. Datetime type does not contain timezone information. For an absolute time point that contains both date time and timezone information, see `Timestamp`_.

+----------+----------------------------------+--------------------------------------------------------------+
| Type     | Syntax                           | Range                                                        |
+==========+==================================+==============================================================+
| Datetime | 'yyyy-MM-dd hh:mm:ss[.fraction]' | '0001-01-01 00:00:00.000000' to '9999-12-31 23:59:59.999999' |
+----------+----------------------------------+--------------------------------------------------------------+



Timestamp
---------

A timestamp instance is an absolute instant independent of timezone or convention. For example, for a given point of time, if we set the timestamp of this time point into another timezone, the value should also be different accordingly. Besides, the storage of timestamp type is also different from the other types. The timestamp is converted from the current timezone to UTC for storage, and is converted back to the set timezone from UTC when retrieving.

+-----------+----------------------------------+------------------------------------------------------------------+
| Type      | Syntax                           | Range                                                            |
+===========+==================================+==================================================================+
| Timestamp | 'yyyy-MM-dd hh:mm:ss[.fraction]' | '0001-01-01 00:00:01.000000' UTC to '9999-12-31 23:59:59.999999' |
+-----------+----------------------------------+------------------------------------------------------------------+


Interval
--------

Interval data type represents a temporal duration or a period. The syntax is as follows:

+----------+--------------------+
| Type     | Syntax             |
+==========+====================+
| Interval | INTERVAL expr unit |
+----------+--------------------+

The expr is any expression that can be iterated to a quantity value eventually, see `Expressions <expressions.rst>`_ for details. The unit represents the unit for interpreting the quantity, including MICROSECOND, SECOND, MINUTE, HOUR, DAY, WEEK, MONTH, QUARTER and YEAR.The INTERVAL keyword and the unit specifier are not case sensitive. Note that there are two classes of intervals. Year-week intervals can store years, quarters, months and weeks. Day-time intervals can store days, hours, minutes, seconds and microseconds. Year-week intervals are comparable only with another year-week intervals. These two types of intervals can only comparable with the same type of themselves.


Conversion between date and time types
--------------------------------------

Basically the date and time types except interval can be converted to each other, but might suffer some alteration of the value or some information loss, for example extracting the time value from a datetime value, or convert a date value to a datetime value and so forth. Here lists the summary of the conversion rules that SQL plugin supports for each of the types:

Conversion from DATE
>>>>>>>>>>>>>>>>>>>>

- Since the date value does not have any time information, conversion to `Time`_ type is not useful, and will always return a zero time value '00:00:00'.

- Conversion from date to datetime has a data fill-up due to the lack of time information, and it attaches the time '00:00:00' to the original date by default and forms a datetime instance. For example, the result to covert date '2020-08-17' to datetime type is datetime '2020-08-17 00:00:00'.

- Conversion to timestamp is to alternate both the time value and the timezone information, and it attaches the zero time value '00:00:00' and the session timezone (UTC by default) to the date. For example, the result to covert date '2020-08-17' to datetime type with session timezone UTC is datetime '2020-08-17 00:00:00' UTC.


Conversion from TIME
>>>>>>>>>>>>>>>>>>>>

- Time value cannot be converted to any other date and time types since it does not contain any date information, so it is not meaningful to give no date info to a date/datetime/timestamp instance.


Conversion from DATETIME
>>>>>>>>>>>>>>>>>>>>>>>>

- Conversion from datetime to date is to extract the date part from the datetime value. For example, the result to convert datetime '2020-08-17 14:09:00' to date is date '2020-08-08'.

- Conversion to time is to extract the time part from the datetime value. For example, the result to convert datetime '2020-08-17 14:09:00' to time is time '14:09:00'.

- Since the datetime type does not contain timezone information, the conversion to timestamp needs to fill up the timezone part with the session timezone. For example, the result to convert datetime '2020-08-17 14:09:00' with system timezone of UTC, to timestamp is timestamp '2020-08-17 14:09:00' UTC.


Conversion from TIMESTAMP
>>>>>>>>>>>>>>>>>>>>>>>>>

- Conversion from timestamp is much more straightforward. To convert it to date is to extract the date value, and conversion to time is to extract the time value. Conversion to datetime, it will extracts the datetime value and leave the timezone information over. For example, the result to convert datetime '2020-08-17 14:09:00' UTC to date is date '2020-08-17', to time is '14:09:00' and to datetime is datetime '2020-08-17 14:09:00'.

Conversion from string to date and time types
---------------------------------------------

A string can also represent and be converted to date and time types (except to interval type). As long as the string value is of valid format required by the target date and time types, the conversion can happen implicitly or explicitly as follows::

    os> SELECT
    ...  TIMESTAMP('2021-06-17 00:00:00') = '2021-06-17 00:00:00',
    ...  '2021-06-18' < DATE('2021-06-17'),
    ...  '10:20:00' <= TIME('11:00:00');
    fetched rows / total rows = 1/1
    +------------------------------------------------------------+-------------------------------------+----------------------------------+
    | TIMESTAMP('2021-06-17 00:00:00') = '2021-06-17 00:00:00'   | '2021-06-18' < DATE('2021-06-17')   | '10:20:00' <= TIME('11:00:00')   |
    |------------------------------------------------------------+-------------------------------------+----------------------------------|
    | True                                                       | False                               | True                             |
    +------------------------------------------------------------+-------------------------------------+----------------------------------+

String Data Types
=================

A string is a sequence of characters enclosed in either single or double quotes. For example, both 'text' and "text" will be treated as string literal. To use quote characters in a string literal, you can include double quotes within single quoted string or single quotes within double quoted string::

    os> SELECT 'hello', "world", '"hello"', "'world'"
    fetched rows / total rows = 1/1
    +-----------+-----------+-------------+-------------+
    | 'hello'   | "world"   | '"hello"'   | "'world'"   |
    |-----------+-----------+-------------+-------------|
    | hello     | world     | "hello"     | 'world'     |
    +-----------+-----------+-------------+-------------+


Boolean Data Types
==================

A boolean can be represented by constant value ``TRUE`` or ``FALSE``. Besides, certain string representation is also accepted by function with boolean input. For example, string 'true', 'TRUE', 'false', 'FALSE' are all valid representation and can be converted to boolean implicitly or explicitly::

    os> SELECT
    ...  true, FALSE,
    ...  CAST('TRUE' AS boolean), CAST('false' AS boolean);
    fetched rows / total rows = 1/1
    +--------+---------+---------------------------+----------------------------+
    | true   | FALSE   | CAST('TRUE' AS boolean)   | CAST('false' AS boolean)   |
    |--------+---------+---------------------------+----------------------------|
    | True   | False   | True                      | False                      |
    +--------+---------+---------------------------+----------------------------+
