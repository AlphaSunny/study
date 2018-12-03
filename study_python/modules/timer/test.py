import datetime
import threading


# 获取现在时间
now_time = datetime.datetime.now()
# 获取明天时间
year = now_time.date().year
month = now_time.date().month
day = now_time.date().day
# 获取明天3点时间
next_time = datetime.datetime.strptime(str(year)+"-"+str(month)+"-"+str(day)+" 14:00:00", "%Y-%m-%d %H:%M:%S")
# # 获取昨天时间
# last_time = now_time + datetime.timedelta(days=-1)

# 获取距离明天3点时间，单位为秒
timer_start_time = (next_time - now_time).total_seconds()
print(timer_start_time)

print()