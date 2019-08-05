# Used to color code terminal commands
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

# Reads file from input, converts its contents into a list
filename = input("Your file name (Path or current root):")

parse_list = [line.rstrip() for line in open(filename)] # strips /n from each element

# Converts the list str values into booleans, makes a tuple out of them

bool_list = []
for val in parse_list:
    if (val == 'T'):
        bool_list.append(True)
    elif (val == 'F'):
        bool_list.append(False)
    else:
        print(bcolors.FAIL + "Invalid file formatting, exiting..." + bcolors.ENDC)
        exit(1)
truth_tuple = tuple(bool_list)
tuple_len = len(truth_tuple)

# Returns the true/false value in user input index

while True:
    q_num = input("Question number? 1 to %d, E to exit\n" % (tuple_len))
    if (q_num == "e"):
        exit(0)
    try:
        q_num = int(q_num)
    except ValueError: # Prints error on unexpected input
        print (bcolors.FAIL + "Input isn't an int! :(" + bcolors.ENDC)
    else:
        try:
            if (truth_tuple[q_num]):
                print("The answer is" + bcolors.OKGREEN + " %s" % (truth_tuple[q_num]) + bcolors.ENDC)
            else:
                print("The answer is" + bcolors.OKBLUE + " %s" % (truth_tuple[q_num]) + bcolors.ENDC)
        except IndexError: # Prints error on a number that is out of bounds
            print (bcolors.FAIL + "Only numbers up to %d are accepted" % (tuple_len) + bcolors.ENDC)