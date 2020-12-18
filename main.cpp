#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "dragon.cpp"

using namespace std;

bool getInput(vector<char>*, vector<char>*);
vector< vector<string> > getDeltaSplit();
vector< vector<string> > getDeltaTwosComp();
vector< vector<string> > getDeltaAddFour();
void splitStrings(vector<char>, vector<char>*, vector<char>*);
vector<char> twosCompliment(vector<char>);
vector<char> addFour(vector<char>, vector<char>, vector<char>, vector<char>);


int main() {

    vector<char> x, y, a, b, c, d;

    while (getInput(&x, &y)) {


        splitStrings(x, &a, &b);
        b = twosCompliment(b);

        splitStrings(y, &c, &d);
        d = twosCompliment(d);

        vector<char> sum = addFour(a, b, c, d);
        vector<int> sum2;
        vector<int> intSum;
        string ss;


        for (auto i : sum) {
            ss.push_back(i);
            sum2.push_back(int(i) - '0');
        }

        int binInt = stoi(ss, nullptr, 2);

        intSum = getDragon(binInt);


        cout << "\nSum in decimal:\t";
        printList(sum2);

        cout << "\nSum in dragon:\t";
        printList(intSum);

        cout << "\n\n\n";

        x.clear(), y.clear(), a.clear(), b.clear(), c.clear(), d.clear();
    }
    return 0;
}

bool getInput(vector<char>* S1, vector<char>* S2) {

    // Read from stdin
    string temp;
    cout << "Enter a binary string (exit to quit): ";
    cin >> temp;

    if (temp == "exit")
        return false;

    for (int i = 0; i < temp.size(); ++i) {
        S1->push_back(temp[i]);
    }

    temp.clear();
    cout << "\nEnter another binary string: ";
    cin >> temp;

    if (temp == "exit")
        return false;

    for (int i = 0; i < temp.size(); ++i) {
        S2->push_back(temp[i]);
    }
    cout << endl;

    while(S1->size() < S2->size())
        S1->insert(S1->begin(), '0');

    while(S2->size() < S1->size())
        S2->insert(S2->begin(), '0');

    return true;
}

vector< vector<string> > getDeltaSplit() {
    vector< vector<string> > delta = {

            //Input
            {"0","1"},      //Input Values
            {"000","110"},  //q0
            {"200","201"},  //q1
            {"100","110"},  //q2
    };
    return delta;
}

vector< vector<string> > getDeltaTwosComp() {
    vector< vector<string> > delta = {

            //Input
            {"0","1"},    //Input Values
            {"20","11"},  //q0
            {"11","10"},  //q1
            {"20","11"},  //q2
    };
    return delta;
}

vector< vector<string> > getDeltaAddFour() {
    vector< vector<string> > delta = {

            //Input
            {"0000","0001","0011","0111", "1111"}, //Input Values
            {"00","01","10","11", "20"}, //q0
            {"01","10","11","20", "21"}, //q1
            {"10","11","20","21", "30"}, //q2
            {"11","20","21","30", "31"}, //q3
    };
    return delta;
}

void splitStrings(vector<char> x, vector<char>* a, vector<char>* b) {
    vector< vector<string> > D = getDeltaSplit();

    int charSize = 0;

    charSize = int(x.size());

    int state = 1;
    for (int i = 0; i < charSize; ++i) {

        char xVal;
        xVal = x.at(i);

        string input;
        input += xVal;
        int temp = 0;

        for (int j = 0; j < D.at(state).size(); ++j) {

            if (D.at(0).at(j) == input) {
                temp = j;
                int nextState = 0;
                char valueToPushA, valueToPushB;

                nextState = D.at(state).at(temp)[0] - '0';
                valueToPushA = D.at(state).at(temp)[1];
                valueToPushB = D.at(state).at(temp)[2];

                a->push_back(valueToPushA); // Get second char from delta
                b->push_back(valueToPushB); // Get third char from delta
                state = nextState + 1;
            }
        }
    }
}

vector<char> twosCompliment(vector<char> x) {
    vector< vector<string> > D = getDeltaTwosComp();
    vector<char> result;

    int charSize = 0;

    charSize = int(x.size());

    int state = 1;
    for (int i = charSize - 1; i >= 0; --i) {

        char xVal;
        xVal = x.at(i);

        string input;
        input += xVal;
        int temp = 0;

        for (int j = 0; j < D.at(state).size(); ++j) {

            if (D.at(0).at(j) == input) {
                temp = j;
                int nextState = 0;
                char valueToPush;

                nextState = D.at(state).at(temp)[0] - '0';
                valueToPush = D.at(state).at(temp)[1];

                result.push_back(valueToPush); // Get second char from delta
                state = nextState + 1;
            }
        }
    }

//    if (state == 3) { // Ignore carry
//        result.push_back('1');
//    }

    reverse(result.begin(), result.end());

    return result;
}

vector<char> addFour(vector<char> w, vector<char> x, vector<char> y, vector<char> z) {
    vector< vector<string> > D = getDeltaAddFour();
    vector<char> result;

    int charSize = int(x.size());


    int state = 1;
    for (int i = charSize - 1; i >= 0; --i) {

        char wVal, xVal, yVal, zVal;
        wVal = w.at(i);
        xVal = x.at(i);
        yVal = y.at(i);
        zVal = z.at(i);

        string input;
        input += wVal;
        input += xVal;
        input += yVal;
        input += zVal;

        sort(input.begin(), input.end());

        int temp = 0;

        for (int j = 0; j < D.at(state).size(); ++j) {

            if (D.at(0).at(j) == input) {
                temp = j;
                int nextState = 0;
                char valueToPush;

                nextState = D.at(state).at(temp)[0] - '0';
                valueToPush = D.at(state).at(temp)[1];

                result.push_back(valueToPush); // Get second char from delta
                state = nextState + 1;
            }

        }

    }

    reverse(result.begin(), result.end());
    while (*result.begin() == '0')
        result.erase(result.begin());
    return result;
}
