## Asynchronous Programming

<br>Use asynchronous tasks to interleave many independent activities on a single thread or a pool of worker threads. 

Async tasks have significantly less memory overhead rather than threads. Typically used on operations that might block, like I/O or networking. Need to add await keyword to calls that may block so that a Future may be returned.

When you do anything that makes system calls, your function spends almost all of its time waiting for the operating system. The execution of the actual code would be narrow slivers between the system calls.

Synchronous functions don't return until the job is done.. and the caller may resume ONLY when the operation is complete.
<br>
### Future
<br>A Future represents an operation that you can test for completion. A future's poll method always returns immediately. If the operation is complete, the poll returns `Poll::Ready(output)`, where `output` is its final result. Otherwise it returns `Pending` 

```rust
trait Future {
    type Output;
    fn poll(self: Pin<&mut Self>, cx: &mut Context<`_>) -> Poll<Self::Output>
}

enum Poll<T> {
    Ready(T),
    Pending,
}
```

An asynchronous function returns a future of a result. You'll need to poll this future until you get a Ready(result). Each time it's polled, the read proceeds as far as it can.

An asynchronous function doesn't actually do anything. It's sole responsibility is to construct and return a future that will do the real work *when it is polled*. Therfore, the future must hold all information necessary to carry out the request made by the call. The future returned must remember the input stream it was called on, the String to append data to, etc. There are also lifetime implications for references. The future returned can live only as long as the values that are borrowed.

No busy polling. You'll only poll a future when it's worthwhile. Something should return Ready, or at least make progress toward the goal. Rust accomplishes this with a callback wake function that is passed through context when you poll the future.

```rust
// important because async methods sometimes part of extension traits rather than main traits
use async_std::io::prelude::*; 
use async_std::net;

async fn cheapo_request(host: &str, port: u16, path &str) -> std::io::Result<String> {
    // Note: async version of TcpStream
    let mut socket = net::TcpStream::connect((host, port)).await? 
    let request = format!("GET {} HTTTP/1.1\r\nHost: {}\r\n\r\n", path, host);
    // Note: async version of write_all
    socket.write_all(request.as_bytes()).await?;
    socket.shutdown(net::Shutdown::Write)?;

    let mut response = String::new();
    socket.read_to_string(&mut response).await?; // async version

    Ok(response)
}
```

await expression evaluates to the final value of the future.

The future returned by an async function wraps up all the information the function body will need to run. It's as if you'd captured the call's stack frame as an ordinary Rust value.... In some sense futures of asynchronous functions are like closures. It is entire chunk of code that is dynamically executed upon callback from the polled Future.

Execution will run until you hit the first await.. if you get a Poll::Pending, you **resume** execution mid-function at the re-entry point where it is about to poll the future. We don't progress to rest of async function until that future is ready... You move on only when the subfuture being awaited is ready. The ability to suspend execution mid-function and then resume later is unique to async functions and has implications on memory management.

Remember that each asynchornous call is a multistep process with subfutures being polled and called.

Asynchronous methods can't be part of traits. Only free functions and functions inherent to a specific type can be asynchronous.
<br>
 ### Executors

An async call does nothing until you pass it to a function like block_on, spawn or span_local that will poll it and drive the work to completion. These functions, called executors, play the role that other languages cover with a global event loop. Because Rust makes the programmer chose an executor to poll your futures, Rust has no need for a global event loop built into the system.

**RUST HAS NO GARBAGE COLLECTION (borrowing, lifetime references). NO GLOBAL EVENT LOOP(executors, task_spawning).** 

 <br>Async functions themselves return futures, so it's the caller's job to do the polling somehow. Do this with async_std::task::block_on

 ```rust
fn main() -> std::io::Result<()> {
    use async_std::task;
    let response = task::block_on(cheapo_request("example.com", 80, "/"))?;
    println!("{}", response);
    Ok(())
}
 ```
The value of block_on is that it knows how to go to sleep until the future is actually worth polling again. Futures returned by async functions retain the waker supplied by the Context passed to poll and involve it when block_on should wake up and try polling again.

Blocking a thread completely on a single future is no better than an synchronous call because you're not doing anything while sleeping (you're still effectively waiting). 

But you can overlap several async requests together through `spawn_local` which will run the entire pool of tasks concurrently until your result is ready. `spawn_local` to build up an array of tasks (like Promise.all?), and then run `block_on` to put it on the thread.

```rust
pub async fn many_requests(requests: Vec<(String, u16, String)>) -> Vec<std::io::Result<String>> {
    use async_std::task;
    let mut handles = vec![];
    for (host, port, path) in requests {
        handles.push(task::span_local(cheapo_request(&host, port, &path)));
    } // not quite correct. borrowed values need longer lifetime in case handle is put on another task / thread but never joined. Wrap in a parent function that owns the values, and then call references to that.
    let mut result = vec![];
    for handle in handles {
        results.push(handle.await); // pushed only after await completes
    }
    results
}

