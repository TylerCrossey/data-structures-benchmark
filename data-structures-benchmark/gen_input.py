import random, sys
n = int(sys.argv[1])
random.seed(int(sys.argv[2]) if len(sys.argv) > 2 else 0)
first = ["ALEX","BLAIR","CASEY","DANA","EMERY","FINN","GRACE","HARPER"]
last = ["ADAMS","BROOKS","CHEN","DIAZ","EVANS","FOSTER","GRANT","HUGHES"]
live = []
for _ in range(n):
    r = random.random()
    if r < 0.6 or not live:
        ssn = f"{random.randrange(10**9):09d}"
        live.append(ssn); op = "i"
    elif r < 0.8:
        ssn = live.pop(random.randrange(len(live))); op = "d"
    else:
        ssn = random.choice(live); op = "r"
    print(op, ssn, random.choice(first), random.choice(last))