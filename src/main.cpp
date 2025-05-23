#include "../include/global.h"
#include <map>
#include <set>
#include <cctype>
#include <regex>

int main() {
    ifstream input("tekstas.txt");
    if (!input.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << endl;
        return 1;
    }
    ofstream output("rezultatai.txt");

    std::regex front_unwanted(R"(^[\"'„“°.,:;!?()\[\]{}<>]+)");
    std::regex back_unwanted(R"([\"'„“°.,:;!?()\[\]{}<>]+$)");

    std::map<string, int> wordCount;
    string line;
    while (getline(input, line)) {
        std::istringstream iss(line);
        string word;
        while (iss >> word) {
            word = std::regex_replace(word, front_unwanted, "");
            word = std::regex_replace(word, back_unwanted, "");
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (!word.empty() && word.length() > 1 && std::any_of(word.begin(), word.end(), ::isalpha))
                wordCount[word]++;
        }
    }

    for (const auto& pair : wordCount) {
        if (pair.second > 1)
            output << pair.first << " : " << pair.second << endl;
    }

    cout << "Skaiciavimas baigtas. Rezultatai issaugoti faile rezultatai.txt" << endl;
    input.close();
    output.close();
    return 0;
}
