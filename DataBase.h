#include <map>
#include <QTime>
#include <QString>
#include <stack>
#include <vector>
class DB
{
private:
    struct elem
    {
        QTime date_create;
        QTime date_change;
        QString name;
        QString contain;
    };
    enum class sort_ways
    {
        by_name,
        by_create,
        by_change
    };
    int get_idx();
    void deep(std::vector<elem*>, int, int, bool (*cmp)(const elem&, const elem&));
    friend bool greater_by_name(const elem& argv1, const elem& argv2);
    friend bool greater_by_create(const elem& argv1, const elem& argv2);
    friend bool greater_by_change(const elem& argv1, const elem& argv2);
    std::map<int, elem *> storage;
    int size;
    int idx;
    std::stack<int> indices;
public:
    DB():size(0), idx(1)
    {}
    ~DB();
    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;
    elem &get(int idx);
    void del(int idx);
    void add(const elem&);
    void sort(sort_ways ways = sort_ways::by_name);
};

bool greater_by_name(const DB::elem& argv1, const DB::elem& argv2);
bool greater_by_create(const DB::elem &argv1, const DB::elem &argv2);
bool greater_by_change(const DB::elem &argv1, const DB::elem &argv2);