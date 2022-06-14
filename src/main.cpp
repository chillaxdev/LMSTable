#include <iostream>

#include "Table.hpp"

using namespace lms;

int main() {
    // Table table();
    Table table(Table::Style::TakeVos);
    table.SetColumns({"No.", "Name", "Author"});

    table.AddRow({"1", "Harry Potter", "J.K. Rowling"});
    table.AddRow({"2", "The Lord of the Rings", "J.R.R. Tolkien"});
    table.AddRow({"3", "The Catcher in the Rye", "J.D. Salinger"});
    table.AddRow({"4", "The Great Gatsby", "F. Scott Fitzgerald"});
    table.AddRow({"5", "The Grapes of Wrath", "John Steinbeck"});

    std::cout << "Books:" << std::endl << std::endl << table << std::endl;
    return 0;
}