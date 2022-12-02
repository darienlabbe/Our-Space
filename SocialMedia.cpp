/**********************************************************************************************************************/
// File: SocialMedia class implementation
// Name: Darien Labbe
// Date: 10/05/2022
// Description: This file implements the functions of the SocialMedia class by collecting the number of users and all
//     of their names, building a follow matrix to know who follows who, and outputs an index html page
/**********************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <cassert>
#include "SocialMedia.hpp"
using namespace std;

//Default Constructor
SocialMedia::SocialMedia(){
    rowSize = colSize = 1;
    names = new string[rowSize];

    //2D Dynamic Array
    followMatrix = new int*[rowSize];
    for (int i = 0; i < rowSize; i++) followMatrix[i] = new int[colSize];
}

//Default Deconstructor
SocialMedia::~SocialMedia() {
    delete [] names;

    for (int i = 0; i < rowSize; i++) delete [] followMatrix[i];
    delete [] followMatrix;
}

//Set Size function sets the size of the follow matrix and the array containing all names
void SocialMedia::setSize(int followSize) {
    rowSize = followSize;
    colSize = followSize;

    //Initialize with correct size and set matrix to 0
    delete [] followMatrix;
    followMatrix = new int*[rowSize];
    for (int i = 0; i < rowSize; i++) followMatrix[i] = new int[colSize];

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++){
            followMatrix[i][j] = 0;
        }
    }

    //Set size names string
    delete [] names;
    names = new string[followSize];
}

//Matrix build function takes in id, goes to the index for that user, and sets 1 to represent a follow
void SocialMedia::matrixBuild(const int ID, string* follows, const string userName, const int numFollowsCount) {
    int idFollow;

    if (!follows[0].empty()) {
        for (int i = 0; i < numFollowsCount; i++) {
            idFollow = stoi(follows[i]);
            followMatrix[ID - 1][(idFollow - 1)] = 1;
        }
    }
    names[ID - 1] = userName;
}

//Get function finds a particular data point in the matrix and returns it, or outputs error
int SocialMedia::get(const int row, const int col) {
    int result;

    if (followMatrix != nullptr) result = followMatrix[row][col];
    else {
        cerr << "Index is out of range for matrix" << endl;
        exit(1);
    }
    return result;
}

//Index html out function outputs the index html which represents the home page of this social media
void SocialMedia::indexHtmlOut() {
    ofstream outFile("index.html");
    assert(outFile.is_open());

    outFile << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n";
    outFile << "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
    outFile << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    outFile << "<title>Our Space</title>\n</head>\n<body style=\"background-color: #181818;color: white;";
    outFile << "font-family: 'Poppins', sans-serif;margin: auto;width: 30%;inline-size: max-content;\">\n";
    outFile << "<h1><img style=\"transform: translateY(20px) translateX(-10px);width: 2em;height: auto;\"";
    outFile << "alt=\"Social Media Logo\"; src=\"indexLogo.png\" />Our Space: User List</h1>\n";
    outFile << "<ol style=\"margin: auto;width: 30%;\">\n";
    for (int i = 0; i < rowSize; i++)
        outFile << "<li><a href=\"user" << i + 1 << ".html\">" << names[i] << "</a></li>\n";
    outFile << "</ol>\n</body>\n</html>" << endl;

    outFile.close();
}