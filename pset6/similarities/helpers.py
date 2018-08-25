from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    # take in strings a and b
    # split each string into lines (at the end)
    a_lines = set(a.split("\n"))
    b_lines = set(b.split("\n"))
    return a_lines & b_lines

def sentences(a, b):
    """Return sentences in both a and b"""
    # take in string inputs a and b,
    # split each string into sentences use sent_tokenize
    a_sentences = set(sent_tokenize(a))
    b_sentences = set(sent_tokenize(b))
    return a_sentences & b_sentences

# Extract substrings from string
def substring_tokenize(str, n):
    substrings = []
    for i in range(len(str) - n + 1):
        substrings.append(str[i:i + n])
    return substrings

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # take in string input a, b and substring length n
    # split each string into all substrings of length n
    a_substrings = set(substring_tokenize(a, n))
    b_substrings = set(substring_tokenize(b, n))
    return a_substrings & b_substrings
