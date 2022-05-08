use actix_web::{web, App, HttpResponse, HttpServer};
use serde::Deserialize;

fn main() {
    // lambda to potentially handle multiple instances to be called
    let server = HttpServer::new(|| {
        App::new()
            // route "/" to get response callback
            .route("/", web::get().to(get_index))
            .route("/gcd", web::post().to(post_gcd))
    });
    println!("Serving on http://localhost:3000...");
    server 
        .bind("127.0.0.1:3000").expect("error binding server to address")
        .run().expect("error running server");
}

fn get_index() -> HttpResponse {
    //default return HttpResponse without 'return' keyword
    HttpResponse::Ok()
        .content_type("text/html")
        .body(
            //rust raw string. post to /gcd with inputs n and m within web form submission
            r#"
                <title>GCD Calculator</title>
                <form action="/gcd" method="post">
                <input type="text" name="n"/>
                <input type="text" name="m"/>
                <button type="submit">Compute GCD</button>
                </form>
            "#,
        )

}

//parameter of webform of type "GcdParameters" 
fn post_gcd(form: web::Form<GcdParameters>) -> HttpResponse {
    if form.n == 0 || form.m == 0 {
        return HttpResponse::BadRequest()
            .content_type("text/html")
            .body("Computing the GCD with zero is boring");
    }

    let response = // use format macro to write to string
        format!("The greatest common divisor of the numbers {} and {} is <b>{}</b>\n",
            form.n, form.m, gcd(form.n, form.m));
    HttpResponse::Ok()
        .content_type("text/html")
        .body(response)
}

// tell serde crate to examine during compilation and automatically generate code to parse using deserialize
// in order to be used for POST request
#[derive(Deserialize)]
struct GcdParameters {
    n: u64,
    m: u64,
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