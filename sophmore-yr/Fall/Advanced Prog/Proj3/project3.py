# Import relevant libraries
import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns
import numpy as np


class Project3:
    def __init__(self) -> None:
        '''
        returns: none, just initializes Project3 Class
        '''
        # The following lines adjust the granularity of reporting.
        pd.options.display.max_rows = 10
        pd.options.display.float_format = "{:.1f}".format
        #import training dataset
        self.training_df = pd.read_csv(filepath_or_buffer="train.csv")
        self.xtrain = self.training_df.loc[:, 'LotFrontage':'MoSold'].to_numpy()[1:]
        #import testing dataset
        self.test_df = pd.read_csv(filepath_or_buffer='test.csv')
        self.xtest = self.test_df.loc[:, 'LotFrontage':'MoSold'].to_numpy()[1:]
        #create random weights
        self.weight = np.random.uniform(-1,1,self.xtrain.shape[1])


    def stats(self) -> None:       
        '''
        returns: none, just prints out the statistical findings of training_df prices
        '''
        #calculate min, max, mean, and stdev of price
        minPrice = self.training_df['Price'].min()
        maxPrice = self.training_df['Price'].max()
        meanPrice = self.training_df['Price'].mean()
        stdevPrice = self.training_df['Price'].std()
        houseNum = self.training_df.shape[0]-1
        #print out findings
        print(f"Minimum value for price: {minPrice}")
        print(f"Mean value for price: {meanPrice}")
        print(f"Maximum value for price: {maxPrice}")
        print(f"Standard deviation for price: {stdevPrice}")
        print(f"Number of houses: {houseNum}")

    def histogram(self) -> None:
        '''
        returns: none, just creates a histogram of trainings_set price
        '''
        #plot a histogram of price
        data = self.training_df['Price']
        plt.hist(data, bins=20, color='blue', edgecolor='black')
        plt.xlabel('Price')
        plt.ylabel('Number of Houses')
        plt.title('Histogram of House Price')
        plt.show()

    def pairplot(self) -> None:
        '''
        returns: none, just creates pairplot of 4 predetermined rows in training set
        '''
        #plot a pair wise plot of GrLivArea, BedroomAbvGr, TotalBsmtSF, FullBath
        rows = ['GrLivArea','BedroomAbvGr','TotalBsmtSF','FullBath']
        sns.pairplot(self.training_df[rows], diag_kws={'bins':20},kind='reg')
        plt.show()


    def calcPred(self, x: np.ndarray) -> None:
        '''
        input x: is the data that will have the price predicted
        returns: nothing, just sets self.pred (predicted values)
        '''
        #predicts value based on weights
        self.pred = np.empty([])
        for i in range(x.shape[0]-1):
            wx = self.w * x[i,:]
            self.pred = np.append(self.pred, np.sum(wx))

    def calcLoss(self, df: pd.DataFrame) -> None:
        '''
        input df: the dataset of prices to calculate the loss against
        returns: nothing, just modifies the self.loss
        '''
        #MSE
        diff = (self.pred - df['Price'].to_numpy()[1:]) ** 2
        self.loss = np.sum(diff)/diff.size

    def calcGradient(self) -> np.ndarray:
        '''
        returns: self.gradient (the gradient that will be used to update weights)
        '''
        #calculates the gradient of loss function based on the predicted price and the correct price
        self.gradient = (2/self.pred.size) * np.dot(self.xtrain.T, (self.pred - self.training_df['Price'].to_numpy()[1:]))
        return self.gradient

    def update(self, a: float) -> None:
        '''
        input a: the learning rate scalar to apply to the gradient
        returns: nothing, just updates weights
        '''
        #updates weights based on the gradient value
        self.w = self.w - a * self.gradient
        
    def train(self, iterations: int, a: float) -> list:
        '''
        input iterations: specifies the number of times the training algorithm will run
        input a: specifies the learning rate scalar
        returns: self.learning curve, to make plotting easier in other functions
        '''
        #reset learning Curve
        self.learningCurve = []
        #bring weights back to initialized random weights
        self.w = self.weight.copy()
        print(self.weight) # for some reason these print statements need to be here, 
        print(self.w)      # otherwise the training does not work
        #apply algorithm 1 that is given
        for i in range(iterations):
            self.calcPred(self.xtrain)
            self.calcLoss(self.training_df)
            self.calcGradient()
            self.update(a)
            self.learningCurve.append(self.loss)
        #return the learning curve for ease of graphing
        return self.learningCurve

    def graphLearning(self, alphas: list[float] = [], iterations: int = 0) -> None:
        '''
        input alphas: a list of all of the learning rate scalars to be graphed
        input iterations: the number of times the algorithm will run
        returns: nothing, just runs the algorithm and graphs the outputs of that
        '''
        #for each alpha value, add to plot
        for alpha in alphas:
            iteration_numbers = range(1, iterations + 1)
            learning_curve = self.train(iterations, alpha)
            plt.plot(iteration_numbers, learning_curve, linestyle='-', label=f'a = {alpha}')
        plt.ylabel('Mean Squared Error')
        plt.xlabel('Iterations')
        plt.title(f'Learning Curve with alphas = {alphas} and {iterations} Iterations')
        plt.legend(loc='best')
        plt.show()
        
    def testModel(self) -> None:
        '''
        returns: nothing, just calculates the MSE of the found weights vs test set of data
        '''
        #test model weights vs test set
        self.calcPred(self.xtest)
        self.calcLoss(self.test_df)
        print('test MSE: ',self.loss)
        
def main():
    
    #create alpha values to be used
    alpha = .2
    alpha1 = 10**-12
    alpha2 = 10**-11
    iterations = 500

    #initialize class
    test = Project3()

    #run test functions
#    test.stats()
#    test.histogram()
#    test.pairplot()

    #graph with alpha = .2 and 10 iterations
#    test.graphLearning([alpha], 10)

    #graph with alpha values 1 and 2, with iterations 
    test.graphLearning([alpha1, alpha2], iterations)

    #print final loss of alpha2
    print('final MSE against training set: ',test.loss)

    #test the trained model against the test set
    test.testModel()

if __name__ =='__main__':
    main()
