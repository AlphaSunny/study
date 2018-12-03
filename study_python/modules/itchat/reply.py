import itchat
from wxpy import *

bot = Bot()
'''
@itchat.msg_register(itchat.content.TEXT)
def text_reply(msg):
    print(msg['Text'])
    return msg['Text']

itchat.auto_login()
itchat.run(）
'''

@itchat.msg_register(itchat.content.FRIENDS)
def deal_with_friend(msg):
    if add_friend_compile.search(msg['Content']) is not None:
        itchat.add_friend(**msg['Text'])  # 自动将新好友的消息录入，不需要重载通讯录
        itchat.send_msg('嘤嘤嘤，我是智障机器人小Pig，\n很高兴认识你，回复关键字:\n\n 加群，博客，公众号，打赏 \n\n 来继续我们的摔跤♂故事！',
                        msg['RecommendInfo']['UserName'])
        itchat.send_image('welcome.png', msg['RecommendInfo']['UserName'])
# 自动处理信息

@bot.core.msg_register(itchat.content.TEXT)
def text_reply(msg):
    print(msg['Text'])
    return msg['Text']

embed()

'''
itchat.auto_login()
itchat.run()
'''