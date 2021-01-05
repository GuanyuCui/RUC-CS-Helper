#2018202147−PageRank.py

#@param input_file_name: 描述一个graph的纯文本邻接表文件名,如’E:\graph.txt’.
#@param damping_factor
def PageRank( input_file_name , damping_factor ):	
	# graph = {'node': [[inEdge], outDegree]}
	graph = {}
	
	# Open and read file.
	with open(input_file_name, 'r') as f:
		contents = f.readlines()
	# Create adjacency list of a graph.
	for line in contents:
		# if line.strip() == '':
			#continue
		left, right = line.split(',')
		right = right.strip()
		# Append inEdge
		graph.setdefault(right,[ [], 0 ])[0].append(left)
		# Increase outEdge
		graph.setdefault(left,[ [], 0 ])[1] += 1
	f.close()
	del line, contents
	del left, right
	
	# Graph size
	graph_size = len(graph)
	# Empty graph
	if graph_size == 0:
		return []
		
	# Collect dangling nodes, but don't add real edge in the graph.
	# Instead, calculate dangling_sum below.
	dangling_nodes = [node for node in graph.keys()\
		if graph[node][1] == 0]
	
	# Dict from nodename(key) to list index, avoid copying dicts.
	# e.g. : 
	# graph_dict = { 'a':... , 'b':..., 'c':... }
	# weight_list = [ 0.33, 0.33, 0.33 ]
	# Only iterate weight_list.
	node_to_index = dict(zip(graph.keys(), range(graph_size)))
	
	# Initial weight
	old_weight = [1.0 / graph_size for i in range(graph_size)]
	
	# Tolerence of errorness.
	tol = 1e-6
	i = 0
	# Iterate
	while True:
		# Dangling sum from dangling nodes to every node.
		dangling_sum = 0
		for node in dangling_nodes:
			dangling_sum += old_weight[node_to_index[node]]
		# Base : (1-alpha) / n
		new_weight = [\
		(1.0 - damping_factor) / graph_size \
		for i in range(graph_size)]
		
		# Dangling nodes contribute to other nodes.
		# alpha * dangling_sum / graph_size
		dangling_avg = damping_factor / graph_size * dangling_sum;
		# Iterate nodes.
		for node in graph.keys():
			# Iterate innodes.
			for innode in graph[node][0]:
				# Add weights.
				new_weight[node_to_index[node]] += \
					damping_factor / graph[innode][1] \
					* old_weight[node_to_index[innode]]
			new_weight[node_to_index[node]] += dangling_avg

		delta = sum([abs(new_weight[i] - old_weight[i])\
			for i in range(graph_size)])
		if delta < tol * graph_size:
			break
		# Update.
		old_weight = new_weight
		i += 1
	del tol, i
	
	# Sort.
	sorted_result = \
		sorted( dict(zip(graph.keys(), new_weight)).items(), \
		key = lambda i: (i[1], i[0]), \
		reverse = True )
	# Generate list and score.
	# Comment 'scores' in homework code.
	node_list_in_descending_order = [term[0] for term in sorted_result]
	scores = [term[1] for term in sorted_result]
	return node_list_in_descending_order , scores


#@param input_Graph: 描述一个graph的纯文本邻接表文件名,如’E:\graph.txt’。 
#@param input_Seed: 描述一个种子集的纯文本文件名,如’E:\seed.txt’。 
#@param damping_factor
def PPR( input_Graph , input_Seed , damping_factor ) : 
	# Read graph like PageRank(...).
	# graph = {'node': [[inEdge], outDegree]}
	graph = {}
	
	# Open and read file.
	with open(input_Graph, 'r') as f:
		contents = f.readlines()
	# Create adjacency list of a graph.
	for line in contents:
		# if line.strip() == '':
			#continue
		left, right = line.split(',')
		right = right.strip()
		# Append inEdge
		graph.setdefault(right,[ [], 0 ])[0].append(left)
		# Increase outEdge
		graph.setdefault(left,[ [], 0 ])[1] += 1
	f.close()
	
	# Graph size
	graph_size = len(graph)
	# Empty graph
	if graph_size == 0:
		return []
		
	# Read seed.
	# seed = {'node' : weight}
	seed = {}
	with open(input_Seed, 'r') as f:
		contents = f.readlines()
	# Create adjacency list of a graph.
	for line in contents:
		# if line.strip() == '':
			#continue
		left, right = line.split(',')
		weight = float(right)
		# Add weight.
		seed[left] = weight
	f.close()
	del line, contents
	del left, right, weight
		
	# Collect dangling nodes, but don't add real edge in the graph.
	# Instead, calculate dangling_sum below.
	dangling_nodes = [node for node in graph.keys()\
		if graph[node][1] == 0]
	
	# Dict from nodename(key) to list index, avoid copying dicts.
	# e.g. : 
	# graph_dict = { 'a':... , 'b':..., 'c':... }
	# weight_list = [ 0.33, 0.33, 0.33 ]
	# Only iterate weight_list.
	node_to_index = dict(zip(graph.keys(), range(graph_size)))
	
	# Initial weight using seed
	p0 = [0 for _ in range(graph_size)]
	for node in seed.keys():
		p0[node_to_index[node]] = seed[node]
	old_weight = p0
	
	# Tolerence of errorness.
	tol = 1e-6
	i = 0
	# Iterate
	while True:
		# Dangling sum from dangling nodes to every node.
		dangling_sum = 0
		for node in dangling_nodes:
			dangling_sum += old_weight[node_to_index[node]]
		# Base : (1-alpha) * p0
		new_weight = [\
		(1.0 - damping_factor) * p0[i]\
		for i in range(graph_size)]
		
		# Dangling nodes contribute to other nodes.
		# alpha * dangling_sum / graph_size
		dangling_avg = damping_factor / graph_size * dangling_sum;
		# Iterate nodes.
		for node in graph.keys():
			# Iterate innodes.
			for innode in graph[node][0]:
				# Add weights.
				new_weight[node_to_index[node]] += \
					damping_factor / graph[innode][1] \
					* old_weight[node_to_index[innode]]
			new_weight[node_to_index[node]] += dangling_avg
		
		delta = sum([abs(new_weight[i] - old_weight[i])\
			for i in range(graph_size)])
		if delta < tol * graph_size:
			break
		# Update.
		old_weight = new_weight
		i += 1
	del tol, i
	
	# Sort.
	sorted_result = \
		sorted( dict(zip(graph.keys(), new_weight)).items(), \
		key = lambda i: (i[1], i[0]), \
		reverse = True )
	# Generate list and score.
	# Comment 'scores' in homework code.
	node_list_in_descending_order = [term[0] for term in sorted_result]
	scores = [term[1] for term in sorted_result]
	return node_list_in_descending_order , scores

# Test PR.
import time
time_start = time.time()
result = PageRank('soc-Epinions1_processed.txt', 0.85)
result_dict_rank10 = dict(zip(result[0][:10], result[1][:10]))
time_end = time.time()
print( 'Time used for PageRank: %.3f s.' %(time_end - time_start) )
print('Node\t\tScore')
for k, v in result_dict_rank10.items():
	print('%s\t\t%.8f' % (k, v))

print()

# Test PPR.
time_start = time.time()
result = PPR('soc-Epinions1_processed.txt', 'soc-Epinions1_seed.txt', 0.85)
result_dict_rank10 = dict(zip(result[0][:10], result[1][:10]))
time_end = time.time()
print( 'Time used for PPR: %.3f s.' %(time_end - time_start) )
print('Node\t\tScore')
for k, v in result_dict_rank10.items():
	print('%s\t\t%.8f' % (k, v))