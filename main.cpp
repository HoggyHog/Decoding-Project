#include <iostream>
#include <fstream>
#include <iomanip>
#include "header.hpp"


using namespace std;

// function to find the 4 most repeating letters
char* max_occurence(int* occurence,char* max_occ){
    //HERE HERE
    for(int i=0;i<6;i++){       
        int max=*(occurence);
        int max_index=0;
        for(int m=1;m<26;m++){
            if(*(occurence+m)>max){
                max=*(occurence+m);
                max_index=m;
            }
        }
        *(max_occ+i)=(char)(max_index+97); 
        *(occurence+max_index)=0;            
    } 
    
    //HERE HERE 
    sort(max_occ,max_occ+6);

   
    return max_occ;
}

char* make_temp_key(char key[][26],char alphabets[]){
    for(int i=0;i<26;i++){

        key[0][i]=alphabets[i];
        if(i==0){
            key[1][i]='q';            
        }
        else if(i==4){
            key[1][i]='k'; 
        }
        else if(i==8){
            key[1][i]='o'; 
        }
        else if(i==19){
            key[1][i]='h'; 
        }
        
        else{
            key[1][i]='_'; 
        }

        
    }
    return reinterpret_cast<char *>(key);

    
}

//function to make the first key using 4 most repeated letters
char* make_key(char max_occ[], char key[][26],char alphabets[]){

    int freq[5];
    for(int i=0;i<5;i++){
        freq[i]=int(freq_single[i])-65;
    }

    for(int i=0;i<26;i++){
        key[0][i]=alphabets[i];
        if(i==freq[0]){
            key[1][i]=max_occ[0];            
        }
        else if(i==freq[1]){
            key[1][i]=max_occ[1]; 
        }
        else if(i==freq[2]){
            key[1][i]=max_occ[2]; 
        }
        else if(i==freq[3]){
            key[1][i]=max_occ[3]; 
        }
        /* else if(i==freq[4]){
            key[1][i]=max_occ[4]; 
        } */
        else{
            key[1][i]='_'; 
        }
    }
    
    return reinterpret_cast<char *>(key);
}

//function to make the occurence for each letter
int* top4(string st ,int* arr){
    
    for(int i=0;i<st.length();i++){       
        char ch=st.at(i);
        int j=int(ch)-97;
        if(j>=0&&j<=25){
            *(arr+j)+=1;
        }
    }
    return arr;
}

//function to make the partial word  using the present key and word
string make_partial_word(char* key,string word){
    string compare="";
    for(int j=0;j<word.length();j++){
        bool found=false;
        for(int i=0;i<26;i++){
            if(word[j]==*(key+(1*26)+i)){
                compare+=*(key+(0*26)+i); 
                found=true;
            }       
        }
        if(!found){
            compare+=word[j];
        }        
    }
    return compare;
}

//function to update the key when we find a unique word
char* update_key(char* key, string word, string dict_word){
    string compare=make_partial_word(key,word);
    for(int i=0;i<compare.length();i++){
        if(int(compare[i])>=97 && int(compare[i])<=122){
            int pos=int(dict_word[i])-65;
            *(key+(1*26)+pos)=compare[i];
        }
    }
    //cout<<"input word->"<<word<<"|| "<<"partial decoded word ->"<<make_partial_word(key,word)<<"|| "<<"dictionary match->"<<dict_word<<endl;
    cout<<"UPDATED KEY"<<endl;
    for(int i=0;i<2;i++){
        for(int j=0;j<26;j++){
            cout<<*(key+(i*26)+j)<<" ";
        }
        cout<<endl;
    }
    return key;
}

//function to get the encoded character for a real character
char get_cipher(char c,char* key){
    for(int i=0;i<26;i++){
        if(*(key+i)==c){
            return *(key+(1*26)+i);
        }
    }
    return ' ';
}

string secret(char* key){
    string word="";
    for(int i=0;i<6;i++){
        word+=*(key+26+i);
    }
    
    return word;
}

