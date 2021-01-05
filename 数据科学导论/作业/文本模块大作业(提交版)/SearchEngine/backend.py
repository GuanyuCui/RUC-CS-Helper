# 导入包
import numpy as np
import pandas as pd
from elasticsearch import Elasticsearch
from elasticsearch import helpers

# 导入全标签短信
messages = pd.read_csv('所有短信.csv')

es = Elasticsearch()
# 创建 message 索引
es.indices.delete(index = 'messages', ignore = [400, 404])
es.indices.create(index = 'messages', ignore = 400)
# mapping 分词
mapping = {
	'properties':{
		'content': {
			'type': 'text',
			'analyzer': 'ik_max_word',
			'search_analyzer': 'ik_max_word'
		}
	}
}
result = es.indices.put_mapping(index = 'messages', body = mapping)

# 按格式写到列表中, 批量添加到 elasticsearch 中
actions = [
	{
		'_index':'messages',
		'_source':
		{
			'label': row['标签'],
			'content': row['内容']
		}
	} for index, row in messages.iterrows()
]
res = helpers.bulk(es, actions)