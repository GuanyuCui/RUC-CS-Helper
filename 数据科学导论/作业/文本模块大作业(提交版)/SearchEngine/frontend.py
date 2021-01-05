# 导入包
import numpy as np
import pandas as pd
from elasticsearch import Elasticsearch
from elasticsearch import helpers
from tabulate import tabulate
import json
import time

# 查询函数, querystr 表示用户输入查询关键词, size 表示需要的条数
def es_query(querystr, size = 10):
	dsl = {
		'query':{
			'match':{
				'content': querystr
			}
		}
	}
	# 查询结果
	result = es.search(index = 'messages', body = dsl, size = size)
	contents = []
	# 处理成 tuple, 方便显示结果给用户
	for element in result['hits']['hits']:
		contents.append(
			tuple(
				(element['_source']['content'], 
				 '是' if element['_source']['label'] == 1 else '否',
				 element['_score'])
			)
		)
	queryresult = pd.DataFrame(contents, columns = ['内容', '是否垃圾短信', '相关性分值'])
	return queryresult
	
print('------------------------------------------------------------')
print('\t\tMy Simple Search Engine\t\t')
print('\t\t(Based on Elasticsearch)\t\t')
print('\t\tAuthor: G.Cui @ INFO.RUC\t\t')
print('------------------------------------------------------------')
print('使用说明:')
print('在"请输入查询内容"处输入想要查询的内容, 输入"QUIT"退出.')
print('接着输入想要显示的条数即可.')
print()

es = Elasticsearch()
while(True):
	querystr = input('请输入查询内容:')
	if(querystr == 'QUIT'):
		break
	size = input('请输入查询条数:')
	start = time.time();
	print('查询结果:')
	print(tabulate(es_query(querystr, size), headers = 'keys', tablefmt = 'psql'))
	end = time.time();
	print('查询用时:', round(end - start, 3), '秒')