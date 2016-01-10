#redis cheatsheet

###key - value

1. set key_name value

2. get key_name value

###increment number

1.incr key_name
>is it equivalent to 
```redis
x = get count
x = x + 1
set count x
```
???
*no*, INCR ensure that it is an *atomic operation*

2.
