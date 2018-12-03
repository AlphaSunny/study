import time,datetime

tss1 = '2013-10-10 23:40:00'
 
timeArray = time.strptime(tss1, "%Y-%m-%d %H:%M:%S")
print(timeArray)   

print("year:", timeArray.tm_year)

print(int(time.mktime(timeArray)))


print('-------------------------------------------------------------------')
tss2 = '23:40:00'
 
timeArray = time.strptime(tss2, "%H:%M:%S")
print(timeArray)   

print("year:", timeArray.tm_year)
print("hour:", timeArray.tm_hour)
print("minute:", timeArray.tm_min)

print(int(time.mktime(timeArray)))