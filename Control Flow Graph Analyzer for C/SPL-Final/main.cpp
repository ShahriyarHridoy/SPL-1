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
#include <fstream>


#define limit 5000
using namespace std;



/********************************* variables ***************************/
extern char commentFreeFile[];
extern char advancedResultFile[];
extern void nameAssign(string name ,int methodNumber);


/**** function detection data***********/
char methodAreaFile[] = "methodArea.txt";
string savedFile[limit];
int sLineArr[limit];
int printFlow[limit];
//int saveFileSize = 0;

struct node{

    int startLine;
    int finishLine;
    string name;
    bool nameFlag; // true if exists in the line containing double brace

} tempNode;

vector <node> methodTracer;
//std::priority_queue<int, std::vector<int>, std::greater<int>> printFlow ;


/*************************************/

int ke=0;
int st=0;
int fi=0;
int ln=0;
int tst=0;
int block=0;
int counter;
int lcount=0;
int saveFileSize=0; //Initialize the number of lines
string keyWord[50000];
string kw;
int start[50000];
int finish[50000];
int kFindLine[50000];
string keys[] = { "if", "for", "while", "else", "case",  "switch", "main"};





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
        if(line[i] != ' ' && line[i] != 13) return line+" "; // carriage return may be present in line
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
             line= commentFreeFileInput(line);
             if(!line.empty()){
                savedFile[saveFileSize]=line;
                //Saving file in string
                //getline(iFile, line);
                cout<<tst++;
                cout<< savedFile[saveFileSize]<< endl;
                saveFileSize++;
            }

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


/* Find total number of occurrences of a key in a word*/
int findKeyword(string word, string key) {

    int keyLen = key.size();
    int lineLen = word.size();// - keyLen + 1;
    int counter = 0; // stores the total number of occurrences of a key
    bool flag;

   /* for(int i=0; i<lineLen; i++) {

        flag = true;
        for(int j=0; j<keyLen; j++) {
            if(word[i] != key[j]) {
                flag = false;
                break;
            }
        }

    }*/


    string s1= word;
    string s2= key;

    flag=false;
    if(strstr(s1.c_str(),s2.c_str())){
       // cout << " \n"<< key << "  -> found\n";
       // flag=true;
        return 1;
    }


    /*if(flag == true) return 1;*/
        else return 0;

}


void printnode(){

    int k=0, temp2;
    int tempSize = methodTracer.size();//Size of total methods
    for(int j=0; j<lcount; j++){
        for(int i=0; i<tempSize; i++){
            //printf("%s = %d to %d" )



           /*

            int check = methodTracer[i].finishLine;
            if(check== 55555){
                methodTracer[i].finishLine = methodTracer[i+1].finishLine + 1;
            }*/
            if(sLineArr[j] == methodTracer[i].startLine){


                cout<< methodTracer[i].name ;//<<"\t"<< methodTracer[i].startLine<<"\t" << methodTracer[i].finishLine <<"\n" ;



                printFlow[k]= methodTracer[i].startLine;
                cout<< "...."<<printFlow[k]<< "......";
                k++;
                printFlow[k]= methodTracer[i].finishLine;
                cout<< "...."<<printFlow[k]<< "\n";
                k++;

            }
        }
    }

   /* cout<< "keyword = "<< ke<< "\tTstart ="<< st<< "\tTfinish ="<< fi<< "\n" ;
    for(int i=0; i< ke; i++){
        cout<< keyWord[i]<< " - "<< start[i]<< " - "<< finish[i]<<  "\n";



        }*/

    for(int k=0; k< (tempSize*2); k++){

        cout << printFlow[k] << "\n";

    }


    cout <<  "************\n";


    for(int i=0;i<(tempSize*2);i++){

         for(int j=0;j<(tempSize*2)-i-1;j++){

             if(printFlow[j]>printFlow[j+1]){

                 temp2=printFlow[j];
                 printFlow[j]=printFlow[j+1];
                 printFlow[j+1]=temp2;

             }
         }
     }

    for(int k=0; k< (tempSize*2); k++){

        cout << printFlow[k] << "\n";

    }


}








