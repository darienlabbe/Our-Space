/**********************************************************************************************************************/
// File: UserProfiles class implementation
// Name: Darien Labbe
// Date: 10/05/2022
// Description: This file implements the functions of the UserProfiles class by reading from the input.json file and
//     building each user and outputting each user's html file
/**********************************************************************************************************************/
#include "UserProfiles.hpp"
#include <fstream>
#include <iostream>
#include <cassert>
using namespace std;

//Default Constructor
UserProfiles::UserProfiles() {
    idStr = 0;
    name = location = picUrl = "";
    allNames = new string[1];
    allNames[0] = "None";
    size = 1;
    follows = new string[1];
    follows[0] = "0";
}

//Default Deconstructor
UserProfiles::~UserProfiles() {
    delete [] allNames;
    delete [] follows;
}

//Tokenizer function that takes in the current token and adds the pertinent data in the class
void UserProfiles::tokenizer(fstream& inFile, const string token, int& numFollows){
    bool noFollows = false, noPic = false, noLocation = false;
    char currentChar, previousChar;
    string info;
    numFollows = 0;

    inFile.get(currentChar);
    if (token == "users") inFile.ignore(256, '\n');
    else if (token == "id_str") {
        while (!isdigit(currentChar)) inFile.get(currentChar);
        inFile.unget();
        getline(inFile, info, '"');
        idStr = stoi(info);
        inFile.ignore(256, '\n');
    }
    else if (token == "name") {
        while (!isalpha(currentChar)) inFile.get(currentChar);
        inFile.unget();
        getline(inFile, info, '"');
        name = info;
        info = "";
        inFile.ignore(256, '\n');
    }
    else if (token == "location") {
        while (!isalpha(currentChar) && !noLocation) {
            if (currentChar == '"' && previousChar == '"') noLocation = true; //Check for location
            previousChar = currentChar;
            inFile.get(currentChar);
        }
        if (!noLocation) {
            inFile.unget();
            getline(inFile, info, '"');
            location = info;
            info = "";
            inFile.ignore(256, '\n');
        } else location = "";
    }
    else if (token == "pic_url") {
        while (!isalpha(currentChar) && !noPic) {
            if (currentChar == '"' && previousChar == '"') noPic = true; //Check for picture url
            previousChar = currentChar;
            inFile.get(currentChar);
        }
        if (!noPic) {
            inFile.unget();
            getline(inFile, info, '"');
            picUrl = info;
            inFile.ignore(256, '\n');
        } else picUrl = "";
    }
    else if (token == "follows") {
        while (!isdigit(currentChar) && !noFollows) {
            previousChar = currentChar;
            inFile.get(currentChar);
            if (previousChar == '[' && currentChar == ']') { //Check for follows
                follows[0] = "";
                noFollows = true;
            }
        }
        if (!noFollows) {
            inFile.unget();
            getline(inFile, info, '"');
            follows[numFollows] = info;
            numFollows++;
            while (currentChar != ']') {
                inFile.get(currentChar);
                if (isdigit(currentChar)) {
                    inFile.unget();
                    getline(inFile, info, '"');
                    follows[numFollows] = info;
                    numFollows++;
                }
            }
        }
    }
}

//Get Sizes function counts the number of users for follower max size
void UserProfiles::getSizes(SocialMedia& curMatrix) {
    char nextChar, currChar;

    ifstream maxSizeInFile("input.json");
    assert(maxSizeInFile.is_open());
    while(!maxSizeInFile.eof()) {
        currChar = nextChar;
        nextChar = maxSizeInFile.peek();
        if (currChar == '}' && nextChar == ',') {
            size++;
            curMatrix.setSize(size);
        }
        maxSizeInFile.ignore();
    }maxSizeInFile.close();
}

//Get Ids function gets all the user Ids and orders them so that the users can be properly sorted
int* UserProfiles::getIds(const int size) {
    int* ids = new int[size];
    char nextChar;
    string token;
    int index = 0;

    ifstream getIds("input.json");
    assert(getIds.is_open());
    while(!getIds.eof()){
        nextChar = getIds.peek();
        if (isalpha(nextChar)){
            getline(getIds, token, '"');
            if (token == "users") getIds.ignore(256, '\n');
            else if (token == "name") getIds.ignore(256, '\n');
            else if (token == "location") getIds.ignore(256, '\n');
            else if (token == "pic_url") getIds.ignore(256, '\n');
            else if (token == "follows") getIds.ignore(256, '\n');
            else if (token == "id_str") {
                getIds.ignore();
                while (!isdigit(nextChar)) getIds.get(nextChar);
                getIds.unget();
                getline(getIds, token, '"');
                ids[index] = stoi(token);
                index++;
            }
        }else getIds.ignore();
    }getIds.close();
    return ids;
}

//Get all names function gets all names for html use
void UserProfiles::getAllNames() {
    int* allIds = getIds(size); //Get ids if names appears before id for each user
    char currentChar;
    string token;
    int index = 0;

    ifstream getNames("input.json");
    assert(getNames.is_open());
    while(!getNames.eof()) {
        currentChar = getNames.peek();
        if (isalpha(currentChar)) {
            getline(getNames, token, '"');
            if (currentChar == ']') { //ignore three lines which moves input to eof
                getNames.ignore(256, '\n');
                getNames.ignore(256, '\n');
                getNames.ignore(256, '\n');
            } else if (token == "users") getNames.ignore(256, '\n');
            else if (token == "location") getNames.ignore(256, '\n');
            else if (token == "pic_url") getNames.ignore(256, '\n');
            else if (token == "follows") getNames.ignore(256, '\n');
            else if (token == "id_str") getNames.ignore(256, '\n');
            else if (token == "name") {
                getNames.get(currentChar);
                while (!isalpha(currentChar)) getNames.get(currentChar);
                getNames.unget();
                getline(getNames, token, '"');
                allNames[(allIds[index]) - 1] = token;
                index++;
                getNames.ignore(256, '\n');
            }
        }else getNames.ignore();
    }getNames.close();
    delete [] allIds;
}

