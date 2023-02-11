#include <iostream>
#include <cstdlib> //used to get random number
#include <ctime>
#include <string>
#include <fstream> //used for file handling
using namespace std;

//global variables
int wallet = 0;
int betting_amount;
int withdraw_amount;
int *ptr_wallet = &wallet;
int *ptr_betting_amount = &betting_amount;
int dice;
int range = 12;

// some function declartion
void main_menu();
void registration();

void introduction() //front interface
{
    cout << "_____________________________________________";
    cout << "\n\n\n\t\t 1xBet Casino \n\t\t" << endl;
    cout << "_____________________________________________";
}

void log_in()
{
    cout << "\n\n\n\t\t< Log in >\n\t\t" << endl;

    string username, password;
    ifstream in;
    in.open("Casino_data.txt");
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    string file_username, file_password;
    bool found = false;

    while (in >> file_username >> file_password)
    {
        if (username == file_username && password == file_password)
        {
            cout << "---Logged in successfully--" << endl;
            found = true;
            main_menu();
            break;
        }
    }

    if (!found)
    {
        cout << "Incorrect username or password" << endl;
        registration();
    }

    in.close();
}

void sign_up()
{
    cout << "\n\n\n\t\t< Sign up >\n\t\t" << endl;

    ifstream in;
    string username, passward;
    cout << "Username : ";
    cin >> username;
    cout << "Passward : ";
    cin >> passward;

    string check;
    in.open("Casino_data.txt");
    while (in >> check)
    {
        if (username == check)
        {
            cout << "---Username already used---" << endl;
            sign_up();
        }
    }
    ofstream of;
    of.open("Casino_data.txt", ios::app);        //Opening file in append mode

    of << username << " " << passward << endl;
    of.close();

    cout << "---Sign up successfully completed---\n\n"
         << endl;
    log_in();
}

void registration()
{
    cout << "\n\n\n\t\t< Registration >\n\t\t" << endl;

    char key_registration;
    cout << "Sign up or Log in (s/l)? ";
    cin >> key_registration;

    if (key_registration == 's')
    {
        sign_up();
    }
    else if (key_registration == 'l')
    {
        log_in();
    }
}

bool condition_BetAmount(int betting_amount) //condition for placing bet in games
{
    if (betting_amount <= wallet)
        return true;
    else
        return false;
}

void exit()
{
    cout << "\n\n\t< Program closed successfully >\n\n\t\t" << endl;
}

void deposit()
{
    int deposit_money;
    cout << "\n\n\t\t< Deposit >\n\n\t\t" << endl;
    cout << "Enter the deposit amount 'rs': ";
    cin >> deposit_money;
    *ptr_wallet += deposit_money;

    cout << "---Money deposited successfully---\n"
         << endl;
    cout << "Updated wallet balance : " << wallet << " rs\n\n\n";

    cout << "Return back to main menu or quit the casino : (m/q) : ";
    char key_deposite;
    cin >> key_deposite;

    if (key_deposite == 'm')
    {
        system("cls");
        introduction();
        main_menu();
    }
    else if (key_deposite == 'q')
    {
        system("cls");
        cout << "\n\n\t\t< Program closed successfully >\n\n\t\t" << endl;
    }
}

void roulette()
{
    cout << "\n\n\t\t< Roulette >\n\n\t\t" << endl;
    cout << "Rule of the game :\n"
         << endl;
    cout << "Select a number between 1 and 12. If you guess the correct number, your money is multiplied by 10.\n\n"
         << endl;

    cout << "Enter the betting amount :- ";
    cin >> betting_amount;
    cout << "\n\n";

    if (betting_amount > wallet)
    {
        cout << "Please check your balance : " << endl;
        cout << "\nWould you like to first deposit or quit? (d/q) : ";
        char key;
        cin >> key;

        if (key == 'd')
        {
            system("cls");
            introduction();
            deposit();
        }
        else if (key == 'q')
        {
            system("cls");
            introduction();
            exit();
        }
    }
    else
    {
        if (condition_BetAmount(betting_amount))
        {
            int key_roulette;
            cout << "Select a number between 0 and 13 : ";
            cin >> key_roulette;

            cout << "Wheel is spinning..." << endl;

            srand(time(0));
            int dice = (rand() % range) + 1;

            cout << "Number is : " << dice << endl;
            cout << "\n\n";

            if (key_roulette == dice)
            {
                cout << "Congratulations! You won. Received 10x of your bet amount." << endl;
                *ptr_wallet += betting_amount * 10;
                cout << "Balance : " << wallet << endl;
                cout << "\n\n";
            }

            else
            {
                cout << "---Better Luck Next Time---" << endl;
                *ptr_wallet -= betting_amount;
                cout << "Balance :" << wallet << endl;
                cout << "\n\n";
            }
        }
        cout << "\nWould you like to play it again or return back to main menu ? (p/m) : ";
        char key;
        cin >> key;

        if (key == 'p')
        {
            system("cls");
            introduction();
            roulette();
        }
        else if (key == 'm')
        {
            system("cls");
            introduction();
            main_menu();
        }
    }
}

