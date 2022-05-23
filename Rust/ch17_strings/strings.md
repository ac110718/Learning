## Strings and Text
<br> to_uppercase() and to_lowercase() return iterators instead of single characters because case conversion isn't always a one-to-one process. For example German letter "sharp S" uppercase is "SS"
<br>
### Patterns for searching text

```rust
assert_eq!(
        "## Elephants"
        .trim_start_matches(|ch: char| ch == '#' || ch.is_whitespace()),
        "Elephants");
```
`&[char]` matches any single character that appears in the list. Use `as_ref()` if you use literals within the array.

```rust
let code = "\t function noodle() { ";
assert_eq!(code.trim_start_matches([' ', '\t'].as_ref()),
    "function noodle() { ");
```
<br>

### Formatting strings

<br>

|Feature|Result|
|---|---|
|from {1} to {0}| can swap order of arguments given|
|{:02?} |minimum digits shown|
|{: .2}|precision of decimals|
|{:<12} |min width 12, but left align|
|{:>12} |min width 12, but right align|
|{:^12} |min width 12, but center align|
|{:=^12} |min width 12, but center align, with padding '=='|
|{:?} | Debugging |



