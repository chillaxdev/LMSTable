#include "Table.hpp"

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>

namespace lms {

Table::Table() {
    minColumnWidth = 2;
    maxColumnWidth = 250;
    surplusColWidth = 0;
    spacing = 5;  // TODO: Add assertions to ensure spacing is an odd number
    cornerChar = '|';
    style = Table::Style::Default;
}

Table::Table(Table::Style tableStyle) : Table() { style = tableStyle; }

Table::~Table() = default;

void Table::SetColumns(const std::list<std::string> &columnNames) {
    assert(columns.empty() && "Columns already set");
    columns = columnNames;
    CalculateColumnWidths();
}

[[maybe_unused]] std::list<std::string> Table::GetColumns() const {
    assert(!columns.empty() && "Columns not set");
    return columns;
}

[[maybe_unused]] std::list<std::list<std::string>> Table::GetRows() const {
    assert(!columns.empty() && "Columns not set");
    return rows;
}

std::ostream &operator<<(std::ostream &os, const lms::Table &table) {
    os << table.GetFormattedString();
    return os;
}

std::string Table::GetFormattedString() const {
    assert(!columns.empty() && "Columns not set");

    std::ostringstream oss;

    if (IsDefaultStyle()) {
        EchoLine(oss);
    }

    EchoEntry(oss, columns);
    oss << std::endl;

    EchoLine(oss);

    for (const auto &row : rows) {
        EchoEntry(oss, row);
        oss << std::endl;

        if (IsDefaultStyle()) {
            EchoLine(oss);
        }
    }

    return oss.str();
}

void Table::AddRow(const std::list<std::string> &rowValues) {
    assert(!columns.empty() && "Columns not set");
    assert(rowValues.size() == columns.size() && "Row size does not match columns size");
    rows.push_back(rowValues);
    CalculateColumnWidths();
}

void Table::EchoLine(std::ostream &os) const {
    cornerChar = '+';
    os << std::setfill('-');
    EchoEntry(os, std::list<std::string>(columns.size(), ""));
    os << std::endl;
    os << std::setfill(' ');
    cornerChar = '|';
}

void Table::EchoSpacing(std::ostream &os, Table::SpacingStrategy strategy) const {
    switch (strategy) {
        case Table::SpacingStrategy::First:
            if (IsDefaultStyle()) {
                os << std::setw(1) << cornerChar;
                os << std::setw(spacing / 2) << "";
            }
            if (IsTakeVosStyle()) {
                os << std::setw(spacing / 2) << "";
            }
            break;
        case Table::SpacingStrategy::Default:
            os << std::setw(spacing / 2) << "";
            os << std::setw(1) << cornerChar;
            os << std::setw(spacing / 2) << "";
            break;
        case Table::SpacingStrategy::Last:
            if (IsDefaultStyle()) {
                os << std::setw(spacing / 2) << "";
                os << std::setw(1) << cornerChar;
            }
            if (IsTakeVosStyle()) {
                os << std::setw(spacing / 2) << "";
            }
            break;
    }
}

void Table::EchoEntry(std::ostream &os, const std::list<std::string> &entry) const {
    assert(!entry.empty() && "Entry is empty");
    assert(columnWidths.size() == entry.size() && "Column widths size does not match entry size");

    size_t colIndex = 0;
    for (const auto &value : entry) {
        EchoSpacing(os, !colIndex ? Table::SpacingStrategy::First : Table::SpacingStrategy::Default);
        os << std::setw(columnWidths[colIndex++]) << value;
    }

    EchoSpacing(os, Table::SpacingStrategy::Last);
}

// TODO: Needs optimizations or think of a better architecture.
void Table::CalculateColumnWidths() {
    assert(!columns.empty() && "Columns not set");

    columnWidths.clear();

    std::vector<std::vector<std::string>> entries;
    entries.emplace_back(columns.begin(), columns.end());

    for (auto it = rows.begin(); it != rows.end(); ++it) {
        auto const &row = *it;
        entries.emplace_back(row.begin(), row.end());
    }

    for (size_t c = 0; c < columns.size(); c++) {
        std::vector<ColumnWidth> columnSizes;
        for (auto &entry : entries) {
            auto const &value = entry[c];
            assert(value.length() < maxColumnWidth && "Value size is greater than maximum allowed length");
            columnSizes.push_back(value.length() + surplusColWidth);
        }

        Table::ColumnWidth maxSize = *std::max_element(columnSizes.begin(), columnSizes.end());
        columnWidths.push_back(std::max(maxSize, minColumnWidth));
    }
}

bool Table::IsDefaultStyle() const { return style == Table::Style::Default; }

bool Table::IsTakeVosStyle() const { return style == Table::Style::TakeVos; }

}  // namespace lms