#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <cctype>
#include <limits>
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <term.h>
#include <unistd.h>
using namespace std;

void titles();
void death(void (*fp)());
void death2(void (*fp)(vector<string>& inv), vector<string>& inv);
void monster();
void mainmenu();
void alt_menu(void (*fp)());
void alt_menu(void (*fp)(vector<string>& inv), vector<string>& inv);
void instructions();
void enforce_int();
void add_item(vector<string>& inv, string object);
void print_inventory(vector<string>& inv);
void intro(vector<string>& inv);
void print_inventory_ask(vector<string>& inv, void (*fp)(vector<string>& inv));
void print_inventory_ask2(vector<string>& inv, void (*fp)());
void centerstring(string s);
int responding(vector<string>& inv, int options, void (*fp)());
int responding(vector<string>& inv, int options, void (*fp)(vector<string>& inv));
void alt_intro(vector<string>& inv);
void alt_intro2(vector<string>& inv);
void alt_intro3(vector<string>& inv);
void firstroom(vector<string>& inv);
void firstroom2(vector<string>& inv);
void keys(vector<string>& inv);
void door(vector<string>& inv);
void door2(vector<string>& inv);
void door3(vector<string>& inv);

int main()
{
    vector<string> inv;
    const string name;
    string response;
    
    //titles();
    
    //mainmenu();
    //intro(inv);
    alt_intro(inv);
    
    return 0;
}

//Function to print titles to screen.
void titles()
{
    centerstring("ADVENTURE GAME");
    cout << endl << endl;
    system("read -n 1 -s -p \"Press the RETURN key to continue...\"");
}

//Function to display the main menu of the game.
void mainmenu()
{
    cout << endl;
    cout << "1. Play game\n";
    cout << "2. Instructions\n";
    cout << "3. Quit\n";
    
    bool done=false;
    int response, count=1;
    
    do
    {
        cin >> response;
        
        if (response==1)
        {
            cout << "OK! We're ready to go...\n\n";
            done=true;
            break;
        }
        if (response==2)
        {
            instructions();
            done=true;
        }
        if (response==3)
        {
            cout << "Return soon to complete your quest!\n";
            exit(1);
        }
        else
        {
            if (count==3)
            {
                cout << "\nYOU SEEM TO BE HAVING SOME TROUBLE...\n";
                count=1;
                mainmenu();
                break;
            }
            cout << "I'm sorry, I don't understand. Please try again...\n";
            count++;
        }
    }
    while(!done);
}

//Function to print menu that includes "Continue" option during game.
void alt_menu(void (*fp)())
{
    centerstring("MENU");
    cout << endl;
    cout << "1. Continue game\n";
    cout << "2. Quit game\n";
    
    bool done=false;
    int response, count=1;
    
    do
    {
        cin >> response;
        
        if (response==1)
        {
            fp();
            done=true;
        }
        if (response==2)
        {
            cout << "Return soon to complete your quest!\n";
            exit(1);
        }
        else
        {
            if (count==3)
            {
                cout << "\nYOU SEEM TO BE HAVING SOME TROUBLE...\n";
                count=1;
                mainmenu();
                break;
            }
            cout << "I'm sorry, I don't understand. Please try again...\n";
            count++;
        }
    }
    while(!done);
}

//Function to print menu that includes "Continue" option during game.
void alt_menu(void (*fp)(vector<string>& inv), vector<string>& inv)
{
    centerstring("MENU");
    cout << endl;
    cout << "1. Continue game\n";
    cout << "2. Quit game\n";
    
    bool done=false;
    int response, count=1;
    
    do
    {
        cin >> response;
        
        if (response==1)
        {
            fp(inv);
            done=true;
        }
        if (response==2)
        {
            cout << "Return soon to complete your quest!\n";
            exit(1);
        }
        else
        {
            if (count==3)
            {
                cout << "\nYOU SEEM TO BE HAVING SOME TROUBLE...\n";
                count=1;
                mainmenu();
                break;
            }
            cout << "I'm sorry, I don't understand. Please try again...\n";
            count++;
        }
    }
    while(!done);
}

