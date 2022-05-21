// iterator is a value that produces a sequences of values, typically for a loop to operator on
// Traverse collections, but also produce lines of text from input stream, connections arriving from network server, values receives from other threads over channel, etc

fn triangle(n: i32) -> i32 {
    let mut sum = 0;
    for i in 1..=n {
        sum += i;
    }
    sum
}

fn triangle_fold(n: i32) -> i32 {
    (1..=n).fold(0, |sum, item| sum + item)
}

// trait Iterator {
//     type Item;
//     fn next(&mut self) -> Option<Self::Item>;
//     ...
// }

// let mut iterator = (&v).into_iter();
// while let Some(element) = iterator.next() {
//     println!("{}", element);
// }    // call Iterator::next repeatedly until it returns None rather than Some(element)

// Iterator is any type that implements Iterator. Iterable is any type that implements IntoIterator.
// An iterator PRODUCES values. The value iterator produces are ITEMS. Code that receives items is the CONSUMER

fn main() {
    assert_eq!(triangle(10), triangle_fold(10));

    let v = vec![4, 20, 12, 8, 6];
    let mut iterator = v.iter();
    assert_eq!(iterator.next(), Some(&4));
    assert_eq!(iterator.next(), Some(&20));
    assert_eq!(iterator.next(), Some(&12));
    assert_eq!(iterator.next(), Some(&8));
    assert_eq!(iterator.next(), Some(&6));
    assert_eq!(iterator.next(), None);

    use std::ffi::OsStr;
    use std::path::Path;

    let path = Path::new("C:/Users/JimB/Downloads/Fedora.iso");
    let mut iterator = path.iter();
    assert_eq!(iterator.next(), Some(OsStr::new("C:")));
    assert_eq!(iterator.next(), Some(OsStr::new("Users")));
    assert_eq!(iterator.next(), Some(OsStr::new("JimB")));

    // if there's more than one common way to iterator over a type, the type usually provides specific methods for each sort of traversal
    // if s is &str, then s.bytes() returns byte iterator, and s.chars() iterprets as UTF-8 and produces each Unicode char

    use std::collections::BTreeSet;
    let mut favorites = BTreeSet::new();
    favorites.insert("Lucy in the Sky With Diamonds".to_string());
    favorites.insert("Liebestraume No. 3".to_string());
    let mut it = favorites.into_iter(); // passes collection by value. takes ownership
                                        // (&favorites).into_iter() for shared reference
                                        // (&mut favorites).into_iter() for mutable reference
    assert_eq!(it.next(), Some("Liebestraume No. 3".to_string()));
    assert_eq!(it.next(), Some("Lucy in the Sky With Diamonds".to_string()));
    assert_eq!(it.next(), None);

    // for element in &collection -> shared reference. Call different IntoIterator implementations
    // for element in &mut collection -> mutable reference
    // for element in collection -> take ownership

    //from_fn produces iterator from function.. never ends, just continuously calls. So need to combine with take to limit
    use rand::random;
    use std::iter::from_fn;
    let lengths: Vec<f64> = from_fn(|| Some((random::<f64>() - random::<f64>()).abs()))
        .take(10)
        .collect();
    println!("{:?}", lengths);

    // use std::iter::successors if each item depends on the one before

    fn fibonacci() -> impl Iterator<Item = usize> {
        let mut state = (0, 1);
        std::iter::from_fn(move || {
            state = (state.1, state.0 + state.1);
            Some(state.0)
        })
    }
    println!("{:?}", fibonacci().take(8).collect::<Vec<_>>());

    let mut outer = "Earth".to_string();
    let inner = String::from_iter(outer.drain(1..4));
    assert_eq!(outer, "Eh");
    assert_eq!(inner, "art");

    // map transforms an iterator by applying a closure to its items
    // filter filters out items from iterator, using closure to decide which to keep and which to drop

    let text = " ponies \n giraffes\niguanas   \nsquid".to_string();
    let v: Vec<&str> = text
        .lines()
        .map(str::trim)
        .filter(|s| *s != "iguanas") // filter borrows by reference so must dereference
        .collect(); // from iterator to vector. No work is done until collect() is called...
                    // text.lines() returns an iterator that WOULD parse lines. Map and filter return iterators that WOULD map or filter
    println!("{:?}", v);
    let _ = ["earth", "water", "air", "fire"]
        .iter()
        .map(|elt| println!("{}", elt))
        .collect::<Vec<_>>(); // nothing would be printed until here.

    // filter_map combines the two functions, dropping anything that evaluates to none

    use std::str::FromStr;
    let text = "1\nfront .25 289\n3.1415 estuary\n";
    for number in text
        .split_whitespace()
        .filter_map(|w| f64::from_str(w).ok())
    // must evaluate to Some(str)
    {
        println!("{:4.2}", number.sqrt());
    }

    //flat_map will concatenate sequences returned by closure

    use std::collections::HashMap;

    let mut major_cities = HashMap::new();
    major_cities.insert("Japan", vec!["Tokyo", "Kyoto"]);
    major_cities.insert("The United States", vec!["Portland", "Nashville"]);
    major_cities.insert("Brazil", vec!["Sao Paulo", "Rio"]);
    major_cities.insert("Indonesia", vec!["Jakarta", "Surabaya"]);

    let countries = ["Japan", "Brazil", "Indonesia"];

    for &city in countries.iter().flat_map(|country| &major_cities[country]) {
        println!("{}", city);
    }

    // Note that flatten has an implicit None filter
    let all_cities: Vec<_> = major_cities.values().flatten().clone().collect();
    for &city in all_cities {
        println!("All cities: {}", city);
    }

    // sometimes methods like ch.to_uppercase() returns not a single character, but an iterator producing one or more characters
    // As such, you'd have an iterator of iterators of characters.. so you need to flatten

    fn to_uppercase(w: &str) -> String {
        w.chars().flat_map(char::to_uppercase).collect()
    }

    println!("{}", to_uppercase(&"uppercase_me".to_string()));

    // take and take while let you end an iterator after a certain number of items or when a closure decides to cut things off

    let message = "To: jimb\r\n\
                    From: superego <editor@oreilly.com>\r\n\
                    \r\n\
                    Did you get any writing done today?\r\n\
                    When will you stop wasting time plotting fractals?\r\n";

    for header in message.lines().take_while(|l| !l.is_empty()) {
        println!("<HEADER> {}", header);
    }

    // skip and skip_while are inverse
    for body in message.lines().skip_while(|l| !l.is_empty()).skip(1) {
        println!("<BODY> {}", body);
    }

    // use peek to draw the next item from iterator but without actually consuming it

    use std::iter::Peekable;

    fn parse_number<I>(tokens: &mut Peekable<I>) -> u32
    where
        I: Iterator<Item = char>,
    {
        let mut n = 0;
        loop {
            match tokens.peek() {
                Some(r) if r.is_digit(10) => {
                    n = n * 10 + r.to_digit(10).unwrap();
                }
                _ => return n,
            }
            tokens.next();
        }
    }

    let mut chars = "22234239,3490234".chars().peekable();
    println!("{}", parse_number(&mut chars));
    println!("{:?}", chars.next());
    println!("{}", parse_number(&mut chars));
    println!("{:?}", chars.next());

    // Fuse ensures that once you return a None, it always returns a None forever

    struct Flaky(bool);

    impl Iterator for Flaky {
        type Item = &'static str;
        fn next(&mut self) -> Option<Self::Item> {
            if self.0 {
                self.0 = false;
                Some("totally the last item")
            } else {
                self.0 = true;
                None
            }
        }
    }
    println!("------");
    let mut flaky = Flaky(true);
    println!("{:?}", flaky.next());
    println!("{:?}", flaky.next());
    println!("{:?}", flaky.next());
    println!("{:?}", flaky.next());
    println!("------");
    let mut not_flaky = Flaky(true).fuse();
    println!("{:?}", not_flaky.next());
    println!("{:?}", not_flaky.next());
    println!("{:?}", not_flaky.next());
    println!("{:?}", not_flaky.next());

    // next_back starts moving from the back (like to fingers moving in to middle)
    println!("------");
    let meals = ["breakfast", "lunch", "dinner"];
    let mut iter = meals.iter();
    println!("{:?}", iter.next());
    println!("{:?}", iter.next_back());
    println!("{:?}", iter.next_back());
    println!("{:?}", iter.next());
    println!("{:?}", iter.next_back());

    // chain will string together and concatenate two iterators of same type
    let v: Vec<i32> = (1..4).chain(vec![20, 30, 40]).collect();
    println!("{:?}", &v);

    // enumerate will return iterator producing pairs with running index (to distinguish one item from another)
    let mut x = [3, 3, 3].into_iter().enumerate();
    println!("{:?}", x.next());
    println!("{:?}", x.next());
    println!("{:?}", x.next());

    // zip is a generalized form of enumerate

    let v: Vec<_> = (0..).zip("ABCDE".chars()).collect();
    println!("{:?}", v);

    use std::iter::repeat;
    let endings = vec!["once", "twice", "chicken soup with rice!"];
    let rhyme: Vec<_> = repeat("going").zip(endings).collect();
    println!("{:?}", rhyme);

    // fizz(div by 3) buzz(div by 5) fizzbuzz(by both)

    use std::iter::once;
    let fizzes = repeat("").take(2).chain(once("fizz")).cycle();
    let buzzes = repeat("").take(4).chain(once("buzz")).cycle();
    let fizzes_buzzes = fizzes.zip(buzzes);

    let fizz_buzz = (1..100).zip(fizzes_buzzes).map(|tuple| match tuple {
        (i, ("", "")) => i.to_string(),
        (_, (fizz, buzz)) => format!("{}{}", fizz, buzz), // pick up any instance
    });
    for line in fizz_buzz {
        println!("{}", line);
    }

    // Accumulator functions

    println!("{:?}", (1..=20).sum::<u64>());
    println!("{:?}", (1..=20).product::<u64>());
    println!("{:?}", [-2, 0, 1, 0, -2, -5].iter().max());
    println!("{:?}", [-2, 0, 1, 0, -2, -5].iter().min());

    let mut populations = HashMap::new();
    populations.insert("Portland", 583776);
    populations.insert("Hometown", 1000000);
    populations.insert("City", 20000);
    populations.insert("Blah", 2);
    populations.insert("Somewhere", 302934);

    println!("{:?}", populations.iter().max_by_key(|&(_name, pop)| pop));
    println!("{:?}", populations.iter().min_by_key(|&(_name, pop)| pop));

    let id = "Iterator";
    println!("{:?}", id.chars().any(char::is_uppercase));
    println!("{:?}", id.chars().all(char::is_uppercase));
    println!("{:?}", id.chars().position(|c| c == 'r'));
    println!("{:?}", id.chars().position(|c| c == 'z'));

    let a = [5, 6, 7, 8, 9, 10];
    println!("{:?}", a.iter().fold(0, |n, _| n + 1)); // count
    println!("{:?}", a.iter().fold(0, |n, i| n + i)); // sum
    println!("{:?}", a.iter().fold(1, |n, i| n * i)); // product
    println!(
        "{:?}",
        a.iter().cloned().fold(i32::min_value(), std::cmp::max)
    ); // max element
}
