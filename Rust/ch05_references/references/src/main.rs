// Arc, Rc, Box<T> are all owning pointers, and values dropped when owner is dropped.
// References are non-owning pointers. No Effect on referents' lifetime
// References must never outlive their referents.
// References are "borrowed" because they must be RETURNED to their owners (and therefore can't outlive).

// Shared ref allows to read, but not modify. Can have many. &T "ref T"
// Mutable ref allows read-write. Can can only have one. &mut T "ref mute T"

// references can never be null in Rust. Use type Option<&T> which will yield None as null pointer or Some(r), where r is &T as nonzero address
// Option<&T> requires you check whether its None before you can use it.

use std::collections::HashMap;

type Table = HashMap<String, Vec<String>>;

// pass by reference especially important in Rust, because spells out how ownership is affected.
// allows function to access or manipulate a structure without taking ownership

fn show(table: &Table) {
    for (artist, works) in table {
        println!("works by {}:", artist);
        for work in works {
            println!("  {}", work);
        }
    }
}

fn sort_works(table: &mut Table) {
    for (_artist, works) in table {
        works.sort();
    }
}

fn main() {
    let mut table = Table::new();
    table.insert(
        "Gesualdo".to_string(),
        vec![
            "many madrigals".to_string(),
            "Tenebrae Responsoria".to_string(),
        ],
    );
    table.insert(
        "Caravaggio".to_string(),
        vec![
            "The Musicians".to_string(),
            "The Galling of St. Matthew".to_string(),
        ],
    );
    table.insert(
        "Vellini".to_string(),
        vec![
            "Perseus with the head of Medusa".to_string(),
            "a salt cellar".to_string(),
        ],
    );
    show(&table); // if show(table) with no ref, println! would take ownership and destroy
    sort_works(&mut table); // notice mutable ref needed to sort
    show(&table);

    let x = 10;
    let r = &x;
    assert!(*r == 10);

    let mut y = 32;
    let m = &mut y;
    *m += 32;
    assert!(*m == 64);
    assert!(y == 64);

    struct Anime {
        name: &'static str,
        bechdel_pass: bool,
    }
    let aria = Anime {
        name: "Aria: The Animation",
        bechdel_pass: true,
    };

    let anime_ref = &aria;
    assert_eq!(anime_ref.name, "Aria: The Animation");
    assert_eq!((*anime_ref).bechdel_pass, true);

    let x = 10;
    let y = 20;
    let mut r = &x;
    let b = true;
    if b {
        r = &y // in C++, this would store value of y to original referrent x, rather than pointing to y
    }
    assert!(*r == 20);

    struct Point {
        x: i32,
        y: i32,
    }
    let point = Point { x: 1000, y: 729 };
    let r: &Point = &point;
    let rr: &&Point = &r;
    let rrr: &&&Point = &rr; // rrr -> rr -> r -> point
    assert_eq!(rrr.x, 1000); // traverses three reference to get to point before fetching x
    assert_eq!(rrr.y, 729);

    let x = 10;
    let y = 10;

    let rx = &x;
    let ry = &y;

    let rrx = &rx;
    let rry = &ry;

    assert!(rx == ry);
    assert!(!std::ptr::eq(rx, ry));
    // assert!(!(rx == rrx)); ERROR type mismatch
    assert!(rx == *rry);
    assert!(ry == *rrx);
}