//Function that prints instructions in the main menu.
void instructions()
{
    cout << endl;
    centerstring("INSTRUCTIONS");
    cout << "\nWelcome to ADVENTURE GAME, an interactive journey told through text alone.\n";
    cout << "Throughout this tale, you will be presented with many choices, choices that will determine your eventual fate within the narrative.\n";
    cout << "These choices will be presented in the form of numbers.\n";
    cout << "When prompted within the story, simply input the number of your desired action, and hit RETURN.\n";
    cout << "You can also access the menu at any point to pause or exit the game by typing \"menu\"";
    cout << "Easy as pie. But, keep in mind...\n\n";
    centerstring("...choices have consequences...");
    cout << "\n\n";
    system("read -n 1 -s -p \"Press the RETURN key to return to the main menu...\"");
    mainmenu();
}

//Function that ensures that input is of an int type.
void enforce_int()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

//Function to center text
void centerstring(string s)
{
    long l=s.length();
    long pos=((80-l)/2);
    for(int i=0;i<pos;i++)
        cout << " ";
    
    cout << s;
}

//Function that adds item to inventory.
void add_item(vector<string>& inv, string object)
{
    inv.push_back(object);
}

//Function that asks player if they would like to print their inventory.
void print_inventory_ask(vector<string>& inv, void (*fp)(vector<string>& inv))
{
    char reply;
    if (inv.size()==0)
    {
        cout << "You have no items in your inventory.\n";
        fp(inv);
    }
    if (inv.size()==1)
    {
        cout << "You have 1 item in your inventory.\n";
        cout << "Would you like to see your inventory, Y/N?\n";
    }
    if (inv.size()>1)
    {
        cout << "You have " << inv.size() << " items in your inventory.\n";
        cout << "Would you like to see your inventory, Y/N?\n";
    }
    cin >> reply;
    if ((reply=='y') || (reply=='Y'))
    {
        char response;
        cout << "In your inventory, you have:\n";
        print_inventory(inv);
        cout << "Continue game, Y/N?";
        cin >> response;
        if ((response=='y') || (response=='Y'))
        {
            fp(inv);
        }
        else
        {
            cout << "Return soon to complete your quest!\n";
            exit(1);
        }
    }
    else
        fp(inv);
}

//Function that asks player if they would like to print their inventory.
void print_inventory_ask2(vector<string>& inv, void (*fp)())
{
    char reply;
    if (inv.size()==0)
    {
        cout << "You have no items in your inventory.\n";
        fp();
    }
    if (inv.size()==1)
    {
        cout << "You have 1 item in your inventory.\n";
        cout << "Would you like to see your inventory, Y/N?\n";
    }
    if (inv.size()>1)
    {
        cout << "You have " << inv.size() << " items in your inventory.\n";
        cout << "Would you like to see your inventory, Y/N?\n";
    }
    cin >> reply;
    if ((reply=='y') || (reply=='Y'))
    {
        char response;
        cout << "In your inventory, you have:\n";
        print_inventory(inv);
        cout << "Continue game, Y/N?";
        cin >> response;
        if ((response=='y') || (response=='Y'))
        {
            fp();
        }
        else
        {
            cout << "Return soon to complete your quest!\n";
            exit(1);
        }
    }
    else
        fp();
}

//Function that prints all inventory items to the screen.
void print_inventory(vector<string>& inv)
{
    for (int i=0; i<inv.size(); i++)
        cout << inv[i] << endl;
}

//Function that explains the player's death and restarts from last checkpoint.
void death(void (*fp)())
{
    char response;
    
    cout << "\nUNFORTUNATELY, YOU HAVE DIED";
    cout << "\nRETURN TO LAST CHECKPOINT, Y/N?\n";
    cin >> response;
    
    if ((response=='y') || (response=='Y'))
    {
        fp();
    }
    else
    {
        cout << "Return soon to complete your quest!\n";
        exit(1);
    }
    
}

//Function that explains the player's death and restarts from last checkpoint.
void death2(void (*fp)(vector<string>& inv), vector<string>& inv)
{
    char response;
    
    cout << "\nUNFORTUNATELY, YOU HAVE DIED";
    cout << "\nRETURN TO LAST CHECKPOINT, Y/N?\n";
    cin >> response;
    
    if ((response=='y') || (response=='Y'))
    {
        fp(inv);
    }
    else
    {
        cout << "Return soon to complete your quest!\n";
        exit(1);
    }
    
}

