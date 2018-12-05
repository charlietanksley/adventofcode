from collections import defaultdict
import datetime
import re
import operator

# input_file = "../input/04-test.txt"
input_file = "../input/04-full.txt"


class Elf(object):
    def __init__(self, id=None):
        self.id = id
        self.shifts = []
        self.naps = []

    def sleeping_time(self):
        return sum([nap.duration() for nap in self.naps])


class TimeRange(object):
    def __init__(self, start_time=None, end_time=None):
        self.start_time = start_time
        self.end_time = end_time

    def duration(self):
        assert self.start_time is not None
        assert self.end_time is not None
        return (self.end_time - self.start_time).seconds / 60.0


guards = defaultdict(lambda: Elf())
log_line_regex = re.compile(r'\[(?P<date>\d{,4}-\d{,2}-\d{,2} \d{,2}:\d{,2})\] (?P<message>.*)')
elf_id_regex = re.compile(r'Guard #(?P<id>\d+).*')

current_elf = None
current_shift = None
current_nap = None
current_state = None

lines = {}
with open(input_file, 'r') as f:
    for line in f:
        log = log_line_regex.match(line)
        timestamp = datetime.datetime.strptime(log.group('date'), "%Y-%m-%d %H:%M")
        message = log.group('message')
        lines[timestamp] = message

sorted_lines = sorted(lines.items(), key=operator.itemgetter(0))

for x in sorted_lines:
    timestamp = x[0]
    message = x[1]

    if message[0] == 'f':
        current_nap = TimeRange(start_time=timestamp)
    elif message[0] == 'w':
        assert current_elf is not None
        current_nap.end_time = timestamp
        current_elf.naps.append(current_nap)
    elif message[0] == 'G':
        if current_shift is not None:
            current_shift.end_time = timestamp
            current_elf.shifts.append(current_shift)
            current_shift = None
        elf_id = elf_id_regex.match(message).group('id')
        current_elf = guards[elf_id]
        current_shift = TimeRange(start_time=timestamp)
    else:
        print("unexpected")

sorted_list = sorted([(k, elf.sleeping_time()) for k, elf in guards.items()], key=operator.itemgetter(1), reverse=True)

most_sleepy = sorted_list[0]

def sleep_count(elf_id):
    sleep_count = defaultdict(int)
    for nap in guards[elf_id].naps:
        for i in range(int(nap.duration())):
            next_minute = nap.start_time + datetime.timedelta(minutes=i)
            sleep_count[next_minute.minute] += 1
    return sleep_count

def most_common_minute(sleep_count):
    try:
        return [(k, v) for k, v in sleep_count.items() if v == max(sleep_count.values())][0]
    except Exception as e:
        pass
    return [0, 0]


# Part 1 - 84636
print("The most sleepy elf",
      most_sleepy[0],
      "part 1",
      int(most_sleepy[0]) * most_common_minute(sleep_count(most_sleepy[0]))[0])


# Part 2 - 91679

most_frequent_sleep_guard_minute = [None, 0, 0]

for elf_id in guards.keys():
    x = most_common_minute(sleep_count(elf_id))
    if x[1] > most_frequent_sleep_guard_minute[2]:
        most_frequent_sleep_guard_minute[0] = elf_id
        most_frequent_sleep_guard_minute[1] = x[0]
        most_frequent_sleep_guard_minute[2] = x[1]

print("Part 2: Elf id",
       most_frequent_sleep_guard_minute[0],
       "minutes",
       int(most_frequent_sleep_guard_minute[0]) * most_frequent_sleep_guard_minute[1])

