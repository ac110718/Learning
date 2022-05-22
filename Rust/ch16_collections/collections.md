## Collections
<br>Rust avoids deep copying values, hence pushes items by value. But rust doesn't have invalidation errors like dangling-pointer issues because of reference lifetimes, use of Options, Results, etc (null is never an option).

BTreeMap stores key-value pairs, but have non-leaf nodes which point you to the right sub-region to explore (i.e.. regions 10-20, 20-30, etc). Pure binary trees have fewer comparisons per search (log N structure) than a B-Tree (constant comparisons at leaf level). But B-trees have better memory locality because memory accesses are grouped together, reducing CPU cache misses.

```rust
let mut vote_counts: HashMap<String, usize> = HashMap::new();
for name in ballots {
    let count = vote_counts.entry(name).or_insert(0);
    *count += 1;
}
```
```rust
let mut word_frequency: HashMap<&str, u32> = HashMap::new();
for c in text.split_whitespace() {
    word_frequency.entry(c)
        .and_modify(|count| *count += 1)
        .or_insert(1);
}
```
```rust
let b1 = large_vector.contains(&"needle"); // slow, checks every element
let b2 = large_hash_set.contains(&"needle"); // fast, hash lookup
```
To store structs into hash table, struct, enums, etc should impleement Hash trait. `#[derive(Hash)]` works so long as fields are all hashable themselves