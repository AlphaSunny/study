import datetime,os,platform

def runTask():
    os_plat = platform.platform()
    if os_plat.startswith("Darwin"):
        print("this is mac")
    elif os_plat.startswith("Window"):
        print("this is window")

def timerRun(sched_timer):
    flag = 0
    while True:
        now = datetime.datetime.now()
        if now==sched_timer:
            runTask()
            flag=1
        else:
            if flag==1:
                sched_timer = sched_timer+ datetime.timedelta(days=1)
                flag=0


if __name__ == "__main__":
    sched_timer = datetime.date.today()
    today = datetime.datetime.today()
    sched_timer = datetime.datetime(today.year, today.month, today.day+1, 13, 16, 0)
    print("run the timer at {0}".format(sched_timer))
    timerRun(sched_timer)