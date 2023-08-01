# Clipboard History Utility

🎓The Clipboard History Utility is a command-line program written in C that allows users to manage a history of copied items in the clipboard. It provides a simple and efficient way to keep track of recently copied texts and retrieve them for pasting when needed.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Compilation](#compilation)
- [Command-Line Options](#command-line-options)
- [System Requirements](#System-Requirements)
- [License](#license)

## Introduction

Managing clipboard history can be challenging, especially when you need to access previously copied items. The Clipboard History Utility solves this problem by providing a menu-based command-line interface to add, view, retrieve, and copy clipboard items.

## Features

- Add text items to the clipboard history.
- Display the clipboard history with item indices.
- Retrieve a specific item from the clipboard history.
- Copy a selected item back to the system clipboard for pasting.
- Clear the entire clipboard history.

## Usage

1. **Add item to clipboard history:**
   - Enter text to add to the clipboard history.
   - To stop adding items, enter 'q' or 'Q'.

2. **Get clipboard history:**
   - Display a list of clipboard items with their corresponding indices.

3. **Retrieve the item from clipboard history:**
   - Enter the index of the item you want to retrieve (from the displayed list).
   - The selected item will be shown, and you will have the option to copy it back to the system clipboard for pasting.

4. **Clear clipboard history:**
   - Clear all items from the clipboard history.

5. **Quit:**
   - Exit the Clipboard History Utility.


## Compilation

For Linux (GCC):
```
gcc clipboard_history.c -o clipboard_history
```

For Windows (MinGW):
```
gcc clipboard_history.c -o clipboard_history.exe
```

## Command-Line Options

The Clipboard History Utility does not use command-line options. Instead, it offers a menu-based command-line interface where users can select options by entering corresponding numbers.

## System Requirements

The Clipboard History Utility is compatible with Windows and Linux operating systems. It does not currently support macOS. To ensure proper functionality, make sure you have the required C compiler installed for your respective platform.

## License

This software is currently not open-source and has "All Rights Reserved." The developer retains all rights to the code. Please contact the developer for any licensing inquiries.



