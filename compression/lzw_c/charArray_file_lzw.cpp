#include <fstream>
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

char * comp(char * input, int & size)
{
  string s(input);
  std::vector<int> vout;
  
  //Compress it into a vector (vout)
  compress(s, std::back_inserter(vout));
  
  uint32_t * toNetwork = new uint32_t[vout.size()];
  
  //Convert the vector into a proper array of integers
  for(int i = 0; i < vout.size(); i++)
  {
    toNetwork[i] = htonl(vout[i]);
  }
  size=vout.size();
  return (char*) toNetwork;
}

char * decomp(char * input, int & size)
{
  int* in = (int*)input;
  //size/=4;
  string s;
  uint32_t * fromNetwork = new uint32_t[size];
  std::vector<int> vin(size);


  for(int i = 0; i < size; i++)
  {
    vin[i] = ntohl(in[i]);
  }

  string result = decompress(vin.begin(), vin.end());

  char* ret = new char[result.size()+1];
  
  strcpy(ret, result.c_str());

  return ret;
}

int main() 
{
  int charSize = 10000;

  string inputFilename = "../gamelogs/2.gamelog";
  string compressedOutputFilename = "../gamelogs/2.gamelog.lzw";
  string outputFilename = "../gamelogs/2.gamelog.run";
  
  ifstream fin;  
  ofstream fcout;    
  ofstream fout;
  
  fin.open(inputFilename.c_str());
  fcout.open(compressedOutputFilename.c_str());
  fout.open(outputFilename.c_str());
  
  char * temp1 = new char[charSize+1];
  
  std::cerr<<"charSize: " << charSize; 
  
  if(fin.good())
  {
    fin.getline(temp1, charSize);
  }
    std::cerr<<"charSize: " << charSize;
  char * temp2 = comp(temp1, charSize);
  std::cerr<<"charSize: " << charSize;
  if(fcout.good())
  {
    fcout.write(temp2, charSize);
  }
  std::cerr<<"charSize: " << charSize;
  char * temp3 = decomp(temp2, charSize);  
  std::cerr<<"charSize: " << charSize;
  if(fout.good())
  {
    fout.write(temp3, charSize);
  }
  std::cerr<<"charSize: " << charSize;
//  cout << endl << temp3 << endl;

  
  delete [] temp1;
  delete [] temp2;
  delete [] temp3;
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
