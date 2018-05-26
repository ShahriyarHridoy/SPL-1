#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <map>
#include <functional>
#include <cstdio>
#include<strstream>
#include<bits/stdc++.h>

using namespace std;


int block=0;

string commentFreeFileInput(string line) {

    if(line[0]=='#') {
        return "";             // Ignores lines starting with '#' like #include <iostream>
    }
    if(line.length() == 0 ) {
        return "";      // Ignores empty Lines
    }

    bool doubleQuote = false; //Keeps the track of first occurrence of a letter in a line
    bool multipleCommentLineFlag;
    int lineSize = line.size();
    for(int i=0; i < lineSize ; i++) {

        if(line[i] == '"' && doubleQuote == false) doubleQuote = true;/*Start of the double quote.
        We will not consider anything inside double quote */
        else if(doubleQuote == true) {

            if(line[i] == '"') doubleQuote = false;     //If the closing double quote is reached
            else continue;                              // else we ignore the character because it is inside the double quote

        }
        else if(multipleCommentLineFlag == true) {      //If the current character is inside of multiple line comment character

            if(line[i]=='*' && line[i+1] =='/') {
                multipleCommentLineFlag = false;
                line[i] = ' ';
                line[i+1]= ' ';
            }
            else line[i]=' ';

        }
        else if(line[i]=='/' && line[i+1] =='*') {      //If the closing of multiple line comment character
            multipleCommentLineFlag = true;
            line[i] = ' ';
            line[i+1] = ' ';
        }
        else if(line[i] == '/' && line[i+1] == '/') {   //if single line comment character is reached, then we ignore the next characters in that line

            for(int j=i ; j<lineSize; j++) line[j] = ' ';
            break;
        }

    }

    for(int i=0; i<lineSize; i++) {
        if(line[i] != ' ' && line[i] != 13) return line+"\n"; // carriage return may be present in line
    }

    return ""; //This is the case when the whole line is comprised of space or carriage return character
}






int main(int argc, char *argv[]){
	ifstream iFile;
	iFile.open(argv[1]);

    if(iFile.is_open()) {


        string line;
        vector<string> lines;
        while(getline(iFile,line)){

            lines.push_back( commentFreeFileInput(line) );  /* Start of function that removes comments and blank lines
            Receives the string part that are not comment or blank line*/




        }




        //   string line;
    //getline(cin,line);
     for(int i=0; i<lines.size();i++)
     {

        istringstream iss(lines[i]);
        string word;

        while(iss>>word)
        {
           for(int i=0;i<word.size();i++)
           {

                if(word[i]=='m' && word[i+1]=='a' && word[i+2]=='i' && word[i+3]=='n' && i+3<word.size()){

                    if(word[i]=='i' && i+1<word.size() && word[i+1]=='f'){
                        printf("%d", block++);
                    }
                }
           }
        }


    }



        iFile.close();  //closing of input file
    }
    return 0;
}

