# Preprocess data.

# Prepare graph
def prepare_graph():
	f_ori = open('soc-Epinions1.txt', 'r')
	contents = f_ori.readlines()
	f_ori.close()
	
	contents = contents[4:]
	contents = [line.replace('\t', ',') for line in contents]
	f_pre = open('soc-Epinions1_processed.txt', 'w')

	for line in contents:
		f_pre.write(line)
	f_pre.close()

# Generate seed.
def generate_seed():
	f_seed = open('soc-Epinions1_seed.txt', 'w')
	for i in range(50):
		f_seed.write(str(i) + ',0.02\n')
	f_seed.close()
	
prepare_graph()
generate_seed()