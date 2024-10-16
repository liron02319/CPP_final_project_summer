<p align="center">
  <img src="https://cdn-media.sforum.vn/storage/app/media/wp-content/uploads/2023/05/tai-monopoly.jpg" alt="monopoly_logo" style="width:450px; height:300px;" align="right">
</p>


# Monopoly Game Project

This project is a C++ implementation of a Monopoly-like game with a graphical interface using SFML (Simple and Fast Multimedia Library).
for more details about SFML GUI - https://www.sfml-dev.org/tutorials/2.6/
The project was developed as a university project and provides a basic simulation of the classic Monopoly game, including players, properties, dice rolls, and gvarious game actions.

## Table of Contents

- [Project Description](#project-description)
- [How to Run the Project](#how-to-Run-the-Project)
- [The Game GUI SFML](#The-Game-GUI-SFML)
    - [Opening Game](#Opening-Game)
    - [The Menu In Game](#the-Menu-In-game)
    - [The Game Board](#The-Game-Board)
    - [Your Turn](#Your-Turn)
    - [How To Roll And Build](#How-To-Roll-And-Build)
    - [Slot Message](#Slot-Message)
      
- [Classes In Project](#Classes-In-Project)
- [Rules](#Rules)

  
![monopoli1](https://github.com/user-attachments/assets/3aabdda5-5f17-4adf-8f5a-56cf35fdd524)


## Project Description

The final project is a version of the familiar and well-known game "Monopoly". Monopoly is a board game that contains 2-8 players and is based on the business world. In this project you will realize a version of the game intended for 2 to 8 players playing through the same computer.
The project is a C++ implementation of a Monopoly-like game with a graphical interface using SFML (Simple and Fast Multimedia Library)


## How to Run the Project

To run the project, you'll need linux. 

1. **Requirements**:
   - Install [SFML 2.6.1](https://www.sfml-dev.org/download.php).
   - A C++ compiler g++.
   - CMake for building the project(makefile).

2. **Building the Project**:
   - Clone the repository:
     ```
     git clone https://github.com/liron02319/CPP_final_project_summer.git

     ```
   - Move to the project directory:
     ```
     cd CPP_final_project_summer-main
     ```
   - Build the project using CMake:
     ```
     make all
     ```
   - Run the executable:
     ```
     ./MonopolyGame
     ```
   

    
## The Game GUI SFML

### Opening Game

In The Opening Of The Game there are 3 Buttons
- Play
- Rules
- Exit

![readmeOpenning](https://github.com/user-attachments/assets/40a2536e-fd11-4a9b-a7fb-28dd1420037a)


### The Menu In Game
In The Menu Of The Game ,The User need to enter a number(how much players in game)

![enternumberplayers](https://github.com/user-attachments/assets/e571404c-d6fe-4a67-9c12-a537a94c7cc8)

After that, To Give The Players Names(each player)

![entername](https://github.com/user-attachments/assets/6dad0670-f32f-48ec-a0ea-9cd92b82230b)


### The Game Board

![boardgame](https://github.com/user-attachments/assets/a9c4bc4f-0aac-47fe-ac8f-46709f270d37)


### Your Turn

When your Name Will be In Color Yellow And Your Token Will be In Silver Color Its your turn

![yourturn1](https://github.com/user-attachments/assets/6cac633f-6c5b-4075-ae9f-973472b7295a)

When your Name Will Not be In Color Yellow And Your Token Will be In Gold Color Its NOT your turn

![notyourturn](https://github.com/user-attachments/assets/ea1f6168-a6c4-4fc0-911c-41c92b47b83f)



### How To Roll And Build

To Roll the Dice ,the player need to press on Roll button

![rolldice](https://github.com/user-attachments/assets/75a9cf75-fa70-4c9a-9aff-067e9f101e9d)

To Build a House ,the player need to press on Build button(only according the rules)

![build](https://github.com/user-attachments/assets/4e5b11bc-8462-484e-871a-9e8bccf98fd0)


### Slot Message

If The Player roll the dice and stand on slot(that he can buy) 
will pop up the player the choice YES/NO


![message](https://github.com/user-attachments/assets/d2cb9d38-26e6-447a-ba3d-e24251a4c429)


### Classes In Project
<pre>

 Dice.cpp
 Button.cpp
 Player.cpp
 Slot.cpp
 Openning.cpp
 Menu.cpp
 Main.cpp
 Game.cpp
 CreateSlot.cpp
 Chance_handling.cpp
  
  
 
  
</pre>


## Rules
-You Can Read The Rules(English) [Here](https://github.com/liron02319/CPP_final_project_summer/wiki/Rules-Game-Monopoly)

-or below:



# פרויקט גמר - מונופול
פרויקט הגמר הוא גרסה של המשחק המוכר והידוע "מונופול".
מונופול הוא משחק לוח המכיל 2-8 שחקנים ומבוסס על עולם העסקים.
בפרויקט הזה אתם תממשו גרסה של המשחק המיועדת ל-2 עד 8 שחקנים המשחקים דרך אותו המחשב.
## חוקי המשחק
המשחק מורכב מלוח המכיל 40 משבצות המקיפות אותו, כל משבצת יכולה לייצג רחוב, קווי רכבת, משבצות מיוחדות ועוד. בהמשך נפרט על סוגי המשבצות השונים.

### משבצות הלוח
כידוע, הלוח מחולק ל-40 משבצות שונות כאשר בכל משבצת השחקן יכול לבצע פעולות שונות. עליכם לבנות לוח דינאמי המאפשר הוספה של משבצות נוספות למשחק. הפורמט המבוקש הוא לפי הלוח הבא: https://shorturl.at/T3HfV
#### רחובות
משבצת הרחוב שייכת לקבוצת צבע כלשהי מתוך 8 קבוצות צבע אפשריות. לכל רחוב יש שם, מחיר, עלות שכירות, מחיר בית ומחיר שכירות עם בית וגם מחיר שכירות עם מלון. שחקן יכול לבנות בית ברחוב כלשהו רק אם הוא מחזיק בכל הרחובות השייכים לאותה קבוצת הצבע. כאשר שחקן נוחת ברחוב השייך לשחקן אחר הוא מחוייב לשלם לו שכירות לפי מה שבנוי באותו הרחוב - אם הרחוב ריק (כלומר ללא בית) השחקן ישלם את מחיר השכירות של אותו הרחוב אבל אם הרחוב מכיל בית השחקן ישלם את השכירות לפי החוקים הבאים: דמי השכירות גדלים פי 2 עם כל בית נוסף. כלומר דמי השכירות הם: דמי השכירות של בית אחד, כפול 2 בחזקת (מספר הבתים פחות 1). אם הרחוב מכיל מלון, השחקן ישלם את דמי השכירות עם המלון. סוגי הצבעים, השמות של הרחובות והמחירים נתונים לשיקול דעתכם.
##### בניית בתים
כזכור, שחקן יכול לבנות בית ברחוב מסוים רק אם מחזיק בכל הרחובות השייכים לאותה קבוצת צבע. ניתן לרכוש עד 4 בתים לכל רחוב ולאחר מכן גם מלון לפי החוקים הבאים:
* כדי לקנות בית נוסף, על השחקן לבנות את אותו המספר של בתים בשאר קבוצות הצבע (כלומר, נניח שיש לי 2 רחובות השייכים לאותה קבוצת צבע ובאחד בניתי בית ובשני לא. לא אפשרי לבנות בית נוסף ברחוב הראשון, עד שנבנה בית ברחוב השני).
* ניתן לבנות בית נוסף במחיר של בית רגיל (כלומר אם עלות בנייה של בית היא 100 שקלים, אז עלות כל בית נוסף גם תהיה 100 שקלים).
* ניתן לבנות מלון רק אחרי שנבנו 4 בתים באותו הרחוב. מחיר המלון הוא מחירם של 4 בתים + 100 שקלים.
#### רכבות
במשחק יש 4 רכבות, רכבת אחת בכל צד של הלוח. העלות של כל רכבת היא 200 שקלים. כאשר שחקן נוחת ברכבת של שחקן אחר הוא ישלם לו מס לפי מספר הרכבות של השחקן אצלו נחתו:
* רכבת אחת - 50 שקלים
* 2 רכבות - 100 שקלים
* 3 רכבות - 150 שקלים
* 4 רכבות - 200 שקלים
#### משבצות מיוחדות
הלוח מכיל משבצות מיוחדות מסוגים שונים.

* משבצת הפתעה - אם השחקן נוחת על המשבצת הזאת הוא מקבל איזושהי "הפתעה", למשל כרטיס יציאה מהכלא או זיכוי של כסף לחשבון. על ההפתעות להיות דינאמיות - כלומר כל הזמן ניתן לייצר הפתעות נוספות. לרשותכם דוגמה להפתעות היכולות להופיע במשחק בקובץ ```monopoly_chance_cards.txt```.
* משבצת "חנייה חופשית" - אם השחקן נוחת במשבצת הזאת הוא מסיים את התור ומעביר אותו לשחקן הבא.
* משבצות מס - אם השחקן נוחת במשבצות מהסוג הזה הוא משלם מס על סך 100 שקלים.
* משבצת "לך לכלא" - אם השחקן נוחת על המשבצת הזאת הוא נכנס לכלא ומשחק לפי הכללים של המשבצת הזאת.
* חברת החשמל וחברת המים - הלוח מכיל 2 משבצות עבור חברת המים וחברת החשמל. עלות על חברה היא 150 שקלים ואם שחקן נוחת במשבצת כזאת שהיא בבעלותו של שחקן אחר, עליו לשלם לאותו שחקן את סכום ההטלה כפול עשר.
#### הכלא
שחקן יכול להיכנס לכלא רק אם נחת על המשבצת "לך לכלא" או קיבל 3 פעמים ברצף "דאבל" בהטלות של הקוביה.
השחקן נמצא בכלא למשך 3 תורים שבמהלכם יכול לנסות לצאת מהכלא בדרכים הבאים:
* להשתמש בקלף יציאה מהכלא (שמקבלים מתיבת ההפתעה).
* לשלם קנס של 50 שקלים.
* להטיל את הקוביות ולקבל "דאבל".

אם עברו 3 תורים והשחקן לא הצליח לצאת מהכלא, עליו לשלם מס של 50 שקלים ואז הוא יוצא מהכלא.

### מהלך המשחק
כל שחקן מתחיל את המשחק עם 1500 שקלים ובתורו מטיל 2 קוביות ומתקדם על הלוח לפי תוצאת ההטלה ולפי החוקים הבאים:
* אם השחקן נחת ברחוב פנוי, הוא יכול לרכוש את אותו הרחוב.
* אם השחקן עבר את משבצת ההתחלה, הוא מקבל 200 שקלים לחשבון שלו.
* אם השחקן נחת במשבצת מיוחדת הוא פועל לפי החוקים של אותה המשבצת (למשל אם נחת במשבצת של תשלום מס השחקן צריך לשלם מס מהחשבון).
* אם תוצאת ההטלה היא "דאבל" השחקן מקבל תור נוסף למשחק. אם הוא קיבל 3 פעמים ברציפות "דאבל" הוא נכנס לכלא לפי החוקים של "כנס לכלא".
* אם השחקן נחת בנכס של שחקן אחר עליו לשלם לו שכירות/מס לפי החוקים של המשבצות.
* אם שחקן לא יכול להרשות לעצמו לשלם מס נוסף הוא "פושט רגל" ויוצא מהמשחק. אם השחקן פושט רגל בגלל חוב לשחקן כלשהו, כל הנכסים של אותו השחקן (כולל הכסף) עוברים לשחקן שהוא הבעלים של החוב. אם החוב הוא לבנק, הבעלות על הרחובות נמחקת.

אם השחקן נחת בכל משבצת שהיא לא "לך לכלא" או "חניה חופשית" השחקן יכול לבנות בתים בנכסים שלו לפי חוקי המשחק.

### ניצחון במשחק
שחקן יכול לנצח במשחק רק אם אחד משני הדברים קורים:
* כל שאר השחקנים פשטו את הרגל.
* בבעלות השחקן 4000 שקלים.

## מה עליכם לממש
יש לממש את הגרסה של המשחק שתתמוך בין 2 ל-8 שחקנים. חשבו כיצד לחלק את הקוד והמחלקות כך שיתאימו לחוקי המשחק.

כמו כן, עליכם לבנות ממשק גרפי המדגים את המשחק, עליכם להדפיס את לוח המשחק והשחקנים על הלוח וליצור ממשק המאפשר לכל השחקנים לשחק בצורה מובנת (כלומר, כל שחקן יכול לראות את המשבצות הפנויות/תפוסות ואת הדברים שבבעלותו).

עליכם גם לכתוב טסטים מקיפים לקוד שכתבתם וגם להוסיף README מפורט.



לרשותכם כמה חומרי עזר:
* לקריאה נוספת על חוקי המשחק והלוח: https://en.wikipedia.org/wiki/Monopoly_(game) 
* מדריך ל-GUI בשם QT  https://wiki.qt.io/Qt_for_Beginners
* מדריך ל-GUI בשם SFML https://www.sfml-dev.org/tutorials/2.6/

נדגיש כי אתם יכולים להשתמש באיזו ספרייה שאתם רוצים כדי לממש את הממשק הגרפי.

שימו לב שהגשת הפרויקט היא אישית. מותר להתייעץ, לקבל עזרה, ולהשתמש באינטרנט אבל יש לדווח בכתב על כל עזרה שקיבלתם, בהתאם לתקנון היושר של המחלקה - https://www.ariel.ac.il/wp/cs/wp-content/uploads/sites/88/2020/08/Guidelines-for-Academic-Integrity.pdf.

בהצלחה!