//Function for response mechanism in game with inventory, menu, and death options.
int responding(vector<string>& inv, int options, void (*fp)(vector<string>& inv))
{
    string response;
    response.clear();
    cout << "Please respond below:\n";
    bool done=false;
    int count=1;
    
    do
    {
        cin >> response;
        
        if ((response=="inv") || (response=="Inv") || (response=="INV"))
        {
            print_inventory_ask(inv, fp);
            done=true;
        }
        if ((response=="menu") || (response=="Menu"))
        {
            alt_menu(fp, inv);
            done=true;
        }
        if ((response=="die") || (response=="Die") || (response=="DIE"))
        {
            cout << "What'd you go and do that for? You were perfectly healthy!\n";
            death2(fp, inv);
            done=true;
        }
        if ((atoi(response.c_str()) <= options) && (atoi(response.c_str())>0))
        {
            return atoi(response.c_str());
            done=true;
        }
        else
        {
            if (count==3)
            {
                cout << "\nYOU SEEM TO BE HAVING SOME TROUBLE...\n\n";
                count=1;
                fp(inv);
                break;
            }
            cout << "I'm sorry, I don't understand. Please try again...\n";
            count++;
        }
    }
    while(!done);
    
    return atoi(response.c_str());
}

//Function with basic layout/template of options and responses.
void monster()
{
    int response, count=1;
    bool done=false;
    
    cout << "There is an angry monster!\n";
    cout << "He swipes at you.\n";
    cout << "Do you...\n";
    cout << "1. Defend yourself.\n";
    cout << "2. Not defend yourself.\n";
    
    do
    {
        cin >> response;
        
        enforce_int();
        
        switch (response)
        {
            case 1:
                cout << "Hooray!\n";
                done=true;
                break;
            case 2:
                //death();
                monster();
                done=true;
                break;
            default:
            {
                if (count==3)
                {
                    cout << "\nYOU SEEM TO BE HAVING SOME TROUBLE...\n\n";
                    count=1;
                    monster();
                }
                cout << "I'm sorry, I don't understand. Please try again...\n";
                break;
            }
        }
        count++;
    }
    while(!done);
}

//Intro story to the game.
void intro(vector<string>& inv)
{
    cout << "Darkness swirls around you. Mists float amidst your consciousness. You see nothing.\n";
    cout << "1. Reach into the darkness.\n";
    cout << "2. Step into the darkness.\n";
    
    cout << "On the floor is:\n1. A Red Key,\n2. A Blue Key,\n3. And a White Key\n";
    cout << "Which would you like to pick up?";
    
    int response, count=1;
    bool done=false;
    
    do
    {
        cin >> response;
        enforce_int();
        switch (response)
        {
            case 1:
                add_item(inv, "The Red Key");
                done=true;
                break;
            case 2:
                add_item(inv, "The Blue Key");
                done=true;
                break;
            case 3:
                add_item(inv, "The White Key");
                done=true;
                break;
            default:
            {
                if (count==3)
                {
                    cout << "\nYOU SEEM TO BE HAVING SOME TROUBLE...\n\n";
                    count=1;
                    intro(inv);
                }
                cout << "I'm sorry, I don't understand. Please try again...\n";
                break;
            }
        }
        count++;
    }
    while(!done);
    
    print_inventory_ask(inv, intro);
}

//Alternate introduction to the game.
void alt_intro(vector<string>& inv)
{
    cout << "Darkness swirls around you. Mists float amidst your consciousness. You see nothing.\n";
    cout << "Do you...\n";
    cout << "1. Reach into the darkness.\n";
    cout << "2. Step into the darkness.\n";
    int reply=responding(inv, 2, alt_intro);
    if (reply==1)
    {
        cout << "Your hand becomes swallowed by blackness. There is nothing.\n\n";
        alt_intro(inv);
    }
    if (reply==2)
    {
        cout << "Ah. Now you're getting somewhere.\n\n";
        cout << "Your foot lands on solid ground.\n";
        alt_intro2(inv);
    }
}

