#include "header.h"
#include <iostream>

int main()
{
    std::vector<Student> students =
    {
        { "Ivanov",  "A1", {5,4,3}, {"Math","Physics","CS"} },
        { "Petrov",  "A1", {2,3,4}, {"Math","History","CS"} },
        { "Sidorov", "B2", {5,5,5}, {"Math","Physics","CS"} },
        { "Alexeev", "B2", {3,2,5}, {"Math","Physics","CS"} }
    };

    std::cout << "Sort by name:\n";
    SortByName(students);
    for (const auto& s : students)
        std::cout << s.Name << " (" << s.GroupId << ")\n";

    std::cout << "\nSort by rating:\n";
    SortByRating(students);
    for (const auto& s : students)
        std::cout << s.Name << '\n';

    std::cout << "\nCount with bad marks: "
              << CountTwoness(students) << '\n';

    std::cout << "Count all 5: "
              << CountExcellent(students) << '\n';

    auto mathExcellent = VectorMathExcellent(students);
    std::cout << "\nMath excellent:\n";
    for (const auto& s : mathExcellent)
        std::cout << s.Name << '\n';

    auto ids = GroupsId(students);
    std::cout << "\nGroups ids:\n";
    for (const auto& id : ids)
        std::cout << id << '\n';

    auto groups = Groups(students);
    std::cout << "\nGroups list:\n";
    for (const auto& g : groups)
    {
        std::cout << "Group " << g.Id << ": ";
        for (const auto& st : g.Students)
            std::cout << st.Name << ' ';
        std::cout << '\n';
    }

    return 0;
}
