from wxpy import *

bot = Bot()

# 定位公司群
company_group = ensure_one(bot.groups().search('聊天机器人测试群'))

# 定位老板
#boss = ensure_one(company_group.search('老板大名'))

# 将老板的消息转发到文件传输助手
@bot.register(company_group)
def forward_boss_message(msg):
    print(type(msg))
    print(msg.location)
    print(msg.member)
    print(msg.text)
    print(msg.raw)
    
    
'''
    if msg.member == boss:
        msg.forward(bot.file_helper, prefix='老板发言')
'''

# 堵塞线程
embed()