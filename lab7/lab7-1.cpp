#include <iostream>
#include <vector>
#include <string>

#include "header.h"

int main() {
    std::vector<std::string> words = {
        "first","second","third","fourth"
    };

    const std::string filename = "words.txt";

    saveToFile(filename, words);

    std::vector<std::string> loaded;
    loadFromFile(filename, loaded);

    std::cout << "Loaded " << loaded.size() << " words:\n";
    for (const auto& w : loaded) {
        std::cout << w << '\n';
    }

    return 0;
}
