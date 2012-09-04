from weibopy.auth import OAuthHandler  
from weibopy.api import API  
import configparser  
  
MAX_PIC_NUM = 3   
  
def press_sina_weibo():  
    ''''' 
    调用新浪微博Open Api实现通过命令行写博文，功能有待完善 
    author: socrates 
    date:2012-02-06 
    新浪微博：@偶是正太
    '''  
    sina_weibo_config = configparser.ConfigParser()  
    #读取appkey相关配置文件  
    try:  
        sina_weibo_config.readfp(open('sina_weibo_config.ini'))  
    except ConfigParser.Error:  
        print ('read sina_weibo_config.ini failed.')  
      
    #获取需要的信息  
    consumer_key = sina_weibo_config.get("userinfo","CONSUMER_KEY")  
    consumer_secret =sina_weibo_config.get("userinfo","CONSUMER_SECRET")  
    token = sina_weibo_config.get("userinfo","TOKEN")  
    token_sercet = sina_weibo_config.get("userinfo","TOKEN_SECRET")  
  
    #调用新浪微博OpenApi(python版)  
    auth = OAuthHandler(consumer_key, consumer_secret)  
    auth.setAccessToken(token, token_sercet)  
    api = API(auth)  
  
    #通过命令行输入要发布的内容  
#    weibo_content = raw_input('Please input content:')  
#    status = api.update_status(status=weibo_content)  
#    print "Press sina weibo successful, content is: %s" % status.text  
    iNum = 2  
    while True:  
        #上传图片，名称和内容如果重复，open api会检查，内容采用了取当前时间的机制  
        #图片名称从0-5循环遍历  
        status = api.upload( str(iNum)+'.jpg', 'test '+str(iNum) )   
      
        if iNum == MAX_PIC_NUM:  
            break  
        else:  
            iNum += 1  
          
if __name__ == '__main__':  
    press_sina_weibo()  
