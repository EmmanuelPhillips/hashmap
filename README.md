# hashmap
## my goal with this project
my goal was to code a hashmap from scratch in c++, having no prior knowledge as to what a hashmap was, or how to implement one (even the embedded std::map and unordered_map)
## what i learned
- what actually is a hashmap: a data structure that maps keys to values. it uses a hash function to compute a bucket index, separating key-value pairs into separate buckets in order to increase efficiency.
- why a hashmap is better/worse than other data structures:
  - lookup is O(1), much faster than a linked list (O(n))
  - Memory overhead is higher, due to bucket array + chaining structure
  - Many keys can be placed in the same bucket whilst other buckets are empty, meaning in a worst case scenario, the time complexity becomes O(n)
## challenges
implementing operator[] overload for me was particularly difficult. i did not exactly comprehend the edge case
secondly, const correctness proved difficult. deciding which functions and variables could and should be marked const, and how it affected return types (particularly with get() function, which needed a const and non-const overload for my code to work well).
## what i would do differently next time
i would think more carefully about const correctness from the start, rather than retrofitting.
i would plan the rehash on paper - i originally made a mistake of not initialising the temp vector with the correct capacity. i should have thought through the data flow more.
