int largest_empty_rectangle()
{
    int area = 0;   // 最大矩形面積，初始化為最小值
    
    for (int i=1; i<=N; ++i)   // 以每一個橫條當做長方形底部
    {
        // 往左可延伸的長度
        for (int j=1; j<=M; ++j)
            if (mp[i][j])
                tl[j] = tl[j-1] + 1;
            else
                tl[j] = 0;
 
        // 往右可延伸的長度
        for (int j=M; j>=1; --j)
            if (mp[i][j])
                tr[j] = tr[j+1] + 1;
            else
                tr[j] = 0;
 
        // 計算長方形往上可延伸的距離
        for (int j=1; j<=M; ++j)
            if (mp[i][j])
                h[j] = h[j] + 1;
            else
                h[j] = 0;
 
        // 計算長方形往上延伸到底後，往左可延伸的距離
        for (int j=1; j<=M; ++j)
            if (l[j] == 0)
                l[j] = tl[j];
            else
                l[j] = min(tl[j], l[j]);
 
        // 計算長方形往上延伸到底後，往右可延伸的距離
        for (int j=1; j<=M; ++j)
            if (r[j] == 0)
                r[j] = tr[j];
            else
                r[j] = min(tr[j], r[j]);
 
        // 計算 Largest Empty Rectangle 並紀錄之
        for (int j=1; j<=M; ++j)
            area = max(area, (l[j] + r[j] - 1) * h[j]);
    }
    
    return area;
}