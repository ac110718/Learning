// All types, structs included, should be PascalCase
// Fields and methods are lowercase, with words separated by underscores

struct GrayscaleMap {
    pixels: Vec<u8>,
    size: (usize, usize),
}

// let width = 1024;
// let height = 576;
// let image = GrayscaleMap {
//     pixels: vec![0; width * height],
//     size: (width, height),
// };

fn new_map(size: (usize, usize), pixels: Vec<u8>) -> GrayscaleMap {
    assert_eq!(pixels.len(), size.0 * size.1);
    GrayscaleMap { pixels, size } // short for GrayscaleMap { pixels: pixels, size: size }
}

// even if struct is pub, its fields are private from outside the module.
// you can't say "new String" or "new Vec" To create a new one, you must use public function like Vec::new()

// Rust will store field values directly into struct's block of memory (ordering not guaranteed though)
// Rust embeds fields directly in struct value, rather than having each field in heal-allocated blocks

#[allow(dead_code)]
struct Broom {
    name: String,
    height: u32,
    health: u32,
    position: (f32, f32, f32),
    intent: BroomIntent,
}

#[derive(Copy, Clone)]
#[allow(dead_code)]
enum BroomIntent {
    FetchWater,
    DumpWater,
}

fn chop(b: Broom) -> (Broom, Broom) {
    let mut broom1 = Broom {
        height: b.height / 2,
        ..b
    }; // take rest of fields from b struct
    let mut broom2 = Broom {
        name: broom1.name.clone(),
        ..broom1
    };

    broom1.name.push_str(" I");
    broom2.name.push_str(" II");

    (broom1, broom2)
}

// RUst methods appear in a separate impl block rather than appearing inside the struct definition
// An impl block is simply a collection of fn definitions, each of which becomes a method on struct type

pub struct Queue<T> {
    older: Vec<T>,
    younger: Vec<T>,
}

// redunant impl<T> makes it clear that impl block covers any type T
// which distinguishes it from an impl block written for one specific kind of Queue (that implements Sum method)

impl<T> Queue<T> {
    // new in Rust is just another function, not a keyword
    // or write -> Self
    pub fn new() -> Queue<T> {
        Queue::<T> {
            older: Vec::new(),
            younger: Vec::new(),
        }
    }
    pub fn push(&mut self, t: T) {
        self.younger.push(t);
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.older.is_empty() {
            if self.younger.is_empty() {
                return None;
            }
            use std::mem::swap;
            swap(&mut self.older, &mut self.younger);
            self.older.reverse();
        }
        self.older.pop()
    }

    pub fn is_empty(&self) -> bool {
        self.older.is_empty() && self.younger.is_empty()
    }
}

fn main() {
    let x = new_map((2, 2), vec![1, 2, 3, 4]);
    assert_eq!(x.pixels.len(), 4);
    assert_eq!(x.size.0, 2);

    let hokey = Broom {
        name: "Hokey".to_string(),
        height: 60,
        health: 100,
        position: (100.0, 200.0, 0.0),
        intent: BroomIntent::FetchWater,
    };

    let (hokey1, hokey2) = chop(hokey);
    assert_eq!(hokey1.name, "Hokey I");
    assert_eq!(hokey1.height, 30);
    assert_eq!(hokey1.health, 100);
    assert_eq!(hokey2.name, "Hokey II");
    assert_eq!(hokey2.height, 30);
    assert_eq!(hokey2.health, 100);

    let mut q = Queue {
        older: Vec::new(),
        younger: Vec::new(),
    };
    q.push('0');
    q.push('1');
    assert_eq!(q.pop(), Some('0'));
    q.push('∞');
    assert_eq!(q.pop(), Some('1'));
    assert_eq!(q.pop(), Some('∞'));
    assert_eq!(q.pop(), None);
    assert!(q.is_empty());
    q.push('Ø');
    assert!(!q.is_empty());
    let mut p = Queue::new();
    p.push('*');
    assert!(!p.is_empty());

    // hold two elements with the same reference lifetime
    struct Extrema<'elt> {
        greatest: &'elt i32,
        least: &'elt i32,
    }

    // return an Extrema whose fields refer to elements of slice
    // elements of slice (with lifetime 's) are borrowed, so returned Extrema struct also uses 's as lifetime of references
    // realistically can write fn find_extrema(slice: *[i32]) -> Extrema
    fn find_extrema<'s>(slice: &'s [i32]) -> Extrema<'s> {
        let mut greatest = &slice[0];
        let mut least = &slice[0];
        for i in 1..slice.len() {
            if slice[i] < *least {
                least = &slice[i];
            }
            if slice[i] > *greatest {
                greatest = &slice[i];
            }
        }
        Extrema { greatest, least }
    }

    let a = [0, -3, 0, 15, 48];
    let e = find_extrema(&a);
    assert_eq!(*e.least, -3);
    assert_eq!(*e.greatest, 48);

    // Deriving Common Traits for Struct Types
    // Each of these traits can be implemented automatically, provided each of its fields implements the trait
    // now we can copy, cline, println!("{:?}", point), and use == and != operators
    #[derive(Copy, Clone, Debug, PartialEq)]
    struct Point {
        x: f64,
        y: f64,
    }

    // Rc to store a pointer to another struct. Shared, read-only
    // What if you need to mutate it just a little bit, for logging?
    // Cell<T> is a struct that you can get and set even if you don't have mut access..

    // pub struct SpiderRobot {
    //     hardware_error_count: Cell<u32>,
    // }
    // impl SpiderRobot{
    //     pub fn add_hardware_error(&self) {
    //         let n = self.hardware_error_count.get();
    //         self.hardware_error_count.set(n + 1);
    //     }
    // }

    // Still not good enough because doesn't let you call mut methods on a shared file
    // What if you need mutable File, and File isn't copyable
    // Use RefCell<T>, which supports borrowing references to T value

    use std::cell::RefCell;
    let ref_cell: RefCell<String> = RefCell::new("hello".to_string());

    let mut r = ref_cell.borrow_mut(); // Ref<String>
    let count = r.len(); // "hello".len()
    assert_eq!(count, 5);

    // let mut w = ref_cell.borrow_mut(); // panic: already borrowed
    r.push_str(" world");
    println!("RefCell Length: {}", r.len());

    // pub struct SpiderRobot {
    //     log_file: RefCell<File>,
    // }

    // impl SpiderRobot {
    //     pub fn log(&self, message: &str) {
    //         let mut file = self.log_file.borrow_mut();
    //         writeln!(file, "{}", message).unwrap();
    //     }
    // }

    // Structs are like AND.. I have X AND Y fields
    // Enums are like OR.. you EITHER have X or Y types.
}
