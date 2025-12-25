#ifndef LAB7_8_9_HEADER_H
#define LAB7_8_9_HEADER_H

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_set>

struct Student
{
    std::string Name;
    std::string GroupId;
    std::vector<unsigned> Ratings;
    std::vector<std::string> Subjects;
};

struct Group
{
    std::string Id;
    std::vector<Student> Students;
};

void SortByName(std::vector<Student>& students)
{
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b)
              {
                  return a.Name < b.Name;
              });
}

void SortByRating(std::vector<Student>& students)
{
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b)
              {
                  double avgA = 0.0;
                  double avgB = 0.0;

                  if (!a.Ratings.empty())
                      avgA = std::accumulate(a.Ratings.begin(), a.Ratings.end(), 0.0) /
                             static_cast<double>(a.Ratings.size());

                  if (!b.Ratings.empty())
                      avgB = std::accumulate(b.Ratings.begin(), b.Ratings.end(), 0.0) /
                             static_cast<double>(b.Ratings.size());

                  if (avgA == avgB)
                      return a.Name < b.Name;
                  return avgA > avgB;
              });
}

std::size_t CountTwoness(const std::vector<Student>& students)
{
    return std::count_if(students.begin(), students.end(),
                         [](const Student& s)
                         {
                             return std::any_of(s.Ratings.begin(), s.Ratings.end(),
                                                [](unsigned r) { return r <= 2; });
                         });
}

std::size_t CountExcellent(const std::vector<Student>& students)
{
    return std::count_if(students.begin(), students.end(),
                         [](const Student& s)
                         {
                             if (s.Ratings.empty())
                                 return false;
                             return std::all_of(s.Ratings.begin(), s.Ratings.end(),
                                                [](unsigned r) { return r == 5; });
                         });
}

std::vector<Student> VectorMathExcellent(const std::vector<Student>& students)
{
    std::vector<Student> result;

    std::copy_if(students.begin(), students.end(), std::back_inserter(result),
                 [](const Student& s)
                 {
                     for (std::size_t i = 0; i < s.Subjects.size() && i < s.Ratings.size(); ++i)
                     {
                         if (s.Subjects[i] == "Math" && s.Ratings[i] == 5)
                             return true;
                     }
                     return false;
                 });

    return result;
}

std::vector<std::string> GroupsId(const std::vector<Student>& students)
{
    std::vector<std::string> ids;
    ids.reserve(students.size());

    for (const auto& s : students)
        ids.push_back(s.GroupId);

    std::sort(ids.begin(), ids.end());
    ids.erase(std::unique(ids.begin(), ids.end()), ids.end());

    return ids;
}

std::vector<Group> Groups(const std::vector<Student>& students)
{
    std::vector<Group> groups;
    auto ids = GroupsId(students);

    groups.reserve(ids.size());
    for (const auto& id : ids)
    {
        Group g;
        g.Id = id;

        std::copy_if(students.begin(), students.end(),
                     std::back_inserter(g.Students),
                     [&id](const Student& s) { return s.GroupId == id; });

        groups.push_back(std::move(g));
    }

    return groups;
}











#endif //LAB7_8_9_HEADER_H