void flowMaker(){


    ofstream my;
    my.open ("check.dot");


    my<< "digraph G { \n";

    int k=0, temp2;
    //priority_queue<int,vector<int>, compare > ;
    int tempSize = methodTracer.size();//Size of total methods


    for(int j=0; j<tempSize; j++){

        if(( methodTracer[j].name == "for") || (methodTracer[j].name == "while")){

            //my<<" \n"<< methodTracer[j].name << methodTracer[j].finishLine  <<"  ->"  << methodTracer[j].name << methodTracer[j].startLine ;
            my<<" \n"<< methodTracer[j].name << methodTracer[j].startLine  <<"  ->"  << methodTracer[j].name << methodTracer[j].finishLine ;
        }


       // if((methodTracer[j].name == "if")){
       //         my<<" \n"<< methodTracer[j].name << methodTracer[j].startLine  <<"  ->"  << methodTracer[j].name << methodTracer[j].finishLine ;
      //  }

    }




    for(int j=0; j<tempSize*2; j++){




        for(int i=0; i<tempSize; i++){

            if(printFlow[j] == methodTracer[i].startLine){

               my<<"  "<< methodTracer[i].name << methodTracer[i].startLine <<"  ->" ;

             /*  for( int k=0; k<5; k++){
                    if(k==4) cout<< "\t\t"<< "\\/"<< "\n";
                    else cout<<"\t\t" << "||"<< "\n";
               }*/


            }


        }
        for(int i=0; i<tempSize; i++){

            if(printFlow[j] == methodTracer[i].finishLine){

                my<<"  "<< methodTracer[i].name <<  methodTracer[i].finishLine ;

                if(j!= ((tempSize*2)-1)){

                   // for( int k=0; k<5; k++){
                        //if(k==4) cout<< "\t\t"<< "\\/"<< "\n";
                        //else cout<<"\t\t" << "||"<< "\n";
                         my<<"  ->" ;

                   //}
                }

            }
        }



    }


    for(int j=0; j<tempSize; j++){

        if(( methodTracer[j].name == "for") || (methodTracer[j].name == "while")){

            my<<" \n"<< methodTracer[j].name << methodTracer[j].finishLine  <<"  ->"  << methodTracer[j].name << methodTracer[j].startLine ;
           // my<<" \n"<< methodTracer[j].name << methodTracer[j].startLine  <<"  ->"  << methodTracer[j].name << methodTracer[j].finishLine ;
        }


        if((methodTracer[j].name == "if") && (methodTracer[j+1].name == "else")){
                my<<" \n"<< methodTracer[j].name << methodTracer[j].startLine  <<"  ->"  << methodTracer[j+1].name << methodTracer[j+1].startLine ;
        }

    }



    my<< "\n } \n";

    my.close();
    //return 0;





   // print_queue(printFlow);



  /*   for(int i=0;i<=10;i++){

         for(int j=0;j<=10-i;j++){

             if(printFlow[j]>printFlow[j+1]){

                 temp2=printFlow[j];
                 printFlow[j]=printFlow[j+1];
                 printFlow[j+1]=temp2;

             }
         }
     }


     for(int k=0; k<tempSize; k++){

        cout << printFlow[k];

    }*/











}









