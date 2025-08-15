#include "DataBase.h"

DB::~DB()
{
    for (const auto &kv : storage)
    {
        delete storage[kv.first];
        storage.erase(kv.first);
    }
}

int DB::get_idx()
{
    if (indices.empty())
        return idx++;
    int result = indices.top();
    indices.pop();
    return result;
}

elem &DB::get(int idx)
{
    if (storage.count(idx))
        return *storage[idx];
    throw "Unknow index"; // поменять на нормальный класс исключений
}

void DB::del(int idx)
{
    if (storage.count(idx))
        indices.push(idx);
    delete storage[idx];
    storage.erase(idx);
    --size;
}

int DB::add(elem *value)
{
    int new_idx = get_idx();
    storage[new_idx] = value;
    ++size;
    keys.push_back(new_idx);
    return new_idx;
}

void DB::sort(sort_ways ways)
{
    std::vector<elem *> copy;
    std::vector<int> keys;
    copy.reserve(size);
    keys.reserve(size);
    for (const auto &kv : storage)
    {
        keys.push_back(kv.first);
        copy.push_back(kv.second);
    }
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
    for (int j = 0; j < copy.size(); ++j)
    {
        storage[keys[j]] = copy[j];
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

bool greater_by_name(const elem &argv1, const elem &argv2)
{
    return argv1.name > argv2.name;
}

bool greater_by_create(const elem &argv1, const elem &argv2)
{
    return argv1.date_create > argv2.date_create;
}

bool greater_by_change(const elem &argv1, const elem &argv2)
{
    return argv1.date_change > argv2.date_change;
}

std::list<int> &DB::get_key()
{
    return keys;
}


// void DB::save()
// {
//     std::ofstream output_file("data", std::ios_base::binary);
//     std::ofstream keys("keys", std::ios_base::binary);
//     keys.write((char*)&size, sizeof(int));
//     for (auto i = storage.begin(); i != storage.end(); ++i)
//     {
//         keys.write((char*)&(i->first), sizeof(int));
//         output_file.write((char*)i->second, sizeof(elem));
//     }
//     output_file.close();
//     keys.close();
// }

// void DB::load()
// {
//     std::ifstream input_file("data", std::ios_base::binary);
//     std::ifstream keys("keys", std::ios_base::binary);
//     keys.read((char*)&size, sizeof(int));
//     int new_key;
//     for (int i = 0; i < size; ++i)
//     {
//         keys.read((char*)&new_key, sizeof(int));
//         storage[new_key] = new elem;
//         input_file.read((char*)storage[new_key], sizeof(elem));
//     }
//     input_file.close();
//     keys.close();

// }

