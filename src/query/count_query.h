#ifndef LEMONDB_COUNT_QUERY_H
#define LEMONDB_COUNT_QUERY_H

#include "query.h"
#include "task.h"

class CountQuery : public ComplexQuery {
    static constexpr const char *qname = "COUNT";
private:
	int number;
public:
    using ComplexQuery::ComplexQuery;
	std::vector<std::string> &getOperands() { return operands; }
    QueryResult::Ptr execute() override;
    std::string toString() override;
    QueryResult::Ptr combine() override;
	void addnumber() { number++; }
};

class CountTask : public Task {
private:
    CountQuery *getQuery() {
        return (CountQuery *) query.get();
    }
public:
    using Task::Task;
    void execute() override;
};

#endif //LEMONDB_COUNT_QUERY_H
