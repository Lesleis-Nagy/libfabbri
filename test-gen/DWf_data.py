from sympy.vector import CoordSys3D
from sympy import *

init_printing()

def d(r1, r2):
    return sqrt((r1 - r2).dot(r1 - r2))

def we_fun(r1, r2):
    def we(r):
        return log( ( d(r1, r) + d(r2, r) + d(r2, r1) ) / ( d(r1, r) + d(r2, r) - d(r2, r1) ) )
    return we

def main():

    C = CoordSys3D("C")

    r1 =  1*C.i + 0*C.j - 1/sqrt(2)*C.k
    r2 = -1*C.i + 0*C.j - 1/sqrt(2)*C.k
    r3 =  0*C.i + 1*C.j + 1/sqrt(2)*C.k
    r  =  0*C.i - 1*C.j + 1/sqrt(2) *C.k

    nf = ((r2 - r1).cross(r3 - r1)).normalize()
    rf = (r1 + r2 + r3)/3
    omega = 2*pi - 6*asin(sqrt( Rational(2,3), evaluate=False), evaluate=False)

    we0 = we_fun(r1, r2)
    we1 = we_fun(r2, r3)
    we2 = we_fun(r3, r1)

    re0 = (r1 + r2) / 2;
    re1 = (r2 + r3) / 2;
    re2 = (r3 + r1) / 2;

    ue0 = (r2 - r1).normalize()
    ue1 = (r3 - r2).normalize()
    ue2 = (r1 - r3).normalize()

    expr = nf.cross(ue0)*we0(r) + nf*omega + \
           nf.cross(ue1)*we1(r) + nf*omega + \
           nf.cross(ue2)*we2(r) + nf*omega

    print(latex(expr))

    print(N(expr, 50))


if __name__ == "__main__":
    main()

