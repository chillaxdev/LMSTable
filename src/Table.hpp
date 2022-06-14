#ifndef LMS_TABLE_HPP
#define LMS_TABLE_HPP

#include <list>
#include <string>
#include <vector>

namespace lms {
class Table {
   public:
    enum class Style { Default, TakeVos };

    Table();

    explicit Table(Table::Style style);

    ~Table();

    void SetColumns(const std::list<std::string> &columnNames);

    void AddRow(const std::list<std::string> &row);

    [[nodiscard]] std::list<std::string> GetColumns() const;

    [[nodiscard]] std::list<std::list<std::string>> GetRows() const;

    [[nodiscard]] std::string GetFormattedString() const;

    friend std::ostream &operator<<(std::ostream &os, const lms::Table &table);

    typedef uint8_t ColumnWidth;

   protected:
    enum class SpacingStrategy { First, Default, Last };

    void EchoEntry(std::ostream &os, const std::list<std::string> &entry) const;

    void EchoSpacing(std::ostream &os, Table::SpacingStrategy strategy = Table::SpacingStrategy::Default) const;

    void EchoLine(std::ostream &os) const;

    void CalculateColumnWidths();

    bool IsDefaultStyle() const;

    bool IsTakeVosStyle() const;

   private:
    std::list<std::string> columns;

    std::list<std::list<std::string>> rows;

    std::vector<Table::ColumnWidth> columnWidths;

    ColumnWidth minColumnWidth;
    ColumnWidth maxColumnWidth;
    uint8_t surplusColWidth;
    uint8_t spacing;
    mutable uint8_t cornerChar;
    Table::Style style;
};
}  // namespace lms

#endif  // LMS_TABLE_HPP