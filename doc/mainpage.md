# chomp {#mainpage}

**chomp** is a small, standalone utility that removes trailing newline
characters from its input.


## Components

| Unit | File(s) | Summary |
| ---- | ------- | ------- |
| Public API | `chomp.h`, `chomp.c` | Version macros, flags, and `sistool_chomp()` |
| Program entry | `entry.c` | Command-line handling and program lifecycle |


## API

The `sistool_chomp()` function reads from an input stream, applies the
requested newline handling flags, and writes the result to an output stream.


<!-- ########################### end of file ########################### -->
