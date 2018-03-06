#include<bits/stdc++.h>


using namespace std;



int main()
{
    string line;
    getline(cin,line);
    
    
    istringstream iss(line);
    
    string word;
    
    while(iss>>word)
    {
       for(int i=0;i<word.size();i++)
       {
            
                if((word[i]=="m" && word[i+1]=="a" && word[i+2]=="i" && word[i+3]=="n" && (i+3)<word.size()){
                    block++;

      
                }
                 if(word[i]=='i' && (i+1)<word.size() && word[i+1]=='f'){
                        
                        printf("%d", block++);
                    }
            
       }
    }   
    
}
