import serial
import os.path
import datetime
import time

#ser = serial.Serial('/dev/ttyUSB0', 9600)
ser = serial.Serial('COM5', 9600)

assignedBus = ["0a", "6b"]
prevBusShelter = "0002" #NEEDS TO BE CHANGED
shelterID = "0001" #NEEDS TO BE CHANGED
decBusNum = [10, 107]
oldData = []

def checkForOldFile(name, oldName):

    if(os.path.exists(name)):
        print("File exists. Moving data...")
        print(name)

        oldData.append(str(datetime.datetime.now())+"\n")

        with open(name, 'r') as file:
            for line in file:
                oldData.append(line)

        oldData.append("---------------------------\n")

    if(os.path.exists(oldName)):
        with open(oldName, 'a') as file:
            for i in range(0, 6):
                file.write(str(oldData[i]))
    else:
        with open(oldName, 'w') as file:
            for i in range(0, 6):
                file.write(str(oldData[i]))

    return

def convertToEpoch(d):
    
    pattern = "%d.%m.%Y %H:%M:%S"
    #epoch = time.mktime(datetime.datetime.strptime(str(d), pattern))
    epoch = time.time()

    return epoch

def send(bus, s):
    
    numOfStops = int(s) + 1
    message = "s0" + assignedBus[bus] + str(numOfStops) + shelterID + "n"
    print("Sending: {}".format(message))

    ser.write(message.encode())
    return

while True:

    incoming = ser.readline().strip()
    #print 'Received %s' % incoming
    print("Received: {}".format(incoming))

    if "s0" not in str(incoming[0:2]):
        print("Message did not originate from source. Ignoring...")
   
    for i in range (0, len(assignedBus)):
        if assignedBus[i] in str(incoming[2:4]) and "s0" in str(incoming[0:2]):
            bus = i

            n = "b" + str(decBusNum[i])
            oldName = str(n) + "-" + str(datetime.date.today()) + ".txt"
            name = n + ".txt"

            checkForOldFile(name, oldName)

            print("Opening: {}".format(name))

            with open(name, 'w') as file:

                d = datetime.datetime.now()
                if prevBusShelter in str(incoming[5:9]):
                    #Writing bus number to line 1
                    file.write(str(decBusNum[i])+"\n")

                    #Writing bus shelter id to line 2
                    file.write(str(prevBusShelter)+"\n")

                    #Writing number of stops to line 3
                    s = str(incoming[4:5])
                    s = s[2:3]
                    file.write(s+"\n")

                    #Writing epoch time to line 4
                    epoch = convertToEpoch(d)
                    file.write(str(epoch)+"\n")

                    send(bus, s)
