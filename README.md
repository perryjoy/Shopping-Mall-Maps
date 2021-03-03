# Shopping-Mall-Maps 

## Product description (RU/EN):
  ### EN

  #### AllMall Mobile App

>  The application allows you to navigate through malls, providing the user with an interactive map of the building, the
>  ability to search for a mall object by name, the ability to plot a route between two selected points.
>  AllMall allows you to aggregate the maps of many malls with a single app.

  #### USER SIDE

  ##### Artifacts provided:
>  - AllMall mobile app for Android platform

  ##### Functionality:
>  - selecting a mall from the list
>    - interactive floor plan of the selected mall
>    - on-tap selection of the object
>    - information about the selected object over the map
>  - searching for an object inside the mall by its title
>    - found object is highlighted
>  - route between two objects
>    - setting the selected object as the start/end point of the route

  ##### Technical requirements:
>  - access to the Internet at the moment when the user is choosing a mall

  #### MALL REPRESENTATIVES SIDE

  ##### Artifacts provided:
>  - the plan of the mall, each object on which is marked with a unique tag (SVG / PDF format)

  ##### Functionality:
   _NB: at this stage, the functionality is provided outside the application interface_
>  - updating titles/descriptions of objects
>  - intuitive interface: changes are made to the table with the columns \<object tag> \<object title> \<object description> ...

  ##### Requirements:
>  - provision of an up-to-date plan of the mall premises
>  - maintaining up-to-date information about shopping center facilities
_________________________________________________________________________________
 ### RU

  #### Мобильное приложение AllMall

>  Приложение позволяет ориентироваться в торговых центрах, предоставляя пользователю интерактивную карту здания,
>  возможность поиска объекта ТЦ по названию, возможность проложить маршрут между двумя выбранными точками.
>  Приложение позволяет агрегировать карты многих ТЦ в одной сущности.


  #### НА СТОРОНЕ ПОЛЬЗОВАТЕЛЯ

  ##### Предоставляемые артефакты:
>  - мобильное приложение AllMall для платформы Android

  ##### Функциональность:
>  - выбор ТЦ из списка
>  - интерактивный поэтажный план выбранного ТЦ
>    - выделение объекта тапом
>    - информация о выделеном объекте поверх карты
>  - поиск объекта внутри ТЦ по названию
>    - выбранный объект выделяется
>  - маршрут между двумя объектами
>    - возможность выбрать выделенный объект как начальную/конечную точку маршрута

  ##### Требования:
>  - доступ к сети интернет на момент выбора ТЦ

  #### НА СТОРОНЕ ПРЕДСТАВИТЕЛЕЙ ТЦ

  ##### Предоставляемые артефакты:
>  - план ТЦ, каждый объект на котором, отмечен уникальным тегом (формат SVG / PDF)
  
  ##### Функциональность:
  _NB: на данном этапе функциональность предоставляется вне интерфейса приложения_
>  - обновление названий/описаний объектов
>  - "интуитивный" интерфейс: изменения вносятся в таблицу со столбцами <тег объекта> <название объекта> <описание объекта> ...

  ##### Требования:
>  - предоставление актуального плана помещений ТЦ
>  - поддержание актуальной информации об объектах ТЦ


## Rules:
  ### Commit & dashboard rules:   
  1) Use only english and past simple tense.
  2) Use Upper chars in the beginning.
  3) Single reason for commit.
  4) Use active voice
  5) Write at the end of the commit message string `AB#* ticket number *`.
  
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
  3) Use global variables only after team discussion.    

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
  3) Naming.
  *	camelCase for: local variables, class members
  *	PascalCase for: functions
  *	snake_case for: data types (except types declared in the libraries used)
  *	UPPER_CASE for: global constants, enumerations elements, macro constants
 ```C
      const float PI_CONSTANT = 3.1415926;
      
      class my_class
      {
          int memberData;
	 	 void ProcessData();
      };
      
      void Foo(int a)
      {
		 int maxNumber;
          double ballForceThrow;
      }
      
      void OpenFile()
      {
      ...
      }
 ```
  4) Indentation
  *	Use only spaces, 4 spaces
  *	Any inner block must be indented, '{' must has same indentation as outer block
  *	Data access specifiers ("public", "protected", "private") has same indentation as class
  *	"case" markers has same indentation as "switch" block
  ```C
  class my_class
  {
  public:
      void ProcessData()
      {
          switch (memberData)
          {
          case 0:
              memberData++;
              break;
          case 1:
              memberData--;
              break;
          case 2:
              printf("Error");
              break;
          }
      }
  private:
      int memberData;
  };
  ```
  5) If function fits the screen, variables declares in the beginning, else in the place of use. 
  6) Insert spaces between operators and operands.
 ```C
      int x = (a + b) * c / d + foo();
 ```
 7) Each variable declaration on a new line.
  ```C
      int x = 3;
      int y = 7;
      double z = 4.25;
 ```
 8) When the line gets longer than 100 characters, divide it into two, making a newline after the operator, and continue writing.
 ```C
   int result = reallyLongFunctionOne() + reallyLongFunctionTwo() + 
        reallyLongFunctionThree() + reallyLongFunctionFour();
 ```
 9) Leave blank lines between functions and between expression groups.
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

## Git workflow

### Main Branch

`Main` is always an up-to-date copy of the existing code in production. No one, including the technical manager, should make changes directly to this branch, as this will directly affect the working product.
All the code is actually written in other branches.

### Develop branch

When starting a project, the first step is to create a `develop` branch for it based on `main`. All the code related to this project should be located here. A `develop` branch is a regular Git branch with the `develop`  prefix.

### Feature Branch

For each new component or functionality, a separate `feature` branch is created, which differs from the usual one only by the `feature`  prefix. This ensures independent development.
When you finish working on the component, you need to send its code from the `feature` branch to the `develop` branch. You need to make a pull request.

### Pull request

A developer cannot directly submit their changes to the `develop` branch. First, they should be checked by the technical manager. This is what pool queries are designed for. After verification, the technical manager must merge this branch with the `develop` branch

### The code conflicts

Let's say that the `develop` branch already contains new code written by the first developer, and if the second developer sends a pool request from its `feature` branch to the `develop` branch, conflicts arise. They should be solved by the reviewer of the request or an experienced developer.
Thus, code conflicts can be resolved by the reviewer of the pool request or by the developer himself in the `feature` branch.

### Bugs

To fix bugs, create a new `feature` branch.

### Main again

When the project is completed, the code from the `develop` branch is merged with `main` and deployed to production. Thus, the working product and the `main` code are the same thing.

## Contributors:   
  Kirillova Arina   
  Karaev Yakov   
  Ignatiev Daniil   
  Kelarev Michal   
  Chepikov Ilya   
  Mozhaev Alexandr  


