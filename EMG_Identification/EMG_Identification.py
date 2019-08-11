import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
from numpy import argmax
from sklearn.metrics import confusion_matrix

# Input data files are available in the "../input/" directory.
# For example, running this (by clicking run or pressing Shift+Enter) will list the files in the input directory

import os
print(os.listdir("../input"))
from tensorflow import keras
from keras.utils import to_categorical
from sklearn.metrics import accuracy_score
# Any results you write to the current directory are saved as output.
test1=pd.read_csv('../input/0.csv')
test1.columns=list(range(0,65))
test2=pd.read_csv('../input/1.csv')
test2.columns=list(range(0,65))
test3=pd.read_csv('../input/2.csv')
test3.columns=list(range(0,65))
test4=pd.read_csv('../input/3.csv')
test4.columns=list(range(0,65))
test1=test1.append([test2,test3,test4],ignore_index=True)
test1_label=test1.pop(64)
print(test1_label,test1.shape)
test1=(test1-test1.mean())/test1.std()
test_label2=to_categorical(test1_label)
from sklearn.model_selection import train_test_split
trainx,testx,trainy, testy = train_test_split(test1,test_label2, test_size=0.2,random_state=1)
valx,test2x,valy,test2y=train_test_split(testx,testy, test_size=0.2,random_state=1)
print(trainx.shape,test2x.shape,trainy.shape,test2y.shape)
model = keras.Sequential()    
model.add(keras.layers.Dense(64, activation='relu', input_shape=[testx.shape[1]]))
model.add(keras.layers.Dropout(rate=.5))
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(8, activation='relu'))
model.add(keras.layers.Dropout(rate=.5))
model.add(keras.layers.BatchNormalization())
model.add(keras.layers.Dense(4,activation='softmax'))
model.compile(loss='categorical_crossentropy',
            optimizer='RMSprop',
            metrics=['accuracy'])
model.summary()
EPOCHS=100
history = model.fit(
  trainx, trainy,batch_size=256,
  epochs=EPOCHS, validation_data = (test2x,test2y), verbose=1)
predictedemg=model.predict(valx)
accuracy_score(argmax(predictedemg,axis=1), argmax(valy,axis=1))
a=confusion_matrix(argmax(predictedemg,axis=1), argmax(valy,axis=1))
import matplotlib.pyplot as plt
import seaborn as sn
df_cm = pd.DataFrame(a, range(4),
                  range(4))

sn.set(font_scale=1.4)#for label size
sn.heatmap(df_cm, annot=True,annot_kws={"size": 16})
