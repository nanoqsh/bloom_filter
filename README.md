# bloom_filter
 Bloom filter data structure implementation

## Example
```cpp
// Create the hash function.
auto hash_fn = [](const std::string &str, size_t seed) -> size_t {
    size_t hash = seed;

    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
};

// Make the `bloom filter` container with optimal size for a given percent of errors.
bloom bl = bloom<const std::string &>::optimal_bloom(100, 0.01, hash_fn);

// Add an item into container.
bl.add("Hello, Bloom!");

// Check the availability.
if (bl.possibly_contains("Hello, Bloom!")) {
    std::cout << "The container possibly contains the `Hello, Bloom!` string.\n";
}
```
