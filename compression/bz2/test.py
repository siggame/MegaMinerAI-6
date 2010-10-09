import bz2

inputTextFile = open('text.txt', 'r')
inputString = inputTextFile.read()
inputTextFile.close()

compressed_string = bz2.compress(inputString)

outputCompressedFile = open('test.bz2', 'w')
outputCompressedFile.write(compressed_string)
outputCompressedFile.close()

inputCompressedFile = open('test.bz2', 'r')

string_to_decompress = inputCompressedFile.read()

decompressed_string = bz2.decompress(string_to_decompress)
inputCompressedFile.close()

outputTextFile = open('text2.txt', 'w')
outputTextFile.write(decompressed_string)
outputTextFile.close()


