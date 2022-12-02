/**********************************************************************************************************************/
// File: UserProfiles class declaration
// Name: Darien Labbe
// Date: 10/05/2022
// Description: This file declares the UserProfiles class
/**********************************************************************************************************************/
#ifndef USER_H
#define USER_H

#include "SocialMedia.hpp"
#include <iostream>

class UserProfiles;

//Made matrix class public to use in tandem
class UserProfiles: public SocialMedia{
    public:
        UserProfiles();
        ~UserProfiles();
        void getSizes(SocialMedia& curMatrix);
        void getAllNames();
        void tokenizer(std::fstream& inFile, std::string token, int& numFollowsCount);
        static void userBuilderJSONParser();
        void userHtmlOut(int numFollows, int maxFollowers, SocialMedia& curMatrix);
        static int* getIds(int size);
    private:
        int idStr;
        std::string name;
        std::string location;
        std::string picUrl;
        std::string* allNames;
        std::string* follows;
        int size;
};

#endif