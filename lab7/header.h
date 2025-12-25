#ifndef LAB7_8_9_HEADER_H
#define LAB7_8_9_HEADER_H
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>


//1 задание
void saveToFile(const std::string& filename,
                const std::vector<std::string>& data)
{
    std::ofstream out(filename);
    if (!out.is_open())
        return;

    for (const auto& word : data)
        out << word << '\n';
}

void loadFromFile(const std::string& filename,
                  std::vector<std::string>& outData)
{
    std::ifstream in(filename);
    if (!in.is_open())
        return;

    outData.clear();
    std::string word;
    while (std::getline(in, word))
        outData.push_back(word);
}


//2 задание
struct Book {
    std::string Author;
    std::string Title;
    int Year;
};

void saveToFile_book(const std::string& filename,
                const std::vector<Book>& data)
{
    std::ofstream out(filename);
    if (!out.is_open())
        return;

    for (const auto& b : data) {
        out << b.Author << '\n';
        out << b.Title  << '\n';
        out << b.Year   << '\n';
    }
}

void loadFromFile_book(const std::string& filename,
                  std::vector<Book>& outData)
{
    std::ifstream in(filename);
    if (!in.is_open())
        return;

    outData.clear();

    std::string author;
    std::string title;
    int year;

    while (true) {
        if (!std::getline(in, author))
            break;
        if (!std::getline(in, title))
            break;
        if (!(in >> year))
            break;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Book b{author, title, year};
        outData.push_back(b);
    }
}


//3 задание
enum class Score
{
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};

struct Student
{
    std::string Name;
    int Year;
    std::map<std::string, Score> RecordBook;
};

// ключ – название группы, значение – список студентов
using Groups = std::map<std::string, std::vector<Student>>;

static int scoreToInt(Score s) {
    return static_cast<int>(s);
}

static Score intToScore(int v) {
    return static_cast<Score>(v);
}

void saveToFile_student(const std::string& filename, const Groups& groups)
{
    std::ofstream out(filename);
    if (!out) return;

    out << groups.size() << '\n';
    for (const auto& [groupName, students] : groups) {
        out << groupName << '\n';
        out << students.size() << '\n';
        for (const auto& st : students) {
            out << st.Name << '\n';
            out << st.Year << '\n';
            out << st.RecordBook.size() << '\n';
            for (const auto& [subject, score] : st.RecordBook) {
                out << subject << '\n';
                out << scoreToInt(score) << '\n';
            }
        }
    }
}

void loadFromFile_student(const std::string& filename, Groups& outGroups)
{
    std::ifstream in(filename);
    if (!in) return;

    outGroups.clear();

    size_t groupCount = 0;
    if (!(in >> groupCount)) return;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (size_t g = 0; g < groupCount; ++g) {
        std::string groupName;
        if (!std::getline(in, groupName)) return;

        size_t studentCount = 0;
        if (!(in >> studentCount)) return;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::vector<Student> students;
        students.reserve(studentCount);

        for (size_t i = 0; i < studentCount; ++i) {
            Student st;

            if (!std::getline(in, st.Name)) return;
            if (!(in >> st.Year)) return;
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            size_t subjCount = 0;
            if (!(in >> subjCount)) return;
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            for (size_t j = 0; j < subjCount; ++j) {
                std::string subject;
                if (!std::getline(in, subject)) return;

                int scoreIntVal = 0;
                if (!(in >> scoreIntVal)) return;
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                st.RecordBook[subject] = intToScore(scoreIntVal);
            }

            students.push_back(std::move(st));
        }

        outGroups[groupName] = std::move(students);
    }
}






#endif //LAB7_8_9_HEADER_H