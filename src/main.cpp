#include "../include/global.h"
#include <map>
#include <set>
#include <cctype>
#include <regex>

bool has_forbidden_inside(const string& word, const std::set<char>& forbidden) {
    if (word.size() <= 2) {
        return false;
    }
    for (size_t i = 1; i + 1 < word.size(); ++i) {
        if (forbidden.count(word[i]) > 0) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream input("tekstas.txt");
    if (!input.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << endl;
        return 1;
    }
    ofstream output("rezultatai.txt");

    std::set<char> forbidden_inside_chars = {'.', '/', '\\', '|', ':', '*', '+', '=', '@'};
    std::regex front_unwanted(R"(^[\"'„“°.,:;!?()\[\]{}<>]+)");
    std::regex back_unwanted(R"([\"'„“°.,:;!?()\[\]{}<>]+$)");

    std::map<string, int> wordCount;
    std::map<string, std::set<int>> wordLines;

    string line;
    int lineNumber = 1;
    while (getline(input, line)) {
        std::istringstream iss(line);
        string word;
        while (iss >> word) {
            word = std::regex_replace(word, front_unwanted, "");
            word = std::regex_replace(word, back_unwanted, "");
            if (has_forbidden_inside(word, forbidden_inside_chars))
                    continue;
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (!word.empty() && word.length() > 1 && std::any_of(word.begin(), word.end(), ::isalpha))
                wordCount[word]++;
                wordLines[word].insert(lineNumber);
        }
        ++lineNumber;
    }

    for (const auto& pair : wordCount) {
        if (pair.second > 1) {
            output << left << setw(20) << pair.first;
            output << " | " << setw(2) << pair.second << " | (";
            auto it = wordLines[pair.first].begin();
            while (it != wordLines[pair.first].end()) {
                output << *it;
                ++it;
                if (it != wordLines[pair.first].end()) {
                    output << ", ";
                }
            }
        output << ")" << endl;
    }
}

    cout << "Skaiciavimas baigtas. Rezultatai issaugoti faile rezultatai.txt" << endl;
    input.close();
    output.close();
    return 0;
}
