import csv
import sys
import re


def main():

    # TODO: Check for command-line usage
    if (len(sys.argv) != 3):
        print("Incorrect Usage")

    # TODO: Read database file into a variable
    rows = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
    sequences = list(rows[0])[1:]
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        dna = file.read()
    # TODO: Find longest match of each sequence in DNA sequence
    count = []
    for sequence in sequences:
        seq = re.findall("(?:"+sequence+")+", dna)
        count.append(str(int(len(max(seq, default=""))/len(sequence))))

    # TODO: Check database for matching profiles
    for row in rows:
        flag = True
        for i in range(len(count)):
            if count[i] != row[sequences[i]]:
                flag = False
                break
        if flag:
            print(row["name"])
            quit()
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
