#include "DataBase.h"

int DB::get_idx()
{
    if (indices.empty())
        return idx++;
    int result = indices.top();
    indices.pop();
    return result;
}

DB::elem &DB::get(int idx)
{
    if (storage.count(idx))
        return *storage[idx];
    throw "Unknow index"; // поменять на нормальный класс исключений
}

void DB::del(int idx)
{
    bool result = storage.erase(idx);
    if (result)
        indices.push(idx);
}

void DB::add(const elem &value)
{
    int new_idx = get_idx();
    storage[new_idx] = new elem(value);
    ++size;
}

void DB::sort(sort_ways ways)
{
    std::vector<elem *> copy;
    copy.reserve(size);
    for (const auto &kv : storage)
        copy.push_back(kv.second);

    bool (*compainer)(const elem &, const elem &);
    switch (ways)
    {
    case (sort_ways::by_name):
        compainer = greater_by_name;
        break;
    case (sort_ways::by_create):
        compainer = greater_by_create;
        break;
    case (sort_ways::by_change):
        compainer = greater_by_change;
        break;
    default:
        break;
    }
    for (int i = copy.size() - 1; i >= 0; --i)
    {
        deep(copy, i, copy.size(), compainer);
    }
    for (int i = copy.size() - 1; i >= 0; --i)
    {
        deep(copy, 0, i, compainer);
    }
}

void DB::deep(std::vector<elem *> mass, int idx, int end, bool (*cmp)(const elem &, const elem &))
{
    while (idx * 2 + 1 < end || idx * 2 + 2 < end)
    {
        int max_idx = idx;
        if (idx * 2 + 1 < end) // есть правый потомок
        {
            if (cmp(*mass[idx * 2 + 1], *mass[max_idx]))
            {
                max_idx = idx * 2 + 1;
            }
        }
        if (idx * 2 + 2 < end) // есть левый потомок
        {
            if (cmp(*mass[idx * 2 + 2], *mass[max_idx]))
            {
                max_idx = idx * 2 + 2;
            }
        }
        if (max_idx != idx)
        {
            std::swap(mass[idx], mass[max_idx]);
            idx = max_idx;
        }
        else
            break;
    }
}

bool greater_by_name(const DB::elem &argv1, const DB::elem &argv2)
{
    return argv1.name > argv2.name;
}

bool greater_by_create(const DB::elem &argv1, const DB::elem &argv2)
{
    return argv1.date_create > argv2.date_create;
}

bool greater_by_change(const DB::elem &argv1, const DB::elem &argv2)
{
    return argv1.date_change > argv2.date_change;
}