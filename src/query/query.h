#ifndef LEMONDB_QUERY_H
#define LEMONDB_QUERY_H

#include <string>
#include <memory>
#include <atomic>
#include "query_base.h"
#include "../uexception.h"
#include "../db/db_table.h"
#include "../query_results.h"
#include "../task_results.h"
#include "../db/db.h"

struct QueryCondition {
    std::string field;
    std::string op;
    std::string value;
};

class NopQuery : public Query {
public:
    QueryResult::Ptr execute() override {
        return std::make_unique<NullQueryResult>();
    }

    std::string toString() override {
        return "QUERY = NOOP";
    }
};


class ConditionedQuery : public Query {
public:
    bool evalCondition(const std::vector<QueryCondition> &conditions,
                       const Table::Object &object);
};

class ComplexQuery : public ConditionedQuery {
protected:
    std::vector<std::string> operands;
    std::vector<QueryCondition> condition;
    std::vector<std::shared_ptr<Task> > tasks;
public:
    typedef std::shared_ptr<ComplexQuery> Ptr;

    ComplexQuery(std::string targetTable,
                 std::vector<std::string> operands,
                 std::vector<QueryCondition> condition)
            : operands(std::move(operands)),
              condition(std::move(condition)) {
        this->targetTable = std::move(targetTable);
    }

    const std::vector<QueryCondition> &getCondition() {
        return condition;
    }
    
    template<class TaskType>
    void addIterationTask(Database &db, Table &table) {
        auto begin = table.begin();
        decltype(begin) end;
        auto size = table.size();
        while (size > 0) {
            if (size >= 100000) {
                size -= 100000;
                end = begin + 100000;
            } else {
                size = 0;
                end = table.end();
            }
            auto task = std::shared_ptr<Task>(new TaskType(Query::Ptr(this), &table, begin, end));
            db.addTask(std::move(task));
        }
    }

};
 

#endif //LEMONDB_QUERY_H
