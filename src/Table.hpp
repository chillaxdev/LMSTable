#ifndef LMS_TABLE_HPP
#define LMS_TABLE_HPP

#include <list>
#include <string>
#include <vector>

namespace lms {
    class Table {
    public:
        Table();

        ~Table();

        void SetColumns(const std::list<std::string> &columnNames);

        void AddRow(const std::list<std::string> &row);

        [[nodiscard]] std::list<std::string> GetColumns() const;

        [[nodiscard]] std::list<std::list<std::string>> GetRows() const;

        [[nodiscard]] std::string GetFormattedString() const;

        friend std::ostream &operator<<(std::ostream &os, const lms::Table &table);

        typedef uint8_t ColumnWidth;

    protected:
        void EchoEntry(std::ostream &os, const std::list<std::string> &entry) const;

        void CalculateColumnWidths();

    private:
        std::list<std::string> columns;

        std::list<std::list<std::string>> rows;

        std::vector<Table::ColumnWidth> columnWidths;

        ColumnWidth minColumnWidth;
        ColumnWidth maxColumnWidth;
        ColumnWidth surplusColWidth;
    };
}


#endif //LMS_TABLE_HPP