void under_Over()
{
    cout << "\n\n\t\t< Under and Over 7 >\n\n\t\t" << endl;
    cout << "Rules for the game :\n"
         << endl;
    cout << "1. Two dice will be Rolled you have to select whether the number is under 7 , over 7 or equal to 7" << endl;
    ;
    cout << "2. If you guess the correct number and it is not 7 then your money gets 2x" << endl;
    cout << "3. If you guess the correct number and its 7 then your money get 5x\n\n"
         << endl;

    cout << "enter money to bet : rs ";
    cin >> betting_amount;
    cout << "\n\n";

    if (betting_amount > wallet)
    {
        cout << "Please check your balance : " << endl;
        cout << "\nWould you like to first deposit money or quit? (d/q) : ";
        char key;
        cin >> key;

        if (key == 'd')
        {
            system("cls");
            introduction();
            deposit();
        }
        else if (key == 'q')
        {
            system("cls");
            introduction();
            exit();
        }
    }
    else
    {
        if (condition_BetAmount(betting_amount))
        {
            char key_under_Over;

            cout << "Select Under,Over or equal to 7  (u/o/e) : " << endl;
            cin >> key_under_Over;

            cout << "Rolling dice ....\n\n"
                 << endl;

            srand(time(0)); 
            int dice = (rand() % range) + 1; //use to get random number

            cout << "Number is : " << dice << endl;
            cout << "\n\n";

            if (key_under_Over == 'u' && dice < 7 || key_under_Over == 'o' && dice > 7)
            {
                cout << "Congratulations! You won. Received 2x of your bet amount." << endl;
                *ptr_wallet += betting_amount * 2;
                cout << "Balance : " << wallet << endl;
            }
            else if (key_under_Over == 'e' && dice == 7)
            {
                cout << "Congratulations! You won. Received 5x of your bet amount." << endl;
                *ptr_wallet += betting_amount * 5;
                cout << "Balance : " << wallet << endl;
            }
            else
            {
                cout << "Better Luck Next Time " << endl;
                *ptr_wallet -= betting_amount;
                cout << "Balance :" << wallet << endl;
                cout << "\n\n";
            }
            cout << "\nWould you like to play it again or return back to main menu ? (p/m) : ";
            char key;
            cin >> key;
            if (key == 'p')
            {
                system("cls");
                introduction();
                under_Over();
            }
            else if (key == 'm')
            {
                system("cls");
                introduction();
                main_menu();
            }
        }

        else
        {
            cout << "---Insufficient Balance--- " << endl;
            cout << "\n\n";
        }
    }
}

void withdraw()
{
    cout << "\n\n\t\t< Withdraw >\n\n\t\t" << endl;
    cout << "Note :- Minimum withdrawal money is 1000 rs\n"
         << endl;
    cout << "Enter the amount to be withdraw : ";
    cin >> withdraw_amount;

    if (withdraw_amount >= 1000 && wallet > withdraw_amount)
    {
        cout << "---Money withdrawal successfully---\n\n";
        cout << "Updated wallet balance : " << (wallet - withdraw_amount) << " rs\n\n";
        cout << "---Money will be credited to your bank account within 24 hrs ,if not then contact in help section.---\n\n"
             << endl;
    }
    else
    {
        cout << "---Please enter minimum amount or check your wallet balanace---\n\n"
             << endl;
    }

    cout << "Return back to main menu or exit the code : (y/n) : ";
    char key_withdraw;
    cin >> key_withdraw;

    if (key_withdraw == 'y')
    {
        system("cls");
        introduction();
        main_menu();
    }
    else
    {
        system("cls");
        cout << "\n\n\t\t< Program closed successfully >\n\n\t\t" << endl;
    }
}

void help()
{
    cout << "\n\n\t\t< Help >\n\n\t\t" << endl;
    cout << " 24/7 Customer Service Available\n\n"
         << endl;
    cout << "Email :- 1xbetcasino@gmail.com" << endl;
    cout << "Phone number : 121000999x\n\n"
         << endl;

    cout << "Return back to main menu or quit : (m/q) : ";
    char key_help;
    cin >> key_help;

    if (key_help == 'm')
    {
        system("cls");
        introduction();
        main_menu();
    }
    else if (key_help == 'q')
    {
        system("cls");
        cout << "\n\n\t< Program closed successfully >\n\n\t\t" << endl;
    }
}

void main_menu()
{
    cout << "\n\n\t\t< Main Menu >\n\n\t\t" << endl;
    cout << "-> Press\n"
         << endl;
    cout << "1. Sign up" << endl
         << "2. Log in" << endl;
    cout << "3. Roulette " << endl
         << "4. Under and Over 7 " << endl;
    cout << "5. Deposit" << endl;
    cout << "6. Withdraw" << endl;
    cout << "7. Help" << endl;
    cout << "8. Exit\n\n"
         << endl;

    int key_main_menu = 0;
    cin >> key_main_menu;

    switch (key_main_menu)
    {
    case 1:
        sign_up();
        break;
    case 2:
        log_in();
        break;
    case 3:
        roulette();
        break;
    case 4:
        under_Over();
        break;
    case 5:
        deposit();
        break;
    case 6:
        withdraw();
        break;
    case 7:
        help();
        break;
    case 8:
        exit();
        break;
    default:
        cout << "Please enter the correct number " << endl;
        break;
    }
}

int main()
{
    introduction();
    registration();
}