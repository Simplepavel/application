#include <map>
#include <QTime>
#include <QString>
#include <stack>
#include <vector>

struct elem
{
    QTime date_create;
    QTime date_change;
    QString name;
    QString contain;
    elem(const QTime& d_crt, const QString& n, const QString& c):
    date_create(d_crt), date_change(date_create), name(n), contain(c)
    {}
};
class DB
{
private:
    enum class sort_ways
    {
        by_name,
        by_create,
        by_change
    };
    void deep(std::vector<elem *>, int, int, bool (*cmp)(const elem &, const elem &));
    // friend bool greater_by_name(const elem &argv1, const elem &argv2);
    // friend bool greater_by_create(const elem &argv1, const elem &argv2);
    // friend bool greater_by_change(const elem &argv1, const elem &argv2);
    std::map<int, elem *> storage;
    int size;
    int idx;
    std::stack<int> indices;
    int get_idx();
public:
    DB() : size(0), idx(1)
    {
    }
    ~DB();
    DB(const DB &) = delete;
    DB &operator=(const DB &) = delete;
    elem &get(int idx);
    void del(int idx);
    int add(elem*);
    void sort(sort_ways ways = sort_ways::by_name);
};

bool greater_by_name(const elem &argv1, const elem &argv2);
bool greater_by_create(const elem &argv1, const elem &argv2);
bool greater_by_change(const elem &argv1, const elem &argv2);