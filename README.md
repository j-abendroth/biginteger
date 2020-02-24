# BigInteger Abstract Data Type

BigInteger ADT capable of performing arithmetic operations on arbitrarily  large signed integers. Utilizes a doubly linked list of longs to represent a signed integer, storing its sign as one object, and a list of non-negative longs representing the integer's magniutde. Each list element is a single digit in the base *b* where *b* is a power of 10: *b = 10^p* and 1 <= p <= 9 to prevent integer overflow. 

Supports following operations on two lists of longs: sum, difference, and product.
