A 32-bit ELF executable loader written in C using POSIX functions. Features
demand paging and invalid access checking. Want to try it out?

```bash
chmod +x example_usage.sh
./example_usage.sh
```

This will compile everything needed and run an example program.

To run other executables, assuming that libso_loader.so and your binary are in
the same folder and you're currently in that folder, run the following command:

```bash
LD_LIBRARY_PATH=. ./so_exec <filename>
```

Note that this loader only supports 32-bit ELF binaries, so if you want to try
out things that are not the test program, you'll have to compile them as such.