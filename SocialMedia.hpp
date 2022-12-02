/**********************************************************************************************************************/
// File: SocialMedia class declaration
// Name: Darien Labbe
// Date: 10/05/2022
// Description: This file declares the SocialMedia class
/**********************************************************************************************************************/
#ifndef SOCIALMEDIA_H
#define SOCIALMEDIA_H

#include <iostream>

class SocialMedia;

class SocialMedia {
public:
    SocialMedia();
    ~SocialMedia();
    void setSize(int followSize);
    void matrixBuild(int ID, std::string* follows, std::string userName, int numFollowsCount);
    void indexHtmlOut();
    int get(int row, int col);
private:
    int rowSize;
    int colSize;
    std::string* names;
protected:
    int** followMatrix;
};

#endif