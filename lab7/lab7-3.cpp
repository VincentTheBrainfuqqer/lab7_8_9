#include <iostream>
#include "header.h"

int main() {
    Groups g;

    Student s1;
    s1.Name = "Alice";
    s1.Year = 1;
    s1.RecordBook["Math"] = Score::Excellent;
    s1.RecordBook["CS"]   = Score::Good;

    Student s2;
    s2.Name = "Bob";
    s2.Year = 2;
    s2.RecordBook["Math"] = Score::Satisfactorily;
    s2.RecordBook["CS"]   = Score::Good;

    g["IU7-11"] = {s1, s2};

    const std::string filename = "groups.txt";

    saveToFile_student(filename, g);

    Groups loaded;
    loadFromFile_student(filename, loaded);

    for (const auto& [groupName, students] : loaded) {
        std::cout << "Group: " << groupName << "\n";
        for (const auto& st : students) {
            std::cout << "  " << st.Name << " (" << st.Year << " year)\n";
            for (const auto& [subj, sc] : st.RecordBook) {
                std::cout << "    " << subj << " -> " << static_cast<int>(sc) << "\n";
            }
        }
    }

    return 0;
}
