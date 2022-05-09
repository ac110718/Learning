fn main() {
    println!("The typed vector contains {:?}", build_vector_typed());
    println!("The inferred vector contains {:?}", build_vector_inferred());

    assert_eq!(10_i8 as u16, 10_u16);
    assert_eq!(2525_u16 as i16, 2525_i16);
    assert_eq!(2_u16.pow(4), 16);
    assert_eq!((-4_i32).abs(), 4);
    assert_eq!(0b101101_u8.count_ones(), 4);

    assert_eq!(10_u8.checked_add(20), Some(30));
    assert_eq!(100_u8.checked_add(200), None); // 2^8 = 256

    assert_eq!(false as i32, 0);
    assert_eq!(true as i32, 1);

    let text = "I see the eigenvalue in thine eye";
    let (head, tail) = text.split_at(21);
    assert_eq!(head, "I see the eigenvalue ");
    assert_eq!(tail, "in thine eye");

    // &T borrow a reference. But it is an immutable, shared reference. Can have as many as you like but are read-only. No modifying
    // &mut T mutable, exclusive reference. Can write, but only way to access value is through the mutable reference
    // "single writer OR multiple readers" rule

    let lazy_caterer: [u32; 6] = [1, 2, 4, 7, 11, 16];
    let taxonomy = ["Animalia", "Arthropoda", "Insecta"];
    assert_eq!(lazy_caterer[3], 7);
    assert_eq!(taxonomy.len(), 3);

    let mut sieve = [true; 10000];
    for i in 2..100 {
        if sieve[i] {
            // println!("Sieving... {}", i);
            let mut j = i * i;
            while j < 10000 {
                sieve[j] = false;
                j += i;
            }
        }
    }
    assert!(sieve[211]);
    assert!(!sieve[9876]);

    let mut chaos = [3, 5, 4, 1, 2];
    chaos.sort();
    assert_eq!(chaos, [1, 2, 3, 4, 5]);

    let mut primes = vec![2, 3, 5, 7];
    assert_eq!(primes.iter().product::<i32>(), 210);
    primes.push(11);
    primes.push(13);
    assert_eq!(primes.iter().product::<i32>(), 30030);

    let buffer = new_pixel_buffer(3, 3);
    assert_eq!(buffer.len(), 9);
    let mut pal = Vec::new();
    pal.push("step");
    pal.push("on");
    pal.push("no");
    pal.push("pets");
    assert_eq!(pal, vec!["step", "on", "no", "pets"]);

    let v: Vec<i32> = (0..5).collect();
    assert_eq!(v, [0, 1, 2, 3, 4]);

    let mut v = Vec::with_capacity(2);
    println!("capacity is now {}", v.capacity());
    v.push(1);
    v.push(2);
    v.push(3);
    println!("capacity is now {}", v.capacity());

    let mut w = vec!["Snow Puff", "Glass Gem"];
    assert_eq!(w.pop(), Some("Glass Gem"));
    assert_eq!(w.pop(), Some("Snow Puff"));
    assert_eq!(w.pop(), None);

    let languages = vec!["Lisp", "Scheme", "C", "C++", "Fortran"];
    for l in languages {
        println!("{}: {}", l,
            if l.len() % 2 == 0 {
                "functional"
            } else {
                "imperative"
            }
        )};
    
    let x: Vec<f64> = vec![0.0, 0.707, 1.0, 0.707]; // stored on heap. vector is just ptr + capacity + length
    let a: [f64; 4] = [0.0, 0.707, 1.0, 0.707]; // stored consecutive slots in memory
    let sx: &[f64] = &x; // points to shared heap w. vector
    let sa: &[f64] = &a; // points to array memory
    print(sx);
    print(sa);
    print(&x[0..2]);
    print(&a[2..]);
    print(&sx[1..3]);
    println!(r###"
        Multiline raw string
        Line Two
        Line Three
    "###);

    let bits = vec!["veni", "vidi", "vici"];
    assert_eq!(bits.concat(), "venividivici");
    assert_eq!(bits.join(", "), "veni, vidi, vici");

    assert!("ONE".to_lowercase() == "one");
    assert!("peanut".contains("nut"));
    assert_eq!("0_0".replace("0","[]"), "[]_[]");
    assert_eq!("        clean\n".trim(), "clean");

    for word in "veni, vidi, vici".split(", ") {
        assert!(word.starts_with("v"));
    }
}

fn build_vector_typed() -> Vec<i16> {
    let mut v: Vec<i16> = Vec::<i16>::new();
    v.push(10i16);
    v.push(20i16);
    v
}

fn build_vector_inferred() -> Vec<i16> {
    let mut v = Vec::new();
    v.push(10);
    v.push(20);
    v
}

fn new_pixel_buffer(rows: usize, cols: usize) -> Vec<u8> {
    vec![0; rows * cols]
}

fn print(n: &[f64]) {
    println!("Number elements: {}", n.len());
    for elt in n {
        println!("{}", elt);
    }
}
