#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Menu items
char beverage[10][50] = {{"Cappuccino"},
                        {"Latte"},
                        {"Mocha Coffee"},
                        {"Cold Coffee"},
                        {"Hot Chocolate"},
                        {"Kadak Chai"},
                        {"Oreo Shake"},
                        {"Kit-Kat Shake"},
                        {"Lemonade"},
                        {"Blue Lagoon"}};
char sides[12][50] = {{"Chicken Burger"},
                     {"Chicken Shawarma"},
                     {"Jalapeno Poppers"},
                     {"Overloaded French Fries"},
                     {"Grilled Sandwich"},
                     {"Overloaded Nachos"},
                     {"Steamed Momos"},
                     {"Garlic Bread"},
                     {"Mixed Sauce Pasta"},
                     {"Schezwan Noodles"},
                     {"Spring Roll"},
                     {"BabyCorn Chilli"}};

//Stores the number of menu items ordered with each index defined for a particular item as given in the menu
int nBev[10] = {0};
int nSid[12] = {0};

int j = 0;
int temp = 0;

//Gives (the index from the menu of items ordered)-1
int orderIndex[22] = {-1, -1, -1, -1, -1, -1, -1, -1 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

//Price of Menu Items
float pBev[10] = {75, 70, 75, 60, 70, 35, 90, 95, 50, 60};
float pSid[12] = {120, 100, 115, 140, 110, 170, 100, 125, 200, 
                  140, 130, 160};


//Calculates the total price of the items ordered and returns the same
float FinalPrice()
{
  float finalPrice, finalBev = 0, finalSid = 0;
  for(int i = 0 ; i < 10 ; i++)
    {
      finalBev = finalBev + nBev[i] * pBev[i];
    }
  for(int i = 0 ; i < 12 ; i++)
    {
      finalSid = finalSid + nSid[i] * pSid[i];
    }
  finalPrice = finalBev + finalSid;
  return finalPrice;
}


//Determines if the user is eligible for a student discount and calculates it (if applicable), Also determines discounts for two specific days from the week and calculates them, Gives the total discount as return value
float Discount()
{
  float finalPrice = FinalPrice();
  time_t tm;
  time(&tm);
  int student;
  float discount = 0;
  printf("**********************************************************************\n");
  printf("*      Are you a student ? (Enter the serial number)                 *\n");
  printf("*                1. Yes, I am a student.                             *\n");
  printf("*                2. No, I am not a student.                          *\n");
  printf("**********************************************************************\n");
  printf("* ");
  scanf("%d",&student);
  if(student == 1)
  {  
    discount = finalPrice * 0.2;
    printf("**********************************************************************\n");
    printf("*   Congratulations! You are elible for a student discount of 20 %%.  *\n");
    printf("**********************************************************************\n");
  }  
  int res;
  res = strncmp(ctime(&tm),"Wed",3);
  if(res == 0)
  {
    printf("**********************************************************************\n");
    printf("*             Congratulations! You are elible for a discount.        *\n");
    printf("*                   On Wednesdays you save 10 %% off.                  *\n");
    printf("**********************************************************************\n");
    discount = discount + finalPrice * 0.1;
  }
  res = strncmp(ctime(&tm),"Fri",3);
  if(res == 0)
  {
    printf("**********************************************************************\n");
    printf("*             Congratulations! You are elible for a discount.        *\n");
    printf("*                  On Fridays you save 15 %% off.                     *\n");
    printf("**********************************************************************\n");
    discount = discount + finalPrice * 0.15;
  }
  return discount;
}

//Calculates 5% GST on the total price of the items ordered and returns the same
float Tax()
{
  float finalPrice = FinalPrice();
  //5% GST
  float tax;
  tax = (finalPrice) * 0.05;
  return tax;
}


//Displays the final bill to be paid by the user when the order has been placed
void bill()
{
  float finalPrice = FinalPrice();
  float tax = Tax();
  int j = 1;
  float itemPrice = 0;
 
  printf("**********************************************************************\n");
  printf("*                                 Bill                               *\n");
  printf("**********************************************************************\n");
  for(int i = 0; i < 22; i++)
    {
      if(orderIndex[i] >= 0)
      {
        int menuIndex;
        menuIndex = orderIndex[i];
        if(j < 10)
          {
            if(menuIndex < 10)
            {
              itemPrice = pBev[menuIndex] * nBev[menuIndex];
              printf("* %d.  %s * %d", j, beverage[menuIndex], nBev[menuIndex]);
              int spaces = 51 - strlen(beverage[menuIndex]);
              for (int k = 0; k <= spaces; k++)
              {
                printf(" ");
              }
              printf("%6.2f *\n", itemPrice);
              j++;
            }
            else
            {
              menuIndex = menuIndex - 10;
              itemPrice = pSid[menuIndex] * nSid[menuIndex];
              printf("* %d.  %s * %d", j, sides[menuIndex], nSid[menuIndex]);
              int spaces = 51 - strlen(sides[menuIndex]);
              for (int k = 0; k <= spaces; k++)
              {
                printf(" ");
              }
              printf("%6.2f *\n", itemPrice);
              j++;
            }
          }
          else
          {
            if(menuIndex < 10)
            {
              itemPrice = pBev[menuIndex] * nBev[menuIndex];
              printf("* %d. %s * %d", j, beverage[menuIndex], nBev[menuIndex]);
              int spaces = 51 - strlen(beverage[menuIndex]);
              for (int k = 0; k <= spaces; k++)
              {
                printf(" ");
              }
              printf("%6.2f *\n", itemPrice);
              j++;
            }
            else
            {
              menuIndex = menuIndex - 10;
              itemPrice = pSid[menuIndex] * nSid[menuIndex];
              printf("* %d. %s * %d", j, sides[menuIndex], nSid[menuIndex]);
              int spaces = 51 - strlen(sides[menuIndex]);
              for (int k = 0; k <= spaces; k++)
              {
                printf(" ");
              }
              printf("%6.2f *\n", itemPrice);
              j++;
            } 
        }
      }
    }
  printf("**********************************************************************\n");
  printf("*     SUB TOTAL                                              %7.2f *\n", finalPrice);
  float discount = Discount();
  float total = finalPrice + tax - discount;
  printf("*       DISCOUNT                                              %6.2f *\n", discount);
  printf("*                                                                    *\n");
  printf("*     GST ( 5 %% )                                             %6.2f *\n", tax - (discount * 0.05));
  printf("**********************************************************************\n");
  printf("*     TOTAL AMOUNT                                           %7.2f *\n", total - (discount * 0.05));
  printf("**********************************************************************\n");
  printf("*                                                                    *\n");
  printf("*                                                                    *\n");
  printf("*                      Thank you for visiting!                       *\n");
  printf("*                          Have a nice day!                          *\n");
  printf("**********************************************************************\n");
}


//Displays the items and their ordered quantities for the convenience of the user to update his order or simply get an idea of the final amount to be paid
void displayCurrentOrder()
{
   int j = 1, flag = -1;
  for (int i = 0; i < 22; i++)
  {
    if (orderIndex[i] >= 0)
    {
      if(flag == -1)
      {
        printf("**********************************************************************\n");
        printf("*                                Order                               *\n");
        printf("**********************************************************************\n");
        flag++;
      }
      int menuIndex;
      menuIndex = orderIndex[i];
      
      if (j < 10)
      {
        if (menuIndex < 10)
        {
          printf("* %d.  %s", j, beverage[menuIndex]);
          int spaces = 61 - strlen(beverage[menuIndex]);
          for (int k = 1; k <= spaces; k++)
          {
            printf(" ");
          }
          printf("%d *\n", nBev[menuIndex]);
          j++;
        }
        else
        {
          menuIndex = menuIndex - 10;
          printf("* %d.  %s", j, sides[menuIndex]);
          int spaces = 61 - strlen(sides[menuIndex]);
          for (int k = 1; k <= spaces; k++)
          {
            printf(" ");
          }
          printf("%d *\n", nSid[menuIndex]);
          j++;
        }
      }
      else
      {
        if (menuIndex < 10)
        {
          printf("* %d. %s", j, beverage[menuIndex]);
          int spaces = 59 - strlen(beverage[menuIndex]);
          for (int k = 0; k <= spaces; k++)
          {
            printf(" ");
          }
          printf("%d *\n", nBev[menuIndex]);
          j++;
        }
        else
        {
          menuIndex = menuIndex - 10;
          printf("* %d. %s", j, sides[menuIndex]);
          int spaces = 59 - strlen(sides[menuIndex]);
          for (int k = 0; k <= spaces; k++)
          {
            printf(" ");
          }
          printf("%d *\n", nSid[menuIndex]);
          j++;
        }
      }
    }
  }
  if(flag == -1)
  {
    printf("**********************************************************************\n");
    printf("*             You have not ordered anything currently!               *\n");
  }
  printf("**********************************************************************\n"); 
}

//Displays the Menu Items to the user
void display()
{
  printf("**********************************************************************\n");
  printf("*                               Menu                                 *\n");
  printf("**********************************************************************\n");
  printf("*                             BEVERAGES                              *\n");
  for(int i = 0 ; i < 22; i++)
  {
    if(i < 10)
    {
      if (i <= 8)
      {
        printf("* %d.    %s", (i + 1), beverage[i]);
        int spaces = 55 - strlen(beverage[i]);
        for(int j = 1 ; j <= spaces; j++)
        {
          printf(" ");
        }
        printf("%.2f", pBev[i]);
        printf(" *\n");
      }
      else
      {
        printf("* %d.   %s", (i + 1), beverage[i]);
        int spaces = 55 - strlen(beverage[i]);
        for(int j = 1 ; j <= spaces; j++)
        {
          printf(" ");
        }
        printf("%.2f", pBev[i]);
        printf(" *\n");
      }
    }
    else
    {
      if ( i == 10)
      {
        printf("**********************************************************************\n");
        printf("*                               SIDES                                *\n");
      }
      int k = i - 10;
      printf("* %d.   %s", (i + 1), sides[k]);
      int spaces = 54 - strlen(sides[k]);
      for(int j = 1 ; j <= spaces; j++)
      {
        printf(" ");
      }
      printf("%.2f", pSid[k]);
      printf(" *\n");
    }
  }
  printf("**********************************************************************\n");
}


//Updates the quantity of items that have already been ordered once (adds to the existing quantities)
void update2(int index, int qty)
{
  int k = orderIndex[index];
  if(k > 10)
  {
    k = k - 10;
    nSid[k] = nSid[k] + qty;
  }
  else
  {
    nBev[k] += qty;
  }
}


//Takes the Menu Index and quantity of the item the user wants to order and stores them in orderIndex and nBev(or nSid) arrays respectively
void order()
{
  int qty = 0, item = 0, flag = 0;
  printf("**********************************************************************\n");
  printf("*      What would you like to order ? (Enter the serial number)      *\n");
  printf("*                         Press 0 to go back.                        *\n");
  printf("  ");
  scanf("%d", &item);
  if(item == 0)
  {
    return;
  }
  else if(item > 0 && item <= 22){
  printf("**********************************************************************\n");
  printf("* Enter the quantity of the item ordered:                            *\n");
  printf("  ");
  scanf("%d", &qty);
  item--;
  for (int i = 0; i < 22; i++)
  {
    if (item == orderIndex[i])
    {
      update2(i, qty);
      flag = 1;
      break;
    }
  }
  if (flag == 0)
  {
    if (item < 10)
    {
      orderIndex[j] = item;
      int temp = orderIndex[j];
      nBev[temp] = qty;
      j++;
    }
    else
    {
      orderIndex[j] = item;
      int temp = orderIndex[j] - 10;
      nSid[temp] = qty;
      j++;
    }
  }
    }
  else{
    printf("*                     Oops! Invalid Input.                           *\n");
  }
}


//Removes a particular item from the ordered items or updates (as chosen by the user) the quantity of an ordered item
void update1()
{
  start:
  system("clear");
  printf("**********************************************************************\n");
  printf("*           What would you like to update? (Enter the S.No.)         *\n");
  printf("*                    1.Remove an item                                *\n");
  printf("*                    2.Quantity of an item                           *\n");
  printf("**********************************************************************\n");
  int choice = 0;
  scanf("%d", &choice);
  switch (choice)
  {
    case 1:
    displayCurrentOrder();
    int remove = 0;
    printf("* Enter the serial number of the item you wish to remove:");
    printf("  ");
    scanf("%d", &remove);
    remove = remove - 1;
    int l = orderIndex[remove];
    if(l > 10)
    {
      l = l - 10;
      nSid[l] = 0;
    }
    else
    {
      nBev[l] = 0;
    }  
    orderIndex[remove] = -1;
    break;
    
    case 2:
    displayCurrentOrder();
    int qty = 0;
    int index = 0;
    printf("* Enter the S.No of the item whose qty you would like to change :");
    printf("  ");
    scanf("%d", &index);
    printf("* Enter the updated quantity: ");
    printf("  ");
    scanf("%d", &qty);
    index--;
    int k = orderIndex[index];
    if(k > 10)
    {
      k = k - 10;
      nSid[k] = qty;
    }
    else
    {
      nBev[k] = qty;
      temp = k;
    }
    break;

    default:
    printf("*                Incorrect option, Please try again !                   ");
    goto start;
    
  }
}


//Gives a pre defined delay between the previos output and the next output
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


//Interwines all the functions to be called according to the requirements of the user 
int main(void) {
  system("clear");
  printf("**********************************************************************\n");
  printf("*                            Welcome to                              *\n");
  printf("*                           Molto Bistro!                            *\n");
  printf("*                                                                    *\n");
  display();
  order();
  int repeat = 1;
  while(repeat)
  {
    delay(700000);
    system("clear");
    printf("**********************************************************************\n");
    printf("*                     What would you like to do?                     *\n");
    printf("*                       1.Add another item                           *\n");
    printf("*                       2.Make changes to the current order          *\n");
    printf("*                       3.View current order                         *\n");
    printf("*                       4.Place the order                            *\n");
    int choice = 0;
    printf("*                       ");
    scanf("%d", &choice);
    if(choice > 0 && choice <= 4)
    {
      switch (choice)
      {
        case 1:
        system("clear");  
        display();  
        order();
        delay(500000);
        continue;

        case 2:
        update1();
        delay(500000);
        continue;

        case 3:
        displayCurrentOrder();
        char k ;
        printf("*                       Press any key to continue.                   *\n");  
        scanf("%c", &k);   
        scanf("%c", &k);  
        continue;

        case 4:
        system("clear");
        bill();
        repeat = 0;  
        break;
          
      }
    }
    else
    {
      printf("*                    OOPS! Invalid Input! Try again.                 *\n");
      continue;
    }
  }
  
  return 0;
}




