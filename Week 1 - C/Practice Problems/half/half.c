// Suppose you are eating out at a restaurant with a friend and want to split the bill evenly.
// You may want to anticipate the amount you’ll owe before the bill arrives with tax added.In this problem,
// you’ll complete a function to calculate the amount each of you owes based on the bill amount, the tax, and the tip.

#include <cs50.h>
#include <stdio.h>

        float
        half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    // Add tax to the bill
    bill += bill * (tax / 100);
    // Add tip to the bill
    bill += bill * ((float) tip / 100);
    // Returns half of the bill
    return bill / 2;
}
