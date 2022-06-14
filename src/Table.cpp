#include "Table.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace lms {
    Table::Table() {
        minColumnWidth = 2;
        maxColumnWidth = 250;
        surplusColWidth = 2;
    }

    Table::~Table() = default;

    void Table::SetColumns(const std::list<std::string> &columnNames) {
        assert(columns.empty() && "Columns already set");
        columns = columnNames;
        CalculateColumnWidths();
    }

    std::list<std::string> Table::GetColumns() const {
        assert(!columns.empty() && "Columns not set");
        return columns;
    }

    std::list<std::list<std::string>> Table::GetRows() const {
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
        EchoEntry(oss, columns);
        oss << std::endl;

        oss << std::endl;

        for (const auto &row: rows) {
            EchoEntry(oss, row);
            oss << std::endl;
        }
        return oss.str();
    }

    void Table::AddRow(const std::list<std::string> &rowValues) {
        assert(!columns.empty() && "Columns not set");
        assert(rowValues.size() == columns.size() && "Row size does not match columns size");
        rows.push_back(rowValues);
        CalculateColumnWidths();
    }

    void Table::EchoEntry(std::ostream &os, const std::list<std::string> &entry) const {
        assert(!entry.empty() && "Entry is empty");
        assert(columnWidths.size() == entry.size() && "Column widths size does not match entry size");


        size_t colIndex = 0;
        for (const auto &value: entry) {
            os << std::setw(columnWidths[colIndex++]) << value;
            os << std::setw(2) << "  ";
        }
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
            for (auto &entry: entries) {
                auto const &value = entry[c];
                assert(value.length() < maxColumnWidth && "Value size is greater than maximum allowed length");
                columnSizes.push_back(value.length() + surplusColWidth);
            }

            Table::ColumnWidth maxSize = *std::max_element(columnSizes.begin(), columnSizes.end());
            columnWidths.push_back(std::max(maxSize, minColumnWidth));
        }

        std::cout << "Column widths: " << std::endl;
        for (auto &width: columnWidths) {
            std::cout << static_cast<uint16_t>(width) << " ";
        }
        std::cout << std::endl;
    }
}