# CLASP - FAQ <!-- omit in toc -->

The FAQ list is under (constant) development. If you post a question on the
Issues forum (https://github.com/synesissoftware/CLASP/issues)
it will be used to create one.

- [Q1: "How do I build CLASP?"](#q1-how-do-i-build-clasp)
- [Q2: "Does CLASP have its own unit-tests?"](#q2-does-clasp-have-its-own-unit-tests)


# FAQs: <!-- omit in toc -->

## Q1: "How do I build CLASP?"

See instructions in [INSTALL.md](./INSTALL.md).

For a **C** API-only build (no **STLSoft** / **xTests**):

```bash
$ ./prepare_cmake.sh --no-cpp --disable-testing
```

**NOTE**: **`--no-cpp`** alone still configures tests, and tests still need
**STLSoft** (via **xTests**). Add **`--disable-testing`** / **`-T`** to
elide both.


## Q2: "Does CLASP have its own unit-tests?"

Yes, under the **./test/unit** and **./test/component** directories.


<!-- ########################### end of file ########################### -->

