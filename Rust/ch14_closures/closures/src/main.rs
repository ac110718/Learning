#[derive(Debug)]
#[allow(dead_code)]
struct City {
    name: String,
    population: i64,
    country: String,
}

fn sort_cities(cities: &mut Vec<City>) {
    // sort_by_key extracts key by which to sort the data
    cities.sort_by_key(|city| -city.population);
}

// Rather than garbage collect, Rust uses idea of reference lifetimes to ensure safety. It's much faster with less overhead
// Rather than borrow a reference, a closure can move. move | city: & City | -> i64 and take complete ownership
// fn(&City) -> bool is fn type (functions only)
// Fn(&City) -> bool is Fn type (functions AND closures))
// This is because closures can always have enclosed data as part of a "custom" function not known until run time.
// No two closures have exactly the same type and has an ad hoc type created by compiler

// Closure performance is fast because it is never allocated to heap (nothing is, unless you put it in a Box, Vec, or container)
// Closure has a distinct type, making Rust memory aware, and allows this to be put on the stack. Rust is memory aware

// a regular closure with references to variables will have pointers to those variables
// a move closure will contain values in memory directly (no pointer)
// a closure with no variable references will be empty

// Closures containing drop() are a special type called FnOnce which disallows multiple calls (double free)
// Three closure categories are FNOnce() [Broadest] | FnMut() | Fn() [modifies only reference variables]
// ...FnOnce || drop(v) ...FnMut() |arg| v.push(arg). Modified vec container ... Fn() |arg| arg + 1, or |arg| v.contains(arg)

use std::collections::HashMap;

#[allow(dead_code)]
struct Request {
    method: String,
    url: String,
    headers: HashMap<String, String>,
    body: Vec<u8>,
}

#[allow(dead_code)]
struct Response {
    code: u32,
    headers: HashMap<String, String>,
    body: Vec<u8>,
}

type BoxedCallback = Box<dyn Fn(&Request) -> Response>;
struct BasicRouter
// C: Fn(&Request) -> Response, // Can't use this because it'll make every C the same exact type
// standardizing across callbacks, as opposed to standardizing type to POINTER to callbacks
{
    routes: HashMap<String, BoxedCallback>,
}

#[allow(dead_code)]
impl BasicRouter {
    fn new() -> BasicRouter {
        BasicRouter {
            routes: HashMap::new(),
        }
    }

    fn add_route<C>(&mut self, url: &str, callback: C)
    where
        C: Fn(&Request) -> Response + 'static, // not safe to store a closure if it contains borred references to variables that go out of scope
    {
        self.routes.insert(url.to_string(), Box::new(callback));
    }

    fn handle_request(&self, request: &Request) -> Response {
        match self.routes.get(&request.url) {
            None => not_found_response(),
            Some(callback) => callback(request),
        }
    }
}

#[allow(dead_code)]
fn not_found_response() -> Response {
    let mut x = HashMap::new();
    x.insert("Response".to_string(), "Not Found".to_string());
    Response {
        code: 404,
        headers: x,
        body: vec![],
    }
}

fn get_form_response() -> Response {
    let mut x = HashMap::new();
    x.insert("Response".to_string(), "Form Response".to_string());
    Response {
        code: 200,
        headers: x,
        body: vec![],
    }
}

fn get_gcd_response(_req: &Request) -> Response {
    let mut x = HashMap::new();
    x.insert("Response".to_string(), "GCD".to_string());
    Response {
        code: 200,
        headers: x,
        body: vec![10, 20],
    }
}

fn main() {
    let mut cities = vec![
        City {
            name: "city1".to_string(),
            population: 100,
            country: "country1".to_string(),
        },
        City {
            name: "city2".to_string(),
            population: 200,
            country: "country1".to_string(),
        },
        City {
            name: "city3".to_string(),
            population: 500,
            country: "country1".to_string(),
        },
    ];
    sort_cities(&mut cities);
    println!("{:?}", cities[0]);

    let y = 10;
    let add_y = |x| x + y;
    let copy_of_add_y = add_y;
    assert_eq!(add_y(copy_of_add_y(22)), 42);

    // for move closures, can reuse them with clone()

    let mut greeting = String::from("Hello, ");
    let greet = move |name| {
        greeting.push_str(name);
        println!("{}", greeting);
    };
    greet.clone()("Alfred");
    greet.clone()("Bruce");

    let mut router = BasicRouter::new();
    router.add_route("/", |_| get_form_response());
    router.add_route("/gcd", |req| get_gcd_response(req));
}

// MVC model (Model - State), (View - Appearance), (Controller - Logic)
// Problem is that each object has reference to each other and object "ownership" is never clear
// Wrong level of abstraction because many objects will cut across all three layers, which need updating
// Rather, ownership must be made explicit, reference cycles mst be eliminated.
// React, etc separation of concerns stems from components, not functional responsibilities
