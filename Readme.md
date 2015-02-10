
# dict

Simple dict implemented by c.

Modified from [clibs/list](https://github.com/clibs/list).

## API

Below is the public api currently provided by "dict".

## dict_t *dict_new();

Allocate and initialize a `dict`.

```c
dict_t *mydict = dict_new();
```

## dict_pair_t \*dict_pair_new(char *key, void *val)

Allocate and initialize a `dict_pair_t` with the given _key_, _val_.

```c
dict_pair_t *pair = dict_pair_new("my key", "my value");
node->val; // "my value"
```

## dict_pair_t \*dict_get(dict_t \*self, char *key)

Return the `dict_pair_t` or __NULL__.

```c
dict_pair_t *pair = dict_get(dict, "some key");
```

## dict_pair_t \* dict_set(dict_t \*self, char *key, void *val)

Insert new `dict_pair_t` to `dict`, and return it.

```c
dict_pair_t *new_pair = dict_set(dict, "other key", "other value");
```

## void dict_remove(dict_t \*self, char *key)

Remove _pair_ from the dict by _key_, freeing it and it's value.

```c
dict_remove(dict, "some key");
```

## void dict_destroy(dict_t *self)

Free the dict and all pairs.

```c
dict_destroy(dict);
```

## dict_iterator_t \*dict_iterator_new(dict_t *dict)

Allocate and initialize a `dict_iterator_t`.

```c
dict_pair_t *pair;
dict_iterator_t *it = dict_iterator_new(dict);
while ((pair = dict_iterator_next(it))) {
  puts(pair->key);
  puts(pair->val);
}
```

## dict_pair_t \*dict_iterator_next(dict_iterator_t *self)

Return the next `dict_pair_t` or __NULL__.

## void dict_iterator_destroy(dict_iterator_t *self);

Free the iterator only.

```c
dict_iterator_destroy(it);
```

## Examples

Dict iteration:

```c
dict_t *langs = dict_new();

dict_pair_t *c = dict_set(langs, "c", "c");
dict_pair_t *js = dict_set(langs, "js", "js");
dict_pair_t *ruby = dict_set(langs, "ruby", "ruby");

dict_pair_t *pair;
dict_iterator_t *it = dict_iterator_new(langs);
while ((pair = dict_iterator_next(it))) {
  puts(pair->key);
  puts(pair->val);
}

dict_iterator_destroy(it);
dict_destroy(langs);
```

stdout:

    c
    js
    ruby

## Benchmarks

    $ make benchmark

     10,000 piars

                set: 0.3125s
                get: 0.0000s
            iterate: 0.0000s

## Testing

    $ make test

## License

(The MIT License)

Copyright (c) 2015 c4605 &lt;bolasblack@gmail.com&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
