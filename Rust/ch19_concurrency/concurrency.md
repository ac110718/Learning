## Concurrency
<br>
Suppose processing large corpus of documents, write a natural loop

<br>

```rust
fn process_files(filenames: Vec<String>) -> io::Result<()> {
    for document in filenames {
        let text = load(&document)?;
        let results = process(text);
        save(&document, results)?;
    }
    Ok(())
}
```
Program would just run sequentially. But you can easily speed this up with fork-join parallelism. Fork is to start a new thread. Join a thread is to wait for it to finish. No locking of shared resources.. the only waiting is at the end when combining the results.

A fork-join program is deterministic as long as the threads are really isolated. Program should produce the same result, regardless of variations in thread speed. This is concurrency model without race conditions.

... but all of this obviously requires isolated units of work.

```rust
use std::{thread, io};

fn process_files_in_parallel(filenames: Vec<String>) -> io::Result<()> {
    const NTHREADS: usize = 8;
    let worklists = split_vec_into_chunks(filenames, NTHREADS);

    let mut thread_handles = vec![];
    for worklist in worklists {
        thread_handles.push(
            thread::spawn(move || process_files(worklist))
        );
    }
    for handle in thread_handles {
        handle.join().unwrap()?;
    }
    Ok(())
}
```
This has same type signature as original `process_files`. Spawn a thread for each worklist.spawn(), which returns a value called a `JoinHandle` 

Worklist is moved into the closure, and spawn will move the entire closure (including the worklist vector) over to the new child thread.

Use the .join() method of the JoinHandles to wait for all eight threads to finish (it's necessary to join, or else you'd get an early exit from the main program).

.join() returns a Result that's an error if the child thread panicked. But panic is safe and per thread, so it's just reported as an error Result rather than spreading to the other threads.

### What if you want to share (immutable) data across threads?

<br> Need to pass an atomic reference count that will keep references alive so long as the count is greater than one.

```rust
fn process_files_in_parallel(filenames: Vec<String>, glossary: Arc<GigabyteMap>) -> io::Result<()> {
    ...
    for worklist in worklists {
        let gloassary_for_child = glossary.clone() // clones just the Arc
        thread_handles.push(
            spawn(move || process_files(worklist, &glossary_for_child))
        );
    }
}
```

Other libraries can be used like Crossbeam (scoped threads) or Rayon library, which pools together all the tasks and pulls into each CPU core. But to the programmer, it's like you're spwaning one thread per element in the vector.

```rust
use rayon::prelude::*

fn process_files_in_parallel(filenames: Vec<String>, glossary: & GigabyteMap) -> io::Result<()> {
    filenames.par_iter()
        .map(|filename| process_file(filename, glossary))
        .reduce_with(|r1, r2| {
            if r1.is_err() { r1 } else { r2 }
        })
        .unwrap_or(Ok(())) 
}
```

### Channels
<br>
A channel is a one-way conduit for sending values from one thread to another. A thread-safe queue. Sort of like Unix pipes.. one end is for sending data, and the other end is for receiving, with two ends owned by two different threads.

sender.send(item) puts a single value into the channel; receiver.recv() removes one. `Sender<String>` and `Receiver<String>` respectively

Ownership is transferred from the sending thread to the receiving thread. If the channel is empty, receiver.recv() blocks until a value is sent.

Threads can communicate by passing values to one another. It's a very simple way for threads to work together without using locking or share memory.

Example: Use channels to build a concurrent program that creates an inverted index. Suppose `documents` is a Vec<PathBuf>, a vector of filenames.

```rust
use std::{fs, thread};
use std::sync::mpsc;

// create a pair of channel values
let (sender, receiver) = mpsc::channel();

// ownership of sender is moved to new thread
let handle = thread::spawn(move || { 
    for filename in documents {
        let text = fs::read_to_string(filename)?;
        // send text into the channel, to later be moved by receiver
        // only the pointer to <String> is copied to receiver
        if sender.send(text).is_err() {
            break;
        }
    }
    Ok(())
});
```
<br>
This code gets wrapped up in a broader function that creates and returns both the reciver and the new thread's JoinHandle (receiver, handle)

then spain a loop that received value like..
```rust
while let Ok(text) = receiver.recv() { do_something_with(text) }
..OR..
for text in receiver { do_something_with(text) }
```

Receiving thread will block until some other thread sends a value. Will end when channel is empty and Sender has been dropped.

Second stage of the pipeline will look something like this...

```rust
fn start_file_indexing_thread(texts: mpsc::Receiver<String>) -> (mpsc::Receiver<InMemoryIndex>, thread::JoinHandle<()>) {
    let (sender, receiver) = mpsc::channel();
    let handle = thread::spawn(move || {
        for (doc_id, text) in texts.into_iter().enumerate() {

            // splits input string per word and produces map from word to lists of positions
            let index = InMemoryIndex::from_single_document(doc_id, text);
            if sender.send(index).is_err() {
                break;
            }
        }
    })

    (receiver, handle)

}
```

