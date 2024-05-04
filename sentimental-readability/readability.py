from cs50 import get_string
import re

str = get_string("Text: ")
letters = len(re.findall("[a-zA-Z]", str))
words = len(re.findall("[ ]", str))+1
sentences = len(re.findall("[\.\!\?]", str))

print(letters)
print(words)
print(sentences)
index = 0.0588 * ((letters / words) * 100) - 0.296 * ((sentences / words) * 100) - 15.8

index = round(index)

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")
