.. This file is licensed under the MIT License (MIT) available on
   http://opensource.org/licenses/MIT.

getwork
=======

``getwork [data]``

If [data] is not specified, returns formatted hash data to work on:

  "midstate" : precomputed hash state after hashing the first half of the data (DEPRECATED)
  "data" : block data
  "hash1" : formatted hash buffer for second hash (DEPRECATED)
  "target" : little endian hash target

If [data] is specified, tries to solve the block and returns true if it was successful.