int main(){

    fileOpenInString("/home/iit/Desktop/SPL-Final/test3.c");


    //stack <char> doubleQoute;   //Saves double quotes
   // stack <char> firstBracket;  //Saves first braces
    stack <char> startB;
    stack <char> finishB;
    stack <string> kName;
    methodTracer.clear();       // Clears the method tracer
    int p=0;



    for(int i=0; i<saveFileSize; i++) {





            stringstream iss(savedFile[i]);  //string line to words
            string word;

            int test=i;
            int tep;
            while(iss>>word) {


                for(int k=0; k<7; k++) { // Total number of keys = 3
                    counter= 0;
                  //  cout<< "word="<<word<< "\n";
                   // cout<< "key="<<keys[k]<< "\n";
                    counter = findKeyword(word, keys[k]); //find the control statements
                    if(counter==1){
                     tep=k;
                     cout<<keys[k]<<"  -> found  "<<endl;
                    // keyWord[ke]=keys[k];
                     kw=keys[k];
                     kFindLine[ln]=i;
                     ln++;
                     ke++;
                     break;
                     }
                }

               /* if(counter==1){                                     //return value to check if the keyword find or not
                    if      (tep==0) tempNode.name=keys[0];         //for if statement
                    else if (tep==1) tempNode.name=keys[1];    //for for statement
                    else if (tep==2) tempNode.name=keys[2];     //for while statement
                    else tempNode.name=keys[tep];                      //for if, case and switch statement
                }  */

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
                        if(keyWord[ke-1]==keys[3]){                       //if "{" not found in second line first letter then check this keyword is "else" or not
                            tempNode.name= kw;
                            tempNode.startLine = i;
                            tempNode.finishLine = i;                       //if this is "else" then start line and finish line is same
                            methodTracer.push_back(tempNode);
                           // start[st]=i;
                           // st++;
                           // finish[fi]=i;
                           // fi++;
                            test= i+1;
                          }
                         else {
                            tempNode.name= kw;
                            tempNode.startLine = i;                        //if keyword is others and cann't find "{" then input start line and wait for last line
                            tempNode.finishLine = 55555;
                            methodTracer.push_back(tempNode);
                          //  start[st]=i;
                          //  st++;
                           // finish[fi]=5555;
                           // fi++;
                            test= i+1;
                         }
                         break;
                   // else if(savedFile[i+1][l]=='{'){

                    }

                }

            }

        }



        if(test==i){







            //if(counter==1) tempNode.name= keyWord[i];

            for(int j=0; j< strLen; j++) {
                //cout<< savedFile[i][j] <<"\n";
                if(  savedFile[i][j]=='{'  ) {
                    //tempNode.startLine = i;
                   // doubleQoute.push('{');
                    //tempNode.name= kw;

                    startB.push(i);
                    kName.push(kw);
                    sLineArr[lcount]= i;
                    lcount++;

                    cout<< "traced entry \n\n";

                }
                else if( savedFile[i][j]=='}'  ) {

                    tempNode.startLine = startB.top();
                    tempNode.finishLine = i;
                    tempNode.name= kName.top();
                    methodTracer.push_back(tempNode);

                    startB.pop();
                    kName.pop();


                    //doubleQoute.pop();


                   // firstBracket.pop();
                    //firstBracket.pop();
                    cout<< methodTracer[p].name <<"\t"<< methodTracer[p].startLine<<"\t" << methodTracer[p].finishLine <<"\n" ;
                    p++;
                    cout<< "traced exit \n\n";
                }
             /*    else if(savedFile[i][j] == '{') {
                    tempNode.startLine = i;
                    cout<< "entryyyyyyyyy\n";
                    doubleQoute.push('{');
                   // start[st]=i;
                   // st++;


                }
                else if(savedFile[i][j] == '}') {
                    cout<< "exitttttttttttt\n";

                    doubleQoute.pop();
                  // finish[fi]=i;
                  // fi++;
                }

                */
               // else if
                //Checks for () Because no struct or array contains () but it contains {}
               /* else if(savedFile[i][j] == '(' && doubleQoute.empty() && firstBracket.empty() ) {
                    firstBracket.push('(');
                }
                else if(savedFile[i][j] == ')' && doubleQoute.empty() && firstBracket.size()==1) {
                    firstBracket.push(')');
                }
                */

            }
        }

    }

    // Assign name to each methods
   //findName();
    printnode();
    flowMaker();



    return 0;
}







