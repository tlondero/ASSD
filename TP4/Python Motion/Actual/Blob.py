class Blob:
     def __init__(self, x,y,threshold):
         self.x = x
         self.y = y
         self.w = 1
         self.h = 1
         self.threshold = threshold
         self.prevBlob = Blob(0,0,threshold)

     def expandB(self,B2):
         xaux=self.x
         yaux=self.y
         self.x=min(xaux,B2.x)
         self.y=min(yaux,B2.y)
         self.w= max(xaux,B2.x)-min(xaux,B2.x)
         self.h= max(yaux,B2.y)-min(yaux,B2.y)

     def same(self,B2):
         if(self.w<self.threshold or self.h<self.threshold):
            aux=(((self.x ) - B2.x) ** 2 + ((self.y) - B2.y) ** 2)
            if (aux<self.threshold) and aux>0:
                return True
            else:
                return False
         else:
             for i in range(int(self.w / self.threshold)):
                 for j in range(int(self.h / self.threshold)):
                     aux=((self.x+i*self.threshold)-B2.x)**2+((self.y+j*self.threshold)-B2.y)**2
                     if(aux < self.threshold and aux>0):
                         return True
                     else:
                         return False