//User builder and JSON parser function that
void UserProfiles::userBuilderJSONParser() {
    char nextChar, currChar;
    string token;
    int numFollowsCount = 0;
    UserProfiles curUser;
    SocialMedia curMatrix;

    //Get all sizes and allocate memory
    curUser.getSizes(curMatrix);
    curUser.follows = new string[curUser.size];
    curUser.allNames = new string[curUser.size];

    //Get all names
    curUser.getAllNames();

    //Gets info for matrix
    fstream matrixRead("input.json");
    assert(matrixRead.is_open());
    while(!matrixRead.eof()){
        currChar = nextChar;
        nextChar = matrixRead.peek();

        //Check if new user to be read
        if (currChar == '}' && nextChar == ',') {
            curMatrix.matrixBuild(curUser.idStr, curUser.follows,curUser.name, numFollowsCount);
            curUser.name = curUser.location = curUser.picUrl = "";
            curUser.follows = new string[curUser.size];
            numFollowsCount = 0;
        }

        if (isalpha(nextChar)) {
            getline(matrixRead, token, '"');
            curUser.tokenizer(matrixRead, token, numFollowsCount);
        }
        if(ispunct(nextChar) || isspace(nextChar) || nextChar == '\n') matrixRead.ignore();
        token = "";
    }
    curMatrix.matrixBuild(curUser.idStr, curUser.follows,curUser.name, numFollowsCount);
    numFollowsCount = 0;

    //Read json file and output the user htmls
    fstream inFile("input.json");
    assert(inFile.is_open());
    while(!inFile.eof()){
        currChar = nextChar;
        nextChar = inFile.peek();

        //Check if new user to be read
        if (currChar == '}' && nextChar == ',') {
            curUser.userHtmlOut(numFollowsCount, curUser.size, curMatrix);
            curUser.name = curUser.location = curUser.picUrl = "";
            numFollowsCount = 0;
        }

        if (isalpha(nextChar)) {
            getline(inFile, token, '"');
            curUser.tokenizer(inFile, token, numFollowsCount);
        }
        if(ispunct(nextChar) || isspace(nextChar) || nextChar == '\n') inFile.ignore();
        token = "";
    }
    curUser.userHtmlOut(numFollowsCount, curUser.size, curMatrix);
    curMatrix.indexHtmlOut();
    inFile.close();
}

//User html out function outputs individual user htmls specialized to each user with user data
void UserProfiles::userHtmlOut(const int numFollows, const int maxFollowers, SocialMedia& curMatrix) {
    bool hasFollowers = false, hasMutuals = false;
    int user;

    ofstream outFile("user" + to_string(idStr) + ".html", ofstream::out | ofstream::trunc);
    assert(outFile.is_open());

    outFile << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n";
    outFile << "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
    outFile << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    outFile << "<title>" << name << "'s Profile</title>\n</head>\n<body style=\"background-color: #181818;";
    outFile << "color: white;font-family: 'Poppins', sans-serif;margin: auto;width: 30%;inline-size: max-content;";
    outFile << "\">\n<h1>" << name;
    if (!location.empty()) outFile << " in " << location;
    outFile << "</h1>\n";
    if (!picUrl.empty()) outFile << R"(<img alt="Profile pic" src=")" << picUrl << "\" />\n";
    else outFile << "<img alt=\"Default pic\" src=\"default.png\" />\n";

    //Follows
    outFile << "<h2>Follows</h2>\n";
    if (!follows[0].empty()) {
        outFile << "<ul>\n";
        for (int i = 0; i < numFollows; i++) {
            user = stoi(follows[i]);
            outFile << "<li><a href=\"user" << user << ".html\">" << allNames[user - 1] << "</a></li>\n";
        }outFile << "</ul>\n";
    }
    else outFile << "<p>None</p>" << endl;

    //Followers
    outFile << "<h2>Followers</h2>\n";
    for (int i = 0; i < maxFollowers; i++) if (curMatrix.get(i, idStr - 1) == 1) hasFollowers = true;
    if (hasFollowers) { //If user has followers then display
        outFile << "<ul>\n";
        for (int i = 0; i < maxFollowers; i++) {
            if (curMatrix.get(i, idStr - 1) == 1)
                outFile << "<li><a href=\"user" << i + 1 << ".html\">" << allNames[i] << "</a></li>\n";
        }
        outFile << "</ul>\n";
    }
    else outFile << "<p>None</p>" << endl; //If user doesn't have followers

    //Mutuals
    outFile << "<h2>Mutuals</h2>\n";
    for (int i = 0; i < maxFollowers; i++) { //Check if mutuals exist
        for (int j = 0; j < numFollows; j++)
            if (curMatrix.get(i, idStr - 1) == 1 && stoi(follows[j]) == i + 1) hasMutuals = true;
    }
    if (hasMutuals) { //If mutuals exist, add them
        outFile << "<ul>\n";
        for (int i = 0; i < maxFollowers; i++) {
            for (int j = 0; j < numFollows; j++) {
                if (curMatrix.get(i, idStr - 1) == 1 && stoi(follows[j]) == i + 1)
                    outFile << "<li><a href=\"user" << i + 1 << ".html\">" << allNames[i] << "</a></li>\n";
            }
        }outFile << "</ul>\n";
    }
    else outFile << "<p>None</p>\n"; //If mutuals don't exist

    outFile << "</body>\n</html>" << endl;
    outFile.close();
}
