# FileSorter

FileSorter is a small C++17 command-line utility that sorts files by their extensions using a user-defined configuration file.

The program reads extension rules from a text config, shows a preview of where each file will be moved, asks for confirmation, and then moves files from a source folder into categorized folders inside an output folder.

## Features

- Reads sorting rules from a `.txt` config file
- Supports multiple extensions per category
- Ignores empty lines and comments in the config
- Trims extra spaces around folder names and extensions
- Shows a safe preview before moving files
- Moves files into category folders
- Sends unknown extensions to `Other`
- Lets the user choose:
  - source folder
  - output folder
- Keeps the console open after execution when launched as an `.exe`

## Example

Source folder:

```text
input/
  movie.mp4
  archive.zip
  setup.exe
  notes.txt
  unknown.qwe
```

Config:

```text
Video: .mp4, .avi, .mkv
Archives: .zip, .rar, .7z
Programs: .exe, .msi
Documents: .txt, .pdf, .docx
```

Output folder after sorting:

```text
sorted/
  Video/
    movie.mp4

  Archives/
    archive.zip

  Programs/
    setup.exe

  Documents/
    notes.txt

  Other/
    unknown.qwe
```

## Project Structure

```text
FileSorter/
  src/
    main.cpp
    config_parser.cpp
    config_parser.h
    file_sorter.cpp
    file_sorter.h

  config/
    File_Exp.txt
```

## Config Format

The configuration file describes which extensions should go into which folders.

Example:

```text
# Media files
Video: .mp4, .avi, .mkv
Images: .png, .jpg, .jpeg, .webp

# Documents
Documents: .txt, .pdf, .docx

# Archives
Archives: .zip, .rar, .7z

# Programs
Programs: .exe, .msi
```

Rules:

- One category per line
- Folder name goes before `:`
- Extensions go after `:`
- Extensions are separated by commas
- Spaces around names and extensions are allowed
- Empty lines are ignored
- Lines starting with `#` are treated as comments

## How It Works

1. The program loads extension rules from `config/File_Exp.txt`.
2. The user enters a source folder.
3. The user enters an output folder.
4. The program scans files in the source folder.
5. For each file, it checks the file extension.
6. If the extension exists in the config, the file is assigned to the matching category.
7. If the extension is unknown, the file is assigned to `Other`.
8. The program shows a preview.
9. After confirmation, files are moved into the output folder.

## Build

### Windows / MinGW

From the project root:

```bash
cd src
g++ main.cpp config_parser.cpp file_sorter.cpp collision_resolver.cpp -std=c++17 -o sorter
```

Run:

```bash
./sorter.exe
```

### Linux

From the project root:

```bash
sudo make && make install
```

Run:

```bash
filesorter
```
(Note: ensure /usr/local/bin is added to your $PATH)

To remove the program from your system:
```bash
sudo make uninstall
```
## Usage

1. Build the project.
2. Make sure the config file exists:

```text
config/File_Exp.txt
```

3. Run the program.
4. Enter the source folder path.
5. Enter the output folder path.
6. Check the preview.
7. Confirm sorting with `y`.

Example:

```text
Enter source folder:
C:/Users/User/Desktop/input

Enter output folder:
C:/Users/User/Desktop/sorted

=== Preview ===
movie.mp4 -> C:/Users/User/Desktop/sorted/Video/movie.mp4
archive.zip -> C:/Users/User/Desktop/sorted/Archives/archive.zip

Continue moving files? (y/n):
y
```

## Safety Notes

Use a test folder before running the program on important files.

The program moves files, so the original source folder will no longer contain the moved files after confirmation.

Recommended first test:

```text
test_input/
  video.mp4
  archive.zip
  document.txt
  unknown.qwe
```

## Current Limitations


- Does not currently support undo
- Does not copy files, only moves them
- Extension matching depends on how extensions are written in the config

## Possible Future Improvements

- Copy mode instead of move mode
- Logging to a file
- JSON or TOML config support
- GUI version
- CMake build support (partially done)

## Why This Project Exists

This project is a small practical utility for organizing files automatically.

It is also a learning project focused on:

- C++17
- `std::filesystem`
- file handling
- config parsing
- maps and strings
- modular project structure
- safe command-line workflows

