# Protocol description

<b>Note:</b> in order everything to work `server` projct should be compiled first

## Workflow

-  Connect to the server socket which runs on the port `12345`
-  Send number of the command you want to use to the server
-  Close connection

## Availble commands

<b>Note:</b> command number is in the parentheses <br>

`Every sent filename should contain an extension, e.g. test.txt !`

### Exit (0)

Stops the server.

### GET \<filename> (1)

Request a specific file from the server.

-  Send name of the file you want to get from the server storage
-  Receive chunked data from the server

### LIST (2)

Get list of available files on the server.

-  Receive string with the filenames separated by space (e.g "test.txt server.txt last.txt")

### PUT \<filename> (3)

Upload a file to the server storage.

-  Send name of the file you want uploaded file to be called on the server
-  Send file content in the chunked format
-  Receive confirmation from the server

### DELETE \<filename> (4)

Request the server to delete a specific file.

-  Send filename to delete from the server
-  Receive confirmation from the server

### INFO \<filename> (5)

Retrieve information about a specific file from the server.

-  Send filename to get info about from the server
-  Receive string with file info which will be in the next format: File size;Created at;Last modified
