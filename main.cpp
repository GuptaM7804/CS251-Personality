// Manav Gupta: CS 2511 Project 2

#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "driver.h"

using namespace std;

// function skeletons
void loadQuestionsFile(ifstream &inFile, set<Question> &unaskedQuestions);
void inputQuestionSet(set<Question> &unaskedQuestions);
string getQuestion(string &line);
void getFactors(string &line, Question &newQuestion);
void loadPersonsFile(ifstream &inFile, set<Person> &people);
void inputPersonSet(string filename, set<Person> &people);
string getPersonName(string &line);
void getPersonScores(string &line, Person &newPerson);
void askQuestion(set<Question> &unaskedQuestions, map<Question, int> &answers);
void statements(Question q);

// Checks if given file opens
// inputs contents from file into a set of questions
// through the use of helper function
void inputQuestionSet(set<Question> &unaskedQuestions) {
    string filename = "questions.txt";
    ifstream inFile;
    inFile.open(filename);
    if (!inFile.fail()) {
        loadQuestionsFile(inFile, unaskedQuestions);
    } else {
        cout << "Error unable to open '" << filename << "'" << endl;
    }
}

// loads data from file into set of Question
void loadQuestionsFile(ifstream &inFile, set<Question> &unaskedQuestions) {
    string line;
    while (!inFile.eof()) {
        getline(inFile, line, '\n');
        if (!line.empty()) {
          Question newQuestion;
          newQuestion.questionText = getQuestion(line);
          while (!line.empty()) {
              getFactors(line, newQuestion);
          }
          unaskedQuestions.insert(newQuestion);
        }
    }
}

// given a string: gets the question from the string
// updates the string so that the question
// and the following whitespace isn't there anymore
string getQuestion(string &line) {
    size_t pos = line.find(".");
    string elQuestion = line.substr(0, pos + 1);
    line = line.substr(pos + 2, line.size() - elQuestion.size() - 1);
    return elQuestion;
}

// given a string: gets the factors and the value they change by
// updates the string to remove the factor, it's changing value
// and/or the following whitespace
void getFactors(string &line, Question &newQuestion) {
    size_t pos = line.find(" ");
    if (line.find(" ") != string::npos) {
        char factorChar = line[0];
        string sub = line.substr(2, pos - 1);
        line = line.substr(pos + 1, line.size() - 1);
        int factorNum = stoi(sub);
        newQuestion.factors.emplace(factorChar, factorNum);
    } else {
      char factorChar = line[0];
      string sub = line.substr(2, line.size());
      line.clear();
      int factorNum = stoi(sub);
      newQuestion.factors.emplace(factorChar, factorNum);
    }
}

// similar to inputQuestionSet...
// checks if file can be opened and
// through the help of a helper function
// inputs data from file to a set of Person
void inputPersonSet(string filename, set<Person> &people) {
    ifstream inFile;
    inFile.open(filename);
    if (!inFile.fail()) {
        loadPersonsFile(inFile, people);
    } else {
        cout << "Error unable to open '" << filename << "'" << endl;
    }
}

// similar to loadQuestionsFile
// inputs data from file into set of Person
void loadPersonsFile(ifstream &inFile, set<Person> &people) {
    string line;
    while (!inFile.eof()) {
        getline(inFile, line, '\n');
        if (!line.empty()) {
          Person newPerson;
          newPerson.name = getPersonName(line);
          while (!line.empty()) {
              getPersonScores(line, newPerson);
          }
          people.insert(newPerson);
        }
    }
}

// similar to getQuestion...
// given a string, returns the name from the string
// and updates string to remove the name
// and the following whitespace
string getPersonName(string &line) {
    size_t pos = line.find(".");
    string name = line.substr(0, pos);
    line = line.substr(pos + 2, line.size() - name.size() - 1);
    return name;
}

// similar to getFactors...
// given a string: gets the factors and the values
// updates the string to remove the factor, it's value
// and/or the following whitespace
void getPersonScores(string &line, Person &newPerson) {
    size_t pos = line.find(" ");
    if (line.find(" ") != string::npos) {
        char factorChar = line[0];
        string sub = line.substr(2, pos - 1);
        line = line.substr(pos + 1, line.size() - 1);
        int score = stoi(sub);
        if (score != 0) {
          newPerson.scores.emplace(factorChar, score);
        }
    } else {
      char factorChar = line[0];
      string sub = line.substr(2, line.size());
      line.clear();
      int score = stoi(sub);
      newPerson.scores.emplace(factorChar, score);
    }
}

// all cout lines in 1 function for the questions
void statements(Question q) {
    cout << "How much do you agree with this statement?" << endl;
    char a = '"';
    cout << a << q.questionText << a << endl;
    cout << endl;
    cout << "1. Strongly disagree" << endl;
    cout << "2. Disagree" << endl;
    cout << "3. Neutral" << endl;
    cout << "4. Agree" << endl;
    cout << "5. Strongly agree" << endl;
    cout << endl;
    cout << "Enter your answer here (1-5): " << endl;
}

// gets 1 question and outputs it
// user enters their answer
// places users answer in a map for answers
void askQuestion(set<Question> &unaskedQuestions, map<Question, int> &answers) {
    Question q = randomQuestionFrom(unaskedQuestions);
    statements(q);
    int answerUser;
    cin >> answerUser;
    answers.emplace(q, answerUser);
}

void statementsV2() {
    cout << "1. BabyAnimals" << endl;
    cout << "2. Brooklyn99" << endl;
    cout << "3. Disney" << endl;
    cout << "4. Hogwarts" << endl;
    cout << "5. MyersBriggs" << endl;
    cout << "6. SesameStreet" << endl;
    cout << "7. StarWars" << endl;
    cout << "8. Vegetables" << endl;
    cout << "9. mine" << endl;
    cout << "0. To end program." << endl;
    cout << endl;
    cout << "Choose test number (1-9, or 0 to end): ";
}

string findName(int i) {
    if (i == 1) {
        return "BabyAnimals.people";
    } else if (i == 2) {
        return "Brooklyn99.people";
    } else if (i == 3) {
        return "Disney.people";
    } else if (i == 4) {
        return "Hogwarts.people";
    } else if (i == 5) {
        return "MyersBriggs.people";
    } else if (i == 6) {
        return "SesameStreet.people";
    } else if (i == 7) {
        return "StarWars.people";
    } else if (i == 8) {
        return "Vegetables.people";
    } else if (i == 9) {
        return "mine.people";
    }
    return "";
}

// main function
int main() {
    // sets and maps necessary for the personality test
    set<Question> unaskedQuestions;
    set<Person> people;
    map<Question, int> answers;

    // gets questions from questions.txt and
    // stores it in set of unaskedQuestions
    inputQuestionSet(unaskedQuestions);

    // number of questions user wants
    int numQuestions;
    cout << "Welcome to the Personality Quiz!" << endl;
    cout << endl;
    cout << "Choose number of questions: ";
    cin >> numQuestions;
    cout << endl;

    int i = 0;
    // loopa until user entered number of questions have been asked
    while (i < numQuestions) {
        askQuestion(unaskedQuestions, answers);
        i++;
    }
    map<char, int> scores = scoresFrom(answers);
    statementsV2();
    cin >> i;
    while (i != 0) {
        string filename = findName(i);
        inputPersonSet(filename, people);
        Person matched = mostSimilarTo(scores, people);
        cout << "You got " << matched.name << "!" << endl;
        cout << endl;
        people.clear();
        statementsV2();
        cin >> i;
    }
    cout << "Goodbye!" << endl;
    return 0;
}
