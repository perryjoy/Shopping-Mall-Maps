# Shopping-Mall-Maps 
  
## Rules:
  ### Commit & dashboard rules:   
  1) Use only english and past simple tense.
  2) Use Upper chars in the beginning.
  3) Single reason for commit.
  4) Use active voice
  5) Write at the end of the commit message string "AB#* ticket number *".
  
  Commit example: 
  ```C
  Created commit rules AB#30
  ```
  or      
  ```C
  Ball disappearing bug was fixed AB#12 
  ```
  That creates link to your commit in azure boards.

  ### Code rules: 
  *Discussion -> Code -> Test -> Review -> Done*     
  1) In 3 days before deadline must be test and review.     
  2) No "magic" numbers and constants in code. Everything must be in enums, defines or special variables.   
  3) Use global variables only after discussion.    

  ### Code style:    
  1) Every figure "{" must be on new string. 
 ```C
      void foo(int a)
      {
	      ...
      }
 ```
  2) Single if-else must be with " { ... }".     
 ```C
      void foo(int a)
      {
	      if(n>0)
        {
         ...
        }
        else
        {
        ...
        }
      }
 ```
  3) camelCase.     
 ```C
      void foo(int a)
      {
	      int maxNumber;
          double ballForceThrow;
      }
      
      void openFile()
      {
      ...
      }
 ```
  4) If function fits the screen, variables declares in the beginning, else in the place of use.    
  5) Insert spaces between operators and operands.
 ```C
      int x = (a + b) * c / d + foo();
 ```
 6) Each variable declaration on a new line.
  ```C
      int x = 3;
      int y = 7;
      double z = 4.25;
 ```
 7) When the line does not fit into the skrin, divide it into two, making a newline after the operator, and continue writing.
 ```C
   int result = reallyLongFunctionOne() + reallyLongFunctionTwo() + 
        reallyLongFunctionThree() + reallyLongFunctionFour();
 ```
 8) Leave blank lines between functions and between expression groups.
  ```C
   void foo() 
   {
    ...
   }
                          // Empty line
   void bar() 
   {
    ...
   }
 ```
## Compare with analogs:

### Galeria Saint-Petersburg(https://www.galeria.spb.ru/schema/):

*Minuses:*
1. Maps are located on the site. Inconvenient to use.
2. Under heavy load will lag.
3. Few people know.
4. Inconvenient scaling.

*Pluses:*
1. Separately allocated toilets, ATMs, discounts, taxi area.
2. Nicely built route.

### Scoreboard in the shopping center:

*Minuses:*
1. Hard to find.
2. Queues.
3. Lag.
4. If you have to visit many shops, it is inconvenient.

*Pluses:*
1. Located in every shopping center.

### Application "Shopping Guide":

*Minuses:*
1. No parking map.
2. Large icons if you do not zoom in.
3. It doesn't work offline.
4. Not supported at the moment(28.02.2021).
5. Only in Moscow.

*Pluses:*
1. Road map around.
2. Good route between floors.
3. Shows stocks.
4. Search for stores by requirements.

## Contributors:   
  Kirillova Arina   
  Karaev Yakov   
  Ignatiev Daniil   
  Kelarev Michal   
  Chepikov Ilya   
  Mozhaev Alexandr  