Later stages of the pipeline look similar, with each one consuming a receiver created by the previous stage...

Have one function that will run the entire pipeline... with each stage of pipeline returning receiver and handler that will be fed one into another until the final stage, which will merge into one big index. Finally, join the handles from each stage to ensure they finish running, and unwrap() to handle any errors.

mpsc stands for multiproducer, single consumer. Can have many senders and one receiver... but if not careful you can wind up sending information fater than receiver can handle, creating huge queue..

Use backpressure. Process will block until there's more room in the pipe. Rust equivalent is to use a synchronous channel. Good way to optimize memory without decreasing throughput.
```rust
let (sender, receiver) = mpsc::sync_channel(1000);
```
Must use an Arc rather than Rc because you have can a data race on the reference count passing and cloning the Rc between two threads.

Iterators can also be passed back and forth across the channel, but you must implement a new trait that specifies that the type must be of not just Iterator, but also of Send and lifetime 'static so that it is failsafe

## Mutex
<br>
Fork-join (map-reduce) is great for highly parallel computation, channels are great for loosely coupled components, but what if you want a shared mutable state?
<br><br>

A **mutex** (or lock) is used to force multiple threads to take turns when accessing certain data. 

The calls for mutex.Acquire() and mutex.Release() mark the beginning and end of a critical section in the code. For each mutex in a program, only one thread can be running inside a critical section at a time. If one thread is in a critical section, all other threads that call mutex.Acquire() will block until the first thread reaches mutex.Release()

```C++
void FernEmpireApp::JoinWaitingList(PlayerId player) {
    mutex.Acquire();

    waitingList.push_back(player);
    if (waitingList.size() >= GAME_SIZE) {
        vector<PlayerId> players;
        waitingList.swap(players);
        StartGame(players);
    }

    mutex.Release();
}
```

We say that the mutex *protects* the data: in this case, mutex protects waitingList. It is the programmer's responsibility to make sure every thread always acquires the mutex before accessing the data and releases it afterward.

But mutexes are very easy to mess up. In C++, the data and the lock are separate objects. Ideally, comments explain that every thread must acquire the mutex before touching the data.

Unlike C++, in Rust the protected data is stored *inside* the Mutex. Creating a new Mutex looks liek creating a new Box or Arc, but Mutex is about locking rather than signifying heap allocation. Arc is handy for sharing things acros threads. Mutex is handy for mutable data that's shared across threads.

```rust
impl FernEmpireApp {
    fn join_waiting_list(&self, player: PlayerId) {
        // returns a MutexGuard<WaitingList> value. 
        // Essentially thin wrapper around a &mut WaitingList object
        let mut guard = self.waiting_list.lock().unwrap();

        guard.push(player);
        if guard.len() == GAME_SIZE {
            let players = guard.split_off(0);
            self.start_game(players);
        }
    } // guard is dropped here but you can manually drop the guard after
} // let players = guard.split_off(0) with drop(guard)
```
A Mutex dynamically enforces exclusive access during run-time vs. doing so statically during compile time. Many threads may have shared access to the mutex itself.. but the mutex is what provides exclusive access to the underlying data.

Channels server as an abstraction boundary in your code, making it easy to separate isolated components for testing. Mutexes encourage a "just add a method" way of working that can lead to a monolithic blob of interrelated code.

Deadlocks. The best protection is to keep critical sections small. Get in, do your work, and get out. Avoid cyclical pipelines (most workflows are acyclic anyways).

## Read / Write Locks

With a mutex, thre protected data has only one reader and one writer (or none). With a read / write lock, it can have either **one writer** or **many readers**.

```rust
use std::sync::RwLock;

struct FernEmpireApp {
    ...
    config: RwLock<AppConfig>
    ...
}
// just read configuration using RwLock::read()
fn mushrooms_enabled(&self) -> bool {
    let config_guard = self.config.read().unwrap();
    config_guard.mushrooms_enabled
}
// reload configuration requires RwLock::write()
fn reload_config(&self) -> io::Result<()> {
    let new_config = AppConfig::load()?;
    let mut config_guard = self.config.write().unwrap();
    *config_guard = new_config; //write in new value
    Ok(())
}
```

## Conditional Variables (Condvar)
<br>
Often a thread needs to wait until a certain condition becomes true:

* During server shutdown, main thread waits until other threads finished exiting
* When worker thread nothing to do, needs to wait until there is some data to process.
* A thread implementing distributed consensus protocol may need to wait until a quorum of peers have responded.

Programs can use *conditional variables* .. which have methods .wait() which blocks until some other thread calls .notify_all(). When desired condition becomes true, we call Condvar::notify_all (or notify_one) to wake up any waiting threads.

```rust
self.has_data_condvar.notify_all();
// go to sleep
while !guard.has_data() {
    guard = self.has_data_condvar.wait(guard).unwrap();
}
```