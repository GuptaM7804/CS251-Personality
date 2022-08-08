//  Manav Gupta: CS 251 Project 2

#include <math.h>
#include <limits>
#include <string>
#include <map>
#include <set>
#include "myrandom.h"

using namespace std;

constexpr double lowest_double = std::numeric_limits<double>::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
    string questionText;  // Text of the question
    map<char, int> factors;   // Map from factors to +1 or -1
    friend bool operator< (const Question& lhs, const Question& rhs) {
        return lhs.questionText < rhs.questionText;
    }
    friend bool operator== (const Question& lhs, const Question& rhs) {
        return lhs.questionText == rhs.questionText;
    }
    friend bool operator!= (const Question& lhs, const Question& rhs) {
        return lhs.questionText != rhs.questionText;
    }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
    string name;      // Name of the person
    map<char, int> scores;  // Map from factors to +1 or -1
    friend bool operator< (const Person& lhs,   const Person& rhs) {
        return lhs.name < rhs.name;
    }
    friend bool operator== (const Person& lhs, const Person& rhs) {
        return lhs.name == rhs.name;
    }
    friend bool operator!= (const Person& lhs, const Person& rhs) {
        return lhs.name != rhs.name;
    }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
*/
Question randomElement(set<Question>& questions) {
    int ind = randomInteger(0, (int)questions.size()-1);
    int i = 0;
    for (auto e : questions) {
        if (i == ind) {
            return e;
        }
        i++;
    }
    return {};
}

// returns a random question from a give set of Question
// deletes that question from that set
// if no question exists, throws an error
Question randomQuestionFrom(set<Question>& questions) {
    auto s = randomElement(questions);
    if (questions.count(s)) {
        questions.erase(s);
        return s;
    }
    throw runtime_error("question set: empty");
}


// returns a map of scores that has a character and int as its elements
// takes in a map of answers to read in data from
// the data is read to see which factor should be updated and by how much
map<char, int> scoresFrom(map<Question, int>& answers) {
    map<char, int> scores;
    for (auto e : answers) {
        for (auto s : e.first.factors) {
            char ch = s.first;
            if (scores.count(ch)) {
                scores[ch] = ((e.second - 3) * s.second) + scores.at(ch);
            } else {
                int score = ((e.second - 3) * s.second);
                scores.emplace(ch, score);
            }
        }
    }
    return scores;
}

// normalizes scores and returns a map to the normalized scores
// given a map of un-normalized scores
map<char, double> normalize(map<char, int>& scores) {
    map<char, double> normalizedScores;
    double length = 0.0;
    for (auto e : scores) {
        length = length + pow(e.second, 2);
    }
    if (length == 0) {
        throw runtime_error("length = 0");
    }
    length = sqrt(length);
    for (auto e : scores) {
        char ch = e.first;
        double normalscore = e.second/length;
        normalizedScores.emplace(ch, normalscore);
    }
    return normalizedScores;
}

// returns a double based on a formula given for this assignment
// takes in two maps and analyses their values to find the
// similarity between them
double cosineSimilarityOf(const map<char, double>& lhs,
                          const map<char, double>& rhs) {
    double similarity = 0.0;
    char ch;
    for (auto e : lhs) {
        // for (auto f : rhs) {
        //     ch = f.first;
        //     if (ch >= 'a' && ch <= 'z') {
        //         ch = f.first - 32;
        //     }
        //     if (e.first == ch) {
        //         similarity = similarity + (e.second * f.second);
        //     }
        // }
        if(rhs.count(e.first)) {
            similarity = similarity + (e.second * rhs.at(e.first));
        }
    }
    return similarity;
}

// returns a person variable depending on which person
// is most similar to the user's scores
// takes in a map of scores and a set of Person as arguements
Person mostSimilarTo(map<char, int>& scores, set<Person>& people) {
    if (scores.size() == 0) {
        throw runtime_error("scores: empty");
    }
    if (people.size() == 0) {
        throw runtime_error("people set: empty");
    }
    for (auto e : people) {
        if (e.scores.size() == 0) {
            throw runtime_error("people scores: empty");
        }
    }
    map<char, double> user = normalize(scores);
    int i = 0;
    double mostSimilar = 0.0;
    map<int, double> findMax;
    for (auto e : people) {
        map<char, double> match = normalize(e.scores);
        mostSimilar = cosineSimilarityOf(user, match);
        findMax.emplace(i, mostSimilar);
        i++;
    }
    i = 0;
    mostSimilar = findMax.at(0);
    for (auto e : findMax) {
        if ((e.second - mostSimilar) > 0.0) {
            mostSimilar = e.second;
            i = e.first;
        }
    }
    int itr = 0;
    Person mostSimilarPerson;
    for (auto e : people) {
        if (i == itr) {
            mostSimilarPerson = e;
        }
        itr++;
    }
    return mostSimilarPerson;
}
