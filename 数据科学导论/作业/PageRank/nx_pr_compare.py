import networkx as nx

def nx_PR_benchmark(input_file_name , damping_factor):
	G = nx.DiGraph()
	edges = []
	# Open and read file.
	with open(input_file_name, 'r') as f:
		contents = f.readlines()
	# Create adjency list of a graph.
	for line in contents:
		# if line.strip() == '':
			#continue
		left, right = line.split(',')
		right = right.strip()
		# Append inEdge
		edges.append((left, right))
	f.close()
	G.add_edges_from(edges)
	
	sorted_result = sorted(\
		nx.pagerank(G, alpha = damping_factor).items(), \
		key = lambda x: (x[1], x[0]), reverse = True)
	
	# Generate list and score.
	# Comment 'scores' in homework code.
	node_list_in_descending_order = [term[0] for term in sorted_result]
	scores = [term[1] for term in sorted_result]
	return node_list_in_descending_order , scores

def nx_PPR_benchmark(input_Graph, input_Seed, damping_factor):
	G = nx.DiGraph()
	nodes = {}
	edges = []
	# Open and read file.
	with open(input_Graph, 'r') as f:
		contents = f.readlines()
	# Create adjency list of a graph.
	for line in contents:
		# if line.strip() == '':
			#continue
		left, right = line.split(',')
		right = right.strip()
		# Append inEdge
		edges.append((left, right))
		# Add node name.
		nodes[left] = 0
		nodes[right] = 0
	f.close()
	G.add_edges_from(edges)
	
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
	
	nstart = nodes
	for node in seed:
		nstart[node] = seed[node]
	
	dangling = dict.fromkeys(nodes, 1 / len(nodes))
	sorted_result = sorted(\
		nx.pagerank(G, alpha = damping_factor, \
			personalization = seed, nstart = nstart, \
			dangling = dangling).items(), \
			key = lambda x: (x[1], x[0]), reverse = True)
	
	# Generate list and score.
	# Comment 'scores' in homework code.
	node_list_in_descending_order = [term[0] for term in sorted_result]
	scores = [term[1] for term in sorted_result]
	return node_list_in_descending_order , scores
	
	return None


# Test nx PR.
import time
time_start = time.time()
result = nx_PR_benchmark('soc-Epinions1_processed.txt', 0.85)
result_dict_rank10 = dict(zip(result[0][:10], result[1][:10]))
time_end = time.time()
print( 'Time used for nx PageRank: %.3f s.' %(time_end - time_start) )
print('Node\t\tScore')
for k, v in result_dict_rank10.items():
	print('%s\t\t%.8f' % (k, v))

print()

# Test nx PPR.
time_start = time.time()
result = nx_PPR_benchmark('soc-Epinions1_processed.txt', 'soc-Epinions1_seed.txt', 0.85)
result_dict_rank10 = dict(zip(result[0][:10], result[1][:10]))
time_end = time.time()
print( 'Time used for nx PPR: %.3f s.' %(time_end - time_start) )
print('Node\t\tScore')
for k, v in result_dict_rank10.items():
	print('%s\t\t%.8f' % (k, v))