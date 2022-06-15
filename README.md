# LMS Table (C++ 17 Table Library)

> ❗ Under Development

LMS stands for "Lightweight Minimal Simple".

This is a simple C++17 library for displaying data in a neatly formatted table.  
It will strictly stand by the principle of LMS which means no fancy fonts, color, etc.

## Style

### Default Style

![image](https://user-images.githubusercontent.com/25753366/173619750-3d422673-2f53-4a54-a9b2-f97054520b4b.png)

### TakeVos Style ([@takev](https://github.com/takev))

![image](https://user-images.githubusercontent.com/25753366/173629807-ed6a6b77-1bd5-4f9e-b1cb-49d744ab3ed0.png)

## Example

```c++
#include "LMSTable.hpp"

using namespace lms;

int main(int argc, char **argv) {
  // Initialize table with style. If not specified, the default style is selected.
  Table table(Table::Style::TakeVos);
  
  // Initialize the columns
  table.SetColumns({"No.", "Name", "Author"});
  
  // Add the rows
  table.AddRow({"1", "Harry Potter", "J.K. Rowling"});
  table.AddRow({"2", "The Lord of the Rings", "J.R.R. Tolkien"});
  table.AddRow({"3", "The Catcher in the Rye", "J.D. Salinger"});
  table.AddRow({"4", "The Great Gatsby", "F. Scott Fitzgerald"});
  table.AddRow({"5", "The Grapes of Wrath", "John Steinbeck"});
  
  // Print the Table
  std::cout << table << std::endl;
  
  // If you want to print it yourself, you can get the output string of rendered table.
  std::string tableString = table.GetFormattedString();
  return 0;
}
```