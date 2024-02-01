# Protocol description

<b>Note:</b> in order everything to work `server` projct should be compiled first

## Workflow

-  Connect to the server socket which runs on the port `12345`
-  Send folder name you want to work with on the server (using sendChunkData)
-  Send number of the command you want to use to the server (length of the data must be 4 bytes)
-  Close connection

## Availble commands

<b>Note:</b> command number is in the parentheses<br>

`Every sent filename should contain an extension, e.g. test.txt !`

### Exit (0)

Stops the server.

### GET \<filename> (1)

Request a specific file from the server.

-  Send name of the file you want to get from the server storage (using sendChunkData)
-  Save chunked data from the server to the file (using receiveChunkedDataToFile)

### LIST (2)

Get list of available files on the server.

-  Receive string with the filenames separated by space (e.g "test.txt server.txt last.txt"). To receive use receiveChunkedData function

### PUT \<filename> (3)

Upload a file to the server storage.

-  Send name of the file you want uploaded file to be called on the server (using sendChunkedData)
-  Send file content in the chunked format (using sendFileUsingChunks)
-  Receive confirmation from the server (using receiveChunkedData)

### DELETE \<filename> (4)

Request the server to delete a specific file.

-  Send filename to delete from the server (using sendChunkedData)
-  Receive confirmation from the server (using receiveChunkedData)

### INFO \<filename> (5)

Retrieve information about a specific file from the server.

-  Send filename to get info about from the server (using sendChunkedData)
-  Receive string with file info which will be in the next format: File size;Created at;Last modified (using receiveChunkedData)
  
## Functions to work with data
`All implementations you can see in the FileTransferTCP-Client/DataStreamer.cpp`

### receiveChunkedData:
- receive integer (4 bytes) from the server which is total size of the data
- receive integer (4 bytes) from the server which is chunk size
- while total received bytes is less than total size receive char array with size of chunk

### receiveChunkedDataToFile:
- receive integer (4 bytes) from the server which is total size of the data
- while total received bytes is less than total size:
  1. receive integer (4 bytes) from the server which is chunk size
  2. receive char array with size of chunk
  3. append that data to file

### sendFileUsingChunks:
- send total size of the data (size of long long, 8 bytes)
- while total sent less than total size:
  1. send chunk size (size of long long, 8 bytes)
  2. take size of chunk bytes data from the file and send it to the server

### sendChunkedData:
- send total size of the data (size of integer, 4 bytes)
- send chunk size (size of integer, 4 bytes)
- while total sent less than total size send size of chunk bytes of the data

## Sequence diagram

![file_transfer_sequence_diagram](https://github.com/danylo-gavrylovskyi/File-Transfer-TCP/assets/118884527/a3a4e056-a7a5-4354-935c-55bcc0b6c1bf)

## Use case diagram

![file_transfer_usecase_diagram](https://github.com/danylo-gavrylovskyi/File-Transfer-TCP/assets/118884527/f54d0510-1edf-4a88-9e72-7aa0552f39a4)

