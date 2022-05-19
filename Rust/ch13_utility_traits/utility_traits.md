## Utility Traits

<br>

| Trait | Description |
| --- | --- |
| Drop | Destructors. Cleanup code |
| Sized | Fixed size at compile time, not dymaically sized (slces) |
| Clone, Copy | Make byte-for-byte copy of memory containing value |
| Deref, DerefMut | Smart pointer types |
| Default | Sensible "default" value |
| AsRef, AsMut | Conversion for borring one type of reference from another
| Borrow, BorrowMut | Additionally guarantees consistent hashing, ordering, and equality
| From, Into | Transforms one type of value into another |
| TryFrom, TryInto | For transformations that might fail
|ToOwned | Conversion trait for converting a references to owned value

<br>**Drop** is analogous to destructor in C++
<br>

```rust
impl Drop for Appellation {
    fn drop(&mut self) {
        print!("dropping {}", self.name);
        if !self.nicknames.is_empty() {
            print!(" (AKA {})", self.nicknames.join(", "));
        }
        println!("");
    }
}

{
    let mut a = Appellation {
        name: "Zeus".to_string(),
        nicknames: vec!["cloud collector".to_string(),
                        "king of the gods".to_string()]
    };
    println!("before assignment");
    a = Appellation { name: "Hera".to_string(), nicknames: vec![] };
    println!("at end of block");
}
```
```
before assignment
Dropping Zeus (AKA cloud collector, king of the gods)
at end of block
Dropping Hera
```

A **sized type** is one whose values all have the same size in memory. Almost all types in Rust are sized: every u64 takes eight bytes, etc. Enums are sized and always occupies enough space to hold its largest variant

T: sized requires T to be a type whose size is known at compile time. **The only use for Sized trait is as a bound for type variables.**

String slice type str (note, without an &) is unsized, as the buffer can be any size. 

dyn types (the referent of a trait object, aka fat pointer) is also unsized,. The pointers themselves are fixed size, but the referent could be a file, network socket, or anything that simply implements the trait.. so <code>dyn Write</code> is considered unsized, but <code>&dyn std::io::Write</code> or <code>`Box<dyn std::io::Write>`</code> are sized

?sized type means questionably sized. <code>struct RcBox<T: ?Sized> { ... }</code>

Cloning a `Vec<String>` not only copies the vector, but also copies each of its `String` elements. This is why Rust doesn't just clone values automatically, but instead requires you to make an explicit method call.

Assignment moves values, rather than copying them. But Rust permits copying when you have a very simple type that doesn't own any resources. Rust permits a type to implement Copy only if a shallow byte-for-byte copy is all it needs. Types that own other resources, like heap buffers, cannot implement Copy. Any type that implements the Drop trait cannot be Copy.

**Deref** specifies how you dereference types using operators like * and .