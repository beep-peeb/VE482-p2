//
// Created by admin on 2017/11/2.
//

#ifndef LEMONDB_DELETE_QUERY_H
#define LEMONDB_DELETE_QUERY_H

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
    CountTask(const Table::KeyType , const std::shared_ptr<ComplexQuery> &query,
               Table &table, Table::Iterator begin, Table::Iterator end) :
            Task(query, table, begin, end) {};
    void execute() override;
};

#endif //LEMONDB_DELETE_QUERY_H
