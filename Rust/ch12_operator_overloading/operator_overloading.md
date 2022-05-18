## Operator Overloads
<br>Below is definition of std::ops::Add

The trait Add<T> is effectively the ability to add a T value to yourself
```rust
trait Add<Rhs = Self> { // Rhs must be same type as self. 
    type Output; 
    fn add(self, rhs: Rhs) -> Self::Output // Output must be of same type as self. 
}
```

```rust
impl Add for Complex<i32> {
    type Output = Complex<i32>;
    fn add(self, rhs: Self) -> Self {
        Complex {
            re: self.re + rhs.re,
            im: self.im + rhs.im
        }
    }
}
```

```rust
impl<T> Add for Complex<T> // generic, not just for i32
where
    T: Add<Output = T>, // restrict T to types that can be added to themselves
{
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        Complex {
            re: self.re + rhs.re,
            im: self.im + rhs.im
        }
    }
}
```

```rust
trait Neg {
    type Output;
    fn neg(self) -> Self::Output;
}

use std::ops::Neg;
impl<T> Neg for Complex<T>
where
    T: Neg<Output = T>
{
    type Output = Complex<T>;
    fn neg(self) -> Complex<T> {
        Complex {
            re: -self.re,
            im: -self.im
        }
    }    
}

use std::ops::AddAssign;

impl<T> AddAssign for Complex<T>
where
    T: AddAssign<T>
{
    fn add_assign(&mut self, rhs: Complex<T>) {
        self.re += rhs.re;
        self.im += rhs.im;
    }
}
```

## Equivalence Comparisons
<br> ParialEq trait is for == and != operators.
```rust
assert_eq!(x == y, x.eq(&y))
assert_eq!(x != y, x.ne(&y))

impl<T: PartialEq> PartialEq for Complex<T> {
    fn eq(&self, other: &Complex<T>) -> bool {
        self.re == other.re && self.im == other.im
    }
}
```



