fn main() {

    let mut padovan = vec![1,1,1]; // allocated here. padovan var owns its value via pointer to buffer. buffer stored on heap.
    for i in 3..10 {
        let next = padovan[i-3] + padovan[i-2];
        padovan.push(next);
    }
    println!("P(1..10) = {:?}", padovan); // var dropped on block exit. along with values

    {
        let point = Box::new((0.625, 0.5)); // allocated to heap here
        let label = format!("{:?}", point); // label owns resulting string and allocated here
        assert_eq!(label, "(0.625, 0.5)");
    } // both dropped here

    struct Person { name: String, birth: i32 }

    let mut composers = Vec::new();
    composers.push(Person {name: "Palestrina".to_string(), birth: 1524 });
    composers.push(Person {name: "Dowland".to_string(), birth: 1563 });
    composers.push(Person {name: "Lully".to_string(), birth: 1623 });
    for composer in &composers {
        println!("{}, born {}", composer.name, composer.birth);
    } // composers owns a vector. The vector owns its elements, each of which is a person struct
    // each struct owns its fields, and the string field owns its text
    // Every value has a single owner. Owners and their owned values form trees
    // Rust single ownership rule forbids arrangement more complex than tree. Every value in rust is member of some tree, rooted in some variable

    // Idea is extended, however..
    // Move: moves values from one owner to another to build, rearrange, or tear down tree
    // Copy types: very simple tyles like ints, float, chars excused from ownership rules
    // reference-counted pointer types Rc and Arc allow you to have multiple owners, under some restrictions
    // Borrow: reference to value. References are non-owning pointers, with limited lifetimes.

    // Suppose s = ['udon', 'ramen', 'soba']; t = s; u = s;
    // Python will assign all three pointers to shared ownership over buffer. Keep track with ref count
    // C++ will make three separate copies
    // Python makes assignment cheap, at expense of ref counting and garbage collection
    // C++ keeps ownership of memory clear, at expense of deep copy
    // Rust will move ownership, leaving source variable uninitialized. 
    // u would be assigned unitialized state of s. Won't compile in Rust
    // Rust assignment is cheap, memory is clear. Price paid is that you must ask for explicit copies when you want via clone.

    let s = vec!["udon".to_string(), "ramen".to_string(), "soba".to_string()];
    let t = s.clone();
    let u = s.clone();
    assert_eq!(s, t);
    assert_eq!(t, u);
    let mut x = "Govinda".to_string(); // to_string needed for fresh string instance, which is given to x
    let y = x;
    x = "Siddhartha".to_string(); // nothing is dropped here
    assert_eq!(y, "Govinda");
    assert_eq!(x, "Siddhartha");

    // be very careful when using variables multiple times in loops
    // after the first assignment or use within a branch, or first loop..
    // ..it will be uninitialized after the first use and fail post branch / first-loop (must be reassigned to something)

    // you can't assign something out of a vector, because position can't be "uninitialized"
    // let third = v[2] results in error. v[2] left with nothing

    let a = vec!["one".to_string(), "two".to_string(), "three".to_string()];
    for mut word in a {
        word.push('!');
        println!("{}", word);
    } // a is now empty

    let string1 = "somnambulance".to_string();
    let string2 = string1; // string1 now empty. String is not a copy type
    assert_eq!(string2, "somnambulance");

    let num2: i32 = 36;
    let num1 = num2; // two numbers created
    assert_eq!(num1, num2);

    // arc "atomic reference count" and safe to share between threads
    // rc "reference count" and same but only safe within same thread

    use std::rc::Rc;

    let s: Rc<String> = Rc::new("shirataki".to_string());
    let t: Rc<String> = s.clone(); // clone the pointer
    let u: Rc<String> = s.clone(); // now three pointers to same Strong Ref Count that keeps track of shared buffer
    // when all Rcs dropped, so is the buffer.

    assert!(s.contains("shira"));
    assert_eq!(t.find("taki"), Some(5));
    println!("{} are quite chewy, almost bouncy, but lack flavor", u);
    // cannot modify like this s.push_str(" noodles");
    // Rust prevents value from being BOTH Shareable AND Mutable.
}
