# World's Best Graphing Calculator
 
 > Authors: \<[Edward Xia](https://github.com/dfire42), [Justin Pham](https://github.com/pjsrcool), [Phoenix Winter](https://github.com/PhoenixWinter542)\>

## Project Description
We decide on coding a graphing calculator because we all hate using our own calculators. It does not have the processing power. To implement this graphing calculator, we plan to use c++ and Qt Creator for c++. We will also use middle school level algebra.
* [qt](https://www.qt.io/) - C++ IDE GUI toolkit

Main Features:
* - Graph an equation
    - x<sup>1</sup>
    - x<sup>2</sup>
- Hold multiple equations
- Display multiple equations simultaneously
- Simplify equations automatically
- GUI based interface
- Input: linear or quadratic equation
- Output: visual graph of the equation

Proposed Features:
* Multiple variable functions
* Higher exponents
* Logarithmic support
* Display Points on mouseover
* Zoom to rescale the graph
* Restrict the range of an equation

Design Patterns
* Strategy:
  - We are using the strategy pattern for the equation interpreter, as we plan to develop several algorithms based on the type of function given by the user.
  - There will be an interpreter algorithm for each type of equation we support.
  - This makes interpreting the user input much simpler than having a large function inside the input class.

* Factory:
  - We are using factory pattern because we need to avoid  baving to interpret the equation outside the interpreter
  - This factory creates the strategy needed to solve each type of equation
  - This helps us adheir to the single responsibility principle

* Mediator:
  - We will be implementing the mediator pattern in our user interface and the way it interacts with the backend.
  - By consolidating the control system to a single class, we can ensure there is no redundant code, or even different implementations of the same thing.
  - It makes it easier to add the functionality we want to do if we have the extra time.
  - Allows us to ensure functions are called in the proper order.


## Class Diagram
 Strategy
 ![Alt text](Strategy_Interpret_User_Input.jpeg?raw=true "Strategy")
 Factory
 ![Alt text](Factory_Interpreter.jpeg?raw=true "Factory")
 Mediator
 ![Alt text](Mediator_GUI.jpeg?raw=true "Mediator")

 ## Screenshots
 ![Alt text](Screenshot1.png?raw=true "one")
 ![Alt text](Screenshot2.png?raw=true "two")
 ![Alt text](Screenshot3.png?raw=true "three")
 ## Installation/Usage
 Linux:
* Dowload the Linux executable
* Run from commandline using "./Graphing_Calculator"

Windows:
* Dowload the Windows execuatable
* Double click the Graphing_Calculator.exe

Usage:
* Type in an expression in the form "y = "
* Hit 'Enter' or click "Graph"
* Previous equations from the current session are found in the dropdown menu
* Click "Delete" to delete the currently shown equation

 ## Testing 
Testing was done using unit tests via Google Test framwork. All individual components were tested in this way. Only gui elements were not directly tested.