#include "asciiart.h";
#include <stdio.h>
#define CONIOEX
#include "conioex.h"

void printAsciiTower(int posX, int posY)
{
	gotoxy(posX, posY);   printf("              ()");
	gotoxy(posX, ++posY); printf("              /|");
	gotoxy(posX, ++posY); printf("             |==|");
	gotoxy(posX, ++posY); printf("             ====");
	gotoxy(posX, ++posY); printf("              XX");
	gotoxy(posX, ++posY); printf("             xXXx");
	gotoxy(posX, ++posY); printf("             XXXX");
	gotoxy(posX, ++posY); printf("             XXXX");
	gotoxy(posX, ++posY); printf("             XXXX");
	gotoxy(posX, ++posY); printf("            xXXXXx");
	gotoxy(posX, ++posY); printf("            XXXXXX");
	gotoxy(posX, ++posY); printf("            XXXXXX");
	gotoxy(posX, ++posY); printf("           xXXXXXXx");
	gotoxy(posX, ++posY); printf("           XXXXXXXX");
	gotoxy(posX, ++posY); printf("          xXXXXXXXXx");
	gotoxy(posX, ++posY); printf("          XXXXXXXXXX");
	gotoxy(posX, ++posY); printf("         XXXXX  XXXXX");
	gotoxy(posX, ++posY); printf("        xXXXX\"  \"XXXXx");
	gotoxy(posX, ++posY); printf("       XXXXXxxxxxxXXXXX");
	gotoxy(posX, ++posY); printf("     xXXXXX\"\"\"\"\"\"\"\"XXXXXx");
	gotoxy(posX, ++posY); printf("   xXXXXXX\"        \"XXXXXXx");
	gotoxy(posX, ++posY); printf("xxXXXXXXX            XXXXXXXxx");
}

// プライヤーアート
void printCharacterBaby(int posX, int posY)
{
	gotoxy(posX, posY);   printf("   ,=""=,");
	gotoxy(posX, ++posY); printf("  c , _,{");
	gotoxy(posX, ++posY); printf("  /|  @ )                 __");
	gotoxy(posX, ++posY); printf(" /  ^~~^|          <=.,__/ '}=");
	gotoxy(posX, ++posY); printf("(_/ ,, ,,)          |_ _>_/~");
	gotoxy(posX, ++posY); printf(" ~|_(/-`)'-,_,_,_,-'(_)-(_)");
}

void printCharacterDogbert(int posX, int posY)
{
	gotoxy(posX, posY);   printf("       .-""-.");
	gotoxy(posX, ++posY); printf("     .'      '");
	gotoxy(posX, ++posY); printf("    / /  |-()()");
	gotoxy(posX, ++posY); printf("   ;  |  |  ()|");
	gotoxy(posX, ++posY); printf("   |  `'`     | ");
	gotoxy(posX, ++posY); printf(" ,_|   | |    |");
	gotoxy(posX, ++posY); printf(" `-;   (_}    ;");
	gotoxy(posX, ++posY); printf("    '.,   __.'");
	gotoxy(posX, ++posY); printf("      / /| |");
	gotoxy(posX, ++posY); printf("     / / | |");
	gotoxy(posX, ++posY); printf("    (__) (__)");
}

void printCharacterGorilla(int posX, int posY)
{
	gotoxy(posX, posY);   printf("           .'`'.");
	gotoxy(posX, ++posY); printf("       .-./ _=_ |.-.");
	gotoxy(posX, ++posY); printf("      {  (,(oYo),) }}");
	gotoxy(posX, ++posY); printf("      {{ |   '   |} }");
	gotoxy(posX, ++posY); printf("      { { |(---)/  }}");
	gotoxy(posX, ++posY); printf("      {{  }'-=-'{ } }");
	gotoxy(posX, ++posY); printf("      { { }._:_.{  }}");
	gotoxy(posX, ++posY); printf("      {{  } -:- { } }");
	gotoxy(posX, ++posY); printf("     ((((|)     (/))))");
}

// 敵アート
void printWolf(int posX, int posY)
{
	gotoxy(posX, posY);   printf("                         ,     ,");
	gotoxy(posX, ++posY); printf("                         |`---/|");
	gotoxy(posX, ++posY); printf("                        /  , , |");
	gotoxy(posX, ++posY); printf("                  __.-'|  / ` /");
	gotoxy(posX, ++posY); printf("         __ ___.-'        ._O|");
	gotoxy(posX, ++posY); printf("      .-'  '        :      _/");
	gotoxy(posX, ++posY); printf("     / ,    .        .     |");
	gotoxy(posX, ++posY); printf("    :  ;    :        :   _/");
	gotoxy(posX, ++posY); printf("    |  |   .'     __:   /");
	gotoxy(posX, ++posY); printf("    |  :   /'----'| `  |");
	gotoxy(posX, ++posY); printf("    `  |`  |      | /| |");
	gotoxy(posX, ++posY); printf("     '.'| /       || ` |");
	gotoxy(posX, ++posY); printf("     | /|.'       '.l ``_");
	gotoxy(posX, ++posY); printf("     || ||             '-'");
	gotoxy(posX, ++posY); printf("     '-''-'");
}