async fn cheapo_owning_request(host: String (not &str), port: u16, path:String) -> std::io::Result<String> {
    cheapo_request(&host, port, &path).await
    // now parent owns the values themselves and lifetime is 'static
}

// main ()

let requests = vec![
    ("example1.com".to_string(), 80, "/".to_string()),
    ("example2.com".to_string(), 80, "/".to_string()),
    ("example3.com".to_string(), 80, "/".to_string()),
]; // block_on one batch of requests, each of which will spawn_local(cheapo_request)
let results = async_std::task::block_on(many_requests(requests));
for result in results {
    match result {
        Ok(response) => println!("{}", response),
        Err(err) => eprintln!("err: {}", err),
    }
}
```

The result is that all three requests will overlap with each other, waking from the same block_on request which is monitoring futures and polling. The time to execute the batch will be max(task_time), rather than task1 + task2 + task3 times sequentially.

Can use entire async blocks to return a future of the value of its last expression. Sometimes it's more clear to write the code this way, because the block can take ownership of reference arguments... Ownership of variables gets transferred to the block (which will determine when they will fall out of scope). This is better than having a parent function.

```rust
handles.push(task::spawn_local(async move { // block owns
    cheapo_request(&host, port, &path).await
}))
```
With blocks, need to specify an Ok::<(), std::io::Error>(()) return type, because if you have await? within a block, it will trigger immediate return back to block if there's an error (leading to inconsistent return types), so just spell out an Ok(()) at end of block for return.

use task::spawn (rather than spawn_local) to run futures that get pulled by an entire thread pool (as opposed to just one thread). More availbility and more equity in processing.. but you could get resumed by a different thread in between polls. So don't use thread-local storage. Use task-local storage

To tap into a thread pool, the future should also implement the `Send` marker trait to be able to safely pass things back and forth between threads. Closures passed to threads will stay on that thread forever because it doesn't leave for polling.. not the case for futures. Example of problem would be a function that uses an Rc reference count (rather than atomic reference count), leading to race condition on Rc

If you have a computationally intensive task, you'll still block (because there's progress being made on the poll). So use `spawn_blocking` to move the task to its own separate thread.

Tokio crate is very large and has several features but can be pulled out into specific dependncies.

You can have two async tasks.. but if you spawn separately and call await (like with client and server in chat app), you will wait for both tasks to finish. Instead you want to execute as soon as EITHER one has finished. so call `from_server.race(to_server)` to get the first one that returns `Poll::Ready()`

Use Arc reference pointers to refer to the same instance of tables (can clone many times). However, when you need to mutate the same state or transfer many things through the same socket. Use Mutex to lock and manage ownership. For HashMaps, can use dashmap crate for specialized concurrency access to similar datatype 

Future / Poll implementation: If future's value is ready, return it. Otherwise, stash a a clone of the Context's waker and return Poll::pending

**Pinning:** A future must always hold all the information needed to resume execution the next time it is polled. Once a future is polled and function body has begun execution, it could borrow references to variables stored in the future and then await.. leaving that part of the future borrowed. Starting after its first poll, we must assume the future may not be safe to move.

Pin is a wrapper for pointer types that restricts how the pointers can be used, ensuring that their references (like Self) cannot ever be moved again.. especially in between Polling. **So you must produce a Pin-wrapped pointer to the future before you can poll it**

Rust's strategy for keeping futures safe: a future can't become dangerous to move until it's polled; you can't poll a future until you've constructed a Pin-wrapped pointer to it; and once you've done that, the future can't be moved.

Side note: even after you Pin something.. you can have full mutable access, and move pointers. Pointers is always safe to move, polled or not. **Only the pointer moves. But its fragile referent stays put.**
<br>
### When to use Async code
<br>
"Great for IO" not necessarily true unless that IO is done outside of computer system (like networking). If IO on the system, that work needs to get same work done either way, and async operation takes more system calls to complete.

<br>
"Easier to write" True in languages with single-thread event loop and garbage collection. Doesn't carry over into Rust because if your Rust program compiles, it is free of data races.

<br>

Async tasks use up less memory. So good for tasks that that really have high numbers (like connections, chat server, multiplayer games, network routers). Faster to create tasks than threads. Good for when you're very busy with several tasks all at once that individually don't take up big "block" of computational time, but may have long-waiting system calls.
