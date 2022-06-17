
### 0-1背包

物品属性：价值value，体积weight

背包属性：背包容量V

**每件物品只能用一次**

```c++
// dp[i][j]:从下标为[0-i]的物品里任意选取，放进容量为j的背包里，价值总和最大是dp[i][j];
递推公式：
    dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]);   
```

```c
// 初始化
for(int j = weight[0]; j <= bagWeight; j++)
    dp[0][j] = value[0];
// 遍历顺序
for(int i=1; i < weight.size(); i++){	//遍历物品
    for(int j=0; j <= bagWeight; j++){	//遍历背包容量
        if(j < weight[i])	//放不进去
            dp[i][j] = dp[i-1][j];
        else
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]);
    }
}
```

**一维滚动数组（状态压缩）**

```
dp[j]:容量为j的背包，所背的物品价值最大是dp[j];
递推公式：
	dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
```

```c++
// 遍历顺序
for(int i=0; i<weight.size(); i++){
    for(int j=bagWeight; j>=weight[i]; j--){
        dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
    }
}
```

**遍历背包容量是倒序遍历是为了保证物品只被放入一次**

​    

### 完全背包

**每件物品都有无限个**

```c
for(int i=0; i<weight.size(); i++){
    for(int j = weight[i]; j<=bagWeight; j++){
        dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
    }
}
```

