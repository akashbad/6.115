import math

numbers = [hex(int(128*math.sin(math.pi*2.0/256*i))+128) for i in range(256)]
rows = [numbers[i:i+8] for i in xrange(0,256,8)]
string_rows = [".db " + ", ".join(row) for row in [[number.replace("x","") + "h" for number in row] for row in rows]]
print "\n".join(string_rows)
