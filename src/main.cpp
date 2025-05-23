#include "../include/global.h"
#include <map>
#include <cctype>
using std::map;

int main() {
    ifstream input("tekstas.txt");
    if (!input.is_open()) {
        std::cerr << "Nepavyko atidaryti failo!" << endl;
        return 1;
    }
    ofstream output("rezultatai.txt");

    map<string, int> wordCount;
    string line;
    while (getline(input, line)) {
        std::istringstream iss(line);
        string word;
        while (iss >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return std::ispunct(c); }), word.end());
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
