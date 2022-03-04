// what is mandelbrot?
// when you square a number.. you fly off to infinity if you are greater than |1|
// what happens when you add a x^2 + c term? for c > 0.25 or less than -2, then you fly off else you stay within zero
// apply this logic to complex numbers and that is what mandelbrot is
// mandelbrot set is set of complex numbers c for which z does not fly out to infinity

// plot re and im components of each c along x and y axis to see if c is in Mandelbrot set. Black if yes, lighter if no
// if z ever leaves radius of 2, it will definitely fly infinitely far away from origin eventually

use num::Complex;
use std::str::FromStr;
use image::ColorType;
use image::png::PNGEncoder;
use std::fs::File;
use std::env;

// Determine of 'c' is in Mandelbrot set, using at most 'limit' iterations to decide
// if 'c' is not in member (member = stays to zero), return Some(i) where i is number of iterations it took c to leave circle radius 2
// if 'c' has hit limit iterations staying in the bounds, return none

fn escape_time(c: Complex<f64>, limit: usize) -> Option<usize> {
    let mut z = Complex { re: 0.0, im: 0.0};
    for i in 0..limit {
        if z.norm_sqr() > 4.0 {
            return Some(i);
        }
        z = z * z + c;
    }
    None
}

// Parse string s as coordinate pair like "400x600" or "1.0,0.5"
// return tuple of type T that implements FromStr
fn parse_pair<T: FromStr>(s: & str, separator: char) -> Option<(T, T)> {
    match s.find(separator) {
        None => None,
        Some(index) => {
            // if able to match this pattern with two Ok elements.. extract into arguments l and r
            match (T::from_str(&s[..index]), T::from_str(&s[index+1..])) {
                (Ok(l), Ok(r)) => Some((l, r)),
                _ => None
            }
        }
    }
}

#[test]
fn test_parse_pair() {
    assert_eq!(parse_pair::<i32>("",        ','), None);
    assert_eq!(parse_pair::<i32>("10,",     ','), None);
    assert_eq!(parse_pair::<i32>(",10",     ','), None);
    assert_eq!(parse_pair::<i32>("10,20",   ','), Some((10, 20)));
    assert_eq!(parse_pair::<i32>("10,20xy", ','), None);
    assert_eq!(parse_pair::<f64>("0.5x",    'x'), None);
    assert_eq!(parse_pair::<f64>("0.5x1.5", 'x'), Some((0.5, 1.5)));
}

fn parse_complex(s: &str) -> Option<Complex<f64>> {
    match parse_pair(s, ',') {
        Some((re, im)) => Some(Complex {re, im}),
        None => None
    }
}

#[test]
fn test_parse_complex() {
    assert_eq!(parse_complex("1.25,-0.0625"),
               Some(Complex { re: 1.25, im: -0.0625 }));
    assert_eq!(parse_complex(",-0.0625"), None);
}

// Given row and column of a pixel.. return corresponding point on the complex plane.
// bounds: width and height of image in pixels. pixel: (column, row) pair
// upper_left and lower_right are points on the complex plane designating area our image covers

fn pixel_to_point(bounds: (usize, usize), pixel: (usize, usize), upper_left: Complex<f64>, lower_right: Complex<f64>) -> Complex<f64> {
    //width and height in terms of complex scaling
    let (width, height) = (lower_right.re - upper_left.re, upper_left.im - lower_right.im);
    Complex {
        re: upper_left.re + pixel.0 as f64 * (width / bounds.0 as f64),
        im: upper_left.im - pixel.1 as f64 * (height / bounds.1 as f64) // pixel.1 increases as we go down so subtract
    }
}

// map out 25, 175 to complex coordinate system if 100,200 represent -1+i, 1-i
#[test]
fn test_pixel_to_point() {
    assert_eq!(pixel_to_point((100, 200), (25, 175),
                              Complex { re: -1.0, im:  1.0 },
                              Complex { re:  1.0, im: -1.0 }),
               Complex { re: -0.5, im: -0.75 });
}

fn render(pixels: &mut [u8], bounds: (usize, usize), upper_left: Complex<f64>, lower_right: Complex<f64>) {
    assert!(pixels.len() == bounds.0 * bounds.1);
    for row in 0..bounds.1 {
        for column in 0..bounds.0 {
            let point = pixel_to_point(bounds, (column, row), upper_left, lower_right);
            pixels[row * bounds.0 + column] = 
                match escape_time(point, 255) { // limit to 255 so we naturally scale to color
                    None => 0, // black if never escaped
                    Some(count) => 255 - count as u8 // ligher color means immediate escape, darker took very long time
                };
        }
    }
}

fn write_image(filename: &str, pixels: &[u8], bounds: (usize, usize)) -> Result<(), std::io::Error> {
    let output = File::create(filename)?;
    let encoder = PNGEncoder::new(output);
    encoder.encode(&pixels, bounds.0 as u32, bounds.1 as u32, ColorType::Gray(8))?; // each byte is an eight bit grayscale value.
    Ok(()) // void return
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 5 {
        eprintln!("Usage: {} FILE PIXELS UPPERLEFT LOWERRIGHT", args[0]);
        eprintln!("Example: {} mandel.png 1000x750 -1.20,0.35 -1,0.20", args[0]);
        std::process::exit(1);
    }
    let bounds = parse_pair(&args[2], 'x').expect("error parsing image dimensions");
    let upper_left = parse_complex(&args[3]).expect("error parsing upper left corner point");
    let lower_right = parse_complex(&args[4]).expect("error parsing lower right corner point");
    // initiate vector of bounds size with 0s
    let mut pixels = vec![0; bounds.0 * bounds.1]; 
    render(&mut pixels, bounds, upper_left, lower_right);
    write_image(&args[1], &pixels, bounds).expect("error writing PNG file");
}
