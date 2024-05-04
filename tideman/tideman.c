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
int get_pair_difference(int index);
int partition(int start, int end);
void quick_sort(int start, int end);
void sort_pairs(void);
bool check_cycle(int root, int current);
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            ranks[rank] = i;
            // Assuming Voters vote different candidates each time.
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
int get_pair_difference(int index)
{
    return preferences[pairs[index].winner][pairs[index].loser] - preferences[pairs[index].loser][pairs[index].winner];
}
int partition(int start, int end)
{
    int p = start;
    int i = start;
    for (int j = start + 1; j < pair_count; j++)
    {
        if (get_pair_difference(j) <= get_pair_difference(i))
        {
            j++;
        }
        else
        {
            i++;
            pair temp = {pairs[i].winner, pairs[i].loser};
            pairs[i] = pairs[j];
            pairs[j] = temp;
        }
    }
    pair temp = {pairs[p].winner, pairs[p].loser};
    pairs[p] = pairs[i];
    pairs[i] = temp;
    return p;
}

void quick_sort(int start, int end)
{
    if (start < end)
    {
        int p = partition(start, end);
        quick_sort(start, p - 1);
        quick_sort(p + 1, end);
    }
    return;
}
void sort_pairs(void)
{
    quick_sort(0, pair_count);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
bool check_cycle(int root, int current)
{
    bool cycle = false;
    for (int i = 0; i < candidate_count && !cycle; i++)
    {
        if (locked[current][i])
        {
            if (i == root)
            {
                return true;
            }
            cycle = check_cycle(root, i);
        }
    }
    return cycle;
}
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool root = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                root = false;
                break;
            }
        }
        if (root)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
