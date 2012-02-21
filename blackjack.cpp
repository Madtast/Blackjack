#include <iostream> /*Cin & Cout*/
#include <cstdio> /*For Character Control*/
#include <ctime> /*For Random*/
#include "blackjack.h" /*Includes Deck class and related functions*/

using namespace std;

/*Declare Functions*/
string niceCardName(char[]);
int countPoints(char[10][2], int);

/*Main Program*/
int main(void)
{
  //Initialize
  srand(time(NULL)); /*Not sure if this should be called here.*/
  
  int game = 0, player_wins = 0, player_ties = 0, player_losses = 0; /*Initialize all integers to zero*/
  int player_hit = 0, opponent_hit = 0, player_total = 0, opponent_total = 0, off_top = 0; /*Initialize all integers to zero*/
  char choice[2], player_card[10][2], opponent_card[10][2]; /*Initalize all character strings/arrays*/
  Deck cards; /*Create new instace of Deck as cards*/
  //cards.shuffle(); /*comment out unless you feel like double shuffling*/

  //Hit first time
  choice[0] = 'H';

  cout << "\nWelcome to Blackjack!\n";

  while(choice[0] != 'Q') /*Keep playing until the user make choice Q*/
  {
    game++; /*Incease game number by one*/
    /*Each turn, shuffle the cards */
    cards.shuffle(); /*you can go without this but you should stop off_top from setting to zero or you'll get the same cards each run*/
    while(opponent_total <= ((rand() % 6) + 12)) /*Each time we randomize the limit to stand at (within limits)*/
    {
      strcpy(opponent_card[opponent_hit], cards.pull(off_top)); /*take card off top of stack and store it in opponent_card array with the rest of their cards*/
      opponent_hit++; off_top++; /*increase the amount of times the opponent hit and the card position taken from top*/
      opponent_total = countPoints(opponent_card, opponent_hit-1); /*calulate current card values*/
    }
    
    /*This Section is for the player*/
    do /*do the following while either the user or computer chose to hit*/
    {
      strncpy(player_card[player_hit], cards.pull(off_top), 2);
      cout << "\nPulling Card #" << off_top << " off the top of the deck!\n";
      cout << "Card Pulled is " << niceCardName(player_card[player_hit]) << "\n\n";
      player_total = countPoints(player_card, player_hit);
      if(player_total > 21)
      {
        choice[0] = 'S';
        cout << "BUST! You have: " << player_total << "\n\n";
      }
      else
      {
        cout << "You have: " << player_total << "\n\n";
        cout << "Enter H to hit or S to stand: ";
        cin >> choice;
      }
      player_hit++; off_top++;
      //cout << off_top;
    } while(toupper(choice[0]) == 'H');
    
    if(toupper(choice[0]) == 'S') /*If you choose to stand*/
    {
      cout << "\nThe Computer Has: " << opponent_total << "\n";
      cout << "You Have : " << player_total << "\n\n";
      
      /*The following IF/ELSE block might be able to be optimized.*/
      if((opponent_total > player_total && opponent_total <= 21) || (opponent_total <= 21 && player_total > 21))
      {
        cout << "You LOST!!!\n\n";
        player_losses++;
      }
      else if(player_total > 21 && opponent_total > 21)
      {
        cout << "You both BUSTED!!!\n\n";
        player_ties++;
      }
      else if(player_total == opponent_total)
      {
        cout << "It's a DRAW!!!\n\n";
        player_ties++;
      }
      else
      {
        cout << "You WON!!!\n\n";
        player_wins++;
      }
      
      cout << "Type C to continue or Q to quit: ";
      cin >> choice[0];
      
      for(int i=0; i<=player_hit; i++)
      {
        player_card[i][0] = 0;
        player_card[i][1] = 0;
      }
      for(int i=0; i<=opponent_hit; i++)
      {
        opponent_card[i][0] = 0;
        opponent_card[i][1] = 0;
      }
      opponent_total = 0, player_hit = 0, player_total = 0, opponent_hit = 0, off_top = 0; /*Reset for new round*/
    }
  }

  cout << "\nOut of all " << game << " games played, you ranked the following!\n";
  cout << "Wins/Games & Losses/Games: " << player_wins << "/" << game << " & " << player_losses << "/" << game << "\n";
  cout << "Winning ratio: " << ((float)player_wins / ((float)game-(float)player_ties)) * 100 << "%\n\n";
  return 0;
}

string niceCardName(char code[]) { /*This takes the two character code exported by Deck in it's array, such as AH and prints Ace of Hearts*/
  char nice_num[6];
  char nice_suite[8];
  char nice_name[20];

  if(code[0] == 'A')
    strncpy(nice_num, "Ace", 3);
  else if(code[0] == 'T')
    strncpy(nice_num, "Ten", 3);
  else if(code[0] == 'J')
    strncpy(nice_num, "Jack", 4);
  else if(code[0] == 'Q')
    strncpy(nice_num, "Queen", 5);
  else if(code[0] == 'K')
    strncpy(nice_num, "King", 4);
  else
    sprintf(nice_num, "%c", code[0]);

  if(code[1] == 'S')
  {
    //strncpy(nice_suite, "Spaids", 6);
    sprintf(nice_name, "%s of Spaids", nice_num);
  }
  else if(code[1] == 'H')
  {
    //strncpy(nice_suite, "Hearts", 6);
    sprintf(nice_name, "%s of Hearts", nice_num);
  }
  else if(code[1] == 'D')
  {
    //strncpy(nice_suite, "Diamonds", 8);
    sprintf(nice_name, "%s of Diamonds", nice_num);
  }
  else if(code[1] == 'C')
  {
    //strncpy(nice_suite, "Clubs", 5);
    sprintf(nice_name, "%s of Clubs", nice_num);
  }
  else
  { }

  return nice_name;
}

/*The countPoints function can be optimized*/
int countPoints(char cards[10][2], int n) /*count points for Blackjack, cards is your array of cards, and n is the number of cards in your hand*/
{
  int points = 0;
  for (int i=0; i<=n; i++)
  {
    if(cards[i][0] == 'T')
    {
      points += 10;
    }
    else if(cards[i][0] == 'J')
    {
      points += 10;
    }
    else if(cards[i][0] == 'Q')
    {
      points += 10;
    }
    else if(cards[i][0] == 'K')
    {
      points += 10;
    }
    else if(cards[i][0] == 'A')
    {
      if(points+11 > 21)
        points += 1;
      else
        points += 11;
    }
    else if(cards[i][0] == '2')
    {
      points += 2;
    }
    else if(cards[i][0] == '3')
    {
      points += 3;
    }
    else if(cards[i][0] == '4')
    {
      points += 4;
    }
    else if(cards[i][0] == '5')
    {
      points += 5;
    }
    else if(cards[i][0] == '6')
    {
      points += 6;
    }
    else if(cards[i][0] == '7')
    {
      points += 7;
    }
    else if(cards[i][0] == '8')
    {
      points += 8;
    }
    else if(cards[i][0] == '9')
    {
      points += 9;
    }
  }
  return points;
}