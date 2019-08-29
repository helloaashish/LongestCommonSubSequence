//Aashish Pandey
//Jesse Pierce
//csce 4110-Assignment 2
//Dec 3 2018
//this programs prompts the user to enter two strings and computes the Longest Common Subsequence between two of them

#include <iostream>
#include<string>
#include <vector>
#include<stack>
#include<iomanip>

using namespace std;

//function declarations
void initialize_table(int first_size, int second_size); //function for initializing the table for computing LCS between the strings
void populate_table(string first, string second);          //function for populating the table for computing the LCS
string longest_sequece(string first, string second);  //function to return the Longest Common Subsequence between the strings

//class value to put the value in table while computing, class value contains an integer value and character direction, default to 0 and N
class Value{
    public:
    int value;
    char direction;
    
    Value(){
        value = 0;
        direction= 'N';
    }
};

vector<Value> row;  //vector of Value objects to store the entire row information
vector < vector <Value> > table;  //2D vector ro store the entire computation table
stack <char> mystack;  //stack to store the LCS

int longest_length=0;
int position_x, position_y;

//fuction to initialize the computation table, and storing all the position to Default Value
void initialize_table(int first_size, int second_size){
    for (int i=0; i<=second_size; i++){
        for (int j=0; j<=first_size; j++){
            row.push_back(Value());
        }
        table.push_back(row);
        row.clear();
        
    }
    }


//function to populate the value
//takes to string as parameters and compares each character of first string to every characters of second string to tabulate the computation table
//char D=> 'diagonal' U=> up and L=> left
void populate_table(string first, string second){
   // cout<<"size of first is "<<first.size();
    for (int r=1; r<=second.size(); r++){
        for (int c=1; c<=first.size(); c++){
            if (second[r-1]==first[c-1]){
                table[r][c].value=(table[r-1][c-1].value + 1);
                table[r][c].direction='D';
                if(table[r][c].value > longest_length) longest_length=table[r][c].value;
                position_x=r;
                position_y=c;
            }
            else{
                if (table[r][c-1].value >= table[r-1][c].value){
                    table[r][c].value =table[r][c-1].value;
                    table[r][c].direction='L';
                    if(table[r][c].value > longest_length) longest_length=table[r][c].value;
                    position_x=r;
                    position_y=c;
                }
                else{
                    table[r][c].value =table[r-1][c].value;
                    table[r][c].direction='U';
                    if(table[r][c].value > longest_length) longest_length=table[r][c].value;
                    position_x=r;
                    position_y=c;
                }
                
            }
            
            
        }
        
    }
    
}

//function to return the LCS between the string
// uses the comutation table to find the LCS
//use stack to store the values from buttom of the table proclating up
//LIFO to pop from the stack to get the subsequence
string longest_sequence(string first, string second){
    
    string LCS;
    int x=position_x;
    int y= position_y;
    while(table[x][y].value!=0){
        if(table[x][y].direction=='D'){
            mystack.push(first[y-1]);
            x=x-1;
            y=y-1;
        }
        else if (table[x][y].direction=='U'){
            x=x-1;
        }
        else {
            y=y-1;
        }
    }
    while(!mystack.empty()){
        LCS.push_back(mystack.top());
        mystack.pop();
    }
    return LCS;
}

/*
int main(){

    int total, lcs;
    string name, DNA;
    cout<<"Enter the total number of the strings you want to check: ";
    cin >>total;
 vector <string> names (total);
 vector <string> DNAs (total);
 vector <vector<int>> displaytable( total);
 //vector <int> thisrow;
    for (int i=0; i<total; i++){
        cout<<"Enter the distinct name: ";
        cin>>name;
        cout<<"Enter the sequence: ";
        cin>>DNA;
        names[i]=name;
        DNAs[i]= DNA;
    }
    
    for (int j=0; j<total; j++){
        for(int k=0; k<total; k++){
            if (j==k){
                displaytable[j][k] = DNAs[j].size();
            }
            else if (j<k){
            initialize_table(DNAs.at(j).size(), DNAs.at(k).size());
            populate_table(DNAs.at(j), DNAs.at(k));
            //thisrow.push_back(longest_length);
                displaytable[j][k]=longest_length;
                
            longest_length=0;
                table.clear();}
            else{
                displaytable[k][j]=longest_length;
            }
                
        }
        
        //displaytable.push_back(thisrow);
        //thisrow.clear();
    }
    cout<<":::::::::::::::::::::::::::::Display Table with LCS Length:::::::::::::::::::::::::::::"<<endl;
    cout<<setw(4)<<" X ";
    for (int i =0; i<total; i++){
        cout<<setw(4)<<names.at(i);
    }
    for(int j=0; j<displaytable.size();j++){
        cout<<endl<<setw(4)<<names.at(j);
        for (int k=0; k<displaytable.size();k++){
            cout<<setw(4)<<displaytable[j][k];
        }
    }
    cout<<endl<<":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
    return 0;
}*/

//main function
int main() {
    //ACGCTG
    //ATGCTGC
    string first, second;
    char again = 'y';
    while(again=='y'){
    
    cout<<"Enter the first string"<<endl;
    cin>>first;
    cout<<"Enter the second string"<<endl;
    cin>>second;
    cout <<"Length of first string is: "<<first.size()<<endl;
     cout <<"Length of second string is: "<<second.size()<<endl;
    
    initialize_table(first.size(), second.size());
    populate_table(first, second);
    cout<<endl<<"the length of longest common sub sequence is: "<<longest_length<<endl;
    cout<<"The longest common subsequence on two given string is: "<<longest_sequence(first,second)<<endl;
        table.clear();
        cout<<"Do you want to check for other sequences?";
        cin>>again;
        longest_length=0;

    }
    return 0;
}