// function to make up the final key if theres a gap
char* generate(char* key){
    string secret_string=secret(key);
    
    for(int i=0;i<26;i++){
        if(*(key+26+i)=='_'){
            int t=0;
            bool condition1=true;
            
            while(condition1){
                t++;
                bool condition2=true;
                for(int j=0;j<secret_string.length()&&condition2;j++){
                    if(char(int(*(key+26+i-1))+t)==secret_string[j]){
                        condition2=false;
                    }
                }
                if(condition2){
                    condition1=false;
                }
            }
            *(key+26+i)=char(int(*(key+26+i-1))+t);
        }
    }

    return key;
}

/* char* generate(char* key){
    for(int i=0;i<26;i++){
        if(*(key+26+i)=='_'){
            *(key+26+i)=char(int(*(key+26+i-1))+1);
        }
    }

    return key;
} */

// function to check if the current key is the real key
bool check(char* key,string words[],string dict[],int lenw,int lend){

        cout<<endl;
        
        cout<<"checking for "<<endl;
        for(int i=0;i<2;i++){
            for(int j=0;j<26;j++){
                cout<<*(key+(i*26)+j)<<" ";
            }
            cout<<endl;
        }
        cout<<endl;

        for(int i=0;i<lenw;i++){

            string word=words[i];
            
            bool go_deeper=true;

            //needed to initialise these 2 outside the j loop
            int c=0;
            string dict_word;
            string possible_word;

            int reason;

            for(int j=0;j<lend;j++){
                
                dict_word=dict[j];
                go_deeper=true;
                
                
                if(dict_word.length()!=word.length()){
                    continue;
                }
                else{
                    string compare=make_partial_word(key,word);                      
                    for(int k=0;(k<compare.length()&&go_deeper);k++){                        
                        if(int(compare[k])>=65&&int(compare[k])<=90){
                            if(compare[k]==dict_word[k]){
                                continue;                                
                            }
                            else{
                                go_deeper=false;
                                reason=1;
                            }
                        }
                        
                    }

                    bool accepted=true;
                    if(go_deeper){
                        
                        for(int i=0;i<compare.length();i++){
                            for(int j=0;j<compare.length();j++){
                                //to check if the dict word and compare word have the same letters at same places
                                if(dict_word[i]==dict_word[j]){
                                    if(compare[i]==compare[j]){
                                        continue;
                                    }
                                    else{
                                        accepted=false;
                                        reason=2;
                                    }
                                }
                                //to check if the dict word and compare word have the same letters at same places
                                if(compare[i]==compare[j]){
                                    if(dict_word[i]==dict_word[j]){
                                        continue;
                                    }
                                    else{
                                        accepted=false;
                                        reason=3;
                                    }
                                }
                                
                            }
                            // NOW TO COMPARE BACKWARDS SIR (so that the key doesnt change the value of sm it shdnt)
                            if(dict_word[i]==compare[i]){
                                continue;
                            }
                            else if(get_cipher(dict_word[i],key)=='_'){
                                continue;
                            }
                            else{
                                accepted=false;
                                reason=4+i;
                            }
                        //Now if it passed thro all that, then go for the kill
                        }
                        if(accepted){
                            possible_word=dict_word;
                            c++;
                            
                        }
                    }
                }
                
            }
            //been through all the dictionary words at this point

            //now in this possible words, check same matching letters ->real deal

            if(c==1){
                bool same=true;
                for(int i=0;i<word.length();i++){
                    if (make_partial_word(key,word)[i]!=possible_word[i]){
                        same=false;
                    }
                }
                if(!same){
                    cout<<"input word->"<<word<<" "<<"partial decoded word ->"<<make_partial_word(key,word)<<" "<<"dictionary match->"<<possible_word<<endl;
                    char* new_key=update_key(key,word,possible_word);
                    
                    cout<<endl;
                    
                    return check(new_key,words,dict,lenw,lend);
                    
                }
                
            }

            if(c==0){    
                cout<<"WORD WITH NO MATCH->"<<make_partial_word(key,word)<<endl;
                cout<<reason<<endl;
                return false;
            }
        
        }        
    return true;

    }



