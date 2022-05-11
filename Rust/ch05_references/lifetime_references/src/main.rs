// lifetime is stretch of program for which a reference is safe to use
// variables have lifetime, extending from point initialized until point where compiler proves no longer in use.

// A reference lifetime assigned to borrower of a variable.
// Rule: if you have a variable x, then reference to x must not outlive x itself
// Variable's lifetime must contain or enclose that of the reference borrowed from it.
// Otherwise, beyond point where x goes out of scope, the reference would be a dangling pointer.

// Rust ensures no reference will ever point to a variable that has gone out of scope.
// Rust is all about transferring the pain of understanding your program from the future to the present.

fn main() {
    // {
    //     let r;
    //     {
    //         let x = 1;
    //         r = &x;
    //     } // x destroyed here. Can't carry it out with r as borrowed referrence
    //     assert_eq!(*r, 1); // borrowed value does not live long enough. r referring to x, but x out of scope
    // }
    // BELOW WORKS

    {
        let x = 1;
        {
            let r = &x;
            assert_eq!(*r, 1);
        }
    }

    // static lifetimes are for global variables
    // mutable statics are not thread-safe (any thread can access), so must be in unsafe block

    // 'a ("tick A") is lifetime parameter of f
    // "for any lifetime 'a"
    // lifetime of p's reference is some 'a, which can be anything so long as it encloses the call to f

    static mut STASH: &i32 = &10;

    // fn f<'a>(p: &'a i32) {
    //     unsafe {
    //         STASH = p;
    //     } // mismatch between static lifetime and lifetime 'a
    // }

    // unable to write function to store reference to global variable without reflecting intention in function signature
    // In rust, a function's signature always exposes the body's behavior
    fn f(p: &'static i32) {
        unsafe {
            STASH = p;
        }
    }

    static WORTH_POINTING_AT: i32 = 1000;
    f(&WORTH_POINTING_AT);

    fn smallest(v: &[i32]) -> &i32 {
        let mut s = &v[0];
        for r in &v[1..] {
            if *r < *s {
                s = r;
            }
        }
        s
    }

    // let s;
    // {
    //     let parabola = [9, 4, 1, 0, 1, 4, 9];
    //     s = smallest(&parabola);
    // } // parabola not alive
    // assert_eq!(*s, 0);

    {
        let parabola = [9, 4, 1, 0, 1, 4, 9];
        let s = smallest(&parabola);
        assert_eq!(*s, 0); // fine: parabola still alive
    }

    struct S<'a, 'b> {
        // if just one single lifetime, x and y must have EXACTLY the same lifetime
        x: &'a i32,
        y: &'b i32,
    }

    let x = 10;
    let r;
    let q;
    {
        let y = 20;
        {
            let s = S { x: &x, y: &y };
            r = s.x;
            q = s.y;
        }
        println!("{}", q);
    }
    println!("{}", r);

    // be careful when modifying vectors that are themselves referred to in the for loop
    // modifying vector can expand capacity to grow.. but the original reference in the for loop could be left dangling when original vector was enlarged / modified to accomodate

    fn extend(vec: &mut Vec<f64>, slice: &[f64]) {
        for elt in slice {
            vec.push(*elt);
        }
    }

    let mut wave = Vec::new();
    let head = vec![0.0, 1.0];
    let tail = [0.0, -1.0];
    extend(&mut wave, &head);
    extend(&mut wave, &tail);
    assert_eq!(wave, vec![0.0, 1.0, 0.0, -1.0]);
    // extend(&mut wave, &wave); wave as "vec" will be extended and moved.. while "slice" pointer will be dangling
    // in other words.. both "vec" and "slice" reference are trying to access the same thing and therefore not exclusive access.

    let mut x = 42;
    let p = &x;
    assert_eq!(*p, 42);
    x += 1; // Possible only if you never look at p again. can't assign to x while being borrowed by p because it's & mut ref
    assert_eq!(x, 43);
}
