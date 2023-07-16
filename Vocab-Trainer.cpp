#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

vector<string> loadTxtFile(string textFile){
    ifstream in(textFile);
    string str;
    vector<string> newVector;
    
    while(getline(in, str)){
	if(str.size() > 0)    
		newVector.push_back(str);
    }
    return newVector;
}

void saveVoc(string fileName, vector<string> myVector){

    
    ofstream output_file(fileName);
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(myVector.begin(), myVector.end(), output_iterator);
    
}

int main() {
    
    vector<string> voc_german = loadTxtFile("voc_german.txt");
    vector<string> voc_latin = loadTxtFile("voc_latin.txt");
    
    cout<<"Language-Trainer\nPlease select: \n";
    cout<<"(1) Add new vocab\n";
    cout<<"(2) Start vocabtest\n";
    int option;
    cin >> option;
   
    int x = 1;
    if(option==1){
        while (x==1){
        cout<<"Translation: (English, spaces as underscores!)\n";
        string german_word;
        string latin_word;
        cin >> german_word;
        cout<<"Vocab: ";
        cin >> latin_word;
        int y_n;
        cout<< latin_word + " means: " + german_word + ". Right? 1 (y) / 0 (n)\n";
        cin>>y_n;
        if(y_n == 1){
            //save Vocabs in vector:
            voc_german.push_back(german_word);
            voc_latin.push_back(latin_word);
            
            saveVoc("./voc_german.txt", voc_german);
            saveVoc("./voc_latin.txt", voc_latin);
            
            cout<<"Successfully added!\n";
            cout<<"Currently saved Vocabs: " + to_string(voc_german.size());
            
            cout<<"\n\n\nAdd more Vocabs?\n";
            cout<<"(1) yes\n(2) no\n";
            cin>>x;
            
        }
        }cout<<"Please restart the program to continue.";
        
    }else{
        cout<<"Starting test...\n\nUnderscores instead of spaces \nAnswer 000 to stop and get the evaluation!\n\n";
        cout<<"(Default 20) How many vocabs to you want to practise: ";
        int howmany = 20;
        int counter = 1;
        cin>>howmany;
        int richtig = 0;
        int falsch = 0;
        
        while (counter <=howmany){
        
        cout<<"\n";
        int random = rand() % voc_latin.size();
        string sel_elem = voc_latin[random];
        string sel_trans = voc_german[random];
        
        cout<<"Translate the following word: " + sel_elem + "\n";
        
        string userInput;
        cin>> userInput;
        if(userInput == sel_trans){
        	cout<<"\nCORRECT!\n\n";
        	richtig++;
        	
        }if(userInput == "000"){
        	cout<<"\n\nEvaluation:\n\n";
        	cout<<to_string(richtig) + " answer(s) was/were correct!\n";
        	cout<<to_string(falsch) + " answer(s) was/were wrong!\n";
        	return 0;
        
        }if(userInput != sel_trans){
        	cout<<"\nWRONG!     CORRECT Translation: "+ sel_trans + "\n\n";
        	falsch++;
        }
        
        counter++;
        }
        
        cout<<"\n\nEvaluation:\n\n";
        cout<< to_string(richtig) + "answer(s) was/were correct!\n";
        cout<< to_string(falsch) + "answer(s) was/were wrong!\n";
        return 0;
        
    }
        
    return 0;
}

