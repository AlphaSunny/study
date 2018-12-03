import itchat
from wxpy import *

#bot = Bot()

'''
@bot.core.msg_register(itchat.content.FRIENDS)
def deal_with_friend(msg):
    #if add_friend_compile.search(msg['Content']) is not None:
    bot.core.add_friend(**msg['Text'])  # 自动将新好友的消息录入，不需要重载通讯录
    bot.core.send_msg('嘤嘤嘤，我是智障机器人小Pig，\n很高兴认识你，回复关键字:\n\n 加群，博客，公众号，打赏 \n\n 来继续我们的摔跤♂故事！',
                    msg['RecommendInfo']['UserName'])
    user = bot.core.search_friends(msg['RecommendInfo']['UserName'])
    print(type(user))
    user ("feaoufej")
        #itchat.send_image('welcome.png', msg['RecommendInfo']['UserName'])
# 自动处理信息
'''

@itchat.msg_register(itchat.content.FRIENDS)
def deal_with_friend(msg):
    #if add_friend_compile.search(msg['Content']) is not None:
    itchat.add_friend(**msg['Text'])  # 自动将新好友的消息录入，不需要重载通讯录
    itchat.send_msg('嘤嘤嘤，我是智障机器人小Pig，\n很高兴认识你，回复关键字:\n\n 加群，博客，公众号，打赏 \n\n 来继续我们的摔跤♂故事！',
                    msg['RecommendInfo']['UserName'])
    user = itchat.search_friends(msg['RecommendInfo']['UserName'])
    print(type(user))
    user ("feaoufej")
        #itchat.send_image('welcome.png', msg['RecommendInfo']['UserName'])
# 自动处理信息


#embed()


itchat.auto_login()
itchat.run()

'''


@bot.register()
def accept_msg(msg):
    bot.core.add_friend(**msg['Text'])
    bot.core.send_msg('嘤嘤嘤，我是智障机器人小Pig，\n很高兴认识你，回复关键字:\n\n 加群，博客，公众号，打赏 \n\n 来继续我们的摔跤♂故事！',
                    msg['RecommendInfo']['UserName'])
    print(msg.card)


embed()
'''