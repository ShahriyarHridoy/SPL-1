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



/********************************* variables ***************************/
extern char commentFreeFile[];
extern char advancedResultFile[];
extern void nameAssign(string name ,int methodNumber);


/**** function detection data***********/
char methodAreaFile[] = "methodArea.txt";
string savedFile[limit];
//int saveFileSize = 0;

struct node{

    int startLine;
    int finishLine;
    string name;
    bool nameFlag; // true if exists in the line containing double brace

} tempNode;

vector <node> methodTracer;

/*************************************/


int block=0;
int counter;
int saveFileSize=0; //Initialize the number of lines
string keys [] = {  "if(", "if", "for(", "for",  "while(", "while", "else", "case",  "switch"};





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
    for(int i=0; i < lineSize-1 ; i++) {

        if(line[i] == '"'){
            if(line[i+1]!= '"'){
                line[i]=' ';
                line[i+1]='"';
             }
         
             else 
             {
                line[i]=' ';
                line[i+1]=' ';
                }
            //doubleQuote = true;/*Start of the double quote.
        //We will not consider anything inside double quote */
        // else if(doubleQuote == true) {

        //    if(line[i] == '"') doubleQuote = false;     //If the closing double quote is reached
        //    else continue;                              // else we ignore the character because it is inside the double quote

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

            savedFile[saveFileSize] = commentFreeFileInput(line);
            //Saving file in string
            //getline(iFile, line);
            saveFileSize++;

        }
        saveFileSize++;
        
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


/* Find total number of occurrences of a key in a word*/
int findKeyword(string word, string key) {

    int keyLen = key.size();
    int lineLen = word.size() - keyLen + 1;
    int counter = 0; // stores the total number of occurrences of a key
    bool flag;

    for(int i=0; i<lineLen; i++) {

        flag = true;
        for(int j=0; j<keyLen; j++) {
            if(word[i+j] != key[j]) {
                flag = false;
                break;
            }
        }
     
    }
    if(flag == true) return 1;
        else return 0;  
    
}

   
void printnode(){
    int tempSize = methodTracer.size();//Size of total methods
    for(int i=0; i<tempSize; i++){
        //printf("%s = %d to %d" )
        int check = methodTracer[i].finishLine;
        if(check== 55555){
            methodTracer[i].finishLine = methodTracer[i+1].finishLine + 1;
        }
        cout<< methodTracer[i].name << methodTracer[i].startLine << methodTracer[i].finishLine ;
    }
}

int main(int argc, char *argv[]){

    fileOpenInString(argv[1]);


    stack <char> doubleQoute;   //Saves double quotes
    stack <char> firstBracket;  //Saves first braces
    methodTracer.clear();       // Clears the method tracer 
    
    

    for(int i=0; i<saveFileSize; i++) {
        
        
        
        
    
        for(int k=0; k<9; k++) { /* Total number of keys = 3 */

            istringstream iss(savedFile[i]);  //string line to words  
            string word;
            counter= 0;
            while(iss>>word) {        
                counter = findKeyword(word, keys[k]); //find the control statements 
            }
            
            if(counter==1){                                     //return value to check if the keyword find or not
                if(k==0 || k==1) tempNode.name=keys[1];         //for if statement
                else if(k==2 || k==3) tempNode.name=keys[3];    //for for statement
                else if(k==4 || k==5) tempNode.name=keys[5];     //for while statement
                else tempNode.name=keys[k];                      //for if, case and switch statement
             }

        }
        
        


        int strLen = savedFile[i].size();   //check 1st line string size
        int check=0;
        for(int l=0; l< strLen; l++){
            if(counter==1){                  //if keyword found then check the first "{" (second brucket) found or not in that line
                if(savedFile[i][l]=='{')
                    check=1;
             }
        }
        if(check !=1){
            if(counter==1){
                for(int l=0; l< savedFile[i+1].size(); l++){           // if keyword found but "{" not in that line then check the next line first letter "{" or not
                    if(savedFile[i+1][l]!=' ' && savedFile[i+1][l]!='{'){
                        if(tempNode.name==keys[6]){                       //if "{" not found in second line first letter then check this keyword is "else" or not
                            tempNode.startLine = i;
                            tempNode.finishLine = i;                       //if this is "else" then start line and finish line is same
                            methodTracer.push_back(tempNode);
                          }
                         else {
                            tempNode.startLine = i;                        //if keyword is others and cann't find "{" then input start line and wait for last line
                            tempNode.finishLine = 55555;                    
                            methodTracer.push_back(tempNode);
                         }   
                         break;
                   // else if(savedFile[i+1][l]=='{'){
                        
                    }
                     
                }   
                        
            }
                        
        }

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
           // else if
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
   //findName();
   printnode(); 
    return 0;
}







