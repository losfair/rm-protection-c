# What is this?
 `rm-protection-c` is another implementation of [rm-protection](https://github.com/alanzchen/rm-protection) in the C programming language.
 It is a safe alternative for removing file. It works exactly the same as `rm` (in fact it passes arguments to `rm` almost untouched).
 The only difference is that it refuses to proceed if a `.*.rm-protection`  file is found and you failed to answer a question.

# Quick Start

1.  Get the binaries from the [Releases](https://github.com/losfair/rm-protection-c/releases) page

2.  Extract the binaries to `/usr/local/bin/` (the dynamically-compiled version is preferred. If it doesn't work, try the statically-compiled version.)

3.  Make an alias for `rm-p` .

     If you are sure, `alias rm="rm-p"`

4.  Protect your files using `protect`.

5.  Happy rm-ing!

# How does it work?

 It consists of two utilities: `rm-p` and `protect`. The latter one is to help you protect files.

 For example, you have a file called `important_file` and it is `protect`ed by `.important_file.rm-protection`.
 `rm-p` will recognize that `important_file` is protected and prompt to ask you a question stored in `.important_file.rm-protection`. `rm-p` will only proceed if you get the answer correctly.

# Requirements
- Linux, unix or macOS (Currently, pre-compiled binaries are only available for Linux)

# Known issues
- Currently does not support protecting files whose name starts with "-".

# How to contribute?
Pull requests and issues are all welcome! Or tell others about this, so you can even `protect` the files you send to others!

Actually I don't care if people are using my implementation at all. I just think this kind of mechanism can be great -- using a `.rm-protection` file that asks questions.

If the community welcomes this mechanism, it will soon be ported/rewritten in every platform or languages, or even be implemented in the GNU coreutils. Then you can even get some default protections shipped with distributions and packages.

**So if you agree on this mechanism, please share with others!**
