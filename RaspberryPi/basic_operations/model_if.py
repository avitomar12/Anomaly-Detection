from sklearn.ensemble import IsolationForest
import pandas as pd

df=pd.read_csv('ideal_reading.txt',sep=',')
X=df.drop(['time'],axis=1)
X_train,X_test=X[:100],X[100:]


clf=IsolationForest(max_samples=10,contamination=0.001)
clf.fit(X_train)
y_pred_train=clf.predict(X_train)
y_pred_test=clf.predict(X_test)


