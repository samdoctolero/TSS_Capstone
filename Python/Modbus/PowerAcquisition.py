#!/usr/bin/env python

import time
a = 2
counter = 0

# import the server implementation
from pymodbus.client.sync import ModbusSerialClient as ModbusClient

# configure the client logging
import logging
logging.basicConfig()
log = logging.getLogger('./modbus.error')
log.setLevel(logging.ERROR)

# choose the serial client
client = ModbusClient(method='rtu', port='/dev/ttyUSB1', baudrate=9600, timeout=1)
client.connect()

# Define the State list
state = ['Start', 'Night Check', 'Disconnected', 'Night', 'Fault!', 'BulkCharge', 'Absorption', 'FloatCharge', 'Equalizing']

while a > 1:

#read the registers from logical address 0 to 30.
  rr = client.read_holding_registers(0,30,1)

#scaling
  batt_scale = 96.667
  i_scale = 66.667
  array_scale = 139.15

#the stuff we want
  battsV = ( rr.registers[9] * 96.667) / 32768
  chargeI = ( rr.registers[11] * float(i_scale )) / (2**15)
  arrayV = ( rr.registers[10] * float(array_scale )) / (2**15)
  statenum = rr.registers[27]
  pwmDuty = rr.registers[28] /2.55
  regTemp = rr.registers[14] 
  powerIn = battsV * chargeI
  ampH = ( rr.registers[17] + rr.registers[18] ) * 0.1

  

#debug
#  print "Battery Voltage: %.2f" % battsV
#  print "Battery Charge Current: %.2f" % chargeI
#  print "Array Voltage: %.2f" % arrayV
#  print "PWM Duty: %.2f" % pwmDuty
#  print "Control State: %.2f" % state
#  print "Controller Temp: %.2f" % regTemp
#  print "Power in: %.2f" % powerIn
#  print "Ah: %.2f" % ampH

  out = "V:%.2f" % battsV + " A:%.3f" % chargeI + " AV:%.2f" % arrayV + " D:%.2f" % pwmDuty + " S:" + state[statenum] + " CT:%.2f" % regTemp + " P:%.2f" % powerIn + " AH:%.2f" % ampH + "\n" 
  fil = open('/mnt/dumpdata.txt', 'w')
  fil.write(out)
  fil.close()
  counter += 1

  if counter == 24:
    tid = time.ctime()
    out = str(tid) + ",%.2f" % battsV + ",%.3f" % chargeI + ",%.2f" % arrayV + ",%.2f" % pwmDuty + "," + state[statenum]  + ",%.2f" % regTemp + ",%.2f" % powerIn + ",%.2f" % ampH + "\n" 
    fil = open('/mnt/dumplog.csv', 'a')
    fil.write(out)
    fil.close()
    counter = 0

  time.sleep(5)

# close the client
client.close()

print "done"