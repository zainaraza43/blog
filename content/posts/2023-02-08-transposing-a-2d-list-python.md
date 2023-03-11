---
title: Transposing a 2D List in Python
date: 2023-02-08
draft: false
---

Transposing a 2-dimensional list in Python is especially useful when reading data that's formatted similar to this:

```
X   Y   Z
1   2   9
2   5   6
3   6   5
...
```

Usually, you'll parse the input line by line and end up with an array that looks something like this:

```py
>>> print(data)
[[1, 2, 9], [2, 5, 6], [3, 6, 5], ...]
```

This usually isn't useful though, as we normally want the x, y, and z values grouped together. Doing this is simple with the help of `zip()` and list unpacking via `*`. Simply do the following to convert the data into a 2d list:

```py
data = [list(i) for i in zip(*data)]
```

The result will be:

```py
>>> print(data)
[[1, 2, 3], [2, 5, 6], [9, 6, 5]]
```

If you do this often, you may want to create a function to do this for you:

```py
def transpose(inputdata):
    return [list(i) for i in zip(*inputdata)]
```

Then you can simply call `transpose(data)` and it will return a new list with the data transposed. To overwrite the `data` variable, simply assign it the value, by calling `data = transpose(data)`
