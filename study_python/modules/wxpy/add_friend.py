from wxpy import *

bot = Bot()


@bot.register(msg_types=FRIENDS)
def auto_accept_friends(msg):
    # 接受好友请求
    new_friend = msg.card.accept()
    # 向新的好友发送消息
    new_friend.set_remark_name("feaofjie")
    new_friend.send('哈哈，我自动接受了你的好友请求')

embed()