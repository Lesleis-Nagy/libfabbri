import mpmath as mp
mp.dps=50



def we_data_set_1():

    v_1 = mp.mpf(1)
    v_neg_1 = mp.mpf(-1)

    v_0 = mp.mpf(0)

    v_1_over_sqrt2 = v_1 / mp.sqrt(2.0)
    v_neg_1_over_sqrt2 = v_neg_1 / mp.sqrt(2.0)

    eps_squared = mp.power(mp.mpf(1E-20), 2);

    r1x = v_1
    r1y = v_0
    r1z = v_neg_1_over_sqrt2

    r2x = v_neg_1
    r2y = v_0
    r2z = v_neg_1_over_sqrt2

    rx = v_0
    ry = v_1
    rz = v_1_over_sqrt2


    print(f"r1: <{r1x}, {r1y}, {r1z}>")
    print(f"r2: <{r2x}, {r2y}, {r2z}>")
    print(f" r: <{rx}, {ry}, {rz}>")

    norm_r2_minus_r =  mp.sqrt( mp.power(r2x - rx,  2) + mp.power(r2y - ry,  2) + mp.power(r2z - rz,  2) + eps_squared)
    print(f"norm(r2-r):")
    mp.nprint(norm_r2_minus_r, n=100)

    norm_r1_minus_r =  mp.sqrt( mp.power(r1x - rx,  2) + mp.power(r1y - ry,  2) + mp.power(r1z - rz,  2) + eps_squared)
    print(f"norm(r1-r):")
    mp.nprint(norm_r1_minus_r, n=100)

    norm_r2_minus_r1 = mp.sqrt( mp.power(r2x - r1x, 2.0) + mp.power(r2y - r1y, 2.0) + mp.power(r2z - r1z, 2.0) + eps_squared)
    print(f"norm(r2-r1): ")
    mp.nprint(norm_r2_minus_r1, n=100)

    result = ( norm_r2_minus_r + norm_r1_minus_r + norm_r2_minus_r1 ) / ( norm_r2_minus_r + norm_r1_minus_r - norm_r2_minus_r1 )
    mp.nprint(result, n=100)
    result = mp.log(result)

    mp.nprint(result, n=100)
    mp.nprint(mp.log(3.0), n=100)


if __name__ == "__main__":
    we_data_set_1()
