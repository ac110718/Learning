fn main() {
    println!("Hello, world!");
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
