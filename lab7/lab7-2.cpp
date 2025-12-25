#include <iostream>
#include <vector>
#include <string>

#include "header.h"

int main() {
    std::vector<Book> books = {
        {"Strugatsky Brothers", "Roadside Picnic", 1972},
        {"J. R. R. Tolkien", "The Hobbit", 1937},
        {"Fyodor Dostoevsky", "Crime and Punishment", 1866}
    };

    const std::string filename = "books.txt";

    saveToFile_book(filename, books);

    std::vector<Book> loaded;
    loadFromFile_book(filename, loaded);

    std::cout << "Loaded " << loaded.size() << " books:\n\n";
    for (const auto& b : loaded) {
        std::cout << "Author: " << b.Author << '\n';
        std::cout << "Title : " << b.Title  << '\n';
        std::cout << "Year  : " << b.Year   << "\n\n";
    }

    return 0;
}
