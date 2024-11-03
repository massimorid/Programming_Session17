#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;

// Function to read the book and return alphabetic characters only
vector<char> readBook(const string &fileName) {
    vector<char> bookContent;
    ifstream file(fileName);
    char ch;

    while (file.get(ch)) {
        if (isalpha(ch)) {
            bookContent.push_back(tolower(ch));
        } else {
            bookContent.push_back(' ');
        }
    }
    return bookContent;
}

// Function to compute word frequency
map<string, int> computeWordFrequency(const vector<char> &bookContent) {
    map<string, int> wordFrequency;
    stringstream ss(string(bookContent.begin(), bookContent.end()));
    string word;

    while (ss >> word) {
        wordFrequency[word]++;
    }
    return wordFrequency;
}

// Function to count unique words
int countUniqueWords(const vector<char> &bookContent) {
    set<string> uniqueWords;
    stringstream ss(string(bookContent.begin(), bookContent.end()));
    string word;

    while (ss >> word) {
        uniqueWords.insert(word);
    }
    return uniqueWords.size();
}

// Function to sort frequencies in descending order
multimap<int, string, greater<>> sortFrequencies(const map<string, int> &frequencies) {
    multimap<int, string, greater<>> sortedFrequencies;
    for (const auto &pair : frequencies) {
        sortedFrequencies.insert({pair.second, pair.first});
    }
    return sortedFrequencies;
}

// Function to output sorted frequencies to a file for plotting
void outputFrequencies(const multimap<int, string, greater<>> &sortedFrequencies, const string &outputFile) {
    ofstream outFile(outputFile);
    int rank = 1;

    for (const auto &pair : sortedFrequencies) {
        outFile << rank << " " << pair.first << " " << pair.second << "\n";
        rank++;
    }
}

// Function to count words that appear only once (hapax legomenon)
int countHapaxLegomenon(const multimap<int, string, greater<>> &sortedFrequencies) {
    int count = 0;
    for (const auto &pair : sortedFrequencies) {
        if (pair.first == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    string fileName = "book.txt";  
    string outputFile = "word_frequencies.txt";

    // Step 1: Read the book
    vector<char> bookContent = readBook(fileName);

    // Step 2: Compute word frequency
    map<string, int> wordFrequency = computeWordFrequency(bookContent);

    // Step 3: Count unique words
    int uniqueWordCount = countUniqueWords(bookContent);
    cout << "Number of unique words: " << uniqueWordCount << endl;

    // Step 4: Sort frequencies
    multimap<int, string, greater<>> sortedFrequencies = sortFrequencies(wordFrequency);

    // Step 5: Output frequencies to file
    outputFrequencies(sortedFrequencies, outputFile);

    // Step 6: Count hapax legomenon
    int hapaxCount = countHapaxLegomenon(sortedFrequencies);
    cout << "Words that appear only once (num ofhapax legomena): " << hapaxCount << endl;

    return 0;
}
