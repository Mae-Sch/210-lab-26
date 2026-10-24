// Mae Schweller
// CompSci 210 data structures
// lab 26
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int NUM_CODES = 20000;
const int NUM_TESTS = 15;
const string INSERT_STRING = "TESTCODE";

int main() {
    srand(time(0));

    cout << "All times are measured in nanoseconds\n\n";
    cout << setw(15) << " "<< setw(15) << "Vector" << setw(15) << "List" << setw(15) << "Set" << endl;
    cout << "Number of tests run: " << NUM_TESTS << endl;

    // First layer denotes test, second is for data types, third is for instance of test
    // ie. testResults[0][1][2] would mean reading -> list -> test instance #2
    int testResults[3][3][NUM_TESTS];

    for (int testNumber = 0; testNumber < NUM_TESTS; ++testNumber) {
        /// *** Reading Tests *** ///

        // cout << setw(15) << "Reading:";

        // testing reading for vector;
        auto VectReadStart = high_resolution_clock::now();
        vector<string> testVector;
        ifstream inFileVect("codes.txt");
        for (int i = 0; i < NUM_CODES; ++i) {
            string tempCode;
            getline(inFileVect, tempCode);
            testVector.push_back(tempCode);
        }
        inFileVect.close();
        auto VectReadEnd = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(VectReadEnd - VectReadStart);
        // cout << setw(15) << duration.count();
        testResults[0][0][testNumber] = duration;

        // testing reading for list
        auto ListReadStart = high_resolution_clock::now();
        list<string> testList;
        ifstream inFileList("codes.txt");
        for (int i = 0; i < NUM_CODES; ++i) {
            string tempCode;
            getline(inFileList, tempCode);
            testList.push_front(tempCode);
        }
        inFileList.close();
        auto ListReadEnd = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(ListReadEnd - ListReadStart);
        // cout << setw(15) << duration.count();
        testResults[0][1][testNumber] = duration;

        // testing reading for set
        auto SetReadStart = high_resolution_clock::now();
        set<string> testSet;
        ifstream inFileSet("codes.txt");
        for (int i = 0; i < NUM_CODES; ++i) {
            string tempCode;
            getline(inFileSet, tempCode);
            testSet.insert(tempCode);
        }
        inFileSet.close();
        auto SetReadEnd = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(SetReadEnd - SetReadStart);
        // cout << setw(15) << duration.count() << endl;
        testResults[0][2][testNumber] = duration;

        /// *** Sorting Tests *** ///

        // cout << setw(15) << "Sorting:";

        // testing sorting for vectors
        auto start = high_resolution_clock::now();
        sort(testVector.begin(), testVector.end());
        auto end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count();
        testResults[1][0][testNumber] = duration;

        // testing sorting for list
        start = high_resolution_clock::now();
        testList.sort();
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count();
        testResults[1][1][testNumber] = duration

        // sets are unsorted to we display -1 for the time
        // cout << setw(15) << -1 << endl;
        testResults[1][2][testNumber] = -1;

        /// *** Inserting Tests *** ///

        // cout << setw(15) << "Inserting:";

        // testing inserting for vector
        start = high_resolution_clock::now();
        testVector.insert(testVector.begin() + (NUM_CODES / 2), INSERT_STRING);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count();

        // testing inserting for list
        start = high_resolution_clock::now();
        list<string>::iterator it = testList.begin();
        advance(it, NUM_CODES / 2);
        testList.insert(it, INSERT_STRING);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count();

        // testing insert for set
        start = high_resolution_clock::now();
        testSet.insert(INSERT_STRING);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count() << endl;

        /// *** Testing Deleting *** ///
        // cout << setw(15) << "Deleting:";

        // testing deleting for vector
        start = high_resolution_clock::now();
        testVector.erase(testVector.begin() + (NUM_CODES / 2));
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count();

        // testing deleting for list
        start = high_resolution_clock::now();
        it = testList.begin();
        advance(it, NUM_CODES / 2);
        testList.erase(it);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count();

        // picking a "middle ish" element to delte to ensure proper testing;
        // adding 3 to make sure it isn't the lement we just inserted
        string toDelete = testVector.at(NUM_CODES / 2 + 3); 

        // testing deleting for set
        start = high_resolution_clock::now();
        testSet.erase(toDelete);
        end = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(end - start);
        // cout << setw(15) << duration.count() << endl;
    }

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/