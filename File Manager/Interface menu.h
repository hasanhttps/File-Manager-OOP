#pragma once

void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}



int CommandInterface() {

    int color1=48;
    int color2=15;

    int Set[] = { color1,color2 };
    int counter = 0;
    char key;

    while (true)
    {

        gotoxy(48, 13);
        color(Set[0]);
        cout << "1. Command (recommended)";

        gotoxy(48, 14);
        color(Set[1]);
        cout << "2. Interface";




        key = _getch();

        if (key == 72 && (counter == 1))
        {
            counter--;
        }
        if (key == 80 && (counter == 0))
        {
            counter++;
        }
        if (key == '\r')
        {
            break;
        }

        Set[0] = color2;
        Set[1] = color2;
        if (counter == 0)
        {
            Set[0] = color1;
        }
        if (counter == 1)
        {
            Set[1] = color1;
        }
    }
    color(7);
    system("cls");
    return counter;
}




int Interface() {
    int color1 = 48;
    int color2 = 15;
    int Set[] = { color1,color2,color2,color2,color2,color2,color2,color2,color2 };
    int counter = 1;
    char key;

    while (true)
    {
        gotoxy(45, 7);
        color(Set[0]);
        cout << "1. Create directory";

        gotoxy(45, 8);
        color(Set[1]);
        cout << "2. Remove directory";

        gotoxy(45, 9);
        color(Set[2]);
        cout << "3. Move directory";

        gotoxy(45, 10);
        color(Set[3]);
        cout << "4. Rename directory";
        
        gotoxy(45, 11);
        color(Set[4]);
        cout << "5. Change directory";
        
        gotoxy(45, 12);
        color(Set[5]);
        cout << "6. Print directory";
        
        gotoxy(45, 13);
        color(Set[6]);
        cout << "7. Open directory";
        
        gotoxy(45, 14);
        color(Set[7]);
        cout << "8. Sort directory";
        
        gotoxy(45, 15);
        color(Set[8]);
        cout << "9. Exit";

        key = _getch();

        if (key == 72 && (counter > 1 && counter < 10))
        {
            counter--;
        }
        if (key == 80 && (counter > 0 && counter < 9))
        {
            counter++;
        }
        if (key == '\r')
        {
            break;
        }

        for (size_t i = 0; i < 9; i++) { Set[i] = color2; }
        for (size_t i = 1; i <= 9; i++) {if (counter == i) Set[i - 1] = color1;}
    }
    system("cls");
    return counter;
}


