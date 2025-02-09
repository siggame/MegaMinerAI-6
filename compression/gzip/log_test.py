#compression with gzip
import gzip

inputTextFile = open('../gamelogs/140.gamelog', 'r')
inputString = inputTextFile.read()
inputTextFile.close()

outputCompressedFile = gzip.open('compressed_gamelogs/140.gamelog.gz', 'wb')
outputCompressedFile.write(inputString)
outputCompressedFile.close()

inputCompressedFile = gzip.open('compressed_gamelogs/140.gamelog.gz', 'rb')
decompressed_string = inputCompressedFile.read()
inputCompressedFile.close()

outputTextFile = open('compressed_gamelogs/140.gamelog', 'wb')
outputTextFile.write(decompressed_string)
outputTextFile.close()


