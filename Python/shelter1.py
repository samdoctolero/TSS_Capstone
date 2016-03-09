def errorInitialize(incoming, msgCHK, busCHK, shelterCHK):

    shelterCHK = 0
    busCHK = 0
    msgCHK = 0

    for i in range (0, len(assignedBus)):
        if assignedBus[i] in str(incoming[2:4]):
            busCHK = 100

    for i in range (0, len(prevBusShelter)):
        if prevBusShelter[i] in str(incoming[6:10]):
            shelterCHK = 100

    return msgCHK, busCHK, shelterCHK

def checkForOldFile(name, oldName):
    oldData = []

    if(os.path.exists(name)):
        print("File exists. Moving data from " + name + " to " + oldName + "\n")

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
    
    numOfStops = s + 1
    
    numOfStops = hex(numOfStops)[2:]

    if int(numOfStops, 16) < 16:
        numOfStops = "0" + str(numOfStops)

    message = "s0" + assignedBus[bus] + str(numOfStops) + shelterID + "n"
    print("Sending: {}".format(message))

    message += "\n"

    ser.write(message.encode())
    return

def errorCheck(msgCHK, busCHK, shelterCHK, incoming):
    if "s0" not in str(incoming[0:2]) and msgCHK < 1:
        print("Message did not originate from shelter.")
        msgCHK += 1

    for i in range (0, len(assignedBus)):
        if assignedBus[i] not in str(incoming[2:4]) and busCHK < 1:
            print("Message does not match bus ID (" + assignedBus[i] + ").")

    for i in range (0, len(prevBusShelter)):
        if prevBusShelter[j] not in str(incoming[6:10]) and shelterCHK < 1:
            print("Message does not match shelter ID (" + prevBusShelter[j] + ").")

import serial
import os.path
import datetime
import time

#ser = serial.Serial('/dev/ttyUSB0', 9600)
ser = serial.Serial('COM5', 9600)

assignedBus = ["0a", "6b"]
prevBusShelter = ["0004"] #NEEDS TO BE CHANGED
shelterID = "0005" #NEEDS TO BE CHANGED
decBusNum = [10, 107]
shelterCHK = 0
busCHK = 0
msgCHK = 0

print("-----------------------------------------")

while True:
    incoming = ser.readline().strip()
    #print 'Received %s' % incoming
    print("Received: {}\n".format(incoming))

    msgCHK, busCHK, shelterCHK = errorInitialize(incoming, msgCHK, busCHK, shelterCHK)

    if len(incoming) == 11:
        for i in range (0, len(assignedBus)):
            for j in range (0, len(prevBusShelter)):
                if assignedBus[i] in str(incoming[2:4]) and "s0" in str(incoming[0:2]) and prevBusShelter[j] in str(incoming[6:10]):
                    n = "b" + str(decBusNum[i])
                    oldName = str(n) + "-" + str(datetime.date.today()) + ".txt"
                    name = n + ".txt"

                    s = str(incoming[4:6])
                    s = s[2:4]
                    s = int(s, 16)

                    checkForOldFile(name, oldName)

                    with open(name, 'w') as file:

                        d = datetime.datetime.now()

                        #Writing bus number to line 1
                        file.write(str(decBusNum[i])+"\n")

                        #Writing bus shelter id to line 2
                        file.write(str(prevBusShelter[j])+"\n")

                        #Writing number of stops to line 3
                        file.write(str(s)+"\n")

                        #Writing epoch time to line 4
                        epoch = convertToEpoch(d)
                        file.write(str(epoch)+"\n")

                        send(i, s)
                        break

            else:
                continue
            break

        errorCheck(msgCHK, busCHK, shelterCHK, incoming)

    else:
        print("Message does not meet length requirements.")

    print("-----------------------------------------")