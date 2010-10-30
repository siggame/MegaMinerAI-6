#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <stdint.h>
#include <arpa/inet.h>
#include <cmath>
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

int comp(char* input, char*&output)
//char * comp(char * input, int & size)
{
  string s(input);
  std::vector<uint32_t> vout;
  
  //Compress it into a vector (vout)
  compress(s, std::back_inserter(vout));
  
  uint32_t * toNetwork = new uint32_t[vout.size()];
  
  //Convert the vector into a proper array of integers
  for(int i = 0; i < vout.size(); i++)
  {
    toNetwork[i] = htonl(vout[i]);
    //cout<<toNetwork[i]<<endl;
  }
  output = (char*) toNetwork;
  //std::cerr<<vout.size()<<std::endl;
  return vout.size()*4;
}

int decomp(char* input, int inputSize, char*& output)
//char * decomp(char * input, int & size)
{
  uint32_t* in = (uint32_t*)input;
  // converts the size down
  inputSize=ceil(inputSize/4.0);
  //cout<<"New size: "<<inputSize<<endl;
  std::vector<uint32_t> vin(inputSize);

  for(int i = 0; i < inputSize; i++)
  {
    //cout<<i<<endl;
    //vin[i]=0;
    //cout<<ntohl(in[i])<<endl;
    vin[i] = ntohl(in[i]);
    //cout<<i<<endl;
  }
  //cout<<"After for"<<endl;
  string result = decompress(vin.begin(), vin.end());
  //cout<<"After decomp"<<endl;
  output = new char[result.size()+1];
  //cout<<"About to copy"<<endl;
  strcpy(output, result.c_str());
  //cout<<"Copied"<<endl;
  return result.size()+1;
}

int main(int argc, char* argv[]) 
{
  if(argc<2)
  {
    cout<<"Give me a game log!"<<endl;
    return 1;
  }
  int inputSize=600000;

  string inputFilename = argv[1];
  string preFilename = "gamelog.pre";
  string compressedOutputFilename = "gamelog.lzw";
  string outputFilename = "gamelog.pst";
  
  ifstream fin;
  ofstream pre;
  ofstream fcout;    
  ofstream fout;
  
  pre.open(preFilename.c_str());
  fin.open(inputFilename.c_str());
  fcout.open(compressedOutputFilename.c_str());
  fout.open(outputFilename.c_str());
  
  char * input = new char[inputSize];
  char * compressed, *decompressed;
  
  //std::cerr<<"inputSize: " << inputSize <<endl;
  
  if(fin.good())
  {
    fin.getline(input, inputSize);
  }

  pre.write(input,inputSize);
  int compressedSize = comp(input, compressed);
  //std::cerr<<"Compressed size: "<<compressedSize<<endl;
  for(int i=0;i<compressedSize;i++)
  {
    //cout<<(int)(compressed[i])<<endl;
  }
 // cin.get();
  if(fcout.good())
  {
    fcout.write(compressed, compressedSize);
  }

  int decompressedSize = decomp(compressed, compressedSize, decompressed);
  if(decompressedSize != inputSize)
  {
    cout<<"Not equal size from beginning to end!"<<endl;
  } 
  //std::cerr<<"Decompressed size: "<<decompressedSize<<endl;
  cout<<"Ratio: "<<1.0*compressedSize/decompressedSize<<endl;
  if(fout.good())
  {
    fout.write(decompressed, decompressedSize);
  }

  delete [] input;
  delete [] compressed;
  delete [] decompressed;

  return 0;
}
