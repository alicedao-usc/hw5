// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::set<std::string> wordleHelper(const std::string& in,
    const std::string& floating, int numDashes, std::set<std::string>& possibleWords);

std::set<std::string> checkValid(std::set<std::string>& possibleWords,
    const std::set<std::string>& dict);
		

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{

    // Add your code here
	
    std::set<std::string> possibleWords;
    std::set<std::string> validWords;

	int numDashes = (int)count(in.begin(), in.end(), '-');

	wordleHelper(in, floating, numDashes, possibleWords);
	validWords = checkValid(possibleWords, dict); 
	
	return validWords;

}
// Define any helper functions here


std::set<std::string> wordleHelper(const std::string& in,
    const std::string& floating,
		int numDashes,
        std::set<std::string>& possibleWords
  ){
	
	if(numDashes <= 0){
		possibleWords.insert(in);
	}

    else if(floating.length() != 0){
        for(unsigned int i = 0; i < in.length(); i++){
					  string temp = in;

            if(temp[i] == '-' && numDashes >= (int)floating.length()){
                for(unsigned int s = 0; s < floating.length(); s++){
                    temp = in;
                    temp[i] = floating[s];
                    string tempF = floating;
                    tempF.erase(s, 1);
                    wordleHelper(temp, tempF, numDashes -1, possibleWords);
                }
            }
        }
                
    }

    else{
        for(unsigned int i = 0; i < in.length(); i++){
            string temp = in;
            if(temp[i] == '-'){
                std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
                for(char c : alphabet){
                    string temp = in;
                    temp[i] = c;
                    wordleHelper(temp, floating, numDashes-1, possibleWords);
                }

            }
        }
    }
	return possibleWords;
	
}

std::set<std::string> checkValid(std::set<std::string>& possibleWords,
  const std::set<std::string>& dict){

	std::set<std::string> validWords;

	for(std::set<std::string>::iterator it = possibleWords.begin(); it != possibleWords.end(); it++ ){
		if(dict.find(*it) != dict.end()){
				validWords.insert(*it);
			}
	}

	return validWords;

}
