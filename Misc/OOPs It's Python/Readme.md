# Challenge Description

> Python is dynamically typed and garbage-collected. It supports multiple programming paradigms, including structured (particularly procedural), **object-oriented and functional programming**. It is often described as a "batteries included" language due to its comprehensive standard library. (From Wiki)

# Hint

> Name mangling

# Writeup

Since there's no real private member in Python, so you can still access the private member by using some tricks. The way Python implement the private is just using [name mangling](https://www.geeksforgeeks.org/name-mangling-in-python/), that's why you should never write your secret in the code even if you think it's "private".

The solution: `chal._Challenge__flag`
