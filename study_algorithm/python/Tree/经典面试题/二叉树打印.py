class Node:
    def __init__(self, val=None):
        self.left = None
        self.right = None
        self.val =  val 



def levelOrderPrint(tree):
    if not tree:
        return
    nodes=collections.deque([tree])                  #仅仅把tree一个元素放进去
    currentCount, nextCount = 1, 0
    while len(nodes)!=0:
        currentNode=nodes.popleft()                    #遍历这一层
        currentCount-=1
        print currentNode.val,
        if currentNode.left:
            nodes.append(currentNode.left)                     #next,count是指下一层的数量
            nextCount+=1                                  
        if currentNode.right:
            nodes.append(currentNode.right)
            nextCount+=1
        if currentCount==0:
            #finished printing current level
            print '\n',
            currentCount, nextCount = nextCount, currentCount         #替换下一层的数量。
			
			
			
			
			