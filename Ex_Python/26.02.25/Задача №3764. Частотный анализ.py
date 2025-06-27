# قراءة المدخلات بشكل صحيح

import sys

lines = []  # تم توحيد اسم المتغير بحروف صغيرة
# while True:
#     try:
for line in sys.stdin:
        # line = input()
        words = line.split()
        lines.extend(words)
    # except EOFError:
    #     break  #  (Ctrl+D أو Ctrl+Z)


frequency = {}
for word in lines:
    if word in frequency:
        frequency[word] += 1
    else:
        frequency[word] = 1

# الترتيب حسب التكرار تنازليًا ثم أبجديًا
sorted_words = sorted(frequency.items(), key=lambda x: (-x[1], x[0]))


for word, _ in sorted_words:
    print(word)