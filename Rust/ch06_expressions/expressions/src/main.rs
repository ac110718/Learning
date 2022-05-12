// Expressions have values. Statements don't (have logic)
// In Rust, expressions do all the work. If and match keywords CAN produce values

fn main() {
    // No ternary in Rust because you can do let.. if..
    let status = if false { 1 } else { 2 };
    assert_eq!(status, 2);
    // String is a growable, heap-allocated data structure whereas str is an immutable fixed-length string somewhere in memory
    let mut opt_string: Option<&str> = Some("Hello");
    // opt_string = None;
    opt_string = if opt_string.is_some() {
        None
    } else {
        Some("Yo")
    };
    println!(
        "Matched contents: {}",
        match opt_string {
            Some(word) => word,
            None => "Nothing here",
        }
    );

    // Block produces a value. No semicolon in Rust returns value of expression (there is meaning)
    // calling a function with semicolon simply called the function, but drops the return value unless specifically assigned

    let display_name = match opt_string {
        Some(word) => word.to_string(),
        None => {
            let x: u8 = 10;
            let y: u8 = 10;
            (x + y).to_string()
        }
    };
    println!("Display: {}", display_name);

    // Shadowing. first line is type Result<String, io::Error>. Second line type is String and supercedes so you can use more easily
    // for line in file.lines() {
    //     let line = line?
    // }

    let code = 2;
    let number = match code {
        0 => 10,
        1 => 20,
        2 => 30,
        _ => 40,
    };
    println!("Number: {}", number);

    // loop over a reference to collection.. or else you'll be CONSUMING each of the values and they will be dropped
    let strings: Vec<String> = vec!["A".to_string(), "B".to_string(), "C".to_string()];
    for rs in &strings {
        println!("String {:?} is at address {:p}.", *rs, rs);
    }

    // Rust checks that every path of function returns a value of the expected return type
    // Warns about unreachable code through branches
    // Expressions that never finish return special type -> ! called divergent function exit() never returns

    // return Vec<i32>::with_capacity(1000); doesn't work because < is less-than operator
    // return Vec::<i32>::with_capacity(1000); works propertly
    // ::<...:> "turbofish"

    // rust doesn't have increment and decrement operators ++ and --

    let is_even = |x: u64| x % 2 == 0;
    let is_odd = |x: u64| -> bool { x % 2 == 1 }; // if specify return type, then body of closure needs to be block

    assert_eq!(is_even(42), true);
    assert_eq!(is_odd(42), false);
}
