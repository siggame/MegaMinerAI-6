#compression with gzip
import zlib

inputTextFile = open('../gamelogs/140.gamelog', 'r')
inputString = inputTextFile.read()
inputTextFile.close()

outputCompressedFile = open('compressed_gamelogs/140.gamelog.zlib', 'wb')
out_file = zlib.compress(inputString)
outputCompressedFile.write(out_file)
outputCompressedFile.close()

inputCompressedFile = open('compressed_gamelogs/140.gamelog.zlib', 'rb')
in_file = inputCompressedFile.read()
decompressed_string = zlib.decompress(in_file)
inputCompressedFile.close()

outputTextFile = open('compressed_gamelogs/140.gamelog', 'wb')
outputTextFile.write(decompressed_string)
outputTextFile.close()


