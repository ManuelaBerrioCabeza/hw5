#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
int countLetters(const string& str, char c);
void wordleHelper(string curr, string floating, const set<string>& dict, set<string>& results, unsigned int idx);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set <string> results;
    wordleHelper(in, floating, dict, results, 0);
    return results;

}

// Define any helper functions here
int countLetters(const string& str, char c){
  int cnt = 0;
  for(unsigned int i =0; i<str.size(); ++i){
    if(str[i] == c){
      cnt++;
    }
  }
  return cnt;

}
void wordleHelper(string curr, string floating, const set<string>& dict, set<string>& results, unsigned int idx){
  if(idx == curr.size()){
    if(dict.count(curr) > 0 && floating.empty()){
      results.insert(curr);
    }
    return;
  }

  if(curr[idx] !='-'){
    wordleHelper(curr, floating, dict, results, idx+1);
    return;
  }

  for(char c = 'a'; c<='z'; ++c){
    curr[idx] = c;
    bool isFloating = false;
    for(unsigned int i = 0; i<floating.size();++i){
      if(floating[i]==c){
        string update = floating;
        update.erase(i,1);
        wordleHelper(curr, update, dict, results, idx+1);
        isFloating=true;
        break;
      }
    }
    if(!isFloating){
      int blanksLeft = countLetters(curr.substr(idx),'-');
      if(blanksLeft >=(int)floating.size()){
        wordleHelper(curr, floating, dict, results, idx+1);
      }
    }
  }
}


