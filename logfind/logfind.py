#! /usr/bin/python
from sys import argv
import datetime

script, filename, start_time, end_time = argv

start_datetime = datetime.datetime.fromtimestamp(float(start_time))
end_datetime = datetime.datetime.fromtimestamp(float(end_time))
f = open(filename, "r")

# dt = datetime.datetime.strptime(datestr, "%a %b %d %H:%M:%S %Y")
# if start_datetime < dt < end_datetime

requests = 0
fofs = 0
response_time = 0
for line in f.readlines():
    if start_datetime < datetime.datetime.strptime(line[:24], "%a %b %d %H:%M:%S %Y") < end_datetime:
        requests += 1
        if line[25:28] == "404":
            fofs += 1
        else:
            response_time += int(line[29:32])

print requests
print fofs
print response_time / float(requests - fofs)
