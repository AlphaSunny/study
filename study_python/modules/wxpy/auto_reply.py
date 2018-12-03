from wxpy import *

bot = Bot()

@bot.register(Friend, msg_types=TEXT)
def auto_reply(msg):
    print(msg)
    print(msg.sender.remark_name)
    print(msg.sender["remark_name"])
    print(type(msg))
    if "ccvt" in msg.text.lower():
        return "I love you"

embed()