def space_translate(x, y, prev):
    for i in range(prev.shape[0]):
            prev[i][0][0] = prev[i][0][0] + x
            prev[i][0][1] = prev[i][0][1] + y
    return prev


