// Suppose you’re taking CS50 (if you’re reading this you probably are!) and spending time every week on each problem set. You may
// be wondering how many hours you’ve spent learning computer science, on average or in total! In this program, you’ll complete a
// function that calculates, based on a user’s input, a total number of hours or an average number of hours across a given number of
// days.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    float totalHours = 0;
    for (int i = 0; i < weeks; i++)
    {
        totalHours += hours[i];
    }
    return output == 'A' ? totalHours / weeks : totalHours;
}
