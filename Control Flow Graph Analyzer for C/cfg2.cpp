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


#define limit 5000
using namespace std;



string savedFile[limit];
//int saveFileSize = 0;

struct node{

    int startLine;
    int finishLine;
    string name;

} tempNode;

vector <node> methodTracer;

/*************************************/


int block=0;
int saveFileSize=0; //Initialize the number of lines




string commentFreeFileInput(string line) {

    if(line.length() == 0 ) {
        return "";      // Ignores empty Lines
    }

    bool doubleQuote = false; //Keeps the track of first occurrence of a letter in a line
    bool multipleCommentLineFlag;
    int lineSize = line.size();
    
    for(int i=0; i < lineSize ; i++) {
        if(line[i]=='#') {
            return "";             // Ignores lines starting with '#' like #include <iostream>
        }
    }
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




void fileOpenInString(char * filename){

    ifstream iFile;
	iFile.open(filename);  //Opening the input file

    if(iFile.is_open()) {

        string line;
       // getline(iFile,line);
      //ifstream iFile(inputFile);

       // while(!iFile.eof()){ 
         while(getline(iFile,line)){   //Reads as long as we do not reach the end of file

            savedFile[saveFileSize++] = commentFreeFileInput(line);
            //Saving file in string
            getline(iFile, line);

        }
        
        iFile.close();      //Closes the inout file
    }
}






string findStringBeforeFirstBrace(string line){

    int firstBracePosition = -1;    //Location of (
    int len = line.size();

    for(int i=0; i<len; i++){

        if( line[i] == '(' ) {
            firstBracePosition = i;
        }
        else if( line[i] == '{' ) {
            line[i] = ' ';  //Making the brace empty
            break;
        }
    }

    if(firstBracePosition != -1 ) return line.substr(0,firstBracePosition);
    else return "";
}




void findName(){

    int tempSize = methodTracer.size();//Size of total methods
    for(int i=0; i<tempSize; i++) {

        int firstLine = methodTracer[i].startLine;  //First line number of a method
        string tempWords[10];   // to store words obtained form analyzing the lines

        int counter;
        string word;
        /** If we found the method name in the line of second brace*/
        istringstream iss( findStringBeforeFirstBrace(savedFile[firstLine]) );  /** Check whether name exits with the second brace*/
        for(counter = 0 ; iss>>word; counter++) {
            tempWords[counter] = word;
        }

        if(counter >= 1) {
           
        }

        if(word==" "){
            istringstream iss1( savedFile[firstLine-1] ) ;  /** Check previous line if keyword not found in that line*/
            for(counter = 0 ; iss1>>word; counter++) {
                tempWords[counter] = word;
                
            }
            if(counter > 1) {
               

            }

        }
    }

}


   




int main(int argc, char *argv[]){

  fileOpenInString(argv[1]);


    stack <char> doubleQoute;   //Saves double quotes
    stack <char> firstBracket;  //Saves first braces
    methodTracer.clear();       // Clears the method tracer 

    for(int i=0; i<saveFileSize; i++) {

        int strLen = savedFile[i].size();


        for(int j=0; j< strLen; j++) {

            if( doubleQoute.empty() && savedFile[i][j]=='{' && firstBracket.size() == 2) {
                tempNode.startLine = i;
                doubleQoute.push('{');

            }
            else if(doubleQoute.size() == 1 && savedFile[i][j]=='}' && firstBracket.size() == 2) {
                tempNode.finishLine = i;
                methodTracer.push_back(tempNode);
                doubleQoute.pop();
                firstBracket.pop();
                firstBracket.pop();

            }
            else if(savedFile[i][j] == '{') {

                doubleQoute.push('{');
            }
            else if(savedFile[i][j] == '}') {

                doubleQoute.pop();
            }
            //Checks for () Because no struct or array contains () but it contains {} 
            else if(savedFile[i][j] == '(' && doubleQoute.empty() && firstBracket.empty() ) {
                firstBracket.push('(');
            }
            else if(savedFile[i][j] == ')' && doubleQoute.empty() && firstBracket.size()==1) {
                firstBracket.push(')');
            }

        }

    }

    // Assign name to each methods
   findName();
    
    return 0;
}







