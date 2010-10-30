#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <stdint.h>
#include <arpa/inet.h>
using namespace std;

/*
char[] intVectorToCharArray(const std::vector<int> v)
{
  char[v.size()] charArray
  
  for(Iterator i = v.begin(); i != v.end(); i++)
  {
    charArray[i] = (char)v[i];
  }
  return charArray;
}
*/



// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.
template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<std::string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[std::string(1, i)] = i;
 
  std::string w;
  for (std::string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    std::string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];
      // Add wc to the dictionary.
      dictionary[wc] = dictSize++;
      w = std::string(1, c);
    }
  }
 
  // Output the code for w.
  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}
 
// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<int,std::string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = std::string(1, i);
 
  std::string w(1, *begin++);
  std::string result = w;
  std::string entry;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";
 
    result += entry;
 
    // Add w+entry[0] to the dictionary.
    dictionary[dictSize++] = w + entry[0];
 
    w = entry;
  }
  return result;
}

char * comp(char * input)
{
  string s(input);
  std::vector<int> vout;
  
  //Compress it into a vector (vout)
  compress(s, std::back_inserter(vout));
  
  uint32_t * toNetwork = new uint32_t[vout.size()+1];
  
  //Convert the vector into a proper array of integers
  for(int i = 0; i < vout.size(); i++)
  {
    toNetwork[i] = htonl(vout[i]);
  }
  
  toNetwork[vout.size()] = 0;//Null character at the end for the cast to c-string
  
  return (char*) toNetwork;
}
/*
char * decomp(char * output)
{
}
*/
int main() 
{
  string consoleString;

  cout <<"Input a string to get it back: "<< endl;
  cin >> consoleString;

  char * main = new char[consoleString.size()+1];
  
  strcpy(main, consoleString.c_str());

   

  cout << endl << main << endl;
  
  delete [] main;
/*
  std::vector<int> compressed;
  compress("TOBEORNOTTOBEORTOBEORNOT", std::back_inserter(compressed));
  copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
  std::string decompressed = decompress(compressed.begin(), compressed.end());
  std::cout << decompressed << std::endl;
 */
  return 0;
}
