#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#define MAX 100000000


int	calculate(int w, long z, int divZ, int addX, int addY){
	int x = z;
	int y = 25;

	x %= 26;
	z /= divZ;
	x += addX;
	x = x == w ? 1 : 0;
	x = x == 0 ? 1 : 0;
	y *= x;
	y++;
	if (y == 26 && addX < 0)
		return MAX + 1;
	z *= y;
	y *= 0;
	y += w;
	y += addY;
	y *= x;
	z += y;
	return z;
}

int main(){

	long z = 0;
	for(int i = 1; i <= 9; i++){
		long zi = calculate(i, z, 1, 14, 0);
		if(zi > MAX)
			continue;
		for(int j = 1; j <= 9; j++){
			long zj = calculate(j, zi, 1, 13, 12);
			if(zj > MAX)
				continue;
			for(int k = 1; k <= 9; k++){
				long zk = calculate(k, zj, 1, 15, 14);
				if(zk > MAX)
					continue;
				for(int l = 1; l <= 9; l++){
					long zl = calculate(l, zk, 1, 13, 0);
					if(zl > MAX)
						continue;
					for(int m = 1; m <= 9; m++){
						long zm = calculate(m, zl, 26, -2, 3);
						if(zm > MAX)
							continue;
						for(int n = 1; n <= 9; n++){
							long zn = calculate(n, zm, 1, 10, 15);
							if(zn > MAX)
								continue;
							for(int o = 1; o <= 9; o++){
								long zo = calculate(o, zn, 1, 13, 11);
								if(zo > MAX)
									continue;
								for(int p = 1; p <= 9; p++){
									long zp = calculate(p, zo, 26, -15, 12);
									if(zp > MAX)
										continue;
									for(int q = 1; q <= 9; q++){
										long zq = calculate(q, zp, 1, 11, 1);
										if(zq > MAX)
											continue;
										for(int r = 1; r <= 9; r++){
											long zr = calculate(r, zq, 26, -9, 12);
											if(zr > MAX)
												continue;
											for(int s = 1; s <= 9; s++){
												long zs = calculate(s, zr, 26, -9, 3);
												if(zs > MAX)
													continue;
												for(int t = 1; t <= 9; t++){
													long zt = calculate(t, zs, 26, -7, 10);
													if(zt > MAX)
														continue;
													for(int u = 1; u <= 9; u++){
														long zu = calculate(u, zt, 26, -4, 14);
														if(zu > MAX)
															continue;
														for(int v = 1; v <= 9; v++){
															long zv = calculate(v, zu, 26, -6, 12);
															if(zv == 0){
																std::cout << "answer: " << i << j << k << l << m << n << o << p << q << r << s << t << u << v << std::endl;
																return 0;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}