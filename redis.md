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

### life time of key

1. EXPIRE key seconds

2. TTL key 
> time to live

    * -1 : never die
    * -2 : not exist

### data structures

1.list
    * RPUSH,LPUSH key value
    * LRANGE key start end
    * 0 -1 : show all
    * 0 1 : index 0 to 1
    * LLEN key
    * LPOP,RPOP key
2. set
    * SADD key value
    * SREM key value: removes value
    * SISMEMBER key value
    * SMEMBERS key : show all keys in the set
    * SUNION key1 key2 ... : keys of combined set (duplication key only show one time)
3. sorted set
    * ZADD key value
    * ZRANGE key start end 
4. hashes
    * HSET hashname key value
    * HGETALL hashname
    * HMSET hashname key1 value1 key2 value2 ...
    * HGET hashname key
    * HINCRBY hashname key incr_value: ex) HINCRBY user:1000 visits 1 => incr 1
    * HDEL hashname key

more hash commands: [here](http://redis.io/commands#hash)


