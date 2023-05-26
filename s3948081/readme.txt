Information for compiling and running the program.
To run this program type:
./ppd <stockfile> <coinfile> <m3>
Where <stockfile> and <coinfile> are two valid files in the expected format and <m3> is a boolean value that decides what configuration the program is in 

For example to run the un modified version run: 
./ppd stock.dat coins.dat false 
Other wise to run the modified version run:
./ppd stock_new.sav coins.dat true

The modified version of code uses a new file format which follows the following pattern:
stock_new.sav:
	I0001|Name|Description|Price|Quantity|Item Options
	I0002|Name|Description|Price|Quantity|Item Options

Where item options are a list of possible item options, where each item is seperated by a comma.
However the program will work with the orginal file format. 


Testing was done using a shell file, to run the tests ./test.sh will run each test. Results are stored in the relevant spreadsheet
