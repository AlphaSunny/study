from urllib import parse
from urllib import request

params = parse.urlencode({'nickname': 'yang', 'content': 'yange', 'send_time': '2018-08-22 16:27:03'})
f = request.urlopen("http://testapi.fnying.com/bot/collect_message.php?%s" % params)

print(f.read())
