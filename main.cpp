/**********************************************************************************************************************/
// File: Main file
// Name: Darien Labbe
// Date: 10/05/2022
// Description: This file starts and initializes the two classes that create the social media. It also times this
//     process as well.
/**********************************************************************************************************************/
#include "UserProfiles.hpp"
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::steady_clock::now();

    UserProfiles makeSocialMedia;
    makeSocialMedia.userBuilderJSONParser();  //Grabbed from json and created the user htmls

    auto end = chrono::steady_clock::now();

    cout << "\nElapsed time in Minutes: " << chrono::duration_cast<chrono::minutes>(end - start).count();
    cout << " min" << endl;
    cout << "Elapsed time in Seconds: " << chrono::duration_cast<chrono::seconds>(end - start).count();
    cout << " sec" << endl;
    cout << "Elapsed time in Milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << " ms" << endl;

    return 0;
}
