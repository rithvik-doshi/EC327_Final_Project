# Calculator App

## Scope

This application will allow you to perform several mathematical operations that applications such as MATLAB allow you to do, minus a subscription and coding
experience. The app is split into three compnents:

1. Pemdas: Allows you to evaluate simple calculations involving the operands '\+', '\-', '\*', '/', '^', and '()'.  
	a. 8\*8 --> 64  
	b. 7^3 --> 343  
	c. 9\+(7/3\+5) --> 16.333333  
	d. 88\-64\+23\-45\+101 --> 103  
2. Graph: Allows you to plot points from an input file and find the line of best fit according to preference.
	Testing:
	a. Make sure that your csv file is included in the current directory. We have included the file 'Data.csv' for you to get started.
	b. Set the x-axis bounds as you wish. Try -15 and 15 to get started.
	c. Select the type of curve fit you wish to implement, or none if you don't wish to curve fit.
3. Matrix: Allows you to conduct various matrix operations between two matrices of your choosing.

## Usage

Many institutions, corportations, students and professors alike will come across data they need to
analyze via graphs and tables. Applications like MATLAB that allow you to do these operations with ease
are costly, and what we're trying to do is bring the main essense of data analysis into a simple app.

## How To Run

1. Make sure your current directory includes the main file "UImain.cpp", dependencies "pemdas.cpp", "Best_Fit.h", "Matrix.h", & "Makefile" and this specific font file is downloaded and in this directory:
	/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf
2. In a terminal window, run the command:
```
make uimain
```
3. Run the resulting executable:
```
./uimain
```



