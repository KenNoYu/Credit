#include <cs50.h>
#include <stdio.h>
#include <math.h>

int checksum(long credit_card, int card_len);
int card_length(long credit_card);
string identifier(int card_len, int cardsum, long credit_card);

int main(void)
{
    // prompts user input
    long credit_card;
    do
    {
        credit_card = get_long("Credit Card Number:");
    }
    while (credit_card <= 0);

    // starts the function to find card length
    int card_len = card_length(credit_card);
    
    // starts the function for luhn's algorithm
    int cardsum = checksum(credit_card, card_len);
    
    //starts the function to identify card
    string card_type = identifier(card_len, cardsum, credit_card);
    printf("Card Type: %s\n", card_type);
}

int card_length(long credit_card)
{
    // declaring variables
    int card_len = 0;
    long temp = credit_card;
    
    // loop to find the length of card
    while (temp > 0)
    {
        temp = temp / 10;
        card_len++;
    }
    return card_len;
}

int checksum(long credit_card, int card_len)
{
    // declaring variables
    int temp_len = card_len;
    long temp_card = credit_card;
    int sum_1 = 0;
    int sum_2 = 0;
    long temp_len2 = pow(10, card_len);
    
    // splits the number from second to last digit and adds it together
    while (temp_len > 0)
    {
         int sum_1_temp = 0;
         int sum_2_temp = 0;
         temp_len2 = temp_len2 / 10;
         
         // for the numbers that are selected
         if (temp_len % 2 == 0)
         {
              sum_1_temp = sum_1_temp + (((temp_card / temp_len2) % 10) * 2);
              sum_1 = sum_1 + ((sum_1_temp / 10) + (sum_1_temp % 10));
         }
         
         // for the numbers that are not selected
         else
         {
              sum_2_temp = sum_2_temp + ((temp_card / temp_len2) % 10);
              sum_2 = sum_2 + sum_2_temp;
         }
         temp_len--;
    }
    // adds the selected and not selected number together
    int cardsum = sum_1 + sum_2;
    return cardsum;
}

string identifier(int card_len, int cardsum, long credit_card)
{
    // created variables
    int last_digit = cardsum % 10;
    string card_type;
    
    // Checks if checksum's last digit is a zero
     if (last_digit == 0)
     {
         if (card_len == 13 | card_len == 15 | card_len == 16)
         {
             // for AMERICAN EXPRESS
             if (card_len == 15)
             {
                 int start_digit = credit_card / 10000000000000;
                 if (start_digit == 34 | start_digit == 37)
                 {
                     card_type = "AMEX";
                 }
                 else
                 {
                     card_type = "INVALID";
                 }
             }
             
             // For VISA and MASTERCARD
             if (card_len == 16)
             {
                 int start_digit = credit_card / 1000000000000000;
                 // starting numbers for MASTERCARD
                 if (start_digit == 5)
                 {
                     card_type = "MASTERCARD";
                 }
                 
                 // checks condition of starting with 4
                 if (start_digit == 4)
                 {
                     card_type = "VISA";
                 }
             }
             // checks for VISA cards that are 13 digits long
             if (card_len == 13)
             {
                 int start_digit = credit_card / 1000000000000;
                 // checks condition of starting with 4
                 if (start_digit == 4)
                 {
                     card_type = "VISA";
                 }
                 else
                 {
                     card_type = "INVALID";
                 }
             }
             
         }
         else
         {
             card_type = "INVALID";
         }
     }
    else
    {
        card_type = "INVALID";
    }
    // determines the final value of the card
    return card_type;
}
