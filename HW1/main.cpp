#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

bool isSign(char c, bool isDotIncluded){
    if (c == ',' || c == ';' || c == ')' || c == ':' || c == '('
        || c == '!' || c == '"' || c == '/') {
        return true;
    }
    return c == '.' && isDotIncluded;
}

string findWord(const string &line, int &index) {
    string word;
    while (index < line.size() && line[index] == ' ') {
        index++;
    }
    while (index < line.size() && line[index] != ' ') {
        if(!isSign(line[index], false)) {
            word += line[index];
        }
        index++;
    }
    return word;
}

void processLine(const string &line, map<string, vector<int>> &words, vector<int> &bounds) {
    int index = 0;
    bounds.push_back(0);
    while (index < line.size()) {
        string word = findWord(line, index);
        if(word.back() == '.') {
            word.pop_back();
            bounds.push_back(index);
        }

        if (!words.count(word) ) {
            vector<int> vec = vector<int>();
            vec.push_back(bounds.size() - 1);
            words[word] = vec;
        } else if (words[word].back() != bounds.size() - 1) {
            vector<int> vec = words[word];
            vec.push_back(bounds.size() - 1);
            words[word] = vec;
        }
    }
}

bool equals(const string &line, int index, const string &word) {
    int startIndex = index;
    while(index < line.size() && line[index] != ' ' && !isSign(line[index],true)){
        if(line[index] != word[index - startIndex]) {
            return false;
        }
        index++;
    }
    return true;
}

void findSentence(const string &line, map<string, vector<int>> &words, vector<int> &bounds) {
    string word;
    cin >> word;
    cout << words[word].size() << endl;
    for (int sent : words[word]) {
        //skip spaces at the beginning
        int ind = bounds[sent];
        while (line[ind] == ' ') {
            ind++;
        }
        while (ind < bounds[sent + 1]){
            while (ind < line.size() && line[ind] == ' ' || isSign(line[ind], false)) {
                cout << line[ind];
                ind++;
            }
            if (equals(line, ind, word)) {
                while(ind < line.size() && line[ind] != ' '){
                    char c = line[ind];
                    putchar(toupper(c));
                    ind++;
                }
            } else {
                while(ind < line.size() && line[ind] != ' '){
                    cout << line[ind];
                    ind++;
                }
            }
        }
        cout << "\n";
    }
}


int main() {
    freopen("in.txt","r", stdin);
    freopen("out.txt","w", stdout);
    vector<int> bounds;
    map<string, vector<int>> words;
    string line;

    getline(cin, line);
    processLine(line, words, bounds);

    int N;
    fflush(stdin);
    cin >> N;
    for (int i = 0; i < N; i++) {
        findSentence(line, words, bounds);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}