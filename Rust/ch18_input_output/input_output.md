## Input and Output
<br>
Rust input and output organized around three traits: 

<br>

|Type|Purpose|
|---|---|
|Read|byte-orinted input. Called *readers*|
|BufRead|reading lines of text|
|Write| Both byte-oriented and UTF-8 text output|

```rust
fn grep(target: &str, reader: R) -> io::Result<()> 
    where R: BufRead
{
    for line_result in reader.lines() {
        let line = line_result?;
        if line.contains(target) {
            prinln!("{}", line);
        }
    }
    Ok(())
}

// Collect over lines into vector
let lines = reader.lines().collect::<io::Result<Vec<String>>>()?
```
<br>
Write macro is similar to println! macro but take in an extra first argument, a writer. Other difference is that they return a Result, so must be handled with ? operator.

```rust
writeln!(io::stderr(), "error: world not helloable")?;
```

### Files and Directories
<br>
Files and directories are mostly in Unicode, but not necessarily. As such, they use their own type OsString to distinguish from Rust strings, which are always valid Unicode.

`path.components()` will return an iterator over components of a given path.

`#[cfg(unix)] pub mod unix` or `#[cfg(target_os = "linux")]` indicates conditional compiation based on operating system