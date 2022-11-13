## features

in scope:
- functions
- variables (mutable and immutable)
- pointers
- if/else
- switch
- for, while, do-while loops
- structs
- static and dynamic arrays
- strongly typed enums

out of scope:
- meta-programming
-

### functions

```
fn func_name(params): ret_type
{
  ...

  ret [expression];
}

fn add(a: i32, b: i32): i32
{
  ret a + b;
}

fn print(): void
{
  ...
}
```

### variables

```
// mutable:
let var_name: var_type;
let var_name: var_type = initial_val;

// immutable:
const var_name: var_type = initial_val;
```
