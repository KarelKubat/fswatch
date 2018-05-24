# fswatch (File System Watcher)

## What it does

`fswatch` monitors one or more directories for changes and runs commands when
such changes are detected. This is mostly useful when developing.

*  Imagine that you're writing a Python script to do something fancy. You are
   adding features and would like to (re)run the script as soon as you save its
   sourcefile:

   ```shell
   cd ~/src
   fswatch python3 myscript.py
   ```

   Now `fswatch` will happily monitor the current directory (`~/src` that you
   `cd`d into) and run `python3 myscript.py` as soon as something in the the
   directory changes (in fact also when something in a subdirectory of `~/src`
   changes). By default, `fswatch` monitors the current directory.

*  Imagine that `myscript.py` reads some files from `~/data` and processes
   them. You want to rerun it as soon as something changes in the data files:

   ```shell
   fswatch -d ~/data python3`
   ```

   Here, flag `-d` adds a directory (plus its subdirs) to be watched.

*  Imagine that you are developing a program `myprog` that's built using
   `make`. As soon as you make a change to the sources, you want to re-run
   `make` to see if all still compiles:

   ```shell
   fswatch make
   ```

*  While developing `myprog` you'd not only like to re-run `make` when
   something changes, but you'd also want to start `myprog` to see that
   it still works:

   ```shell
   fswatch -- sh -c 'make && ./myprog'
   ```

   Here, using `sh -c 'make && ./myprog` will start `./myprog` only when `make`
   succeeds. (Read up on shell scripting if this is new to you.). `fswatch`
   needs the flag `--` to tell it to stop scanning for flags, or it would get
   confused by the hypen in `-c` which isn't for `fswatch` but for `sh`.

There are of course flags to control the behaviour of `fswatch`. You get a
full listing by running `fswatch` without arguments (or `fswatch -h`). Some
of the flags that might need explaining, are:

*  `-a`: Without this flag, `fswatch` skips watching typical editor backup
   files, ones that start with `#` or `~` or `.`. If you want `fswatch` to
   also monitor such files, add a `-a`.

*  `-K`: Without this flag, `fswatch` will stop when it has no more files
   to watch. If the watched directory might become empty, but `fswatch` should
   patiently wait for new files, add `-K`.

*  `-k NSEC` (nr. of seconds): When `fswatch` detects a change, and `NSEC` has
   expired, then it will kill any running program and redo all. This is handy
   when you are developing daemons that otherwise don't terminate. The default
   is 30 seconds.

## How to get it

Clone the repository and simply type `make`. You will need a C++ compiler. This
makes `fswatch` locally (in the sources directory).

If you want to install the program into `$HOME/bin` (i.e., your personal *bin*
directory), then type `make install`. If you want to install it into another
directory, e.g. `/usr/local/bin`, type

```shell
BINDIR=/usr/local/bin make install
```

## License

`fswatch` is distributed under GPLV3, which basically means that you're free to
do with it as you like, you may modify it, provided that you keep the license
intact and that you make your changes available to everyone. As a personal
favor, I'd like to be informed of any changes or new handy features so that I
can merge them into the sources for a next version.

See the file `LICENCE.md`.
