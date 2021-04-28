# Calculator App

## Scope

This application will allow you to perform several mathematical operations that applications such as MATLAB allow you to do, minus a subscription and coding
experience. The app is split into three compnents:

1. Pemdas: Allows you to evaluate simple calculations involving the operands '+', '-', '*', '/', '^', and '()'.
2. Graph: Allows you to plot points from an input file and find the line of best fit according to preference.
3. Matrix: Allows you to conduct various matrix operations between two matrices of your choosing.

## Usage

Many institutions, corportations, students and professors alike will come across data they need to
analyze via graphs and tables. Applications like MATLAB that allow you to do these operations with ease
are costly, and what we're trying to do is bring the main essense of data analysis into a simple app.

## How To Run

1. Make sure your current directory includes the dependencies "pemdas.cpp", "Best_Fit.h", "Matrix.h", & "Makefile" and this specific font file is downloaded and in this directory:
	/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf
2. In a terminal window, run the command:
```
make uimain
```
3. Run the resulting executable:
```
./uimain
```


## Known Bugs
- Inverse Matrices for 3x3 matrices and above
- Co-factoring for 3x3 matrices and above 
- No error-checking for invalid statements in pemdas.cpp, such as "*+28-3", statements involving negative answers such as '9-19', and dividing by zero.

## Changelogs
- 4/22/21 BETA 0.1 basic Matrix functions and 2x2 inverses
