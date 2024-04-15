#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Look for a candidate called {name}
    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        // If candidate found, update {ranks} and return {true}. {ranks[i]} is the voter's {i}th preference
        if (strcmp(candidates[currentCandidateIndex], name) == 0)
        {
            ranks[rank] = currentCandidateIndex;
            return true;
        }
    }

    // If no candidate found, dont update any ranks and return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the {preferences} array based on the current voter's {ranks}

    for (int currentPreferredCandidateIndex = 0; currentPreferredCandidateIndex < candidate_count - 1;
         currentPreferredCandidateIndex++)
    {
        for (int currentCandidateIndex = currentPreferredCandidateIndex + 1; currentCandidateIndex < candidate_count;
             currentCandidateIndex++)
        {
            // {preferences[i][j]} is the number of voters who prefer {i} over {j}
            preferences[ranks[currentPreferredCandidateIndex]][ranks[currentCandidateIndex]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // The function should add all pairs of candidates where one candidate is preferred to the pairs array. A pair of candidates who
    // are tied (one is not preferred over the other) should not be added to the array.
    // The function should update the global variable {pair_count} to be the number of pairs of candidates. (The pairs should thus
    // all be stored between {pairs[0]} and {pairs[pair_count - 1]}, inclusive).

    // Compare candidates
    for (int firstCandidateIndex = 0; firstCandidateIndex < candidate_count; firstCandidateIndex++)
    {
        for (int secondCandidateIndex = 0; secondCandidateIndex < candidate_count; secondCandidateIndex++)
        {

            if (preferences[firstCandidateIndex][secondCandidateIndex] == preferences[secondCandidateIndex][firstCandidateIndex])
            {
                continue;
            }

            if (preferences[firstCandidateIndex][secondCandidateIndex] > preferences[secondCandidateIndex][firstCandidateIndex])
            {
                pairs[pair_count].winner = firstCandidateIndex;
                pairs[pair_count].loser = secondCandidateIndex;
                pair_count++;
            }
        }
    }
    return;
}

// Function to sort pairs based on preference strength
void sort_pairs(void)
{
    // Variables for Bubble Sort
    int swapCounter;
    pair temporaryPairHolder[1];

    // Perform Bubble Sort until no more swaps are needed
    do
    {
        // Initialize swap counter for each iteration
        swapCounter = 0;

        // Iterate through each pair
        for (int currentPairIndex = 0; currentPairIndex < pair_count - 1; currentPairIndex++)
        {
            // Get the current pair and the next pair
            pair currentPair = pairs[currentPairIndex];
            pair nextPair = pairs[currentPairIndex + 1];

            // Get the preference strengths of the current and next pairs
            int currentStrength = preferences[currentPair.winner][currentPair.loser];
            int nextStrength = preferences[nextPair.winner][nextPair.loser];

            // Compare the preference strengths and swap if necessary
            if (currentStrength < nextStrength)
            {
                temporaryPairHolder[0] = pairs[currentPairIndex];
                pairs[currentPairIndex] = pairs[currentPairIndex + 1];
                pairs[currentPairIndex + 1] = temporaryPairHolder[0];

                // Increment swap counter
                swapCounter++;
            }
        }
    }
    while (swapCounter > 0); // Continue the loop if swaps were made in the current iteration
}

// Function to check if locking a pair creates a cycle
bool isCyclic(int potentialWinner, int potentialLoser)
{
    // Check if there is a direct lock from loser to winner
    if (locked[potentialLoser][potentialWinner])
    {
        return true;
    }

    // Check if there is an indirect lock through other candidates
    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        // Check if the potential winner is locked with another candidate
        if (locked[currentCandidateIndex][potentialWinner])
        {
            // Check if the potential loser is indirectly locked through the candidate
            return isCyclic(currentCandidateIndex, potentialLoser);
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // The function should create the locked graph, adding all edges in decreasing order of victory strength so long as the edge
    // would not create a cycle.

    for (int currentPairIndex = 0; currentPairIndex < pair_count; currentPairIndex++)
    {
        // Extract the current winner and the current loser for better readability
        int currentWinner = pairs[currentPairIndex].winner;
        int currentLoser = pairs[currentPairIndex].loser;

        // Skip pairs that create a cycle
        if (!isCyclic(currentWinner, currentLoser))
        {
            // locked[i][j] means i is locked in over j
            locked[currentWinner][currentLoser] = true;
        }
    }
    return;
}

// Function to print the winner of the election
void print_winner(void)
{
    int winnerIndex;

    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        // Flag to check if the current candidate is the source of all edges
        bool isSource = true;

        // Check each other candidate to see if they have an edge to the current candidate
        for (int currentOtherIndex = 0; currentOtherIndex < candidate_count; currentOtherIndex++)
        {
            // If there is an edge from another candidate to the current candidate, set isSource to false
            if (locked[currentOtherIndex][currentCandidateIndex] == true)
            {
                isSource = false;
            }
        }

        // If the current candidate is the source of all edges, set it as the winner
        if (isSource)
        {
            winnerIndex = currentCandidateIndex;
        }
    }

    printf("%s\n", candidates[winnerIndex]);

    return;
}
