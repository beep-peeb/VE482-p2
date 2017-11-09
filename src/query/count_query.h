#ifndef LEMONDB_COUNT_QUERY_H
#define LEMONDB_COUNT_QUERY_H

#include "query.h"
#include "task.h"

class CountQuery : public ComplexQuery {
    static constexpr const char *qname = "COUNT";
    int number;
public:
    LEMONDB_QUERY_WRITER(false);
    using ComplexQuery::ComplexQuery;
    std::vector<std::string> &getOperands() { return operands; }
    QueryResult::Ptr execute() override;
    std::string toString() override;
    QueryResult::Ptr combine() override;
    void addnumber() { number++; }
};

class CountTask : public Task {
protected:
    LEMONDB_QUERY_PTR(CountQuery);
public:
    using Task::Task;
    void execute() override;
};

#endif //LEMONDB_COUNT_QUERY_H
