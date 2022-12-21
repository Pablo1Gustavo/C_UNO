import re
import os
import subprocess

you = "main"
opp = "sample_a"
command = ['../uno', '../bots/'+opp, '../bots/'+you, '-q']

games = 1000
wins = 0
balance = 0

for i in range(1, games + 1):
    os.system('clear')
    print(f'Running {i}° of {games} games')
    print(
        '█' * (i // (games // 25)) +
        '▒' * (25 - i // (games // 25)),
        '%.1f%%\n'% (i / games * 100)
    )

    result = subprocess.run(command, stdout=subprocess.PIPE)
    result = result.stdout.decode('utf-8').split('\n')

    fst, snd = result[-3], result[-2]

    youCards = int(re.findall(r'-?\d', fst)[1])
    oppCards = int(re.findall(r'-?\d', snd)[1])

    if you in fst:
        wins += 1
    else:
        youCards, oppCards = youCards, oppCards

    balance += finalYou - finalOpp

os.system('clear')

print('== FINAL RESULTS ==')
print('Wins:', wins)
print('Win rate: %.1f%%'% (wins / games * 100))
print('Balance: ', balance)