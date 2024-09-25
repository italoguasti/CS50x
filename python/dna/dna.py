import csv
import sys


def main():
    # Verifique o uso da linha de comando
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        return

    # Ler arquivo de banco de dados em uma variável
    database = []
    with open(sys.argv[1]) as db_file:
        reader = csv.DictReader(db_file)
        for row in reader:
            database.append(row)

    # Ler arquivo de sequência de DNA em uma variável
    with open(sys.argv[2]) as seq_file:
        dna_sequence = seq_file.read().strip()

    # Encontre a correspondência mais longa de cada STR na sequência de DNA
    str_counts = {}
    for str_name in reader.fieldnames[1:]:  # Exclude the 'name' column
        str_counts[str_name] = longest_match(dna_sequence, str_name)

    # Verifique o banco de dados para perfis correspondentes
    for person in database:
        if all(int(person[str_name]) == str_counts[str_name] for str_name in str_counts):
            print(person['name'])
            return

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