void printDolphin(int posX, int posY)
{
	gotoxy(posX, posY);   printf("                                  __");
	gotoxy(posX, ++posY); printf("                               _.-~  )");
	gotoxy(posX, ++posY); printf("                    _..--~~~~,'   ,-/  ");
	gotoxy(posX, ++posY); printf("                 .-'. . . .'   ,-','    ,' )");
	gotoxy(posX, ++posY); printf("               ,'. . . _   ,--~,-'__..-'  ,'");
	gotoxy(posX, ++posY); printf("             ,'. . .  (@)' ---~~~~      ,'");
	gotoxy(posX, ++posY); printf("            /. . . . '~~             ,-'");
	gotoxy(posX, ++posY); printf("           /. . . . .             ,-'");
	gotoxy(posX, ++posY); printf("          ; . . . .  - .        ,'");
	gotoxy(posX, ++posY); printf("         : . . . .       _     /");
	gotoxy(posX, ++posY); printf("        . . . . .          `-.:");
	gotoxy(posX, ++posY); printf("       . . . ./  - .          )");
	gotoxy(posX, ++posY); printf("      .  . . |  _____..---.._/");
	gotoxy(posX, ++posY); printf("~---~~~~----~~~~             ~~");
}

void printMushroom(int posX, int posY)
{
	gotoxy(posX, posY);   printf("        __.....__");
	gotoxy(posX, ++posY); printf("     .'` _  o    ``.");
	gotoxy(posX, ++posY); printf("   .' O (_)     () o`.");
	gotoxy(posX, ++posY); printf("  .           O       .");
	gotoxy(posX, ++posY); printf(" . ()   o__...__    O  .");
	gotoxy(posX, ++posY); printf(". _.--```       ```--._ .");
	gotoxy(posX, ++posY); printf(":'                     ';");
	gotoxy(posX, ++posY); printf(" `-.__    :   :    __.-'");
	gotoxy(posX, ++posY); printf("      ``` - : : -```");
	gotoxy(posX, ++posY); printf("         J     L");
	gotoxy(posX, ++posY); printf("         :     :");
	gotoxy(posX, ++posY); printf("        J       L");
	gotoxy(posX, ++posY); printf("        :       :");
	gotoxy(posX, ++posY); printf("        `._____.'");
}

void printGhost(int posX, int posY)
{
	gotoxy(posX, posY);   printf("     .-.");
	gotoxy(posX, ++posY); printf("   .'   `.");
	gotoxy(posX, ++posY); printf("   :g g   :");
	gotoxy(posX, ++posY); printf("   : o    `.");
	gotoxy(posX, ++posY); printf("  :         ``.");
	gotoxy(posX, ++posY); printf(" :             `.");
	gotoxy(posX, ++posY); printf(":  :         .   `.");
	gotoxy(posX, ++posY); printf(":   :          ` . `.");
	gotoxy(posX, ++posY); printf(" `.. :            `. ``;");
	gotoxy(posX, ++posY); printf("    `:;             `:'");
	gotoxy(posX, ++posY); printf("       :              `.");
	gotoxy(posX, ++posY); printf("        `.              `.     .");
	gotoxy(posX, ++posY); printf("          `'`'`'`---..,___`;.-'");

}

void printPikachu(int posX, int posY)
{
	gotoxy(posX, posY);   printf("`;-.          ___,");
	gotoxy(posX, ++posY); printf("  `.` _...._/`.-``");
	gotoxy(posX, ++posY); printf("    |        /      ,");
	gotoxy(posX, ++posY); printf("    /()   () |    .' `-._");
	gotoxy(posX, ++posY); printf("   |)  .    ()|  /   _.'");
	gotoxy(posX, ++posY); printf("   |  -'-     ,; '. <");
	gotoxy(posX, ++posY); printf("    ;.__     ,;|   > '");
	gotoxy(posX, ++posY); printf("   / ,    / ,  |.-'.-'");
	gotoxy(posX, ++posY); printf("  (_/    (_/ ,;|.<`");
	gotoxy(posX, ++posY); printf("    |    ,     ;-`");
	gotoxy(posX, ++posY); printf("     >   |    /");
	gotoxy(posX, ++posY); printf("    (_,-'`> .'");
	gotoxy(posX, ++posY); printf("         (_,'");
}