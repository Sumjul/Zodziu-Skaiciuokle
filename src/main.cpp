#include "../include/global.h"
#include "../include/links.h"
#include <unordered_set>
#include <map>
#include <set>
#include <cctype>
#include <regex>

int main()
{
    // Failu atidarymas ir tikrinimas
    ifstream input("tekstas.txt");
    if (!input.is_open())
    {
        std::cerr << "Nepavyko atidaryti failo!" << endl;
        return 1;
    }
    ofstream wordsOutput("pasikartojimai.txt");
    ofstream linksOutput("nuorodos.txt");

    // Naudojami asociatyvus konteineriai ir regex
    std::unordered_set<string> foundLinks;
    std::map<string, int> wordCount;
    std::map<string, std::set<int>> wordLines;
    std::regex insideUnwanted(R"([\\/.|:*+=@!?#$%^&~`<>\",;\[\]])");
    std::regex front_unwanted(R"(^[\"'„“°.,:;!?()\[\]{}<>]+)");
    std::regex back_unwanted(R"([\"'„“°.,:;!?()\[\]{}<>]+$)");

    // Zodziu ir nuorodu paieska bei isvedimas
    string line;
    int lineNumber = 1;
    while (getline(input, line))
    {
        std::sregex_iterator begin(line.begin(), line.end(), linkSearch);
        std::sregex_iterator end;
        for (std::sregex_iterator i = begin; i != end; ++i)
        {
            std::string url = i->str();
            if (foundLinks.insert(url).second)
            {
                linksOutput << url << endl;
            }
        }
        std::istringstream iss(line);
        string word;
        while (iss >> word)
        {
            word = std::regex_replace(word, front_unwanted, "");
            word = std::regex_replace(word, back_unwanted, "");
            if (std::regex_search(word, insideUnwanted))
            {
                continue;
            }
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (!word.empty() && word.length() > 1 && std::any_of(word.begin(), word.end(), ::isalpha))
            {
                wordCount[word]++;
                wordLines[word].insert(lineNumber);
            }
        }
        ++lineNumber;
    }
    for (const auto &pair : wordCount)
    {
        if (pair.second > 1)
        {
            wordsOutput << pair.first;
            wordsOutput << " --- | " << pair.second << " | (";
            auto it = wordLines[pair.first].begin();
            while (it != wordLines[pair.first].end())
            {
                wordsOutput << *it;
                ++it;
                if (it != wordLines[pair.first].end())
                {
                    wordsOutput << ", ";
                }
            }
            wordsOutput << ")" << endl;
        }
    }

    // Programos pabaiga
    input.close();
    wordsOutput.close();
    linksOutput.close();
    cout << "-----------------------------------------------------------" << endl;
    cout << "Skaiciavimai baigti." << endl;
    cout << "Pasikartojantys zodziai issaugoti faile: pasikartojimai.txt" << endl;
    cout << "Nuorodos issaugotos faile: nuorodos.txt" << endl;
    cout << "-----------------------------------------------------------" << endl;
    system("pause");
    return 0;
}
