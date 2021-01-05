import scrapy
import re
import os

class WWY_spider(scrapy.Spider):
	name = "WWYSpider"
	
	def start_requests(self):
		# 由于网页较多, 所以爬取前创建三种评分的保存路径
		savepath = os.getcwd() + '/html'
		if not os.path.isdir(savepath):
			os.makedirs(savepath)
		if not os.path.isdir(savepath + '/h'):
			os.makedirs(savepath + '/h')
		if not os.path.isdir(savepath + '/m'):
			os.makedirs(savepath + '/m')
		if not os.path.isdir(savepath + '/l'):
			os.makedirs(savepath + '/l')
		# 主链接
		rootpath = 'https://movie.douban.com/subject/30402296/comments'
		# 三种评分各自的链接
		urls = [
			'?start=0&limit=20&sort=new_score&status=P&percent_type=h',
			'?start=0&limit=20&sort=new_score&status=P&percent_type=m',
			'?start=0&limit=20&sort=new_score&status=P&percent_type=l'
		]
		# 分三类开始爬
		for url in urls:
			yield scrapy.Request(url=rootpath+url, callback=self.parse)
			
	def parse(self, response):
		# 经过事前试验, 不登录的前提下, 用户在浏览器最多可以访问至start=200的页面
		comment_start_limit = 200
		rootpath = 'https://movie.douban.com/subject/30402296/comments'
		# 正则得到目前的 start
		start = re.search(r"(?<=start=)(\d+)", response.url).group(0)
		# 评论打分种类
		commenttype = response.url[-1]
		# 按格式命名
		filename = 'WWY-%s-start-%s.html' % (commenttype, start)
		# 保存
		with open(os.getcwd() + '/html/' + commenttype + '/' + filename, 'wb') as f:
			f.write(response.body)
		self.log('Saved file %s' % filename)
		# 如果没达到上限
		if(int(start) < comment_start_limit):
			# html 里获得 “下页” 按钮的链接
			nextlink = rootpath + re.search(r"(\?start=(?:[^\"])*)\" data-page=\"\" class=\"next\"", response.text).group(1)
			# 新请求
			yield scrapy.Request(url=nextlink, callback=self.parse)