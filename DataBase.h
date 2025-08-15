#include <map>
#include <QTime>
#include <QString>
#include <stack>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>



struct elem
{
    QTime date_create;
    QTime date_change;
    QString name;
    QString contain;
    bool save;
    elem(){};
    elem(const QTime& d_crt, const QString& n, const QString& c):
    date_create(d_crt), date_change(date_create), name(n), contain(c), save(true)
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
    std::map<int, elem *> storage;
    int size;
    int idx;
    std::stack<int> indices;
    std::list<int> keys;
    int get_idx();
    
public:
    DB() : size(0), idx(1)
    {}
    ~DB();
    DB(const DB &) = delete;
    DB &operator=(const DB &) = delete;
    elem &get(int idx);
    void del(int idx);
    int add(elem*);
    void sort(sort_ways ways = sort_ways::by_name);
    // void save();
    // void load();
    std::list<int>& get_key();
    // void print()
    // {
    //     for (auto i = storage.begin(); i != storage.end(); ++i)
    //     {
    //         qDebug() << i->first << ' ' << i->second->name; 
    //     }
    // }


};

bool greater_by_name(const elem &argv1, const elem &argv2);
bool greater_by_create(const elem &argv1, const elem &argv2);
bool greater_by_change(const elem &argv1, const elem &argv2);