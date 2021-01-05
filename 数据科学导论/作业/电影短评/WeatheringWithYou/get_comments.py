from bs4 import BeautifulSoup
import codecs
import os
import re

# 打开一个 html, 并返回获取到的短评内容
def get_comments(html):
	# 打开文件, 并用 BeautifulSoup 处理
	html_doc = open(html)
	bf = BeautifulSoup(html_doc, 'html.parser')
	# 获取用户名以及对应的评论
	users = bf.find_all(name="a", attrs={"href":re.compile(r"https://www.douban.com/people/"), "title": False})
	comments = bf.find_all(class_="short")
	# 写入字典并返回
	usercomments = {}
	for (user, comment) in zip(users, comments):
		# 注意过滤评论里的换行及多余的空格
		usercomments.update({user.text : comment.text.replace('\n', '').replace(' ', '')})
	return usercomments

# 将字典按格式写入txt文件
def write_txt(filepath, content, code):
	with codecs.open(filepath, 'a', encoding=code) as f:
		for key, value in content.items():
			f.write('[' + key + ']:' + value + '\n')
			
# 将字典按格式写入csv文件
def write_csv(filepath, content, code):
	with codecs.open(filepath, 'a', encoding=code) as f:
		for key, value in content.items():
			# 在字段左右加上" ", 避免内部 , 错误分隔
			f.write('"' + key + '","' + value + '"\n')

# 主方法
def main():
	# 三种不同打分的评论
	kinds = ['h', 'm', 'l']
	#if not os.path.isdir('txt'):
		#os.makedirs('txt')
	if not os.path.isdir('csv'):
		os.makedirs('csv')
	for kind in kinds:
		#txtsavepath = 'txt/WWY-' + kind + '.txt'
		csvsavepath = 'csv/WWY-' + kind + '.csv'
		# 创建空文件 / 或清空原有内容
		#f = open(txtsavepath, 'w')
		#f.close()
		f = open(csvsavepath, 'w')
		f.close()
		# 三路遍历 html/ 下的文件
		for (dirpath,dirnames,filenames) in os.walk(os.getcwd() + '/html/' + kind):
			for filename in filenames:
				# 是 html 文件
				if os.path.splitext(filename)[1]=='.html':
					# 处理写入csv
					usercomments = get_comments(dirpath + '/' + filename)
					#write_txt(txtsavepath, usercomments, 'utf8')
					write_csv(csvsavepath, usercomments, 'utf8')
				
if __name__ == '__main__':
	main()