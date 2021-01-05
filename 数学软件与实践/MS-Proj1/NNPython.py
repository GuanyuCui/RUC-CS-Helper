import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from scipy.interpolate import make_interp_spline, BSpline

def sigmoid(x):
	# Sigmoid activation function: f(x) = 1 / (1 + e^(-x))
	return 1 / (1 + np.exp(-x))

def deriv_sigmoid(x):
	# Derivative of sigmoid: f'(x) = f(x) * (1 - f(x))
	fx = sigmoid(x)
	return fx * (1 - fx)

def mse_loss(y_true, y_pred):
	# y_true and y_pred are numpy arrays of the same length.
	return ((y_true - y_pred) ** 2).mean()

class OurNeuralNetwork:
	'''
	A neural network with:
		- 2 inputs
		- a hidden layer with 2 neurons (h1, h2)
		- an output layer with 1 neuron (o1)

	*** DISCLAIMER ***:
	The code below is intended to be simple and educational, NOT optimal.
	Real neural net code looks nothing like this. DO NOT use this code.
	Instead, read/run it to understand how this specific network works.
	'''
	def __init__(self):
		# Weights
		self.w1 = np.random.normal()
		self.w2 = np.random.normal()
		self.w3 = np.random.normal()
		self.w4 = np.random.normal()
		self.w5 = np.random.normal()
		self.w6 = np.random.normal()

		# Biases
		self.b1 = np.random.normal()
		self.b2 = np.random.normal()
		self.b3 = np.random.normal()

	def feedforward(self, x):
		# x is a numpy array with 2 elements.
		h1 = sigmoid(self.w1 * x[0] + self.w2 * x[1] + self.b1)
		h2 = sigmoid(self.w3 * x[0] + self.w4 * x[1] + self.b2)
		o1 = sigmoid(self.w5 * h1 + self.w6 * h2 + self.b3)
		return o1

	def train(self, data, all_y_trues, epochs = 1000, learn_rate = 1, epoch_gap = 10):
		'''
		- data is a (n x 2) numpy array, n = # of samples in the dataset.
		- all_y_trues is a numpy array with n elements.
			Elements in all_y_trues correspond to those in data.
		'''
		
		# Split dataset into train and test
		X_train, X_test, y_train, y_test = train_test_split(data, all_y_trues, test_size = 0.50)
		
		'''
		X_train = data[0::2]
		X_test = data[1::2]
		y_train = all_y_trues[0::2]
		y_test = all_y_trues[1::2]
		'''
		
		# Arrays used to plot later
		epoch_arr = []
		loss_arr = []
		corr_arr = []
		
		for epoch in range(epochs):
			for x, y_true in zip(X_train, y_train):
				# --- Do a feedforward (we'll need these values later)
				sum_h1 = self.w1 * x[0] + self.w2 * x[1] + self.b1
				h1 = sigmoid(sum_h1)

				sum_h2 = self.w3 * x[0] + self.w4 * x[1] + self.b2
				h2 = sigmoid(sum_h2)

				sum_o1 = self.w5 * h1 + self.w6 * h2 + self.b3
				o1 = sigmoid(sum_o1)
				y_pred = o1

				# --- Calculate partial derivatives.
				# --- Naming: d_L_d_w1 represents "partial L / partial w1"
				d_L_d_ypred = -2 * (y_true - y_pred)

				# Neuron o1
				d_ypred_d_w5 = h1 * deriv_sigmoid(sum_o1)
				d_ypred_d_w6 = h2 * deriv_sigmoid(sum_o1)
				d_ypred_d_b3 = deriv_sigmoid(sum_o1)

				d_ypred_d_h1 = self.w5 * deriv_sigmoid(sum_o1)
				d_ypred_d_h2 = self.w6 * deriv_sigmoid(sum_o1)

				# Neuron h1
				d_h1_d_w1 = x[0] * deriv_sigmoid(sum_h1)
				d_h1_d_w2 = x[1] * deriv_sigmoid(sum_h1)
				d_h1_d_b1 = deriv_sigmoid(sum_h1)

				# Neuron h2
				d_h2_d_w3 = x[0] * deriv_sigmoid(sum_h2)
				d_h2_d_w4 = x[1] * deriv_sigmoid(sum_h2)
				d_h2_d_b2 = deriv_sigmoid(sum_h2)

				# --- Update weights and biases
				# Neuron h1
				self.w1 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_w1
				self.w2 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_w2
				self.b1 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_b1

				# Neuron h2
				self.w3 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_w3
				self.w4 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_w4
				self.b2 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_b2

				# Neuron o1
				self.w5 -= learn_rate * d_L_d_ypred * d_ypred_d_w5
				self.w6 -= learn_rate * d_L_d_ypred * d_ypred_d_w6
				self.b3 -= learn_rate * d_L_d_ypred * d_ypred_d_b3

			# --- Calculate total loss at the end of each epoch
			if epoch % epoch_gap == 0:
				# Loss on train dataset
				y_train_preds = np.apply_along_axis(self.feedforward, 1, X_train)
				loss = mse_loss(y_train, y_train_preds)
				# Correctness on the test dataset
				corr_test = correctness(y_test, self.predict(X_test))	
				print("Epoch %d, Train Loss: %.5f, Test Correctness: %.5f" % (epoch, loss, corr_test))
				
				epoch_arr.append(epoch)
				loss_arr.append(loss)
				corr_arr.append(corr_test)
		
		# Plot
		epoch_arr = np.array(epoch_arr)
		loss_arr = np.array(loss_arr)
		corr_arr = np.array(corr_arr)
		
		plt.figure(figsize = (8, 6))
		plt.plot(epoch_arr, loss_arr)
		plt.xlabel('Epoch', size = 14)
		plt.ylabel('Loss', size = 14)
		plt.xticks(size = 12)
		plt.yticks(size = 12)
		plt.savefig("NNPython1.png", dpi = 300)
		plt.show()
		
		plt.figure(figsize = (8, 6))
		plt.plot(epoch_arr, corr_arr)
		plt.xlabel('Epoch', size = 14)
		plt.ylabel('Correctness', size = 14)
		plt.xticks(size = 12)
		plt.yticks(size = 12)
		plt.savefig("NNPython2.png", dpi = 300)
		plt.show()
				
	def predict(self, X_test):
		y_test_preds = np.where(np.apply_along_axis(self.feedforward, 1, X_test) > 0.5, 1, 0)
		return y_test_preds
		
def normalize(x):
	# Return a normalized vector of x
	return (x - x.mean()) / x.std()
	
def correctness(y_test, y_test_preds):
	# Return the correctness between y_test and y_test_preds
	return np.mean(y_test == y_test_preds)
	
df = pd.read_excel('data.xlsx')
data = np.zeros((df.shape[0], 2))

# Normalize vectors
data[:, 0] = normalize(df['身高/cm'].values)
data[:, 1] = normalize(df['体重/kg'].values)

df['性别'].replace('男', '0', inplace = True)
df['性别'].replace('女', '1', inplace = True)
all_y_trues = np.array(df['性别'].astype(int))


# Train our neural network!
network = OurNeuralNetwork()
network.train(data, all_y_trues, epochs = 5000, learn_rate = 0.005, epoch_gap = 1)