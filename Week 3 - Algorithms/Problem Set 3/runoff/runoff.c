#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // If name is a match for the name of a valid candidate, then you should update the global preferences array to indicate that
    // the voter has that candidate as their rank preference(where 0 is the first preference, 1 is the second, etc)
    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        if (strcmp(name, candidates[currentCandidateIndex].name) == 0)
        {
            preferences[voter][rank] = currentCandidateIndex;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // The function should update the number of votes each candidate has at this stage in the runoff.
    // Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already
    // been eliminated.

    for (int currentVoterIndex = 0; currentVoterIndex < voter_count; currentVoterIndex++)
    {
        // Search for a candidate thats not eliminated in the preferences table
        for (int currentRankIndex = 0; currentRankIndex < candidate_count; currentRankIndex++)
        {
            int currentCandidateIndex = preferences[currentVoterIndex][currentRankIndex];
            // Count a vote if the candidate isn't eliminated
            if (!candidates[currentCandidateIndex].eliminated)
            {
                candidates[currentCandidateIndex].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Search if any candidate has more than half of the votes, print out their name and return true
    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        if (candidates[currentCandidateIndex].votes * 2 > voter_count)
        {
            printf("%s\n", candidates[currentCandidateIndex].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int miniumVotes = candidates[0].votes;

    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        if (candidates[currentCandidateIndex].eliminated)
            continue;

        if (candidates[currentCandidateIndex].votes < miniumVotes)
            miniumVotes = candidates[currentCandidateIndex].votes;
    }

    return miniumVotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        if (candidates[currentCandidateIndex].eliminated)
            continue;

        if (candidates[currentCandidateIndex].votes != min)
            return false;
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int currentCandidateIndex = 0; currentCandidateIndex < candidate_count; currentCandidateIndex++)
    {
        if (candidates[currentCandidateIndex].votes == min)
            candidates[currentCandidateIndex].eliminated = true;
    }
    return;
}
