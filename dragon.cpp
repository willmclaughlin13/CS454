//
// Created by Will on 12/10/2018.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void convertToBinary(int original, vector<int> *A) {
    A->clear();
    for (int i = 0; original > 0; ++i)
    {
        A->push_back(original % 2);
        original = original / 2;
    }
    reverse(A->begin(), A->end());
}

bool checkIfPower(const vector<int> A) {

    int count = 0;
    for (auto i : A) {
        if (i == 1)
            count++;
    }

    if (count == 1)
        return true;
    else
        return false;

}

void printList(vector<int> list) {
    vector<int> list2;
    int size = list.size()%4;
    int j = 0;

    for ( j; j < 4 - size; ++j) {
        list2.push_back(0);
    }

    for (auto i : list) {
        list2.push_back(i);
    }

    int count = 0;
    for(auto i : list2) {
        if (count % 4 == 0 && count != 0)
            cout << ' ';
        cout << i;
        count++;
    }

}

vector<int> getDragon(int original)
{

    vector<int> A;

    if (original == 0) {
        cout << "\n\n\nDRAGON: ";
        printList(A);
        return A;

    }

    convertToBinary(original, &A);

    int n = A.size() - 1;
    int a = int(pow(2, n + 1));


    convertToBinary(a, &A);

    int b = a - original;

    convertToBinary(b, &A);

    int dragon = 0;

    bool done = false;

    dragon = a;

    if (checkIfPower(A)) {

        dragon += b;

        convertToBinary(dragon, &A);
        return A;

    } else {
        while (!done) {

            dragon += int(pow(2, n));


            int difference = original - ((int(pow(2, n + 1)) - int(pow(2, n))));

            convertToBinary(difference, &A);

            if (checkIfPower(A)) {
                int valToAdd = n;

                dragon += valToAdd;

                convertToBinary(dragon, &A);
                done = true;
            } else {

                n = A.size() - 1;
                original = difference;

                int valToAdd = pow(2, n+1);
                dragon += valToAdd;
            }
        }
    }

}