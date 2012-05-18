for (int k = 0; k < 11; ++k) 
    for (int i = 0; i < 11; ++i) 
        for (int j = 0; j < 11; ++j) 
            M[i][j] = min(M[i][j], M[i][k] + M[k][j]);