//Branch of "Step into darkness" from intro
void alt_intro2(vector<string>& inv)
{
    cout << "Do you...\n";
    cout << "1. Reach into the darkness.\n";
    cout << "2. Step further into the darkness.\n";
    int reply=responding(inv, 2, alt_intro2);
    if (reply==1)
    {
        cout << "Your hand becomes swallowed by blackness. There is nothing.\n\n";
        alt_intro2(inv);
    }
    if (reply==2)
    {
        cout << "What an interesting sensation.\n\n";
        cout << "You inch forward, your foot resting on firm surfaces.\n";
        alt_intro3(inv);
    }
}

void alt_intro3(vector<string>& inv)
{
    cout << "Do you...\n";
    cout << "1. Reach into the darkness.\n";
    cout << "2. Step even further and further into the darkness.\n";
    int reply=responding(inv, 2, alt_intro3);
    if (reply==1)
    {
        cout << "Your hand becomes swallowed by blackness. There is still nothing. Still.\n\n";
        alt_intro3(inv);
    }
    if (reply==2)
    {
        cout << "Your foot slips and the ground gives way beneath you.\n";
        cout << "You tumble downward, the blackness completely encapsulates you...\n\n";
        system("read -n 1 -s -p \"Press the RETURN key to continue...\"");
        cout << endl;
        cout << "You awaken in a circular, brick room.\n";
        cout << "Your face is pressed hard against a rough, straw floor.\n";
        cout << "Dim shafts of light spill in through cracks in the walls.\n\n";
        firstroom(inv);
    }
}

void firstroom(vector<string>& inv)
{
    cout << "1. Look up.\n2. Get up.\n";
    int reply=responding(inv, 2, firstroom);
    if (reply==1)
    {
        cout << "The walls extend far upward above you.\nRotted and broken wooden beams criss-cross above you.\n";
        cout << "Higher up you can spot large wooden cogs, faded and misaligned with age.\n";
        cout << "Beyond the cogs and structures, the ceiling has completely fallen through.";
        cout << "Small bits of light from this opening up top reach on the ground, but there is too much clutter in your way to see the outside.\n\n";
        firstroom(inv);
    }
    if (reply==2)
    {
        cout << "You wearily rise to your feet and brush some dirt and straw from your face.\n";
        cout << "As you stand up, you notice a small metal box placed by your feet.\n";
        firstroom2(inv);
    }
}

void firstroom2(vector<string>& inv)
{
    cout << "1. Look up.\n2. Open the box.\n";
    int reply=responding(inv, 2, firstroom2);
    if (reply==1)
    {
        cout << "The walls extend far upward above you.\nRotted and broken wooden beams criss-cross above you.\n";
        cout << "Higher up you can spot large wooden cogs, faded and misaligned with age.\n";
        cout << "Beyond the cogs and structures, the ceiling has completely fallen through.\n";
        cout << "Small bits of light from this opening up top reach you on the ground, but there is too much clutter in your way to see the outside.\n\n";
        firstroom2(inv);
    }
    if (reply==2)
    {
        cout << "You lift the lid to the box. The metal squeaks as you do so.\nInside, you find a red key, a blue key, and a white key.\n";
        cout << "Your pocket is small and the keys are large. You can only carry one.\n";
        keys(inv);
    }
}

void keys(vector<string>& inv)
{
    cout << "Do you take:\n";
    cout << "1. The Red Key.\n2. The Blue Key.\n3. The White Key.\n";
    int reply=responding(inv, 3, keys);
    if (reply==1)
        add_item(inv, "The Red Key");
    if (reply==2)
        add_item(inv, "The Blue Key");
    if (reply==3)
        add_item(inv, "The White Key");
    cout << "You can check your inventory at any time by entering \"inv\" during an option sequence.\n";
    cout << "Try it now:\n";
    responding(inv, 0, door);
}

void door(vector<string>& inv)
{
    cout << "\nAs you close the lid of the box, you notice a door on the other side of the room.\n";
    cout << "How appropriate...\n";
}


