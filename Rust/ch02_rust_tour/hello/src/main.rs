use std::str::FromStr; // bring in FromStr trait (interface) into namespace
use std::env;

fn main() {
    let mut numbers = Vec::new();
    for arg in env::args().skip(1) {
        // from_str implementation for u64.. returns Result (ok, error).. 
        // expect handles error
        numbers.push(u64::from_str(&arg).expect("error parsing argument"));
    }
    if numbers.len() == 0 {
        eprintln!("Usage: gcd NUMBER ...");
        std::process::exit(1);
    }
    let mut d = numbers[0];
    for m in &numbers[1..] { // borrow reference pointer to vector's elements
        d = gcd(d, *m); // dereference m.. iterate through all elements
    }
    // template string with parameters. {:?} catch-all for debugging print types
    println!("The greatest common divisor of {:?} is {}", numbers, d);
}

fn gcd(mut n: u64, mut m: u64) -> u64 {
    assert!(n != 0 && m != 0);
    while m != 0 {
        if m < n { // swap so m is bigger
            let t = m;
            m = n;
            n = t;
        }
        m = m % n; 
        // keep pulling out n (small) from m (big) (and cycle through) until you find a zero remainder.. 
        // which is the GCD of both, that "fits" into the two numbers.
    }
    n
}

#[test]
fn test_gcd() {
    assert_eq!(gcd(14, 15), 1);
    assert_eq!(gcd(2 * 3 * 5 * 11 * 17, 3 * 7 * 11 * 13 * 19), 3 * 11);
}
