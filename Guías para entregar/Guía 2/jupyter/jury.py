import numpy as np


class JuryTest:
    def __init__(self, den):# a0,a1,a2,...,an
        self.D = den
        self.__M=0
        self.stable=True

    def hipotesis(self):
        aux1=0
        aux2=0
        for i in range(len(self.D)-1):
            aux1+=self.D[i]
        mu = (-1) **(len(self.D)-1)
        for i in range(len(self.D) ):
            aux2 += self.D[i] * (-1)**i
        if(aux1>0) and (aux2>0) and (self.D[0] < self.D[len(self.D)-1]):
            return True
        else:
            return False



    def juryMatrix(self):
        N =len(self.D)
        self.M = np.zeros([2*(N-1)-3,N])
        aux=np.zeros([N-2,N])
        for i in range(N):
            aux[0,i]=self.D[i]
        for i  in range(1,N-2):
            for j in range(N-1):
                aux[i,j]= aux[i-1,0]*aux[i-1,j]-aux[i-1,N-i]*aux[i-1,N-i-j]
                if(np.abs(aux[i-1,0]) < np.abs(aux[i-1,N-i]) and i>1):
                    self.stable=False
        for i in range (N-3):
            self.M[2*i,:]=aux[i]
            self.M[2*i+1,:]= aux[i,::-1]
        self.M[2*(N-1)-4,:]=aux[N-3]
        return self.M

    def stability(self):
        return self.stable




tst = JuryTest([1,1,2,3,4,5,6])
Y=tst.juryMatrix()
print("Hipotesis: ", tst.hipotesis())
print("Matrix: ",Y)
print("Stability ",tst.stable)