int main(){

    //getting in the whole input text into a string
    string st;
    
    ifstream in(path_file);
    getline(in,st);

    //getting all the input text into an array
    string input_words[st.length()];
    string word1;
    bool keep_searching=true;
    int word_count=0;
    int i=0;

    while(keep_searching){
        if(i==st.length()){
            keep_searching=false;
        }
        else if(int(st[i])>=97&&int(st[i])<=122){
            word1+=st[i];
            i+=1;
        }  
        else if(int(st[i])==92){
            i+=2;
        }
        else{
            if(word1!="" && word1!=" "){
                input_words[word_count]=word1;
                word_count++;
                word1=""; 
                i+=1;
            }
            else{
                i+=1;    
            }
        }       
    } 



    //getting all the words in the dict into a dict array

    string demo;
    string word2;
    bool condition;
    string dict[97569];
    int lend=0;
    ifstream on(path_dict);

    while(getline(on,demo)){
        word2="";
        condition=true;
        for(int i=0;(i<demo.length()&&condition);i++){
            if((int(demo[i])==32)||(int(demo[i])==9)){
                condition=false;  
            }
            else{
                word2+=demo[i];
            }
        }
        dict[lend]=word2; 
        lend++;
    }
    
    
    /* for(int i=0;i<97569;i++){
        word2="";
        condition=true;
        getline(on,demo);
        for(int i=0;(i<demo.length()&&condition);i++){
            if((int(demo[i])==32)||(int(demo[i])==9)){
                condition=false;  
            }
            else{
                word2+=demo[i];
            }
        }
        dict[i]=word2;   
    }
    int lend=sizeof(dict)/sizeof(dict[0]); */

   


    int arr[26];             //placeholder array for the no of occurences
    for(int i=0;i<26;i++){
        arr[i]=0;            //making it all 0 cos when we add +1, we actually add to some garbage value
    }

    int* occurence=top4(st,arr);     //array which has the no of occurence of each letter
    
    char max_occ[4];          //placeholder array for the 4 most repeated characters
    for(int i=0;i<4;i++){
        max_occ[i]=' ';         //same reason as above
    }
    char* max_boi=max_occurence(occurence,max_occ); //array which has the 4 most repeated characters
    /* for(int i=0;i<4;i++){
        cout<<max_occ[i]<<" ";
    } */
    
    //char the_deal[4]={'e','q','o','w'};

    char alphabets[26];       //array having the capital alphabets
    for(int i=0;i<26;i++){
        char ch=(char)(65+i);
        alphabets[i]=ch;
    }
    char null_key[2][26];
    bool stay=true;

    char* key;
    
    int count=0;

    do{        
        cout<<count<<" run"<<endl;
        count++;
        key=make_key(max_boi,null_key,alphabets);        //has the permutuation of the 4 imp at the positions of ETAI 
        //make the stuff for each of the key formed ->go for the kill
        stay=check(key,input_words,dict,word_count,lend);
        
        if(!stay){
            cout<<"NOT THE KEY!!"<<endl;
            cout<<endl;
        }
        else{
            cout<<"FOUND THE KEY!!"<<endl;
            cout<<endl;
        }

                    //HERE HERE HERE HERE
    }while(next_permutation(max_boi,max_boi+6) && !stay); 

    /* key=make_temp_key(null_key,alphabets);

    check(key,input_words,dict,word_count,lend); */
      
    if(stay){
        char* final_key=generate(key); //->using secret word enumeration to get the whole key if some letter is missing


        cout<<"THE FINAL KEY"<<endl;
        for(int i=0;i<2;i++){
            for(int j=0;j<26;j++){
                cout<<*(final_key+(i*26)+j)<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        
        cout<<"THE ENCODED TEXT"<<endl;
        for(int i=0;i<st.length();i++){
            if(int(st[i])==92){
                cout<<st[i];
                i++;
                cout<<st[i];
            }
            else{
                bool found=false;
                for(int j=0;j<26;j++){
                    if(*(final_key+26+j)==st[i]){
                        found=true;
                        cout<<*(final_key+j);
                }        
                }
                if(!found){
                    cout<<st[i];
                }
            }
        }  
        cout<<endl;  

    }
    else{
        cout<<endl;
        cout<<"FAIL CHECK"<<endl;
    } 
}


