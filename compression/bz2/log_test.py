import bz2

inputTextFile = open('../gamelogs/140.gamelog', 'r')
inputString = inputTextFile.read()
inputTextFile.close()

compressed_string = bz2.compress(inputString)

outputCompressedFile = open('compressed_gamelogs/140.gamelog.bz2', 'w')
outputCompressedFile.write(compressed_string)
outputCompressedFile.close()

inputCompressedFile = open('compressed_gamelogs/140.gamelog.bz2', 'r')

string_to_decompress = inputCompressedFile.read()

decompressed_string = bz2.decompress(string_to_decompress)
inputCompressedFile.close()

outputTextFile = open('compressed_gamelogs/140.gamelog', 'w')
outputTextFile.write(decompressed_string)
outputTextFile.close()


