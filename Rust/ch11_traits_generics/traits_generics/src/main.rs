// Traits are Rust's take on interfaces or abstract base classes
// A trait represents a capability: something a type can do.

// trait Write {
//     fn write(&mut self, buf: &[u8]) ->Result<usize>;
//     fn flush(&mut self) -> Result<()>;
//     fn write_all(&mut self, buf: &[u8]) -> Result<()>
// }

// The trait itself must be in scope. Otherwise, all its methods are hidden.
// Stored in own namespace because allows you to add new methods to any type (easy name conflicts)
// Clone and iterator always in scope by default
use std::io::Write;

// type of out is "a mutable reference to any value that implements the Write trait"
// dyn Write is known as a trait object
fn say_hello(out: &mut dyn Write) -> std::io::Result<()> {
    out.write_all(b"hello world\n")?;
    out.flush()
}

// fn say_hello<W: Write>(out: &mut W) // generic function version
// use Trait object when you need a collection of values of mixed types, all together

// min can be used with arguments of any
// type T that implements Ord trait
// A requirement like this is called a bound, because it sets limits on which types T could possibly be.
#[allow(dead_code)]
fn min<T: Ord>(value1: T, value2: T) -> T {
    if value1 <= value2 {
        value1
    } else {
        value2
    }
}

fn main() {
    use std::fs::File;
    let mut local_file = File::create("hello.txt").unwrap();
    say_hello(&mut local_file).unwrap();

    let mut bytes = vec![];
    say_hello(&mut bytes).unwrap();
    assert_eq!(bytes, b"hello world\n");

    // a variable size has to be known at compile time, so you can't say
    let mut buf: Vec<u8> = vec![];
    // let writer: dyn Write = buf; // error: 'Write' does not have a constant size
    // reference to trait type is trait object and has constant size
    let _writer: &mut dyn Write = &mut buf;
    // trait object is fat pointer consisting of pointer to the value
    // plus, a pointer to a table representing that value's type (vtable containing impl Write for Vec and all its methods)
    // File is a kind of writer. Just adds the address of appropriate vtable, turning regular pointer into a fat pointer
    let _w: Box<dyn Write> = Box::new(local_file);

    // let v1 = (0 .. 1000).collect(); // error: can't infer type
    let v2 = (0..1000).collect::<Vec<i32>>();
    println!("{:?}", v2[999]);

    // for multiple traits use + sign
    // fn top_ten<T: Debug + Hash + Eq>(values: &Vec<T>) { ... }

    // Generic functions can have multiple type parameters:
    // fn run_query<M: Mapper + Serialize, R: Reducer + Serialize>(
            // data: &DataSet, map: M, reduce: R) -> Results { ... }

    // OR..
    // fn run_query<M, R>(data: &DataSet, map: M, reduce: R) -> Results
    // where M: Mapper + Serialize, R: Reducer + Serialize

    // Can specify both lifetime and trait parameters, with lifetime first
    // fn nearest<'t, 'c, P>(target: &'t P, candidates: &'c [P]) -> &'c P
        // where P: MeasureDistance { ... }

    // trait Vegetable { ... }

    // struct Salad<V: Vegetable> {
    //     veggies: Vec<V>                  // all of the same type. Too restrictive!
    // }
    // struct Salad { 
    //     veggies: Vec<dyn Vegetable>      // error: `dyn Vegetable` does not have a constant size
    // }
    // struct Salad {
    //     veggies: Vec<Box<dyn Vegetable>> // Pointer to trait type. Works.
    // }

    // same idea for shapes, monsters, routing algorithms.. have similar "behaviors" but very different properties

    // to implement trait for a type.. say impl Trait for Type (and only define specified functions there)
    // other methods not in trait must be implemented via separate impl block

    // trait Visible {
    //     fn draw(&self, canvas: &mut Canvas);
    //     fn hit_test(&self, x: i32, y: i32) -> bool;
    // }

    // impl Visible for Broom {
    //     fn draw(&self, canvas: &mut Canvas) {
    //         for y in self.y - self.height - 1 .. self.y {
    //             canvas.write_at(self.x, y, '|');
    //         }
    //         canvas.write_at(self.x, self.y, 'M');
    //     }
    //     fn hit_test(&self, x:i32, y:i32) -> bool {
    //         self.x == x
    //         && self.y - self.height - 1 <= y
    //         && y <= self.y
    //     }
    // }

    // impl Broom { // such helper functions, while having to be defined elsewhere, can be used in the trait impl blocks
    //     fn broomstick_range(&self) -> Range<i32> {
    //         self.y - self.height - 1 .. self.y
    //     }
    // }

    // traits can have default implementations where you don't have to define yourself and can fall back on

    // Can extend trait to a whole family of types at once..
    
    // use std::io::{self, Write};

    // trait WriteHtml {
    //     fn write_html(&mut self, html: &HtmlDocument) -> io::Result<()>
    // }

    // "for every type W that implements Write, here's an implementation of WriteHtml for W"
    // impl<W: Write> WriteHtml for W {
    //     fn write_html(&mut self, html: &HtmlDocument) -> io::Result<()> { ... }
    // }

    // serde library implements Serialize for bool, i8, i16, array, tupe, Vec, HashMap, and tons of types
    // adds a .serialize() method to all these types... 
    // can call .serialize() on many different types.

    // Subtraits.. declare that a trait is an extension of another trait
    // trait Creature: Visible. Every type that implements Creature must also implement Visible trait

    // Equivalent..
    // "hello".to_string()
    // str::to_string("hello") // implements ToString
    // ToString::to_string("hello")
    // <str as ToString>::to_string("hello")

    // let zero = 0; // could be anything.. i8, u8..
    // zero.abs(); // can't tell ambiguous numeric type
    // i64::abs(zero); // okay

    // Traits aren't just a grouping of methods, but they can also describe relationships between types.
    // For example.. the iterator..
    // pub trait Iterator {
    //     type Item;
    //     fn next(&mut self) -> Option<Self::Item>; // Must return Some(Item)
    // }
    // impl Iterator for Args {
    //     type Item = String; // Item is type String
    //     fn next(&nut self) -> Option<String> { ... }
    // }

    // -> impl Iterator<Item=u8> 
    // return anything that implements Iterator for Item type u9

    // but the below doesn't work.. because the return types are incompatible (different amounts of memory)
    // works only for free functions and functions associated with specific types.
    // fn make_shape(shape: &str) -> impl Shape {
    //     match shape {
    //         "circle" => Circle::new(),
    //         "triangle" => Triangle::new(),
    //         "shape" => Rectangle::new(),
    //     }
    // }

    // Associated constants can be defined for traits..
    // trait Float {
    //     const ZERO: self;
    //     const ONE: self;
    // }
    // impl Float for f32 {
    //     const ZERO: f32 = 0.0;
    //     const ONE: f32 = 1.0;
    // }
    // fn add_one<T: Float + Add<Output=T>>(value: T) -> {
    //     value + T::ONE
    // }

    
    )
}
