// Unlike enums in C++, Rust enum can contain data of varying types
// Example Result<String, io::Error>
// "Price" of using them is that must access the data safely, using pattern matching
// Can't just call field of an enum like shape.radius, must be "matched" with patterns

// Programming is data processing. Getting data into the right shape can make a huge difference.

// enum Ordering {
//     Less,
//     Equal,
//     Greater,
// }

use std::cmp::Ordering::{self, *};

fn compare(n: i32, m: i32) -> Ordering {
    if n < m {
        Less
    } else if n > m {
        Greater
    } else {
        Equal
    }
}

#[derive(Debug)]
enum HttpStatus {
    Ok = 200,
    NotModified = 304,
    NotFound = 404,
}

fn http_status_from_u32(n: u32) -> Option<HttpStatus> {
    match n {
        200 => Some(HttpStatus::Ok),
        304 => Some(HttpStatus::NotModified),
        404 => Some(HttpStatus::NotFound),
        _ => None,
    }
}

#[derive(Copy, Clone, Debug, PartialEq, Eq)]
#[allow(dead_code)]
enum TimeUnit {
    Seconds,
    Minutes,
    Hours,
    Days,
    Months,
    Years,
}
// enums can have methods just like structs
#[allow(dead_code)]
impl TimeUnit {
    fn plural(self) -> &'static str {
        match self {
            TimeUnit::Seconds => "seconds",
            TimeUnit::Minutes => "minutes",
            TimeUnit::Hours => "hours",
            TimeUnit::Days => "days",
            TimeUnit::Months => "months",
            TimeUnit::Years => "years",
        }
    }

    fn singular(self) -> &'static str {
        self.plural().trim_end_matches('s')
    }
}

#[derive(Copy, Clone, Debug, PartialEq, Eq)]
#[allow(dead_code)]
enum RoughTime {
    InThePast(TimeUnit, u32),
    JustNow,
    InTheFuture(TimeUnit, u32),
}

fn rough_time_to_english(rt: RoughTime) -> String {
    match rt {
        RoughTime::InThePast(units, count) => format!("{} {} ago", count, units.plural()),
        RoughTime::JustNow => format!("just now"),
        RoughTime::InTheFuture(units, count) => format!("{} {} from now", count, units.plural()),
    } // keep in mind that patterns CONSUME values
}

// enum Option<T> {
//     None,
//     Some(T),
// }

// enum Result<T, E> {
//     Ok(T),
//     Err(E),
// }

#[derive(Debug)]
enum BinaryTree<T> {
    Empty,
    NonEmpty(Box<TreeNode<T>>),
}

#[derive(Debug)]
struct TreeNode<T> {
    element: T,
    left: BinaryTree<T>,
    right: BinaryTree<T>,
}

impl<T: Ord> BinaryTree<T> {
    fn add(&mut self, value: T) {
        match *self {
            BinaryTree::Empty => {
                *self = BinaryTree::NonEmpty(Box::new(TreeNode {
                    element: value,
                    left: BinaryTree::Empty,
                    right: BinaryTree::Empty,
                }))
            }
            BinaryTree::NonEmpty(ref mut node) => {
                if value <= node.element {
                    node.left.add(value);
                } else {
                    node.right.add(value);
                }
            }
        }
    }
}

// match account {
//     // refs needed here to borrow the matched values, or else you'll move and consume them
//     Account { ref name, ref language, .. } => { // .. means ignore rest of variables
//         ui.greet(name, language);
//         ui.show_settings(&account); // ok with ref. Without ref, you'll be trying to borrow moved value: account
//     }
// }

// match line_result {
//     Err(ref err) => log_error(err),
//     Ok(ref mut line) => {
//         trim_comments(line);
//         handle(line);
//     }
// }

// keep in mind that in an expression & creates a reference. In a patterm & MATCHES a reference
// match friend.borrow_car() {
//     Some(&Car { ref engine, ..}) => // okay if engine has ref. the &Car is just pattern matching
// }

// Match guard. Combine match pattern with if constraint
// match point_to_hex(click) {
//     None => Err("That's not a game space."),
//     Some(hex) if hex == current_hex => Err("You're already here!"),
//     Some(hex) => Ok(hex)
// }

// Matching with | OR

// let at_end = match chars.peek() {
//     Some(&'\r') | Some(&'\n') | None => true,
//     _ => false,
// }

// match next_char {
//     '0'..='9' => self.read_number(),
//     'a'..='Z' | 'A'..='Z' => self.read_word(),
//     ' ' | '\t' | '\n' => self.skip_whitespace(),
//     _ => self.handle_punctuation(),
// }

// Binding with @. If you need to reference the unpacked variable during match pattern for processing, don't rebuild

// match self.get_select() {
//     Shape::Rect(top_left, bottom_right) => {
//         optimized_paint(&Shape::Rect(top_left, bottom_right))
//     }
//     ..vs..
//     rect @ Shape::Rect(..) => {
//         optimized_paint(&rect)
//     }
// }

// match chars.next() {
//     Some(digit @ '0'..='9') => read_number(digit, chars),
// }

fn main() {
    println!("{:?}", compare(32, 64));
    println!("{:?}", http_status_from_u32(304));
    let four_score_and_seven_years_ago = RoughTime::InThePast(TimeUnit::Years, 4 * 20 + 7);
    // println!("{:?}", four_score_and_seven_years_ago);
    println!("{}", rough_time_to_english(four_score_and_seven_years_ago));
    let three_hours_from_now = RoughTime::InTheFuture(TimeUnit::Hours, 3);
    // println!("{:?}", three_hours_from_now);
    println!("{}", rough_time_to_english(three_hours_from_now));
    let planets = vec![
        "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Earth", "Neptune",
    ];
    let mut tree = BinaryTree::Empty;
    for planet in planets {
        tree.add(planet);
    }
    println!("{:?}", tree);
}
